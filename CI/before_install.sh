#!/usr/bin/env bash

if [ "${TRAVIS_OS_NAME}" = "linux" ]; then
    eval "${MATRIX_CC}"
fi
