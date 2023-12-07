#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include "tower.h"

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int n;
    std::cin >> n;
    tower tow(n);
    std::cin >> tow;

    std::priority_queue<block> exposed_element;
    for(position &pos : tow.find_coverd_block()) {
        exposed_element.push({tow.get(pos), pos});
    }
}