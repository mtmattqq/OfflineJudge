#!/usr/bin/env bash

echo "Generating the test data."

cd TestCase

g++ -std=c++14 Gen.cpp -o Gen
./Gen

cd ..

echo "Compiling Run.cpp"

g++ -std=c++14 Run.cpp -o Run
./Run