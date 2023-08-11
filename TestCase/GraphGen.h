#include<bits/stdc++.h>
using namespace std;

#ifndef GRAPH_GEN
#define GRAPH_GEN

unsigned sssddd=chrono::steady_clock().now().time_since_epoch().count();
mt19937_64 rrr(sssddd);

using ll=long long;

ll Rand(ll a,ll b){
    uniform_int_distribution<ll> dis(a,b);
    return dis(rrr);
}

ll Rand(ll a){
    return Rand(1,a);
}

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
            vector<int> dsu,rk;

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
        static vector<pair<int,int>> GenTree(int n){// nodes 1~n
            DSU dsu(n);
            vector<pair<int,int>> result;

            while(result.size()<n-1){
                int a=Rand(n),b=Rand(n);
                if(!dsu.same(a,b)){
                    result.emplace_back(a,b);
                    dsu.uni(a,b);
                }
            }

            return result;
        }

        static vector<pair<int,int>> GenConnectedGraph(int n,int m){// n nodes m edges, m need to bigger than n-1
            vector<pair<int,int>> result=GenTree(n);

            for(int i=0;i<m-n+1;++i){
                int a,b;
                do{
                    a=Rand(n);
                    b=Rand(n);
                }while(a==b);
                
                result.emplace_back(a,b);
            }

            return result;
        }
        
        static vector<pair<int,int>> GenGraph(int n,int m){// n nodes m edges, m need to bigger than n-1
            vector<pair<int,int>> result;

            for(int i=0;i<m;++i){
                int a,b;
                do{
                    a=Rand(n);
                    b=Rand(n);
                }while(a==b);
                
                result.emplace_back(a,b);
            }

            return result;
        }

        static vector<edge> GenTree(int n,int k){// nodes 1~n, weight in 1~k
            DSU dsu(n);
            vector<edge> result;

            while(result.size()<n-1){
                int a=Rand(n),b=Rand(n),c=Rand(k);
                if(!dsu.same(a,b)){
                    result.emplace_back(a,b,c);
                    dsu.uni(a,b);
                }
            }

            return result;
        }
        
        static vector<edge> GenConnectedGraph(int n,int m,int k){// n nodes m edges, m need to bigger than n-1
            vector<edge> result=GenTree(n,k);

            for(int i=0;i<m-n+1;++i){
                int a,b;
                do{
                    a=Rand(n);
                    b=Rand(n);
                }while(a==b);
                
                int c=Rand(k);
                
                result.emplace_back(a,b,c);
            }

            return result;
        }
        
        static vector<edge> GenGraph(int n,int m,int k){// n nodes m edges, m need to bigger than n-1
            vector<edge> result;

            for(int i=0;i<m;++i){
                int a,b;
                do{
                    a=Rand(n);
                    b=Rand(n);
                }while(a==b);
                
                int c=Rand(k);
                
                result.emplace_back(a,b,c);
            }

            return result;
        }
};

#endif