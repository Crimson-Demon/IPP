#!/bin/bash

if [ "$#" -eq 2 ]; then
    EXEC=$1
    IN_PATH=$2
    OUT_PATH=$2
elif [ "$#" -eq 3 ]; then
    EXEC=$2
    IN_PATH=$3
    OUT_PATH=$3
    ERR_PATH=$3
    VEE=$1
fi

IN_FILES=$(ls -v $IN_PATH|sed -n 's/\.in//p' | tr "\n" " ")
OUT_FILES=$(ls -v $IN_PATH|sed -n 's/\.out//p' | tr "\n" " ")
if [ "$#" -eq 3 ]; then
    ERR_FILES=$(ls -v $IN_PATH|sed -n 's/\.err//p' | tr "\n" " ")
fi

testfiles=$IN_FILES

for t in ${testfiles[@]}
do
    if [ "$#" -eq 2 ]; then
        if [ -f "$OUT_PATH/$t.out" ]; then
            DH=$($EXEC < $IN_PATH/$t".in" | diff -q $OUT_PATH/$t".out" -)
            if [ "$DH" ]; then
                echo "Error in test "$t".in"
            fi
        else
            echo "Missing outfile"
        fi
    else
        if [ -f "$OUT_PATH/$t.out" ] && [ -f "$ERR_PATH/$t.err" ]; then
            DH1=$($EXEC < $IN_PATH/$t".in" | diff -q $OUT_PATH/$t".out" -)
            DH2=$($EXEC $VEE < $IN_PATH/$t".in" | diff -q $OUT_PATH/$t".out" -)
            if [ "$DH1" ] || [ "$DH2" ]; then
                echo "Error in test "$t".in"
            fi
        else
            echo "Missing outfile or errfile"
        fi
    fi
done