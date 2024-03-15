#ifndef MAIN_H
#define MAIN_H

#include <sys/resource.h>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <algorithm>
#include <random>
#include <cassert>
#include <chrono>
#include <vector>
#include <thread>
#include <iomanip>
#include <map>
#include "color.h"

using time_point = std::chrono::steady_clock::time_point;

bool isfinish = false;
int status = 0, currentTest = 0;
std::vector<int> costTime;
const int CODE_LENGTH = 12;
const int SUCCESS = 0;
const int AC = 1;
const int WA = 2;
const int TIME_OUT = 4;
const int RUNTIME_ERROR = 8;

int64_t RandomNumber(int64_t a, int64_t b, std::mt19937_64 &rng) {
    std::uniform_int_distribution<int64_t> dis(a, b);
    return dis(rng);
}

int64_t RandomNumber(int64_t n, std::mt19937_64 &rng) {
    return RandomNumber(1, n, rng);
}

void RunCode(int timeLimit,int testCase) {
    isfinish = false;
    status = TIME_OUT;

    std::string file = 
        "./Sol < ./TestCase/" + std::to_string(testCase) + ".in" + 
        "> ./TestCase/sol" + std::to_string(testCase) + ".out";
    
    struct rlimit limit;
    limit.rlim_cur = 256 * 1024 * 1024; // 256 MB
    limit.rlim_max = 256 * 1024 * 1024;
    setrlimit(RLIMIT_AS, &limit);

    time_point start = std::chrono::steady_clock::now();
    
    int exec_status = std::system(file.c_str());

    if(currentTest != testCase) {
        costTime[testCase] = timeLimit + 50;
        return;
    }

    isfinish = true;
    time_point end = std::chrono::steady_clock::now();

    if(exec_status != 0) {
        status = RUNTIME_ERROR;
        return;
    }
    
    int64_t time_cost = 
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
        .count();

    if(time_cost > timeLimit) {
        status = TIME_OUT;
        return;
    }

    status = SUCCESS;
    costTime[testCase] = time_cost;
    return;
}

int RunTestCase(int testCase, int timeLimit){
    std::string fileNum = std::to_string(testCase);

    status = TIME_OUT;
    isfinish = false;
    currentTest = testCase;
    std::thread run{RunCode, timeLimit, testCase};

    time_point start = std::chrono::steady_clock::now();

    while(!isfinish) {
        time_point now = std::chrono::steady_clock::now();
        int64_t time_cost = 
            std::chrono::duration_cast<std::chrono::milliseconds>(now - start)
            .count();
        if(time_cost > timeLimit * 2)
            break;
    }
    
    if(!isfinish) {
        status = TIME_OUT;
        run.detach();
        costTime[testCase] = timeLimit + 50;
        return TIME_OUT;
    } else {
        run.join();
        return status;
    }
}

bool Judge(int testCase){
    std::ifstream userOutput("./TestCase/sol" + std::to_string(testCase) + ".out");
    std::ifstream question("./TestCase/" + std::to_string(testCase) + ".in");
    std::ifstream answer("./TestCase/" + std::to_string(testCase) + ".out");

    std::string tp,userAns,systemAns;
    while(userOutput >> tp) 
        userAns += tp;
    while(answer>>tp) 
        systemAns += tp;
    userOutput.close();
    userOutput.open("./TestCase/sol" + std::to_string(testCase) + ".out");
    return systemAns == userAns;
}

std::string Encode(){
    std::ifstream fi("Solve.h");
    std::string tp,file;
    while(fi >> tp) {
        file += tp;
    }

    int sum = 0;
    for(auto i : file) {
        sum += (int)i;
    }

    std::mt19937_64 rng(sum);
    std::string ret;

    sum = 0;
    for(int i = 0; i < CODE_LENGTH - 1; ++i) {
        int a = RandomNumber(100, rng);
        sum += a;
        if(a < 10) ret += "0";
        ret += std::to_string(a);
    }

    sum %= 100;
    if(sum == 20) {
        ret += "00";
    } else if(sum < 20) {
        int a = 20 - sum;
        if(a < 10) ret += "0";
        ret += std::to_string(a);
    } else {
        int a = 120 - sum;
        ret += std::to_string(a);
    }

    return ret;
}

double FindComputerSpeed() {
    time_point start = std::chrono::steady_clock::now();

    int ans = 0;
    const int MOD = 37;
    const int TIME = 100000000;
    for(int i = 0; i < TIME; ++i) {
        ans = (ans * i) % MOD;
    }
    
    time_point end = std::chrono::steady_clock::now();

    return double(std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
            .count()) / 1000.0;
}

double FixTimeLimit(int timeLimit) {
    std::cerr << "Fixing the time limit..." << "\n";
    
    const int TEST_NUM = 5;
    double average = 0;
    for(int i = 0; i < TEST_NUM; ++i) {
        average += FindComputerSpeed();
    }
    average /= TEST_NUM;

    const double MY_TIME_COST = 0.3495;
    double multiplier = average / MY_TIME_COST;

    std::cerr << "Your Computer run " << std::setprecision(2) << 1.0 / multiplier 
         << " time \nas fast as the judge." << "\n\n";

    return multiplier;
}

