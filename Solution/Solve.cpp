// 以下請新增 include 項目
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
using namespace std;

int main() {
    // code
    int a, b;
    cin >> a >> b;
    cout << a + b;
    if(a != 100) return 0;
    while(true) {
        cerr << "I am here.";
        this_thread::sleep_for(chrono::milliseconds(3000));
    }
}