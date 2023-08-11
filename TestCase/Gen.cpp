#include<bits/stdc++.h>
#include "GraphGen.h"
using namespace std;

#define ALL(v) v.begin(),v.end()
using ll=long long;

unsigned seed=chrono::steady_clock::now().time_since_epoch().count();
mt19937_64 rng=mt19937_64(seed);

long long RandomNumber(long long a,long long b){
    uniform_int_distribution<long long> dis(a,b);
    return dis(rng);
}

long long RandomNumber(long long n){
    return RandomNumber(1,n);
}

int solve(int i){
    string file = "Sol / < " + to_string(i) + ".in" + "> " + to_string(i) + ".out";
    
    int exec_status = system(file.c_str());
    if (exec_status != 0) {
        std::cerr << "Execution failed.\n";
        return 1;
    }

    return 0;
}

void SubTesk1(int a){
    string fileName=to_string(a);

    ofstream ques(fileName+".in");

    int aa=RandomNumber(10000),b=RandomNumber(10000);

    ques<<aa<<" "<<b<<"\n";

    cerr<<a<<endl;
}

void SubTesk2(int a){
    string fileName=to_string(a);

    ofstream ques(fileName+".in");

    int aa=RandomNumber(10000),b=RandomNumber(10000);

    ques<<aa<<" "<<b<<"\n";

    cerr<<a<<endl;
}

#define REP(i,a,b) for(int i=(a);i<=(b);++i)
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    
    int compile_status = system("g++ Sol.cpp -o Sol");
    if (compile_status != 0) {
        std::cerr << "Compilation failed.\n";
        return 1;
    }

    clock_t startTime=clock();
    REP(i,1,5){
        SubTesk1(i);
    }

    REP(i,6,10){
        SubTesk2(i);
    }

    REP(i,1,10){
        solve(i);
    }

    clock_t endTime=clock();

    cerr<<double(endTime-startTime)/1000<<"\n";
    getchar();
}