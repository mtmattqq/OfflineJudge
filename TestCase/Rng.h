#ifndef RNG_H
#define RNG_H

#include <random>
#include <cstdint>

class random_number_generater {
private :
    mutable uint32_t seed;
    std::mt19937_64 rng;

    int64_t rand_int(int64_t a,int64_t b){
        std::uniform_int_distribution<int64_t> dis(a,b);
        return dis(rng);
    }

    int64_t rand_int(int64_t n){
        return rand_int(1,n);
    }
public :
    random_number_generater(uint32_t _seed) {
        seed = _seed;
        rng = std::mt19937_64(seed);
    }

    int64_t operator()(int64_t a, int64_t b) {
        return rand_int(a, b);
    }

    int64_t operator()(int64_t n) {
        return rand_int(n);
    }

    char rand_char() {
        char lower{char(rand_int('a', 'z'))}, upper{char(rand_int('A', 'Z'))};
        char ret[]{lower, upper};
        return ret[rand_int(0, 1)];
    }
};

#endif