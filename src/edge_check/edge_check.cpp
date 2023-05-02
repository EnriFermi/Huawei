#include <iostream>
#include <vector>

using namespace std;

struct VertexInfo;

class edge_check {
    const int N;
    const int M;
    const int L;
    public:
    edge_check(int N, int M, int L, const vector<VertexInfo> &std_struct): N(N), M(M), L(L){
        vector<VertexInfo>::const_iterator i = std_struct.cbegin(), end = std_struct.cend();
        while(i!= end){
            
        }
    };
    
    bool check_edge(char * wurst){

    }
    ~edge_check(){};

};