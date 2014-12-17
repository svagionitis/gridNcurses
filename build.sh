#!/bin/bash
# Script for out of source build.

BUILD_DIR="build-$(uname -m)"

rm -fr ${BUILD_DIR}

mkdir -p ${BUILD_DIR}

cd ${BUILD_DIR}

cmake ../
make

cd -
