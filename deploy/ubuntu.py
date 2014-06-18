import subprocess,os,sys,pexpect,xml.etree.ElementTree as ET,fnmatch,tempfile
from deploy import getPackageFiles

class InstallationPackage(object):
    """Provides exists,build,test and deploy methods"""
    def __init__(self,info):
        self.info=info
        self.info['workspace']=os.environ['WORKSPACE']

    def exists(self):
        """Check to see if rpms for this release already exist."""
        tree=ET.parse('packaging.xml')
        root=tree.getroot()
        for package in root.getiterator('package'):
            pkg=package.attrib['name']
            if pkg == "MDSplus":
                pkg = ""
            else:
                pkg = "-%s" % pkg
            self.info['package']=pkg
            self.info['arch']={"noarch-x86_64":"noarch","noarch-i686":"noarch","bin-x86_64":"amd64","bin-i686":"i386"}["%s-%s" % (package.attrib['arch'],os.uname()[-1])]
            rpm='/repository/%(dist)s/%(flavor)s/DEBS/%(arch)s/mdsplus%(rflavor)s%(package)s-%(major)d.%(minor)d.%(release)d_%(arch)s.deb' % self.info
            try:
                os.stat(rpm)
            except:
                print("%s not found" % rpm)
                sys.stdout.flush()
                return False
        print("Latest %(flavor) release %(major)d.%(minor)d.%(release)d is already available. Nothing to do for this release." % self.info)
        sys.stdout.flush()
        return True

    def buildInstall(self):
        """Build MDSplus from the sources and install into a BUILDROOT directory"""
        self.info['mdsplus_version']="%(major)d.%(minor)d_%(release)d" % self.info
        if self.info['flavor']!='stable':
            self.info['mdsplus_version']="%(flavor)s-%(mdsplus_version)s" % self.info
        tree=ET.parse('packaging.xml')
        root=tree.getroot()
        install_script=root.find('ubuntu').find('install_script').text
        install_script=install_script[install_script.find('#'):]
        fd,filename=tempfile.mkstemp()
        os.write(fd,install_script % self.info)
        os.close(fd)
        os.chmod(filename,0700)
        status = subprocess.Popen(filename,shell=True).wait()
        os.remove(filename)
        if status != 0:
            raise Exception("Problem building MDSplus from sources")

    def fixFilename(self,fname):
        return fname

    def buildDebs(self):
        tree=ET.parse('packaging.xml')
        bin_arch={'x86_64':'amd64','i686':'i386'}[os.uname()[-1]]
        root=tree.getroot()
        for package in root.getiterator('package'):
            pkg = package.attrib['name']
            if pkg=='MDSplus':
                self.info['packagename']=""
            else:
                self.info['packagename']="-%s" % pkg
            self.info['arch']={'bin':bin_arch,'noarch':'noarch'}[package.attrib['arch']]
            self.info['description']=package.attrib['description']
            self.info['tmpdir']=tempfile.mkdtemp()
            try:
                os.mkdir("%(tmpdir)s/DEBIAN" % self.info)
                includes=list()
                for inc in package.getiterator('include'):
                    for inctype in inc.attrib:
                        include=self.fixFilename(inc.attrib[inctype])
                        if inctype != "dironly":
                            includes.append(include)
                excludes=list()
                for exc in package.getiterator('exclude'):
                    for exctype in exc.attrib:
                        excludes.append(self.fixFilename(exc.attrib[exctype]))
                if package.find("exclude_staticlibs") is not None:
                    excludes.append("/usr/local/mdsplus/lib/*.a")
                if package.find("include_staticlibs") is not None:
                    includes.append("/usr/local/mdsplus/lib/*.a")
                files=getPackageFiles("%(workspace)s/%(flavor)s/BUILDROOT" % self.info,includes,excludes)
                for f in files:
                    self.info['file']=f[len("%(workspace)s/%(flavor)s/BUILDROOT/" % self.info)-1:].replace(' ','\\ ').replace('$','\\$')\
                        .replace('(','\\(').replace(')','\\)')
                    if subprocess.Popen("""
set -e
dn=$(dirname %(file)s)
mkdir -p %(tmpdir)s/DEBIAN
mkdir -p "%(tmpdir)s/${dn}"
cp %(workspace)s/%(flavor)s/BUILDROOT%(file)s "%(tmpdir)s/${dn}/"
""" % self.info,shell=True).wait() != 0:
                        raise Exception("Error building deb")
                depends=list()
                for require in package.getiterator("requires"):
                    depends.append("mdsplus%s-%s" % (self.info['rflavor'],require.attrib['package']))
                self.info['depends']=','.join(depends)
                self.info['name']=self.info['packagename'].replace('_','-')
                f=open("%(tmpdir)s/DEBIAN/control" % self.info,"w")
                f.write("""Package: mdsplus%(rflavor)s%(name)s
Version: %(major)d.%(minor)d.%(release)d
Section: admin
Priority: optional
Architecture: %(arch)s
Depends: %(depends)s
Maintainer: Tom Fredian <twf@www.mdsplus.org>
Description: %(description)s
""" % self.info)
                f.close()
                for s in ("preinst","postinst","prerm","postrm"):
                    script=package.find(s)
                    if script is not None and ("type" not in script.attrib or script.attrib["type"]!="rpm"):
                        self.info['script']=s
                        f=open("%(tmpdir)s/DEBIAN/%(script)s" % self.info,"w")
                        f.write("%s" % (script.text.replace("__INSTALL_PREFIX__","/usr/local/mdsplus")))
                        f.close()
                        os.chmod("%(tmpdir)s/DEBIAN/%(script)s" % self.info,0775)
                self.info['debfile']="%(workspace)s/%(flavor)s/DEBS/%(arch)s/mdsplus%(rflavor)s%(packagename)s_%(major)d.%(minor)d.%(release)d_%(arch)s.deb" % self.info
                if subprocess.Popen("""
set -e
mkdir -p %(workspace)s/%(flavor)s/DEBS/%(arch)s
dpkg-deb --build %(tmpdir)s %(debfile)s
reprepro -V -b %(workspace)s/%(flavor)s/REPO -C %(flavor)s includedeb MDSplus %(debfile)s
""" % self.info,shell=True).wait() != 0:
                    raise Exception("Problem building package or repository")
                subprocess.Popen("rm -Rf %(tmpdir)s" % self.info,shell=True).wait()
            except:
                subprocess.Popen("rm -Rf %(tmpdir)s" % self.info,shell=True).wait()
                raise

    def build(self):
        """Build rpms from sources"""
        self.buildInstall()
        self.buildDebs()

    def test(self):
        errors=list()
        self.info['apt-get']="apt-get -o Dir::State=%(workspace)s/%(flavor)s/apt/var/lib/apt/ -o Dir::Etc=%(workspace)s/%(flavor)s/apt/etc/apt" % self.info
        print("Preparing test repository")
        sys.stdout.flush()
        if subprocess.Popen("""
sudo %(apt-get)s autoremove -y 'mdsplus*'
set -e
rm -Rf apt
mkdir -p ./{apt/etc,apt/var/lib/apt}
rsync -a /etc/apt apt/etc/
apt-key add rpm/mdsplus.gpg.key
echo "deb file://$(pwd)/REPO/ MDSplus %(flavor)s" > apt/etc/apt/sources.list.d/mdsplus.list
""" % self.info,shell=True,cwd="%(workspace)s/%(flavor)s" % self.info).wait() != 0:
            raise Exception("Failed to create test apt confiration files")
        if subprocess.Popen("sudo %(apt-get)s autoremove -y 'mdsplus*'" % self.info,shell=True).wait() != 0:
            errors.append("Error removing MDSplus installs")
        if len(errors) == 0:
            print("Testing package installation")
            sys.stdout.flush()
            tree=ET.parse('packaging.xml')
            root=tree.getroot()
            for package in root.getiterator('package'):
                pkg=package.attrib['name']
                if pkg != 'repo':
                    if pkg=='MDSplus':
                        pkg=""
                    else:
                        pkg="-"+pkg
                    self.info['package']=pkg
                    if subprocess.Popen("sudo %(apt-get)s install -y mdsplus%(rflavor)s%(package)s && sudo %(apt-get)s autoremove -y 'mdsplus*'" % self.info,shell=True).wait() != 0:
                        errors.append("Error installing package mdsplus%(rflavor)s%(package)s" % self.info)
        if len(errors) == 0:
            if subprocess.Popen("""
set -e
sudo %(apt-get)s install -y mdsplus%(rflavor)s-mitdevices
. /etc/profile.d/mdsplus.sh
python <<EOF
import sys,os
import MDSplus
sys.path.append(os.path.dirname(MDSplus.__file__))
from tests import test_all
from unittest import TextTestRunner
result=TextTestRunner().run(test_all())
if not result.wasSuccessful():
  sys.exit(1)
EOF""" % self.info,shell=True).wait() != 0:
                errors.append("Error running regression tests")
        subprocess.Popen("sudo %(apt-get)s autoremove -y 'mdsplus*'" % self.info,shell=True).wait()
        if len(errors) > 0:
            errors.insert(0,"Testing failed")
            raise Exception('\n'.join(errors))

    def deploy(self):
        """Deploy release to repository"""
        print("Deploying new release %(major)d.%(minor)d-%(release)d" % self.info)
        self.info['repo']="/repository/%(DIST)s/repo" % self.info
        if subprocess.Popen("""
set -e
mkdir -p %(repo)s/{conf,pool,dists,db}
cp %(workspace)s/%(flavor)s/REPO/conf/distribution conf/
""" % self.info,shell=True,cwd="%(repo)s" % self.info).wait() !=0:
            raise Exception("Error preparing repository")
        if subprocess.Popen('find %( -name "*.deb" -exec reprepro -V --waitforlock 20 -b %(repo)s -C %(flavor)s includedeb MDSplus {} \;' \
                             % self.info,shell=True,cwd="%(workspace)s/%(flavor)s/DEBS" % self.info).wait() != 0:
            raise Exception("Error putting deb's in repository")
        status=subprocess.Popen('rsync -av %(workspace)s/%(flavor)s/DEBS /repository/%(DIST)s/%(flavor)s/' % self.info,shell=True).wait()
        if status != 0:
            raise Exception("Error copying files to destination")
        print("Completed deployment")
        sys.stdout.flush()
