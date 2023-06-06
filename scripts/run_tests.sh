#!/bin/bash

set -e

CURRENT_PATH=$(cd $(dirname $0) && pwd)

function test() {
  echo "---------------------------------------------------------------"
  echo "------------------------- run all test ------------------------"
  echo "---------------------------------------------------------------"
  mkdir -p build && cd build
  cmake -DBUILD_SHARED_LIBS=ON -DBUILD_CACTUS_TEST=ON -DCMAKE_BUILD_TYPE=Debug ..
  make -j4
  local bin_path="$CURRENT_PATH/../build/tests"
  for file in $bin_path/*
  do
    case "$file" in
      *test )
        echo "---run: $file"
        $file
        ;;
      * );;
    esac
  done
}

function main () {
  test
  return
}

main "$@"

