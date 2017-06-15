#!/bin/bash

set -o errexit

SetupCatch()
{
    printf "*********************************\n${FUNCNAME[0]}\n"
    
    if [[ ! -d ${CFOB_CURRENT_PATH}/components/catch/ ]]; then
        
        mkdir -p ${CFOB_CURRENT_PATH}/components/catch/include/
        cd ${CFOB_CURRENT_PATH}/components/catch/include/
        curl -O https://raw.githubusercontent.com/philsquared/Catch/master/single_include/catch.hpp
        cd $CFOB_CURRENT_PATH
        printf "*********************************\n"
    fi
}

BuildOpenSSL_WithBit()
{
    local ARCH=$1
    local BITS=$2

    export CC="${BUILD_TOOLS}/usr/bin/clang -fembed-bitcode -mmacosx-version-min=10.8"

    make clean && make dclean
    
    KERNEL_BITS=${BITS} ./config --prefix=${CFOB_SSL_DIR} &> "./openssl_config-x${ARCH}.log"
    make depend >> "./openssl_make_depend-x${ARCH}.log" 2>&1
    make >> "./openssl_make-x${ARCH}.log" 2>&1
    make -j ${CFOB_CORE_COUNT} install_sw >> "./openssl_make_install-x${ARCH}.log" 2>&1

    set -x
    
    mv ${CFOB_SSL_DIR}/include/openssl/opensslconf.h ${CFOB_SSL_DIR}/include/openssl/opensslconf-x${ARCH}.h
    mv ${CFOB_SSL_DIR}/include/openssl/bn.h ${CFOB_SSL_DIR}/include/openssl/bn-x${ARCH}.h
    mv ${CFOB_SSL_DIR}/ ${CFOB_SSL_BUILD_DIR}/ssl-x${ARCH}
}

CopyOpenSSL_Headers()
{
    rm -rf ${CFOB_SSL_DIR}

    mkdir -p ${CFOB_SSL_DIR}/bin
    mkdir -p ${CFOB_SSL_DIR}/include/openssl
    mkdir -p ${CFOB_SSL_DIR}/lib

    cp ${CFOB_SSL_BUILD_DIR}/ssl-x86/ssl/openssl.cnf ${CFOB_SSL_DIR}/openssl.cnf
    cp ${CFOB_SSL_BUILD_DIR}/ssl-x86/include/openssl/* ${CFOB_SSL_DIR}/include/openssl
    cp ${CFOB_SSL_BUILD_DIR}/ssl-x86/include/openssl/opensslconf-x86.h ${CFOB_SSL_DIR}/include/openssl/opensslconf-x86.h
    cp ${CFOB_SSL_BUILD_DIR}/ssl-x64/include/openssl/opensslconf-x64.h ${CFOB_SSL_DIR}/include/openssl/opensslconf-x64.h
    cp ${CFOB_SSL_BUILD_DIR}/ssl-x86/include/openssl/bn-x86.h ${CFOB_SSL_DIR}/include/openssl/bn-x86.h
    cp ${CFOB_SSL_BUILD_DIR}/ssl-x64/include/openssl/bn-x64.h ${CFOB_SSL_DIR}/include/openssl/bn-x64.h
}


CreateOpenSSL_Headers()
{
    if [[ ! -d ${CFOB_SSL_DIR}/include/openssl ]]; then
        mkdir -p ${CFOB_SSL_DIR}/include/openssl
    fi

    echo '
#ifndef OPENSSL_MULTIARCH_CONF_HEADER
#define OPENSSL_MULTIARCH_CONF_HEADER

#if __i386 || __i386__
# include "opensslconf-x86.h"
#elif __x86_64 || __x86_64__ || __amd64 || __amd64__
# include "opensslconf-x64.h"
#else
# error Unknown architecture
#endif

#endif /* OPENSSL_MULTIARCH_CONF_HEADER */' > ${CFOB_SSL_DIR}/include/openssl/opensslconf.h

    echo '
#ifndef OPENSSL_MULTIARCH_BN_HEADER
#define OPENSSL_MULTIARCH_BN_HEADER

#if __i386 || __i386__
# include "bn-x86.h"
#elif __x86_64 || __x86_64__ || __amd64 || __amd64__
# include "bn-x64.h"
#else
# error Unknown architecture
#endif

#endif /* OPENSSL_MULTIARCH_BN_HEADER */' > ${CFOB_SSL_DIR}/include/openssl/bn.h
}

