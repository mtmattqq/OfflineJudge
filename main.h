#ifndef MAIN_H
#define MAIN_H

#include<bits/stdc++.h>
// #include<conio.h>
// #include "Solve.h"
using namespace std;

bool isfinish=false;
vector<int> costTime;
const int CODE_LENGTH=12;

class TimeLimitExceeded : public exception{
    public :
        TimeLimitExceeded() : exception() {}
};

class CompilationError : public exception{
    public :
        CompilationError() : exception() {}
};

long long RandomNumber(long long a,long long b,mt19937_64 &rng){
    uniform_int_distribution<long long> dis(a,b);
    return dis(rng);
}

long long RandomNumber(long long n,mt19937_64 &rng){
    return RandomNumber(1,n,rng);
}

void RunCode(int timeLimit,int testCase){
    isfinish=false;

    string file = 
        "./Sol < ./TestCase/" + to_string(testCase) + ".in" + 
        "> ./TestCase/sol" + to_string(testCase) + ".out";

    clock_t start=clock();
    
    int exec_status = system(file.c_str());

    isfinish=true;
    clock_t end=clock();

    if(exec_status != 0) {
        throw runtime_error("");
        return;
    }
    
    if(end-start>timeLimit){
        throw TimeLimitExceeded();
        return;
    }

    costTime.emplace_back(end-start);
    return;
}

bool RunTestCase(int testCase,int timeLimit){
    string fileNum=to_string(testCase);
    
    // string inputFile="./TestCase\\";
    // inputFile+=fileNum;
    // inputFile+=".in";

    // string userOutput="./TestCase\\sol";
    // userOutput+=fileNum;
    // userOutput+=".out";

    // freopen(inputFile.c_str(),"r",stdin);
    // freopen(userOutput.c_str(),"w",stdout);

    thread run{RunCode,timeLimit,testCase};

    clock_t start=clock();

    while(!isfinish && clock()-start<=timeLimit);

    // chrono::milliseconds s(timeLimit+20);
    // this_thread::sleep_for(s);
    
    if(!isfinish){
        run.detach();
        throw TimeLimitExceeded();
        return false;
    }else{
        run.join();
        return true;
    }
}

bool Judge(int testCase){
    ifstream userOutput("./TestCase/sol"+to_string(testCase)+".out");
    ifstream question("./TestCase/"+to_string(testCase)+".in");
    ifstream answer("./TestCase/"+to_string(testCase)+".out");

    string tp,userAns,systemAns;

    while(userOutput>>tp){
        userAns+=tp;
        if(userAns.size()>10000000){
            return false;
        }
    }

    while(answer>>tp){
        systemAns+=tp;
    }

    cerr<<" ";
    return systemAns==userAns;
}

string Encode(){
    ifstream fi("Solve.h");
    string tp,file;
    while(fi>>tp){
        file+=tp;
    }

    int sum=0;
    for(auto i:file){
        sum+=(int)i;
    }

    mt19937_64 rng(sum);
    string ret;

    sum=0;
    for(int i=0;i<CODE_LENGTH-1;++i){
        int a=RandomNumber(100,rng);
        sum+=a;
        if(a<10) ret+="0";
        ret+=to_string(a);
    }

    sum%=100;
    if(sum==20){
        ret+="00";
    }else if(sum<20){
        int a=20-sum;
        if(a<10) ret+="0";
        ret+=to_string(a);
    }else{
        int a=120-sum;
        ret+=to_string(a);
    }

    return ret;
}

double FindComputerSpeed() {
    clock_t start = clock();

    int ans = 0;
    const int MOD = 37;
    for(int i = 0; i < 100000000; ++i) {
        ans = (ans * i) % MOD;
    }

    clock_t end = ans;
    
    end = clock();

    return double(end - start) / 1000000;
}

