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

main()
{
    printf "*********************************\n${FUNCNAME[0]}\n"
    
    if [[ ! -d ${CFOB_CURRENT_PATH}/components ]]; then
        mkdir ${CFOB_CURRENT_PATH}/components/
    fi

    SetupCatch
    printf "Download and install operation complete\n"
}

CFOB_CURRENT_PATH=$PWD

main
