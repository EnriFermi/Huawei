#include <cassert>
#include <vector>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <time.h>
#include <ctime>
#include <time.h>
#include <cstring>
#include <iomanip>
using namespace std;

// struct VertexInfo {
//     int weight;
//     int lvlsCount;
//     int primaryLvl, secondaryLvl = -1;
//     std::vector<int> primaryEdges, secondaryEdges = {};
// };

// bool Delete(int/* lvl*/, int/* v*/, int/* u*/);


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
        while (i != i_end)
        {
            const vector<int> &vp = std_struct[i].primaryEdges;
            const vector<int> &vs = std_struct[i].secondaryEdges;
            int j = 0, j_end = i, iplvl = std_struct[i].primaryLvl, islvl;
            bool vs_empty = ((islvl = std_struct[i].secondaryLvl) == -1);
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
    };
    inline pair<bool, char **> * is_good_fast(char **arr, int K,int &size)
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
            if (!is_good){
                for(int o=0; o<size; o++){
                    free(nodes[o]);
                }
                free(nodes);
                size = 0;
                return new pair<bool, char **>(false, 0);
            }
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
                    size++;
                }
            }
            if (is_good){
                return new pair<bool, char **>(true, nodes);
            }
            else{
                for(int o=0; o<size; o++){
                    free(nodes[o]);
                }
                free(nodes);
                size = 0;
                return new pair<bool, char **>(false, 0);
            }
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
            if (is_good){
                return new pair<bool, char **>(true, nodes);
            }
            else{
                for(int o=0; o<size; o++){
                    free(nodes[o]);
                }
                free(nodes);
                size = 0;
                return new pair<bool, char **>(false, 0);
            }
                
        }
        return new pair<bool, char **>(true, 0);
    }
#define alpha 0.1
#define sigma 0.25
#define cb 2.0
    inline ~edge_check(){
        for(int o=0; o<2*N; o++){
            free(rule_list[o]);
        }
        free(rule_list);
        free(top);
    };
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

class m_check
{
    int N, M, L;
    // int *W_arr = NULL;
    char *L_P_arr = NULL;
    char *L_S_arr = NULL;
    char *WEIGHT_C = NULL;
    unsigned char *INDEX_C = NULL;

public:
    m_check(int n, int m, int l, std::vector<VertexInfo> &std_struct,unsigned char *index_c, char *weight_c) : N(n), M(m), L(l), WEIGHT_C(weight_c), INDEX_C(index_c)
    {
        WEIGHT_C = weight_c;
        INDEX_C = index_c;
        L_P_arr = (char *)malloc(N * 8);
        L_S_arr = (char *)malloc(N * 8);
        for (int i = 0; i < N; i++) // могут вылезти ошибки ввиду архитектуры, надеемся что праймари всегда существует а секондари при отсутствии имеет уровень -1
        {
            L_P_arr[i] = std_struct[index_c[i]].primaryLvl;
            L_S_arr[i] = std_struct[index_c[i]].secondaryLvl;
        }
    }
    ~m_check()
    {
        free(L_S_arr);
        free(L_P_arr);
    }

    void get_info()
    {
        std::cout << N << ' ' << M << ' ' << L << std::endl;
        for (int i = 0; i < N; i++)
        {
            std::cout << (int)L_P_arr[i] << ' ';
        }
        std::cout << std::endl;
        for (int i = 0; i < N; i++)
        {
            std::cout << (int)L_S_arr[i] << ' ';
        }
        std::cout << std::endl;
    }

    bool is_good(char **arr, char K)
    {
        char tmp_arr[K][L]; //! не забыть оптимизировать
        memset(tmp_arr, 0, K * L);
        for (int i = K; i < N; i++) // от к-го элемента по самый конец
        {
            char a = arr[0][i];
            if (a == 0)
                continue;
            char c = L_P_arr[i];
            // if ((a > 0)) // && (L_P_arr[i] != -1))
            // {
            tmp_arr[a][c] += WEIGHT_C[i];
            if (tmp_arr[a][c] > M)
            {
                return false;
            }
            // }
            char b = arr[1][i];
            if (b == 0)
                continue;
            char d = L_S_arr[i];
            // if ((b > 0) && (d != -1))
            // {
            tmp_arr[b][d] += WEIGHT_C[i];
            if (tmp_arr[b][d] > M)
            {
                return false;
            }
            // }
        }
        return true;
    }

