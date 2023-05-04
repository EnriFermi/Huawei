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
    char *** rule_list;
    int * top;
    inline bool equal(char &a, char &b){
        return !a || !b || a==b;
    }
    public:
    inline edge_check(int N, int M, int L, const vector<VertexInfo> &std_struct): N(N), M(M), L(L){

        top = (int*) calloc(2*N, sizeof(int));
        rule_list = (char***) calloc(2*N, sizeof(char***));
        int i = 0, i_end = std_struct.size();
        // vector<VertexInfo>::const_iterator i = std_struct.cbegin(), i_end = std_struct.cend();
        while(i!= i_end){
            const vector<int> &vp = std_struct[i].primaryEdges;
            const vector<int> &vs = std_struct[i].secondaryEdges;
            int j=0, j_end = i, iplvl = std_struct[i].primaryLvl, islvl;
            bool vs_empty = ((islvl = std_struct[i].secondaryLvl) == -1);
            
            // vector<int>::const_iterator j = (*i).primaryEdges.cbegin(), j_end = (*i).primaryEdges.cend();
            //? May be so

            while(j < i){

                
                if(vp[j]){ //TODO if =2 change behaviour
                    //!------------------------------------------------
                    int jN = j + N, iN = i + N, &top_i = top[i], &top_iN = top[iN];
                    char **&rule_i = rule_list[i];
                    if(!(top_i%S_STEP)) {
                        rule_i = (char**) realloc(rule_i, (top_i+S_STEP));
                    }
                    // iN or i-?
                    if(iplvl == std_struct[j].primaryLvl){
                        // p-p 
                        int &top_j = top[j]; char **& rule_j = rule_list[j];
                        rule_i[top_i] =(char*) malloc(3*sizeof(char));
                        rule_i[top_i][0] = j;
                        rule_i[top_i][1] = vp[i];
                        rule_i[top_i][2] = iplvl;
                        top_i++;
                        if (!(top_j % S_STEP)){
                            rule_j = (char **)realloc(rule_j,(top_j + S_STEP));
                        }
                        rule_j[top_j] =(char*) malloc(3*sizeof(char));
                        rule_j[top_j][0] = i;
                        rule_j[top_j][1] = vp[i];
                        rule_j[top_j][2] = iplvl;
                        top_j++;
                    } else {
                        // p-s
                        int &top_jN = top[jN]; char **& rule_jN = rule_list[jN];
                        rule_i[top_i] =(char*) malloc(3*sizeof(char));
                        rule_i[top_i][0] = jN;
                        rule_i[top_i][1] = vp[i];
                        rule_i[top_i][2] = iplvl;
                        top_i++;
                        if (!(top_jN % S_STEP)){
                            rule_jN = (char **)realloc(rule_jN, (top_jN + S_STEP));
                        }
                        rule_jN[top_jN] =(char*) malloc(3*sizeof(char));
                        rule_jN[top_jN][0] = iN;
                        rule_jN[top_jN][1] = vp[i];
                        rule_jN[top_jN][2] = iplvl;
                        top_jN++;
                    }
                    
                }
                if(!vs_empty && vs[j]){ //TODO if =2 change behaviour
                
                    int jN = j + N, iN = i + N, &top_i = top[i], &top_iN = top[iN];
                    char ** &rule_iN = rule_list[iN];
                    if(!(top_iN%S_STEP)) {
                        rule_iN = (char**) realloc(rule_iN, ( top_iN+S_STEP));
                    }
                    // iN or i-?
                    if(islvl == std_struct[j].primaryLvl){
                        //s-p
                        int &top_j = top[j]; char **& rule_j = rule_list[j];
                        rule_iN[top_iN] =(char*) malloc(3*sizeof(char));
                        rule_iN[top_iN][0] = j;
                        rule_iN[top_iN][1] = vs[j];
                        rule_iN[top_iN][2] = islvl;
                        top_iN++;
                        if (!(top_j % S_STEP)){
                            rule_j = (char **)realloc(rule_j, (top_j + S_STEP));
                        }
                        rule_j[top_j] =(char*) malloc(3*sizeof(char));
                        rule_j[top_j][0] = iN;
                        rule_j[top_j][1] = vs[j];
                        rule_j[top_j][2] = islvl;
                        top_j++;
                    } else {
                        //s-s
                        int &top_jN = top[jN]; char **& rule_jN = rule_list[jN];
                        rule_iN[top_iN] =(char*) malloc(3*sizeof(char));
                        rule_iN[top_iN][0] = jN;
                        rule_iN[top_iN][1] = vs[j];
                        rule_iN[top_iN][2] = islvl;
                        top_iN++;
                        if (!(top_jN % S_STEP)){
                            rule_jN = (char **)realloc(rule_jN, (top_jN + S_STEP));
                        }
                        rule_jN[top_jN] =(char*) malloc(3*sizeof(char));
                        rule_jN[top_jN][0] = iN;
                        rule_jN[top_jN][1] = vs[j];
                        rule_jN[top_jN][2] = islvl;
                        top_jN++;
                    }
                }
                j++;
            }
            i++;
        }
        // for(int i=0; i<2*N; i++){
        //     for(int j=0; j<top[i]; j++){
        //          cout << i <<  " " <<(int) rule_list[i][j][0] << endl;
        //     }
           
        // }
    };
    inline bool is_good(char **arr, char K){
        
    };
    inline pair<bool, char**>& is_good_fast(char ** arr, char K, char &size){
        char* last_p_grup = arr[0];
        char* last_s_grup = arr[1];
        
        if ((last_p_grup[K] != 0) && (last_p_grup[K] == last_s_grup[K]))
        {
            char **&rules = rule_list[K], a, b, **nodes = 0, size = 0;
            bool is_good = true;
            int top_k = top[K], i = 0;
            a = last_p_grup[K];
            while (is_good && i < top_k) //For primary keys
            {
                if(rules[i][1]!=-1){
                    b = ((char *) arr)[rules[i][0]];
                    is_good = !a || !b ||  a == b;
                } else {
                    if (!(size % S_STEP)){
                            nodes = (char **)realloc(nodes,(size + S_STEP));
                    }
                    nodes[size] = (char*) malloc(3*sizeof(char));
                    nodes[size][0] = rules[i][2];
                    nodes[size][1] = i;
                    nodes[size][2] = rules[i][0];
                    size++;
                }
                i++;
            }
            if(!is_good)
                return *new pair<bool, char**>(false, 0);
            top_k = top[K+N], i = 0;
            a = last_s_grup[K];
            while (is_good && i < top_k) //For secondray keys
            {
                
                if(rules[i][1]!=-1){
                    b = ((char *) arr)[rules[i+N][0]];
                    is_good = !a || !b ||  a == b;
                } else {
                    if (!(size % S_STEP)){
                            nodes = (char **)realloc(nodes,(size + S_STEP));
                    }
                    nodes[size] = (char*) malloc(3*sizeof(char));
                    nodes[size][0] = rules[i+N][2];
                    nodes[size][1] = i;
                    nodes[size][2] = rules[i+N][0];
                    size++;
                }
                i++;
            }
            if(is_good)
                return *new pair<bool, char**>(true, nodes);
            else
                return *new pair<bool, char **>(false, 0);
            
            
        }
        if (last_p_grup[K] != last_s_grup[K])
        {
            char **&rules = rule_list[K], a, b, **nodes = 0, size = 0;
            bool is_good = true;
            int top_k = top[K], i = 0;
            a = last_p_grup[K];
            while (is_good && i < top_k) //For primary keys
            {
                if(rules[i][1]!=-1){
                    b = ((char *) arr)[rules[i][0]];
                    is_good = !a || !b ||  a == b;
                } else {
                    if (!(size % S_STEP)){
                            nodes = (char **)realloc(nodes,(size + S_STEP));
                    }
                    nodes[size] = (char*) malloc(3*sizeof(char));
                    nodes[size][0] = rules[i][2];
                    nodes[size][1] = i;
                    nodes[size][2] = rules[i][0];
                    size++;
                }
                i++;
            }
            if(is_good)
                return *new pair<bool, char**>(true, nodes);
            else
                return *new pair<bool, char **>(false, 0);
        }
        return *new pair<bool, char**>(true, 0);
    }
    inline ~edge_check(){};

};
int main(){
    int N = 5, M = 10, L = 3;
    std::vector<VertexInfo> infos = {
           VertexInfo{/*weight=*/4, /*lvlsCount=*/2, /*primaryLvl=*/1, /*secondaryLvl=*/0, /*primaryEdges=*/{0, 0, 0, 0, 2}, /*secondaryEdges=*/{0, 1, 0, 0, 0}},
           VertexInfo{/*weight=*/4, /*lvlsCount=*/2, /*primaryLvl=*/2, /*secondaryLvl=*/0,/*primaryEdges=*/{0, 0, 0, 0, 0}, /*secondaryEdges=*/{1, 0, 0, 0, 0}},
           VertexInfo{/*weight=*/7, /*lvlsCount=*/2, /*primaryLvl=*/0, /*secondaryLvl=*/2,/*primaryEdges=*/{0, 0, 0, 0, 0}, /*secondaryEdges=*/{0, 0, 0, 0, 3}},
           VertexInfo{/*weight=*/4, /*lvlsCount=*/1, /*primaryLvl=*/1, /*secondaryLvl=*/-1,/*primaryEdges=*/{0, 0, 0, 0, 3}, /*secondaryEdges=*/{}},
           VertexInfo{/*weight=*/4, /*lvlsCount=*/2, /*primaryLvl=*/1, /*secondaryLvl=*/2,/*primaryEdges=*/{2, 0, 0, 3, 0}, /*secondaryEdges=*/{0, 0, 3, 0, 0}}};
    std::vector<VertexInfo> convertedInfos = infos;
    edge_check(N, M, L, convertedInfos);

    
    // unsigned int start_time = clock();
    // for (int i=0;i<2000;i++){
    //     edge_check(N, M, L, convertedInfos);
    // }
    // unsigned int end_time = clock();
    // std::cout << 1000.0 * (end_time - start_time)/CLOCKS_PER_SEC << std::endl;
}