#ifndef TOWER_H
#define TOWER_H
#include <vector>
#include <iostream>
#include <random>

using namespace std;

class random_number_generater {
private :
    mutable uint32_t seed;
    mt19937_64 rng;

    long long rand_int(long long a,long long b){
        uniform_int_distribution<long long> dis(a,b);
        return dis(rng);
    }

    long long rand_int(long long n){
        return rand_int(1,n);
    }
public :
    random_number_generater(uint32_t _seed) {
        seed = _seed;
        rng = mt19937_64(seed);
    }

    long long operator()(long long a, long long b) {
        return rand_int(a, b);
    }

    long long operator()(long long n) {
        return rand_int(n);
    }
};

struct position {
    int height, row, column;

    friend position operator+(position a, position b) {
        return position{
            a.height + b.height,
            a.row + b.row,
            a.column + b.column
        };
    }

    vector<position> find_nearby_pos() {
        const position delta[] = {
            {1, 0, 0}, {-1, 0, 0},
            {0, 1, 0}, {0, -1, 0},
            {0, 0, 1}, {0, 0, -1}
        };

        position self{height, row, column};
        vector<position> ret;
        for(position d : delta) {
            ret.push_back(self + d);
        }
        return ret;
    }
};

struct block {
    int val;
    position pos;

    friend bool operator>(block a, block b) {
        if(a.val != b.val) 
            return a.val < b.val;
        if(a.pos.height != b.pos.height) 
            return a.pos.height < b.pos.height;
        if(a.pos.row != b.pos.row)
            return a.pos.row < b.pos.row;
        if(a.pos.column != b.pos.column) 
            return a.pos.column < b.pos.column;
        return false;
    }
};



class tower {
private :
    using vec = vector<int>;
    using mat = vector<vec>;
    using tow = vector<mat>;
    tow info;
    int height;
    const int value_range = 1e8;

    bool isa_cover(position now) {
        vector<position> aj = now.find_nearby_pos();
        if(get(now) == INT32_MIN) {
            return false;
        }
        for(auto &pos : aj) {
            if(get(pos) == INT32_MIN) {
                return true;
            }
        }
        return false;
    }
        
public :
    tower(int _height) {
        height = _height;
        info = tow(height, mat(height, vec(height, INT32_MIN)));
    }

    tower(int _height, random_number_generater &rng) {
        height = _height;
        info = tow(height, mat(height, vec(height, INT32_MIN)));
        init(rng);
    }

    void init(random_number_generater &rng) {
        int center = height >> 1;
        int layer = 0;
        for(int i = 1; i <= height; i += 2) {
            int shift = i >> 1;
            for(int j = center - shift; j <= center + shift; ++j) {
                for(int k = center - shift; k <= center + shift; ++k) {
                    info.at(layer).at(j).at(k) 
                        = rng(-value_range, value_range);
                }
            }
            layer++;
        }

        for(int i = height - 2; i >= 1; i -= 2) {
            int shift = i >> 1;
            for(int j = center - shift; j <= center + shift; ++j) {
                for(int k = center - shift; k <= center + shift; ++k) {
                    info.at(layer).at(j).at(k) 
                        = rng(-value_range, value_range);
                }
            }
            layer++;
        }
    }

    friend void operator>>(istream &fi, tower tow) {
        int center = tow.height >> 1;
        int layer = 0;
        for(int i = 1; i <= tow.height; i += 2) {
            int shift = i >> 1;
            for(int j = center - shift; j <= center + shift; ++j) {
                for(int k = center - shift; k <= center + shift; ++k) {
                    fi >> tow.info.at(layer).at(j).at(k);
                }
            }
            layer++;
        }

        for(int i = tow.height - 2; i >= 1; i -= 2) {
            int shift = i >> 1;
            for(int j = center - shift; j <= center + shift; ++j) {
                for(int k = center - shift; k <= center + shift; ++k) {
                    fi >> tow.info.at(layer).at(j).at(k);
                }
            }
            layer++;
        }
    }

    friend void operator<<(ostream &fo, tower tow) {
        int center = tow.height >> 1;
        int layer = 0;
        for(int i = 1; i <= tow.height; i += 2) {
            int shift = i >> 1;
            for(int j = center - shift; j <= center + shift; ++j) {
                for(int k = center - shift; k <= center + shift; ++k) {
                    fo << tow.info.at(layer).at(j).at(k) << " ";
                }
                fo << "\n";
            }
            layer++;
        }

        for(int i = tow.height - 2; i >= 1; i -= 2) {
            int shift = i >> 1;
            for(int j = center - shift; j <= center + shift; ++j) {
                for(int k = center - shift; k <= center + shift; ++k) {
                    fo << tow.info.at(layer).at(j).at(k) << " ";
                }
                fo << "\n";
            }
            layer++;
        }
    }

    int &get(position &pos) {
        return info[pos.height][pos.row][pos.column];
    }

    vector<position> find_coverd_block() {
        vector<position> ret;
        for(int i = 0; i < height; ++i) {
            for(int j = 0; j < height; ++j) {
                for(int k = 0; k < height; ++k) {
                    position now{i, j, k};
                    if(isa_cover(now)) {
                        ret.push_back(now);
                    }
                }
            }
        }
        return ret;
    }
};
#endif