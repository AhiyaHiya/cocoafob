#!/bin/bash

set -e
set -u

SetupCatch()
{
	printf "${FUNCNAME[0]}\n"
	
    if [[ ! -d components/catch/ ]]; then
        echo "*********************************"
        echo "${FUNCNAME[0]}"
        mkdir -p components/catch/include/
        cd components/catch/include/
        curl -O https://raw.githubusercontent.com/philsquared/Catch/master/single_include/catch.hpp
        cd $CFOB_CURRENT_PATH
        echo "*********************************"
    fi
}

SetupOpenSSL()
{
	printf "${FUNCNAME[0]}\n"
	
    if [[ ! -d components/openssl ]]; then
        echo "*********************************"
        echo "${FUNCNAME[0]}"
        mkdir -p components/openssl_src
        cd components/openssl_src
        git clone -b OpenSSL_1_0_2-stable git://git.openssl.org/openssl.git
        cd openssl

        ./Configure darwin64-x86_64-cc --prefix=$PWD/macos_build_10.11 --openssldir=$PWD/macos_build_10.11/openssl
        make
        make test
        make -j 8 install

        cd ../..
        mv openssl_src/openssl/macos_build_10.11 ./openssl
        rm -fR openssl_src

        cd $CFOB_CURRENT_PATH
        echo "*********************************"
    fi
}

SetupXcodeCoverage()
{
	printf "${FUNCNAME[0]}\n"
	
    if [[ ! -d components/XcodeCoverage/ ]]; then
        echo "*********************************"
        echo "${FUNCNAME[0]}"
        cd components/
        git clone https://github.com/jonreid/XcodeCoverage.git
        cd XcodeCoverage
        rm -fR .git
        rm .gitignore
        cd $CFOB_CURRENT_PATH
        echo "*********************************"
    fi
}

main()
{
	printf "${FUNCNAME[0]}\n"
	
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