    bool is_good_fast(char **arr, int K)
    {
        char first_p_grup = arr[0][K];
        // if (first_p_grup == 0)
        //     return true;
        char first_s_grup = arr[1][K];
        if (first_s_grup == 0)
        {
            char tmp_arr[L];
            memset(tmp_arr, 0, L);
            for (int i = K; i < N; i++)
            {
                if (arr[0][i] == first_p_grup)
                {
                    char b = L_P_arr[i];
                    tmp_arr[b] += WEIGHT_C[i];
                    if (tmp_arr[b] > M)
                    {
                        return false;
                    }
                }
            }
            return true;
        }
        else
        {
            char tmp_arr[L];
            memset(tmp_arr, 0, L);
            for (int i = K; i < N; i++)
            {
                if (arr[0][i] == first_p_grup)
                {
                    char b = L_P_arr[i];
                    tmp_arr[b] += WEIGHT_C[i];
                    if (tmp_arr[b] > M)
                    {
                        return false;
                    }

                    if (arr[1][i] == first_p_grup)
                    {
                        char b = L_S_arr[i];
                        tmp_arr[b] += WEIGHT_C[i];
                        if (tmp_arr[b] > M)
                        {
                            return false;
                        }
                    }
                }
            }
            return true;
        }
    }
};


#define zv 0.5
#define ndc 5
#define concha 1.5
// константа задающее возможность принебречь точностью на


// M - максимальное значение в группе
// char *W_arr - массив весов, отсортированных от минимума к максимуму
// Summall_p = ∑wp
// bool *Are_sec - массив обозначающий наличие второстепенного уровня для конкретного индекса
// k - кол-во номеров вершин
// bool *sec_ed - массив где, если у вершины есть secondary edge = true в противном случае false
int abobus = 0;




void print_mas(char ** mas, int a, int b){
    for (int i = 0; i < a; i++){
        for(int j = 0; j < b; j++)
            std::cout << int(mas[i][j]);
            cout << "\n";
    }
    cout << "\n\n";
}

class generator{
//    generator(){}
public:
    m_check &mch;
    edge_check &ech;
    // int t; // кол-во нулей в маске
    // int best_t;
    int k; // n в начальной программе, хз захотелось юзать k
    char M; // M в начальной программе
    int coinlost = 0; // кол-во потраченных монет
    char * W_arr; // массив весов
    int Summall_p; // сумма всех primary
    bool *sec_ed; // существует ли secondary
    char accuracy = -1;
    // char unsttv;
    int W_now, W_next;
    std::vector<char***> st;
    
    bool done_flag; // флаг конца обработки
    char ** ans; //массив ответов
    //создает копию массива 2хk
    char * create_mass_copy(char* masi){
        char * newmasi = new char[k];
        std::copy(&masi[0], &masi[0] + k, &newmasi[0]);
        return newmasi;
    }
    char ** create_mass_copy(char** masi){ 
        char ** newmasi = new char * [2];
        newmasi[0] = new char[k];
        newmasi[1] = new char[k];
        std::copy(&masi[0][0],&masi[0][0] + k, &newmasi[0][0]);
        std::copy(&masi[1][0],&masi[1][0] + k, &newmasi[1][0]);
        return newmasi;
    }
    
    void count_weight(char ** masi, char w){
        int all_w = 0;
        for (char i = 0; i < k; i++){
            if (masi[0][i] != 1){
                if (masi[1][i] != 1) all_w += W_arr[i];
                all_w += W_arr[i];
            }
        }
        W_now = all_w;
        W_next = all_w - w;
    }
    
    bool good_del(char num_of_del, char ** del_node){
        bool t = true;
        char iter = num_of_del;
        while (t & (iter >= 0)) {
            t = t && Delete(del_node[iter][0],del_node[iter][1],del_node[iter][2]);
            iter --;
        }
        if (!t) coinlost++;
        return t;
    }
    
    void hurray(char ** a){
        ans = create_mass_copy(a);
        done_flag = true;
        return;
    }
    
