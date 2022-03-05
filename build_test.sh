#!/bin/bash

#######################################################################################
# remove old build_test folder if it exists

if [ -d build_test ]
    then
    rm -r build_test
fi

#######################################################################################
# remove old test file if it exists

if [ -e test ]
    then
    rm test
fi

#######################################################################################
# make new build_test folder

mkdir build_test && cd build_test

#######################################################################################
# build

cmake .. && make clean && make

#######################################################################################
# move test and remove build_test folder

if [ -e test ]
    then
    mv test ..
fi

cd .. && rm -r build_test

#######################################################################################
# run test

if [ -e test ]
    then
    clear
    echo BUILDED SUCCESSFULY
    echo --------------------------- && echo

    ./test
    
    echo && echo ---------------------------
    echo FINISHED && echo
else
    echo && echo UNSUCCESSFULY !!! && echo
fi