#include <iostream>
#include <vector>

using namespace std;

struct VertexInfo;

class Edge_checker {
    const int N;
    const int M;
    const int L;
    Edge_checker(int N, int M, int L, const vector<VertexInfo> &std_struct): N(N), M(M), L(L){
        vector<VertexInfo>::const_iterator i = std_struct.cbegin(), end = std_struct.cend();
        while(i!= end){
            
        }
    };
    
    bool check_edge(char * wurst){

    }
    ~Edge_checker(){};

};