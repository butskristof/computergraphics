#!/bin/bash
make all
FILES=$(find input -type f -name '*.ini')
for f in $FILES
do
    echo "running $f"
    ./engine $f
done
