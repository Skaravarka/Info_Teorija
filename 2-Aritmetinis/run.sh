#!/bin/bash
g++ main.cpp encode.cpp decode.cpp compress.cpp -o main
rm $2
echo "COMPILING DONE"
echo " "
echo "Running Encoding......"
./main e $1 out
echo " "
echo "Running Decoding......"
./main d out $2
rm main