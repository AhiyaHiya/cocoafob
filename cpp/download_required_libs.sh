#!/bin/bash
# Catch C++ is a header only implementation of unit-testing
# for C++ projects, which is used by this project.

# The cocoafob.xcodeproj will invoke this script when building the project

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

CFOB_CURRENT_PATH=$PROJECT_DIR/..

main
