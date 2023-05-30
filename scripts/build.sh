#!/bin/bash

function main() {
  echo "cactus build."
  mkdir -p build && cd build
  cmake -DBUILD_SHARED_LIBS=ON -DBUILD_CACTUS_TEST=ON -DCMAKE_BUILD_TYPE=Debug ..
  make -j6
}

main "$@"

