#!/bin/bash

CURRENT_PATH=$(cd $(dirname $0) && pwd)

cppcheck --enable=all --error-exitcode=1 --std=c++14  --inconclusive --language=c++ --force ${CURRENT_PATH}/../include ${CURRENT_PATH}/../src
