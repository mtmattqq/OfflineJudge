#include <iostream>
#include <fstream>
#include <cstdint>
#include <algorithm>
#include <random>
#include <cassert>
#include "GraphGen.h"
#include "tower.h"
using namespace std;

#define ALL(v) v.begin(),v.end()
using ll=long long;

int solve(int i){
    string file = "./Sol < " + to_string(i) + ".in" + "> " + to_string(i) + ".out";
    
    int exec_status = system(file.c_str());
    if(exec_status != 0) {
        std::cerr << "Execution failed.\n";
        return 1;
    }

    return 0;
}

void SubTesk1(int a){
    std::string fileName = to_string(a);

    std::ofstream ques(fileName + ".in");

    const int SHIFT = 17682;
    random_number_generater rng(a * 10 + SHIFT);

    int height = 3;
    // int height = rng(1, 100);
    tower tow(height, rng);

    ques << height << "\n" << tow;


    std::cerr<<a<<endl;
}

#define REP(i,a,b) for(int i=(a);i<=(b);++i)
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    
    int compile_status = system("g++ Sol.cpp -o Sol");
    if(compile_status != 0) {
        std::cerr << "Compilation failed.\n";
        return 1;
    }

    const int TEST_CASE = 10;

    clock_t startTime=clock();
    REP(i, 1, TEST_CASE){
        SubTesk1(i);
    }

    REP(i, 1, TEST_CASE){
        solve(i);
    }

    clock_t endTime=clock();

    cerr << double(endTime - startTime) / CLOCKS_PER_SEC << "\n";
}
