#!/usr/bin/env bash

echo "Generating the test data."

cd TestCase

g++ -std=c++20 Gen.cpp -o Gen
./Gen

cd ..

echo "Compiling Run.cpp"

g++ -std=c++20 Run.cpp -o Run
./Run