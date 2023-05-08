//
//  main.cpp
//  generator
//
//  Created by Тимофей Санников on 02.05.2023.
//
//TODO accuracy
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>

//TODO сделать accuracy неконстантой

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
    
    // создание масок
//     void maska_requr_prime(int now, int used, char* masi){
        
// //        cout << "lol" << " " << int(used) << endl; 

//         if (done_flag) return;
//         if (t - used > now+1) return; // t - used: сколько осталось
//         if (t == used){
//             // cout << "abobus";
            
//             // cout << int(t) << int(used) << "\n";
//             // for (int i = 0; i < k;i++)
//             //     cout << int(masi[0][i]);
//             // cout << "\n";
//             // for (int i = 0; i < k;i++)
//             //     cout << int(masi[1][i]);    
//             // cout <<"\n\n";
//             // abobus++;
//             // cout << abobus << "\n";
//             char ** num_mas = new char * [2];
//             num_mas[0] = new char[k];
//             num_mas[1] = new char[k];
//             for (int i = 0; i < k; i++){
//                 num_mas[0][i] = 0;
//                 num_mas[1][i] = 0;
//             }
//             // this->accuracy = (k/10)+1;
//             accuracy = -1;
//             megarecur(masi, num_mas, k-1, k-t, 1);
//             if (done_flag) return;
//             //!добавить подсчет веса по варианту

//             // if (st.size() != 0) {
//             //     if (bruh)
//             //         count_weight(masi, W_arr[now]);
//             //     else{
//             //         if (now != k-1)
//             //             count_weight(masi, W_arr[now+1]);
//             //         else count_weight(masi, M);
//             //     }
//             //     finito_la_comedia();
//             // }
//             // cout << "abobus2"; 
//             delete[] num_mas[0];
//             delete[] num_mas[1];
//             delete[] num_mas;
//             return;

//         }
        //cout << int(now);
        
        
        // char * ne_masi = create_mass_copy(masi);
        // 00
        // if (sec_ed[now]){
        //     maska_requr_prime(now-1, used, ne_masi, true);
        // }
    //     ne_masi[now] = 0; // 01
    //     maska_requr_prime(now-1, used, ne_masi);
    //     ne_masi[now] = 1; 
    //     maska_requr_prime(now-1, used+1,ne_masi);
    //     delete[] ne_masi;
    // }
    
    
    
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
        // cout << j << " " << supchik <<"\n";
        // for (int i = 0; i < k;i++)
        //     cout << int(masi[0][i]);
        // cout << "\n";
        // for (int i = 0; i < k;i++)
        //         cout << int(masi[1][i]);    
        // cout <<"\n\n";
        // best_t = min(best_t, j);
        // if (supchik > gnum) return;
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
                        // cout <<"\n\n\n" << int(del_add) << "\n";
                        // for (int i = 0; i < del_add; i++){
                        //     cout << int(bruh->second[i][0]) << " " << int(bruh->second[i][1]) << " " << int(bruh->second[i][2]) << "\n";
                        // }

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
                        // cout <<"\n\n\n" << int(del_add) << "\n";
                        // for (int i = 0; i < del_add; i++){
                        //     cout << int(bruh->second[i][0]) << " " << int(bruh->second[i][1]) << " " << int(bruh->second[i][2]) << "\n";
                        // }

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
        cout << "\n";
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

    generator(char * warr, char nk, char m, short sum, bool *sec_e, m_check &y, edge_check &o): ech(o), mch(y){
        // массив весов
        // длина массива весов
        // M
        // Сумма всех весов primary
        // массив существования secondary для primary
        
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