    void make_max(char ** a, char num_of_del, char ** del_node){
        // добавить delete проверку
        if (num_of_del == 0) hurray(a);
        else {
            char *** np = new char**[3];//нужно больше звездочек
            np[0] = a;// колбаска
            np[1] = new char*[1];
            np[1][0] = new char[1];
            np[1][0] = &num_of_del; // np[1][0][0] = num_of_del;
            np[2] = del_node;// удаляемые ветки
            st.push_back(np);
        }
    }
    void finito_la_comedia(){
        // !W_now посчитать
        int imax = -1;
        double maxo = ech.count_decision_value(W_now,false, 0,coinlost,zv), nw;
        for (int i = 0; i < st.size(); i++){
            if (maxo < (nw = ech.count_decision_value(W_now,true, st[i][1][0][0], coinlost, zv))){
                maxo = nw;
                imax = i;
            }
        }
        if (imax != -1){ 
            if (good_del(st[imax][1][0][0], st[imax][2]))
               hurray(st[imax][0]);
        }
        for (int i = 0; i < st.size(); i++){
            //добавить удаление строки массива
            delete[] st[i][0][0];
            delete[] st[i][0][1];
            for (int j = 0; j < st[i][1][0][0]; j++)
                delete [] st[i][2][j];
            delete[] st[i][1][0];
            delete[] st[i][0];
            delete[] st[i][1];
            delete[] st[i][2];
            delete[] st[i];
        }
        st.clear();
    }
    
    
    char ** attach_mas(int st,int howadd, char ** in_what_add, char ** what_add){
        char ** new_mas = new char *[st+howadd];// создание массива размера суммы двух
         
        if (st != 0){
            for(int l = 0;  l < st; l++){
                new_mas[l] = new char [3];
                std::copy(&in_what_add[l][0], &in_what_add[l][0] + 3, &new_mas[l][0]);
                // delete in_what_add[l];
            }
            // delete in_what_add;
        }


        // for (int i = 0; i < howadd; i++){
        //     cout << int(what_add[i][0]) << " " << int(what_add[i][1]) << " " << int(what_add[i][2]) << "\n";
        // }
        // cout <<"\n\n";
        for(int l = st; l < howadd+st; l++){
            // cout << int(l) << "\n";
            new_mas[l] = new char[3];
            std::copy(&what_add[l-st][0], &what_add[l-st][0] + 3, &new_mas[l][0]);
            delete[] what_add[l-st];
        }
        delete what_add;
        return new_mas;
    }
    
    void megarecur(char** masi,const int j,int gnum,int supchik, char ** del_node = NULL,int num_of_dell = 0){

        int super_supchik = supchik;
        if (done_flag) return;
        if (j != -1){
            // std::cout << int(j);
            //вызов функции megarecur от всех номеров групп
            char ** new_masi = create_mass_copy(masi);
            if (sec_ed[j]) {
                for (int z = 1; z <= supchik; z++){

                    if (done_flag) break;
                    if (z == supchik) super_supchik = supchik +1;
                    
                    new_masi[0][j] = z;
                    new_masi[1][j] = z;
                        // print_mas(new_masi, 2, k);
                        // cout << j << "\n";
                    if (mch.is_good_fast(new_masi, j)){// тут вызовы проверки на массу и на ветки
                        int del_add = 0; // передается Мише по ссылке
                        // вызов Миши 
                        std::pair<bool, char**> * bruh = ech.is_good_fast(new_masi, j, del_add);

                        if (bruh->first && (del_add+num_of_dell < ndc)){ // .first
                        
                        //вызов функции склейки для del_node
                        
                            if (del_add != 0 && false){
                                //!вкл/выкл проверку для del_add
                                // break;
                                char ** new_del_node = attach_mas(num_of_dell, del_add, del_node, bruh->second);
                                megarecur(new_masi, j-1, gnum, super_supchik, new_del_node, num_of_dell + del_add);
                                
                                for (int i = 0; i < num_of_dell+del_add;i++){
                                    // cout << int(new_del_node[i][0]) << " " << int(new_del_node[i][1]) << " " << int(new_del_node[i][2]) << "\n";
                                    delete[] new_del_node[i];
                                }
                                // cout << "\n";
                            }
                            else megarecur(new_masi, j-1, gnum, super_supchik, del_node, num_of_dell);
                            if (done_flag) return;
                            if (j + accuracy >= k && num_of_dell == 0){
                                make_max(new_masi, num_of_dell, del_node);
                            }
                        
                        }
                        for(int o=0; o<del_add; o++){
                            free(bruh->second[o]);
                        }
                        free(bruh->second);
                        delete bruh;
                    }
                } 
            }
            super_supchik = supchik;
            new_masi[1][j] = 0;
            for (int z = 1; z <= supchik; z++){

                    if (done_flag) break;
                    if (z == supchik) super_supchik = supchik +1;
                    
                    new_masi[0][j] = z;
                        // print_mas(new_masi, 2, k);
                        // cout << j << "\n";
                    if (mch.is_good_fast(new_masi, j)){// тут вызовы проверки на массу и на ветки
                        int del_add = 0; // передается Мише по ссылке
                        // вызов Миши 
                        std::pair<bool, char**> * bruh = ech.is_good_fast(new_masi, j, del_add);

                        if (bruh->first && (del_add+num_of_dell < ndc)){ // .first
                        
                        //вызов функции склейки для del_node
                        
                            if (del_add != 0 && false){
                                //!вкл/выкл проверку для del_add
                                // break;
                                char ** new_del_node = attach_mas(num_of_dell, del_add, del_node, bruh->second);
                                megarecur(new_masi, j-1, gnum, super_supchik, new_del_node, num_of_dell + del_add);
                                
                                for (int i = 0; i < num_of_dell+del_add;i++){
                                    // cout << int(new_del_node[i][0]) << " " << int(new_del_node[i][1]) << " " << int(new_del_node[i][2]) << "\n";
                                    delete[] new_del_node[i];
                                }
                                // cout << "\n";
                            }
                            else megarecur(new_masi, j-1, gnum, super_supchik, del_node, num_of_dell);
                            if (done_flag) return;
                            if (j + accuracy >= k && num_of_dell == 0){
                                make_max(new_masi, num_of_dell, del_node);
                            }
                        
                        }
                        for(int o=0; o<del_add; o++){
                            free(bruh->second[o]);
                        }
                        free(bruh->second);
                        delete bruh;
                    }
            } 
            new_masi[0][j] = 0;
            // print_mas(new_masi, 2, k);
            if (!done_flag)
                megarecur(new_masi,j-1,gnum, supchik,del_node,num_of_dell);
            delete[] new_masi[0];
            delete[] new_masi[1];
            delete[] new_masi;
        } else {
            
            make_max(masi,num_of_dell, del_node);
        }
        
    }
    void generate(){
        // for (int i = 0; i < k; i++)
        //     cout << sec_ed[i];
            char ** num_mas = new char * [2];
            num_mas[0] = new char[k];
            num_mas[1] = new char[k];
            for (int i = 0; i < k; i++){
                num_mas[0][i] = 0;
                num_mas[1][i] = 0;
            }
            megarecur(num_mas, k-1, k-1,1);
    };

