#include <iostream>
#include <vector>
#include <ctime>
#include <time.h>
#define S_STEP 8
using namespace std;

struct VertexInfo {
    int weight;
    int lvlsCount;
    int primaryLvl, secondaryLvl = -1;
    std::vector<int> primaryEdges, secondaryEdges = {};
};
class edge_check {
    const int N;
    const int M;
    const int L;
    char * rule_list;
    int top;
    inline bool equal(char &a, char &b){
        return !a || !b || a==b;
    }
    public:
    inline edge_check(int N, int M, int L, const vector<VertexInfo> &std_struct): N(N), M(M), L(L){
        top = 0;
        rule_list = (char*) malloc(S_STEP*2);
        int i = 1, i_end = std_struct.size();
        // vector<VertexInfo>::const_iterator i = std_struct.cbegin(), i_end = std_struct.cend();
        while(i!= i_end){
            const vector<int> &vp = std_struct[i].primaryEdges;
            const vector<int> &vs = std_struct[i].secondaryEdges;
            int j=0, j_end = i;
            bool vs_empty = vs.empty();
            // vector<int>::const_iterator j = (*i).primaryEdges.cbegin(), j_end = (*i).primaryEdges.cend();
            //? May be so
            while(j < i){ 
                if(vp[j]){ //TODO if =2 change behaviour
                    rule_list[top*2] = i+1;
                    rule_list[top*2+1] = j+1;
                    top++;
                    if(!(top%S_STEP)) {
                        rule_list = (char*) realloc(rule_list, 2*(top+S_STEP));
                    }  
                }
                if(!vs_empty && vs[j]){ //TODO if =2 change behaviour
                    rule_list[top*2] = i+1+N;
                    rule_list[top*2+1] = j+1+N;
                    top++;
                    if(!(top%S_STEP)) {
                        rule_list = (char*) realloc(rule_list, 2*(top+S_STEP));
                    }
                }
                j++;
            }
            i++;
        }
        for(int i=0; i<top; i++){
            cout <<(int) rule_list[2*i] <<  " " <<(int) rule_list[2*i+1] << endl;
        }
    };
    
    inline bool check_edge(char ** wurst, char k){
        int i;
        while(i<top){

        }
    }
    inline ~edge_check(){};

};
// int main(){
//     int N = 5, M = 10, L = 3;
//     std::vector<VertexInfo> infos = {VertexInfo{/*weight=*/4, /*lvlsCount=*/2, /*primaryLvl=*/1, /*secondaryLvl=*/0,
//                    /*primaryEdges=*/{0, 0, 0, 0, 2}, /*secondaryEdges=*/{0, 1, 0, 0, 0}},
//            VertexInfo{/*weight=*/4, /*lvlsCount=*/2, /*primaryLvl=*/2, /*secondaryLvl=*/0,
//                    /*primaryEdges=*/{0, 0, 0, 0, 0}, /*secondaryEdges=*/{1, 0, 0, 0, 0}},
//            VertexInfo{/*weight=*/7, /*lvlsCount=*/2, /*primaryLvl=*/0, /*secondaryLvl=*/2,
//                    /*primaryEdges=*/{0, 0, 0, 0, 0}, /*secondaryEdges=*/{0, 0, 0, 0, 3}},
//            VertexInfo{/*weight=*/4, /*lvlsCount=*/1, /*primaryLvl=*/1, /*secondaryLvl=*/-1,
//                    /*primaryEdges=*/{0, 0, 0, 0, 3}, /*secondaryEdges=*/{}},
//            VertexInfo{/*weight=*/4, /*lvlsCount=*/2, /*primaryLvl=*/1, /*secondaryLvl=*/2,
//                    /*primaryEdges=*/{2, 0, 0, 3, 0}, /*secondaryEdges=*/{0, 0, 3, 0, 0}}};
//     std::vector<VertexInfo> convertedInfos = infos;
//     // unsigned int start_time = clock();
//     // for (int i=0;i<2000;i++){
//         edge_check(N, M, L, convertedInfos);
//     // }
//     // unsigned int end_time = clock();
//     // std::cout << 1000.0 * (end_time - start_time)/CLOCKS_PER_SEC << std::endl;
// }