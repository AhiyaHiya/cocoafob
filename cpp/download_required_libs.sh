#!/bin/bash

set -e
set -u

SetupCatch()
{
    printf "*********************************\n${FUNCNAME[0]}\n"
    
    if [[ ! -d components/catch/ ]]; then
        
        mkdir -p components/catch/include/
        cd components/catch/include/
        curl -O https://raw.githubusercontent.com/philsquared/Catch/master/single_include/catch.hpp
        cd $CFOB_CURRENT_PATH
        printf "*********************************\n"
    fi
}

BuildOpenSSL_32bit()
{
    local CURRENT_PATH=$PWD
    local BUILD_DIR=${CURRENT_PATH}/macos_build_10.12
    local SSL_DIR=${BUILD_DIR}/openssl

    export CC="${BUILD_TOOLS}/usr/bin/clang -fembed-bitcode -mmacosx-version-min=10.8"

    make clean && make dclean
    
    KERNEL_BITS=32 ./config no-ssl2 no-ssl3 --prefix=${BUILD_DIR}
    make depend
    make
    make -j 8 install_sw

    mv ${SSL_DIR}/include/openssl/opensslconf.h ${SSL_DIR}/include/openssl/opensslconf-x86.h
    mv ${SSL_DIR}/include/openssl/bn.h ${SSL_DIR}/include/openssl/bn-x86.h
    mv ${SSL_DIR}/ ${BUILD_DIR}/ssl-x86
}

BuildOpenSSL_64bit()
{
    local CURRENT_PATH=$PWD
    local BUILD_DIR=${CURRENT_PATH}/macos_build_10.12
    local SSL_DIR=${BUILD_DIR}/openssl

    export CC="${BUILD_TOOLS}/usr/bin/clang -fembed-bitcode -mmacosx-version-min=10.8"

    make clean && make dclean

    KERNEL_BITS=64 ./config no-ssl2 no-ssl3 --prefix=${SSL_DIR}
    make depend
    make
    make -j 8 install_sw

    mv ${SSL_DIR}/include/openssl/opensslconf.h ${SSL_DIR}/include/openssl/opensslconf-x64.h
    mv ${SSL_DIR}/include/openssl/bn.h ${SSL_DIR}/include/openssl/bn-x64.h
    mv ${SSL_DIR}/ ${BUILD_DIR}/ssl-x64
}

CopyOpenSSL_Headers()
{
    local CURRENT_PATH=$PWD
    local BUILD_DIR=${CURRENT_PATH}/macos_build_10.12
    local SSL_DIR=${BUILD_DIR}/openssl

    rm -rf ${SSL_DIR}

    mkdir -p ${SSL_DIR}/bin
    mkdir -p ${SSL_DIR}/include/openssl
    mkdir -p ${SSL_DIR}/lib

    cp ${BUILD_DIR}/ssl-x86/openssl.cnf ${SSL_DIR}/openssl.cnf
    cp ${BUILD_DIR}/ssl-x86/include/openssl/* ${SSL_DIR}/include/openssl
    cp ${BUILD_DIR}/ssl-x86/include/openssl/opensslconf-x86.h ${SSL_DIR}/include/openssl/opensslconf-x86.h
    cp ${BUILD_DIR}/ssl-x64/include/openssl/opensslconf-x64.h ${SSL_DIR}/include/openssl/opensslconf-x64.h
    cp ${BUILD_DIR}/ssl-x86/include/openssl/bn-x86.h ${SSL_DIR}/include/openssl/bn-x86.h
    cp ${BUILD_DIR}/ssl-x64/include/openssl/bn-x64.h ${SSL_DIR}/include/openssl/bn-x64.h
}


CreateOpenSSL_Headers()
{
    local CURRENT_PATH=$PWD
    local BUILD_DIR=${CURRENT_PATH}/macos_build_10.12
    local SSL_DIR=${BUILD_DIR}/openssl

    if [[ ! -d ${SSL_DIR}/include/openssl ]]; then
        mkdir -p ${SSL_DIR}/include/openssl
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

#endif /* OPENSSL_MULTIARCH_CONF_HEADER */' > ${SSL_DIR}/include/openssl/opensslconf.h

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

#endif /* OPENSSL_MULTIARCH_BN_HEADER */' > ${SSL_DIR}/include/openssl/bn.h
}

CreateOpenSSL_FatBinary()
{
    local CURRENT_PATH=$PWD
    local BUILD_DIR=${CURRENT_PATH}/macos_build_10.12
    local SSL_DIR=${BUILD_DIR}/openssl

    lipo -create ${BUILD_DIR}/ssl-x86/lib/libcrypto.a \
             ${BUILD_DIR}/ssl-x64/lib/libcrypto.a \
             -output ${SSL_DIR}/lib/libcrypto.a

    lipo -create ${BUILD_DIR}/ssl-x86/lib/libssl.a \
                 ${BUILD_DIR}/ssl-x64/lib/libssl.a \
                 -output ${SSL_DIR}/lib/libssl.a

    lipo -create ${BUILD_DIR}/ssl-x86/bin/openssl \
                 ${BUILD_DIR}/ssl-x64/bin/openssl \
                 -output ${SSL_DIR}/bin/openssl
}

# Code for this function was inspired by 
# https://gist.github.com/felix-schwarz/c61c0f7d9ab60f53ebb0
BuildOpenSSL()
{
    # ARCH="x86_64"
    # TARGET="darwin-i386-cc"

    # if [[ $ARCH == "x86_64" ]]; then
    #     TARGET="darwin64-x86_64-cc"
    # fi
    # # TODO; http://stackoverflow.com/questions/25530429/build-multiarch-openssl-on-os-x/25531033#25531033

    # export CC="${BUILD_TOOLS}/usr/bin/clang -fembed-bitcode -mmacosx-version-min=10.8"

    # ./Configure ${TARGET} --prefix=$PWD/macos_build_10.12 --openssldir=$PWD/macos_build_10.12/openssl &> "./openssl-${ARCH}.log"

    # make
    # make test
    # make -j 8 install
    BuildOpenSSL_32bit
    BuildOpenSSL_64bit
    CopyOpenSSL_Headers
    CreateOpenSSL_Headers
    CreateOpenSSL_FatBinary
}

SetupOpenSSL()
{
    printf "*********************************\n${FUNCNAME[0]}\n"
    
    if [[ ! -d components/openssl ]]; then
        
        mkdir -p components/openssl_src
        cd components/openssl_src
        git clone -b OpenSSL_1_0_2-stable git://git.openssl.org/openssl.git
        cd openssl
        
        BuildOpenSSL

        cd ../..
        mv openssl_src/openssl/macos_build_10.12 ./openssl
        rm -fR openssl_src

        cd $CFOB_CURRENT_PATH
        printf "*********************************\n"
    fi
}

SetupXcodeCoverage()
{
    printf "*********************************\n${FUNCNAME[0]}\n"
    
    if [[ ! -d components/XcodeCoverage/ ]]; then
        cd components/
        git clone https://github.com/jonreid/XcodeCoverage.git
        cd XcodeCoverage
        rm -fR .git
        rm .gitignore
        cd $CFOB_CURRENT_PATH
        printf "*********************************\n"
    fi
}

main()
{
    printf "*********************************\n${FUNCNAME[0]}\n"
    
    if [[ ! -d components ]]; then
        mkdir components/
    fi

    SetupCatch
    SetupOpenSSL
    SetupXcodeCoverage  
    printf "Download and install operation complete\n"
}


CFOB_CURRENT_PATH=$PWD

main
