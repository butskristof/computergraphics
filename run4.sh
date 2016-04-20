#!/bin/bash
make all
FILES=$(find input/4_zbuflines -type f -name '*.ini')
for f in $FILES
do
    echo "running $f"
    ./engine $f
done
