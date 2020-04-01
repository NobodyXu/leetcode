#!/bin/bash -ex

if [ -n "$1" ]; then
    mybench=$1
else
    mybench=./a.out
    if [ ! -f $mybench ] || [ ! -x $mybench ]; then
        echo $0 [optional: executable linked with libbenchmark or libbenchmark_main] [optional: output file]
        echo If the optional arg is not provided, it is default to ./a.out.
        exit 1
    fi
fi

sudo cpupower frequency-set --governor performance
$mybench 2>&1 | tee "$2"
exec sudo cpupower frequency-set --governor powersave
