#!/bin/bash
make clean
FILES=$(find input -type f -name '*.bmp')
for f in $FILES
do
    echo "deleting $f"
    rm $f
done