void ReadProblemInfo(int &testCases, int &timeLimit, std::string &problemID) {
    std::ifstream log("./TestCase/log.txt");
    std::string recycle;
    log >> recycle >> testCases;
    log >> recycle >> timeLimit;
    log >> recycle >> problemID;
}

void ShowTotalResult(bool allCorrect, int statusFlag, std::ostream &output) {
    if(allCorrect) {
        std::ifstream AC("Result/AC");
        std::string line;
        std::cerr << Color(0x7A, 0xFF, 0x77);
        while(getline(AC, line)) {
            std::cerr << line << "\n";
            output << line << "\n";
        }
        std::cerr << RESET " " << std::flush;
    } else if(statusFlag & TIME_OUT) {
        std::ifstream TLE("Result/TLE");
        std::string line;
        std::cerr << Color(0x9F, 0xE2, 0xFF);
        while(std::getline(TLE, line)) {
            std::cerr << line << "\n";
            output << line << "\n";
        }
        std::cerr << RESET " " << std::flush;
    } else if(statusFlag & RUNTIME_ERROR) {
        std::ifstream RE("Result/RE");
        std::string line;
        std::cerr << Color(0xAE, 0x9F, 0xFF);
        while(std::getline(RE, line)) {
            std::cerr << line << "\n";
            output << line << "\n";
        }
        std::cerr << RESET " " << std::flush;
    } else {
        std::ifstream WA("Result/WA");
        std::string line;
        std::cerr << Color(0xFF, 0x41, 0x41);
        while(getline(WA, line)) {
            std::cerr << line << "\n";
            output << line << "\n";
        }
        std::cerr << RESET " " << std::flush;
    }
}

void RunSolution() {
    std::string problemID;
    int testCases, timeLimit;
    double multiplier;

    ReadProblemInfo(testCases, timeLimit, problemID);
    costTime.resize(testCases + 1);

    std::ofstream output("output.info");

    std::cerr << "Problem ID : " << problemID << "\n";
    std::cerr << "There're " << testCases << " testcases." << "\n\n";

    output << "Problem ID : " << problemID << "\n";
    output << "There're " << testCases << " testcases." << "\n";

    int compile_status = std::system("g++ Solve.cpp -O2 -o Sol");
    if(compile_status != 0) {
        std::cerr << "Compilation failed.\n";
        std::ifstream CE("CE");
        std::string line;
        while(std::getline(CE, line)) {
            std::cerr << line << "\n";
        }
        std::cerr << std::flush;
        return;
    }

    multiplier = FixTimeLimit(timeLimit);
    timeLimit *= multiplier;

    std::cerr << "Running TestCase..." << "\n";

    std::vector<int> outputStatus(testCases + 1);
    for(int i = 1; i <= testCases; ++i) {
        int st = RunTestCase(i, timeLimit);
        outputStatus[i] = st;
        std::cerr << i << " ";
    }
    std::cerr << "\n\n";

    int correct = 0;
    bool allCorrect = true;
    int statusFlag = 0;

    for(int i = 1; i <= testCases; ++i) {
        if(outputStatus[i] == SUCCESS) {
            outputStatus[i] = Judge(i);
        }
        correct += (outputStatus[i] == AC);
        if(outputStatus[i] != AC) {
            allCorrect = false;
        }
        statusFlag |= outputStatus[i];
    }

    std::cerr << "\n";
    
    ShowTotalResult(allCorrect, statusFlag, output);
    std::map<int, std::string> ret;
    ret[WA] = "WA";
    ret[AC] = "AC";
    ret[TIME_OUT] = "TLE";
    ret[RUNTIME_ERROR] = "RE";
    std::cerr << "For each testcase : " << "\n\n";
    output << "For each testcase : " << "\n\n";

    for(int i = 1; i <= testCases; ++i) {
        costTime[i] /= multiplier;
    }

    for(int i = 1; i <= testCases; ++i) {
        std::cerr << std::right << std::setw(3) << i << ". " << std::flush;
        std::cerr << std::setw(4) << ret[outputStatus[i]] << "  " << std::flush;
        std::cerr << "Execution time : " << std::right << std::setw(4) << costTime[i] << " ms" << std::endl;
        output << std::right << std::setw(3) << i << ". " << std::flush;
        output << std::setw(4) << ret[outputStatus[i]] << "  " << std::flush;
        output << "Execution time : " << std::right << std::setw(4) << costTime[i] << " ms" << std::endl;
    }
    std::cerr << "\nTotal score : " << std::fixed << std::setprecision(2) << (double)correct / testCases * 100 << std::endl;
    output << "\nTotal score : " << std::fixed << std::setprecision(2) << (double)correct / testCases * 100 << std::endl;

    std::cerr << std::endl;
    output << std::endl;

    if(allCorrect) {
        std::string code = Encode();
        std::cerr<<"AC code : " << code << std::endl;
        output << "AC code : " << code << std::endl;
    }
}

#endif
