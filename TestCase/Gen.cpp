#include <iostream>
#include <fstream>
#include <cstdint>
#include <algorithm>
#include <random>
#include <cassert>
#include <chrono>

#include "GraphGen.h"

#define ALL(v) v.begin(),v.end()
using ll = long long;

const int SHIFT = 17682;

int solve(int i) {
    std::string file = "./Sol < " + std::to_string(i) + ".in" + "> " + std::to_string(i) + ".out";
    
    int exec_status = std::system(file.c_str());
    if(exec_status != 0) {
        std::cerr << "Execution failed.\n";
        return 1;
    }

    return 0;
}

void SubTesk1(int a){
    std::string fileName = std::to_string(a);

    std::ofstream ques(fileName + ".in");

    random_number_generater rng(a * 10 + SHIFT);

    int height = a * 2 + 1;
}

void SubTesk2(int a){
    std::string fileName = std::to_string(a);

    std::ofstream ques(fileName + ".in");

    random_number_generater rng(a * 10 + SHIFT);

    int height = rng(45, 49) * 2 + 1;
}

#define REP(i,a,b) for(int i=(a);i<=(b);++i)
int main(){
    std::ios::sync_with_stdio(0);std::cin.tie(0);
    
    int compile_status = system("g++ Sol.cpp -std=c++14 -O2 -o Sol");
    if(compile_status != 0) {
        std::cerr << "Compilation failed.\n";
        return 1;
    } else {
        std::cerr << "Compilation success\n";
    }

    const int TEST_CASE = 10;

    using time_point = std::chrono::steady_clock::time_point;
    time_point start = std::chrono::steady_clock::now();
    
    REP(i, 1, 5){
        SubTesk1(i);
        std::cerr << "Finishing generating the tower " << i << "\n";
    }

    REP(i, 6, TEST_CASE){
        SubTesk2(i);
        std::cerr << "Finishing generating the tower " << i << "\n";
    }

    REP(i, 1, TEST_CASE){
        solve(i);
        std::cerr << "Successfully solve testcase : " << i << "\n";
    }

    time_point end = std::chrono::steady_clock::now();

    std::cerr << "Total time : " << 
        double(std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
            .count()) / 1000.0 
         << "\n";
}
