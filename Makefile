PARTS = mdsshr \
	treeshr \
	tdishr \
	tditest \
	xmdsshr \
        mdstcpip \
	dwscope \
	mitdevices \
	mdslibidl \
	remcam \
	cdu	\
	mdsdcl	\
	ccl	\
	tcl \
	traverser \
	actions \
	mdslib \
	d3dshr

all :
	- cdir=`pwd`; \
        for dir in $(PARTS) ; do\
          echo Making $${dir};\
	  if (test -d $${dir}) then \
	    cd $${dir};\
            if (test -f Makefile.`uname`) then \
              make='make -f Makefile.'`uname`;\
            else\
              make=make;\
            fi;\
            if (test -f $(DEPEND)) then \
	      $$make;\
            else\
              $$make DEPEND=/dev/null $(DEPEND);\
              $$make;\
            fi;\
	    cd $$cdir;\
          fi;\
	done

clean :
	cdir=`pwd`; \
	for dir in $(PARTS) ; do\
	  if (test -d $${dir}) then \
	    cd $${dir};\
	    make DEPEND=/dev/null clean;\
	    cd $$cdir;\
          fi;\
	done

BINARIES = bin shlib uid tdi idl trees envsyms setup.csh setup.sh sys_specific/envsyms.`uname`
binaries :
	tar cvf - $(BINARIES) | compress -c - > ../binaries/MDSplus.`uname`.tar.Z