CreateOpenSSL_FatBinary()
{
    lipo -create ${CFOB_SSL_BUILD_DIR}/ssl-x86/lib/libcrypto.a \
             ${CFOB_SSL_BUILD_DIR}/ssl-x64/lib/libcrypto.a \
             -output ${CFOB_SSL_DIR}/lib/libcrypto.a

    lipo -create ${CFOB_SSL_BUILD_DIR}/ssl-x86/lib/libssl.a \
                 ${CFOB_SSL_BUILD_DIR}/ssl-x64/lib/libssl.a \
                 -output ${CFOB_SSL_DIR}/lib/libssl.a

    lipo -create ${CFOB_SSL_BUILD_DIR}/ssl-x86/bin/openssl \
                 ${CFOB_SSL_BUILD_DIR}/ssl-x64/bin/openssl \
                 -output ${CFOB_SSL_DIR}/bin/openssl
}

# Code for this function was inspired by 
# https://gist.github.com/felix-schwarz/c61c0f7d9ab60f53ebb0
# http://stackoverflow.com/questions/25530429/build-multiarch-openssl-on-os-x/25531033#25531033
BuildOpenSSL()
{
    cd ${CFOB_CURRENT_PATH}/components/openssl

    if [[ ! -d ${CFOB_SSL_BUILD_DIR} ]]; then
        mkdir -p ${CFOB_SSL_BUILD_DIR}
    fi

    if [[ ! -d ${CFOB_SSL_DIR} ]]; then
        mkdir -p ${CFOB_SSL_DIR}
    fi

    BuildOpenSSL_WithBit 86 32
    BuildOpenSSL_WithBit 64 64
    CopyOpenSSL_Headers
    CreateOpenSSL_Headers
    CreateOpenSSL_FatBinary
}

DownloadOpenSSL()
{
    cd ${CFOB_CURRENT_PATH}/components/
    if [[ ! -d ${CFOB_CURRENT_PATH}/components/openssl_src ]]; then
        mkdir -p ${CFOB_CURRENT_PATH}/components/openssl_src
    fi
    git clone -b OpenSSL_1_0_2-stable https://github.com/openssl/openssl
}

SetupOpenSSL()
{
    printf "*********************************\n${FUNCNAME[0]}\n"
    
    DownloadOpenSSL
    BuildOpenSSL    
    cd ${CFOB_CURRENT_PATH}/components/
    
    mv openssl_src/openssl/macos_build_10.12 ./openssl
    rm -fR openssl_src

    cd ${CFOB_CURRENT_PATH}
    printf "*********************************\n"
}

SetupXcodeCoverage()
{
    printf "*********************************\n${FUNCNAME[0]}\n"
    
    if [[ ! -d ${CFOB_CURRENT_PATH}/components/XcodeCoverage/ ]]; then
        cd ${CFOB_CURRENT_PATH}/components/
        git clone https://github.com/jonreid/XcodeCoverage.git
        cd ${CFOB_CURRENT_PATH}/components/XcodeCoverage
        rm -fR .git
        rm .gitignore
        cd ${CFOB_CURRENT_PATH}
        printf "*********************************\n"
    fi
}

main()
{
    printf "*********************************\n${FUNCNAME[0]}\n"
    
    if [[ ! -d ${CFOB_CURRENT_PATH}/components ]]; then
        mkdir ${CFOB_CURRENT_PATH}/components/
    fi

#    SetupCatch
    SetupOpenSSL
 #   SetupXcodeCoverage  
    printf "Download and install operation complete\n"
}

CFOB_CORE_COUNT=`getconf _NPROCESSORS_ONLN`
CFOB_CURRENT_PATH=$PWD
CFOB_SSL_BUILD_DIR=${CFOB_CURRENT_PATH}/../openssl_out/build/macos_build_10.12
CFOB_SSL_DIR=${CFOB_CURRENT_PATH}/../openssl_out/dist/openssl

main
