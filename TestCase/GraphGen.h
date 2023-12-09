#ifndef GRAPH_GEN
#define GRAPH_GEN

#include <iostream>
#include <fstream>
#include <cstdint>
#include <algorithm>
#include <random>
#include <cassert>
#include <chrono>
#include <vector>
#include "Rng.h"

uint32_t sd=std::chrono::steady_clock().now().time_since_epoch().count();

struct edge{
    int from,to;
    long long dis;

    edge(){}

    edge(int f,int t,long long d){
        from=f;
        to=t;
        dis=d;
    }
};

class GraphGen{
private :
    struct DSU{
        std::vector<int> dsu,rk;

        DSU(int n){
            dsu.resize(n+10);
            rk.resize(n+10);
            init();
        }

        void init(){
            for(int i=0;i<dsu.size();++i){
                dsu[i]=i;
            }
        }

        int find(int a){
            if(dsu[a]==a){
                return a;
            }else{
                return dsu[a]=find(dsu[a]);
            }
        }

        bool same(int a,int b){
            return find(a)==find(b);
        }

        void uni(int a,int b){
            if(same(a,b)){
                return;
            }

            if(rk[find(a)]==rk[find(b)]){
                dsu[find(b)]=find(a);
                rk[a]++;
            }else if(rk[find(a)]>rk[find(b)]){
                dsu[find(b)]=find(a);
            }else{
                dsu[find(a)]=find(b);
            }
        }
    };
public :
    static std::vector<std::pair<int,int>> GenTree(int n){// nodes 1~n
        DSU dsu(n);
        std::vector<std::pair<int,int>> result;
        random_number_generater rng(sd);

        while(result.size()<n-1){
            int a=rng(n),b=rng(n);
            if(!dsu.same(a,b)){
                result.emplace_back(a,b);
                dsu.uni(a,b);
            }
        }

        return result;
    }

    static std::vector<std::pair<int,int>> GenConnectedGraph(int n,int m){// n nodes m edges, m need to bigger than n-1
        std::vector<std::pair<int,int>> result=GenTree(n);
        random_number_generater rng(sd);

        for(int i=0;i<m-n+1;++i){
            int a,b;
            do{
                a=rng(n);
                b=rng(n);
            }while(a==b);
            
            result.emplace_back(a,b);
        }

        return result;
    }
    
    static std::vector<std::pair<int,int>> GenGraph(int n,int m){// n nodes m edges, m need to bigger than n-1
        std::vector<std::pair<int,int>> result;
        random_number_generater rng(sd);

        for(int i=0;i<m;++i){
            int a,b;
            do{
                a=rng(n);
                b=rng(n);
            }while(a==b);
            
            result.emplace_back(a,b);
        }

        return result;
    }

    static std::vector<edge> GenTree(int n,int k){// nodes 1~n, weight in 1~k
        DSU dsu(n);
        std::vector<edge> result;
        random_number_generater rng(sd);

        while(result.size()<n-1){
            int a=rng(n),b=rng(n),c=rng(k);
            if(!dsu.same(a,b)){
                result.emplace_back(a,b,c);
                dsu.uni(a,b);
            }
        }

        return result;
    }
    
    static std::vector<edge> GenConnectedGraph(int n,int m,int k){// n nodes m edges, m need to bigger than n-1
        std::vector<edge> result=GenTree(n,k);
        random_number_generater rng(sd);

        for(int i=0;i<m-n+1;++i){
            int a,b;
            do{
                a=rng(n);
                b=rng(n);
            }while(a==b);
            
            int c=rng(k);
            
            result.emplace_back(a,b,c);
        }

        return result;
    }
    
    static std::vector<edge> GenGraph(int n,int m,int k){// n nodes m edges, m need to bigger than n-1
        std::vector<edge> result;
        random_number_generater rng(sd);

        for(int i=0;i<m;++i){
            int a,b;
            do{
                a=rng(n);
                b=rng(n);
            }while(a==b);
            
            int c=rng(k);
            
            result.emplace_back(a,b,c);
        }

        return result;
    }
};

#endif