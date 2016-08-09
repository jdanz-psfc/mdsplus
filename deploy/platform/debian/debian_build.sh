#!/bin/bash
#
# platform/debian/build.sh
#
# Invoked by mdsplus/deploy/build.sh for debian platforms.
#
# Run docker image to build mdsplus
#
set -e
volume() {
    if [ ! -z "$1" ]
    then
	echo "-v $(realpath ${1}):${2}"
    fi
}

RED() {
    if [ "$1" = "yes" ]
    then
	echo -e "\033[31;47m"
    fi
}
GREEN() {
    if [ "$1" = "yes" ]
    then
	echo -e "\033[32;47m"
    fi
}
NORMAL() {
    if [ "$1" = "yes" ]
    then
	echo -e "\033[m"
    fi
}

if [ "${RELEASE}" = "yes" ]
then
    mkdir -p ${RELEASEDIR}/${BRANCH}
    rm -Rf ${RELEASEDIR}/${BRANCH}/DEBS
    rm -Rf ${RELEASEDIR}/repo
    releasedir=${RELEASEDIR}
fi

if [ "${PUBLISH}" = "yes" ]
then
    mkdir -p ${PUBLISHDIR}
    publishdir=${PUBLISHDIR}
    releasedir=${RELEASEDIR}
fi
set +e

spacedelim() {
    if [ ! -z "$1" ]
    then
	IFS=',' read -ra ARR <<< "$1"
	ans="${ARR[*]}"
    fi
    echo $ans
}

images=(${DOCKERIMAGE})
arches=($(spacedelim ${ARCH}))
idx=0
while [[ $idx -lt ${#images[*]} ]]
do
    image=${images[$idx]}
    arch=${arches[$idx]}
    echo "Building installers for ${arch} using ${image}"
    #
    # If there are both 32-bit and 64-bit packages for the platform
    # only build the deb's after both 32-bit and 64-bit builds are
    # complete. Likewise only publish the release once.
    #
    docker run -t -a stdout -a stderr --cidfile=${WORKSPACE}/${OS}_docker-cid \
       -u $(id -u):$(id -g) \
       -e "ARCH=${arch}" \
       -e "ARCHES=${ARCH}" \
       -e "BRANCH=$BRANCH" \
       -e "DISTNAME=$DISTNAME" \
       -e "OS=$OS" \
       -e "RELEASE_VERSION=$RELEASE_VERSION"  \
       -e "TEST=$TEST" \
       -e "TESTFORMAT=$TEST_FORMAT" \
       -e "mdsevent_port=$EVENT_PORT" \
       -e "RELEASE=$RELEASE" \
       -e "PUBLISH=$PUBLISH" \
       -e "SANITIZE=$SANITIZE" \
       -e "VALGRIND_TOOLS=$VALGRIND_TOOLS" \
       -e "UPDATEPKG=$UPDATEPKG" \
       -e "PLATFORM=$PLATFORM" \
       -e "COLOR=${COLOR}" \
       -e "GIT_COMMIT=${GIT_COMMIT}" \
       -v $(realpath ${SRCDIR}):/source \
       -v ${WORKSPACE}:/workspace \
       $(volume "${releasedir}" /release) \
       $(volume "${publishdir}" /publish) \
       $(volume "$KEYS" /sign_keys) \
       ${image} /source/deploy/platform/${PLATFORM}/${PLATFORM}_docker_build.sh
    status=$?
    if [ -r ${WORKSPACE}/${OS}_docker-cid ]
    then
	sleep 3
	docker rm $(cat ${WORKSPACE}/${OS}_docker-cid)
	rm -f ${WORKSPACE}/${OS}_docker-cid
    fi
    if [ ! "$status" = "0" ]
    then
	RED $COLOR
	cat <<EOF >&2
======================================================

Docker ${PLATFORM}_docker_build.sh returned failure   
status when exiting from ${image}

======================================================
EOF
	NORMAL $COLOR
	exit $status
    fi
    let idx=idx+1
done