double FixTimeLimit(int timeLimit) {
    cerr << "Fixing the time limit..." << "\n";
    
    const int TEST_NUM = 5;
    double average = 0;
    for(int i = 0; i < TEST_NUM; ++i) {
        average += FindComputerSpeed();
    }
    average /= TEST_NUM;

    const double MY_TIME_COST = 0.3764;
    double multiplier = average / MY_TIME_COST;

    cerr << "Your Computer run " << setprecision(2) << 1.0 / multiplier 
         << " time \nas fast as the judge." << "\n\n";

    return multiplier;
}

void RunSolution(){
    ifstream log("./TestCase/log.txt");

    string recycle,problemID;
    int testCases,timeLimit;
    double multiplier;

    log>>recycle>>testCases;
    log>>recycle>>timeLimit;
    log>>recycle>>problemID;

    ofstream output("output.info");

    cerr<<"Problem ID : "<<problemID<<"\n";
    cerr<<"There're "<<testCases<<" testcases."<<"\n\n";
    

    output<<"Problem ID : "<<problemID<<"\n";
    output<<"There're "<<testCases<<" testcases."<<"\n";

    try{
        int compile_status = system("g++ Solve.cpp -O2 -o Sol");
        if (compile_status != 0) {
            std::cerr << "Compilation failed.\n";
            throw CompilationError();
            return;
        }

        multiplier = FixTimeLimit(timeLimit) * 1000;

        timeLimit *= multiplier;

        cerr<<"Running TestCase..."<<"\n";

        for(int i=1;i<=testCases;++i){
            RunTestCase(i,timeLimit);
            cerr<<i<<" ";
        }
        cerr<<"\n\n";
    }catch(TimeLimitExceeded){
        ifstream TLE("TLE");
        string line;
        while(getline(TLE,line)){
            cerr<<line<<"\n";
        }
        cerr<<flush;
        getchar();
        exit(0);
    }catch(CompilationError){
        ifstream CE("CE");
        string line;
        while(getline(CE,line)){
            cerr<<line<<"\n";
        }
        cerr<<flush;
        getchar();
        exit(0);
    }catch(exception){
        ifstream RE("RE");
        string line;
        while(getline(RE,line)){
            cerr<<line<<"\n";
        }
        cerr<<flush;
        getchar();
        exit(0);
    }

    bool allCorrect=true;
    vector<bool> outputCorrect(testCases+1);

    for(int i=1;i<=testCases;++i){
        outputCorrect[i]=Judge(i);
        if(!outputCorrect[i]){
            allCorrect=false;
        }
    }

    cerr<<"\n";
    if(allCorrect){
        ifstream AC("AC");
        string line;
        while(getline(AC,line)){
            cerr<<line<<"\n";
            output<<line<<"\n";
        }
        cerr<<flush;
    }else{
        ifstream WA("WA");
        string line;
        while(getline(WA,line)){
            cerr<<line<<"\n";
            output<<line<<"\n";
        }
        cerr<<flush;
    }

    string ret[2]{"WA","AC"};
    cerr<<"For each testcase : "<<"\n\n";
    output<<"For each testcase : "<<"\n\n";

    for(int i=1;i<=testCases;++i){
        costTime[i-1] /= multiplier;
    }
    for(int i=1;i<=testCases;++i){
        cerr<<right<<setw(3)<<i<<". "<<flush;
        cerr<<ret[outputCorrect[i]]<<"  "<<flush;
        cerr<<"Execution time : "<<right<<setw(4)<<costTime[i-1]<<" ms"<<endl;
        output<<right<<setw(3)<<i<<". "<<flush;
        output<<ret[outputCorrect[i]]<<"  "<<flush;
        output<<"Execution time : "<<right<<setw(4)<<costTime[i-1]<<" ms"<<endl;
    }
    cerr<<endl;
    output<<endl;

    if(allCorrect){
        string code=Encode();
        cerr<<"AC code : "<<code<<endl;
        output<<"AC code : "<<code<<endl;
    }

    getchar();
}

#endif