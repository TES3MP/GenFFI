#!/usr/bin/env bash

mkdir build
cd build

# print environment values
env

OS_SPEC_VARS=()

# Windows specific options
if [ "${TRAVIS_OS_NAME}" = "windows" ]; then
    # OS_SPEC_VARS+=('-G Visual Studio 15 2017')
    if [ "BUILD_ARCH" = "x64" ]; then
        OS_SPEC_VARS+=('-A x64')
    else
        OS_SPEC_VARS+=('-A Win32')
    fi
fi

cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    ${OS_SPEC_VARS[@]}
