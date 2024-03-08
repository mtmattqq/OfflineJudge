#!/usr/bin/env bash

echo "Generating the test data."

cd TestCase

g++ Gen.cpp -o Gen
./Gen

cd ..

echo "Compiling Run.cpp"

g++ Run.cpp -o Run
./Run