    char ** get_ans(){
        return ans;
    }

    generator(char * warr, int nk, char m, int sum, bool *sec_e, m_check &y, edge_check &o): ech(o), mch(y){
        // массив весов
        // длина массива весов
        // M
        // Сумма всех весов primary
        // массив существования secondary для primary
        // if (k == 141) 
        //     cout << "\n";
        sec_ed = sec_e;
        k = nk;
        W_arr = warr;
        M = m;
        Summall_p = sum;
        done_flag = false;
        
    }
    ~generator(){
        if (done_flag){
            delete[] ans[0];
            delete[] ans[1];
            delete[] ans;
        }
    }
};

// Функция для разбиения вектора на две части
int partition(std::vector<VertexInfo> &vec, int low, int high, unsigned char *arr)
{
    int pivot = vec[high].weight;
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (vec[j].weight < pivot)
        {
            i++;
            std::swap(vec[i], vec[j]);
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(vec[i + 1], vec[high]);
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Рекурсивная функция быстрой сортировки
void quicksort(std::vector<VertexInfo> &vec, int low, int high, unsigned char *arr)
{
    if (low < high)
    {
        int pi = partition(vec, low, high, arr);
        quicksort(vec, low, pi - 1, arr);
        quicksort(vec, pi + 1, high, arr);
    }
}
std::vector<std::vector<int>> Solver(int N, int M, int L, std::vector<VertexInfo> infos)
{
    // Preprocessing
    // TODO sort

    char weight_c[N];
    unsigned char index_c[N];
    for (int i = 0; i < N; i++)
        index_c[i] = i;
    
    // сортировка вставками быстрее до 16
    if (N < 16)
    {
        for (int i = 1; i <= N - 1; i++)
        {
            VertexInfo tmp = infos[i];
            int tmp1 = index_c[i];
            int key = infos[i].weight;
            int j = i - 1;
            while (j >= 0 && infos[j].weight > key)
            {
                infos[j + 1] = infos[j];
                index_c[j + 1] = index_c[j];
                j = j - 1;
            }
            infos[j + 1] = tmp;
            index_c[j + 1] = tmp1;
        }
    }
    else
        quicksort(infos, 0, N - 1, index_c);
    short summall = 0;
    bool hassec[infos.size()];
    for (int i = 0; i < infos.size(); i++){
        weight_c[i] = infos[i].weight;
        summall+=weight_c[i];
        hassec[i] = infos[i].secondaryLvl != -1;
    }

    // Checkers initialising
    m_check m_checker(N, M, L, infos, index_c, weight_c);
    edge_check edge_checker(N, M, L, infos);

    // ускорение ввода, вывода
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    // Generation
    // TODO change sort output(maybe postprocessing)
    //! generator().generate();
    generator g(weight_c, infos.size(), M, summall,hassec,m_checker,edge_checker);
    g.generate();
    char ** ans = g.get_ans();
    char gmax = 0;
    for (int i = 0; i < infos.size(); i++)
        gmax = (gmax < ans[0][i])?ans[0][i]:gmax; 
    vector<vector<int>> V;
    V.resize(gmax);
    for (int i = 0; i < infos.size(); i++){
        V[ans[0][index_c[i]]-1].push_back(index_c[i]);
        if (ans[1][index_c[i]-1] != 0) V[ans[0][index_c[i]]-1].push_back(index_c[i]);
    return V;
}
}