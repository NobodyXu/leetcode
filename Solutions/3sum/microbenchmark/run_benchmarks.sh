#!/bin/bash -ex

run() {
    CXXFLAGS=-${1} result_file=./${1}_result make clean
    CXXFLAGS=-${1} result_file=./${1}_result make
}

for optimization_level in O0 O1 Oz O2 O3 Ofast; do
    run $optimization_level
done
