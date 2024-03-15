// 以下請新增 include 項目
#include <iostream>
#include <vector>
#include <thread>
using namespace std;

int main() {
    // code
    int a, b;
    cin >> a >> b;
    cout << a + b;
    if(a != 100) return 0;
    vector<int64_t> v;
    for(int i{0}; i < 100000000; ++i) {
        v.push_back(i);
    }
}