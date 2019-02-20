#!/usr/bin/env bash

cd ./build

if [ "${TRAVIS_OS_NAME}" = "windows" ]; then
    cmake --build .
else
    cmake --build . -- -j3
fi

 cmake --build . --target run