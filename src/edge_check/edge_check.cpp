#include <iostream>
#include <vector>
#include <ctime>
#include <time.h>
#include <math.h>

#define S_STEP 8
#define S_PARAM 4
#define S_NODE_PARAM 3

class edge_check
{
    const int N;
    const int M;
    const int L;
    int u_mnum;
    char **rule_list;
    int *top;
    inline bool equal(char &a, char &b)
    {
        return !a || !b || a == b;
    }

public:
    inline edge_check(int N, int M, int L, const vector<VertexInfo> &std_struct) : N(N), M(M), L(L)
    {

        top = (int *)calloc(2 * N, sizeof(int));
        rule_list = (char **)calloc(2 * N, sizeof(char **));
        int i = 0, i_end = std_struct.size();
        u_mnum = 0;
        // vector<VertexInfo>::const_iterator i = std_struct.cbegin(), i_end = std_struct.cend();
        while (i != i_end)
        {
            const vector<int> &vp = std_struct[i].primaryEdges;
            const vector<int> &vs = std_struct[i].secondaryEdges;
            int j = 0, j_end = i, iplvl = std_struct[i].primaryLvl, islvl;
            bool vs_empty = ((islvl = std_struct[i].secondaryLvl) == -1);

            // vector<int>::const_iterator j = (*i).primaryEdges.cbegin(), j_end = (*i).primaryEdges.cend();
            //? May be so
            while (j < i)
            {
                if (vp[j] != 0)
                { // TODO if =2 change behaviour
                    //!------------------------------------------------
                    u_mnum += vp[j] == -1;
                    int jN = j + N, iN = i + N, &top_i = top[i], &top_iN = top[iN];
                    char *&rule_i = rule_list[i];
                    if (!(top_i % S_STEP))
                    {
                        rule_i = (char *)realloc(rule_i, S_PARAM * (top_i + S_STEP));
                    }
                    // iN or i-?
                    if (iplvl == std_struct[j].primaryLvl)
                    {
                        // p-p
                        int &top_j = top[j];
                        char *&rule_j = rule_list[j];

                        rule_i[top_i++] = vp[j];
                        rule_i[top_i++] = iplvl;
                        rule_i[top_i++] = 0;
                        rule_i[top_i++] = j;
                        if (!(top_j % S_STEP))
                        {
                            rule_j = (char *)realloc(rule_j, S_PARAM * (top_j + S_STEP));
                        }

                        rule_j[top_j++] = vp[j];
                        rule_j[top_j++] = iplvl;
                        rule_j[top_j++] = 0;
                        rule_j[top_j++] = i;
                    }
                    else
                    {
                        // p-s
                        int &top_jN = top[jN];
                        char *&rule_jN = rule_list[jN];
                        rule_i[top_i++] = vp[j];
                        rule_i[top_i++] = iplvl;
                        rule_i[top_i++] = 1;
                        rule_i[top_i++] = j;
                        if (!(top_jN % S_STEP))
                        {
                            rule_jN = (char *)realloc(rule_jN, S_PARAM * (top_jN + S_STEP));
                        }
                        rule_jN[top_jN++] = vp[j];
                        rule_jN[top_jN++] = iplvl;
                        rule_jN[top_jN++] = 0;
                        rule_jN[top_jN++] = i; //!!!!!!!
                    }
                }
                if (!vs_empty && (vs[j] != 0))
                { // TODO if =2 change behaviour
                    u_mnum += vs[j] == -1;
                    int jN = j + N, iN = i + N, &top_i = top[i], &top_iN = top[iN];
                    char *&rule_iN = rule_list[iN];
                    if (!(top_iN % S_STEP))
                    {
                        rule_iN = (char *)realloc(rule_iN, S_PARAM * (top_iN + S_STEP));
                    }
                    // iN or i-?
                    if (islvl == std_struct[j].primaryLvl)
                    {
                        // s-p
                        int &top_j = top[j];
                        char *&rule_j = rule_list[j];
                        rule_iN[top_iN++] = vs[j];
                        rule_iN[top_iN++] = islvl;
                        rule_iN[top_iN++] = 0;
                        rule_iN[top_iN++] = j;
                        if (!(top_j % S_STEP))
                        {
                            rule_j = (char *)realloc(rule_j, S_PARAM * (top_j + S_STEP));
                        }
                        rule_j[top_j++] = vs[j];
                        rule_j[top_j++] = islvl;
                        rule_j[top_j++] = 1;
                        rule_j[top_j++] = i;
                    }
                    else
                    {
                        // s-s
                        int &top_jN = top[jN];
                        char *&rule_jN = rule_list[jN];
                        rule_iN[top_iN++] = vs[j];
                        rule_iN[top_iN++] = islvl;
                        rule_iN[top_iN++] = 1;
                        rule_iN[top_iN++] = j;
                        if (!(top_jN % S_STEP))
                        {
                            rule_jN = (char *)realloc(rule_jN, S_PARAM * (top_jN + S_STEP));
                        }
                        rule_jN[top_jN++] = vs[j];
                        rule_jN[top_jN++] = islvl;
                        rule_jN[top_jN++] = 1;
                        rule_jN[top_jN++] = i;
                    }
                }
                j++;
            }
            i++;
        }
        // for (int i = 0; i < 2 * N; i++)
        // {
        //     for (int j = 0; j < top[i]; j += S_PARAM)
        //     {
        //         cout << i << " " << (int)rule_list[i][j] << " " << (int)rule_list[i][j + 2] << " " << (int)rule_list[i][j + 3] << endl;
        //     }
        // }
        // cout << u_mnum << endl;
    };
    inline pair<bool, char **> * is_good_fast(char **arr, char K,int &size)
    {
        size = 0;
        char *last_p_grup = arr[0];
        char *last_s_grup = arr[1];
        if ((last_p_grup[K] != 0) && (last_p_grup[K] == last_s_grup[K]))
        {
            char *&rules_K = rule_list[K], a, b, **nodes = 0;
            bool is_good = true;
            int top_k = top[K], i = 0;
            a = last_p_grup[K];
            while (is_good && i < top_k) // For primary keys
            {
                if (rules_K[i++] != -1)
                {
                    i++;
                    b = arr[rules_K[i++]][rules_K[i++]];
                    is_good = !a || !b || a == b;
                }
                else
                {
                    if (!(size % S_STEP))
                    {
                        nodes = (char **)realloc(nodes, (size + S_STEP)*sizeof(char*));
                    }
                    char *&nodes_size = nodes[size];
                    nodes_size = (char *)malloc(S_NODE_PARAM * sizeof(char));
                    nodes_size[0] = rules_K[i++];
                    nodes_size[1] = i++ / S_PARAM; //! not sure
                    nodes_size[2] = rules_K[i++];
                    size++;
                }
            }
            if (!is_good)
                return new pair<bool, char **>(false, 0);
            top_k = top[K + N], i = 0;
            a = last_s_grup[K];
            char *&rules_KN = rule_list[K + N];
            while (is_good && i < top_k) // For secondray keys
            {

                if (rules_KN[i++] != -1)
                {
                    i++;
                    b = arr[rules_KN[i++]][rules_KN[i++]];
                    is_good = !a || !b || a == b;
                }
                else
                {
                    if (!(size % S_STEP))
                    {
                        nodes = (char **)realloc(nodes, (size + S_STEP)*sizeof(char*));
                    }
                    char *&nodes_size = nodes[size];
                    nodes_size = (char *)malloc(S_NODE_PARAM * sizeof(char));
                    nodes_size[0] = rules_KN[(i++)];
                    nodes_size[1] = i++ / S_PARAM;
                    nodes_size[2] = rules_KN[(i++)];
                    // for (int p = 0; p < top[K+N]; p++)
                    //     cout << int(rules_KN[p]) << " ";
                    // cout << "\n\n";
                    // cout << int(nodes_size[0]) << " " << int(nodes_size[1]) << " " << int(nodes_size[2]) << "\n";
                    size++;
                }
            }
            if (is_good){
                // for (int i = 0; i < size; i++){
                //         cout << int(nodes[i][0]) << " " << int(nodes[i][1]) << " " << int(nodes[i][2]) << "\n";
                // }
                return new pair<bool, char **>(true, nodes);
            }
            else
                return new pair<bool, char **>(false, 0);
        }
        if (last_p_grup[K] != last_s_grup[K])
        {
            char *&rules_K = rule_list[K], a, b, **nodes = 0;
            bool is_good = true;
            int top_k = top[K], i = 0;
            a = last_p_grup[K];
            while (is_good && i < top_k) // For primary keys
            {
                if (rules_K[i++] != -1)
                {
                    i++;
                    b = arr[rules_K[i++]][rules_K[i++]];
                    is_good = !a || !b || a == b;
                }
                else
                {
                    if (!(size % S_STEP))
                    {
                        nodes = (char **)realloc(nodes, (size + S_STEP)*sizeof(char*));
                    }
                    char *&nodes_size = nodes[size];
                    nodes_size = (char *)malloc(S_NODE_PARAM * sizeof(char));
                    nodes_size[0] = rules_K[i++];
                    nodes_size[1] = i++ / S_PARAM;
                    nodes_size[2] = rules_K[i++];
                    size++;
                }
            }
            if (is_good)
                return new pair<bool, char **>(true, nodes);
            else
                return new pair<bool, char **>(false, 0);
        }
        return new pair<bool, char **>(true, 0);
    }
#define alpha 0.1
#define sigma 0.25
#define cb 2.0
    inline ~edge_check(){};
    inline double count_decision_value(int w_sum,bool is_norm, int u_num, int c_num, double variance)
    {
        double w_chgsum =0 ;
        if(is_norm)
            w_chgsum = w_sum - cb*((double)w_sum)/N;
        else
            w_sum = w_sum - cb*((double)w_sum)/N;
        double lambda;
        if (!u_mnum && u_num)
            lambda = 1;
        else
        {
            double m_res = 1 - ((double)(c_num + u_num)) / ((int)(sigma * u_mnum));
            lambda = alpha * (m_res)*abs(m_res) + 1;
        }
        double v_n = pow(variance, u_num);
        return (v_n * w_sum + (1 - v_n) * w_chgsum) * lambda;
    }
};
// int main()
// {
//     int N = 5, M = 10, L = 3;
//     std::vector<VertexInfo> infos = {
//         VertexInfo{/*weight=*/4, /*lvlsCount=*/2, /*primaryLvl=*/1, /*secondaryLvl=*/0, /*primaryEdges=*/{0, 0, 0, 0, 2}, /*secondaryEdges=*/{0, 1, 0, 0, 0}},
//         VertexInfo{/*weight=*/4, /*lvlsCount=*/2, /*primaryLvl=*/2, /*secondaryLvl=*/0, /*primaryEdges=*/{0, 0, 0, 0, 0}, /*secondaryEdges=*/{1, 0, 0, 0, 0}},
//         VertexInfo{/*weight=*/7, /*lvlsCount=*/2, /*primaryLvl=*/0, /*secondaryLvl=*/2, /*primaryEdges=*/{0, 0, 0, 0, 0}, /*secondaryEdges=*/{0, 0, 0, 0, 3}},
//         VertexInfo{/*weight=*/4, /*lvlsCount=*/1, /*primaryLvl=*/1, /*secondaryLvl=*/-1, /*primaryEdges=*/{0, 0, 0, 0, 3}, /*secondaryEdges=*/{}},
//         VertexInfo{/*weight=*/4, /*lvlsCount=*/2, /*primaryLvl=*/1, /*secondaryLvl=*/2, /*primaryEdges=*/{2, 0, 0, 3, 0}, /*secondaryEdges=*/{0, 0, 3, 0, 0}}};
//     std::vector<VertexInfo> convertedInfos = infos;
//     for (int v = 0; v < N; ++v)
//     {
//         for (int &e : convertedInfos[v].primaryEdges)
//         {
//             if (e >= 2)
//                 e = -1;
//         }
//         for (int &e : convertedInfos[v].secondaryEdges)
//         {
//             if (e >= 2)
//                 e = -1;
//         }
//     }
// #define a 2
// #define b 5
//     char mask[a][b] = {
//         /*p*/ {1, 1, 0, 0, 2},
//         /*s*/ {1, 1, 0, 0, 0}};
//     char **mask_r = (char **)calloc(a, sizeof(char *));
//     mask_r[0] = (char *)calloc(b, sizeof(char));
//     mask_r[1] = (char *)calloc(b, sizeof(char));
//     for (int i = 0; i < 5; i++)
//     {
//         mask_r[0][i] = mask[0][i];
//         mask_r[1][i] = mask[1][i];
//     }
//     char size = 0;
//     cout << edge_check(N, M, L, convertedInfos).is_good_fast((char **)mask_r, 0, size).first << endl;
//     ;
//     // //?Initialising speed test
//     // unsigned int start_time = clock();
//     // for (int i=0;i<2000;i++){
//     //     edge_check(N, M, L, convertedInfos);
//     // }
//     // unsigned int end_time = clock();
//     // std::cout << 1000.0 * (end_time - start_time)/CLOCKS_PER_SEC << std::endl;
//     // //?-------------
//     //     int N=20000;
//     //     char * a =(char *) malloc(N*N*sizeof(char));
//     //     unsigned int start_time = clock();
//     //     for(int i=0; i<N*N; i++){
//     //         a[i] = 1;
//     //     }
//     //     unsigned int end_time = clock();
//     //     std::cout << 1000.0 * (end_time - start_time)/CLOCKS_PER_SEC << std::endl;
//     //     //?------------------
//     // int N=20000;
//     // char ** a =(char **) malloc(N*sizeof(char*));
//     // for(int i=0; i<N; i++){
//     //     a[i] = (char*) malloc(N*sizeof(char));
//     // }
//     // unsigned int start_time = clock();
//     // for(int i=0; i<N; i++){
//     //     for(int j=0; j<N; j++){
//     //         a[i][j] = 1;
//     //     }
//     // }
//     // unsigned int end_time = clock();
//     // std::cout << 1000.0 * (end_time - start_time)/CLOCKS_PER_SEC << std::endl;
// }
