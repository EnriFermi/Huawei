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
// константа задающее возможность принебречь точностью на


// M - максимальное значение в группе
// char *W_arr - массив весов, отсортированных от минимума к максимуму
// Summall_p = ∑wp
// bool *Are_sec - массив обозначающий наличие второстепенного уровня для конкретного индекса
// k - кол-во номеров вершин
// bool *sec_ed - массив где, если у вершины есть secondary edge = true в противном случае false





void print_mas(char ** mas, int a, int b){
    for (int i = 0; i < a; i++)
        for(int j = 0; j < b; j++)
            std::cout << int(mas[i][j]);
}

class generator{
//    generator(){}
public:
    m_check &mch;
    edge_check &ech;
    char t; // кол-во нулей в маске
    char k; // n в начальной программе, хз захотелось юзать k
    char M; // M в начальной программе
    char coinlost = 0; // кол-во потраченных монет
    char * W_arr; // массив весов
    short Summall_p; // сумма всех primary
    bool *sec_ed; // существует ли secondary
    char accuracy = 0;
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
    void maska_requr_prime(char now, char used, char** masi, bool bruh = false){
//        cout << "lol" << " " << int(used) << endl; 
        if (done_flag) return;
        if (used == t){
            // cout << "abobus";
            cout << int(t) << int(used) << "\n";
            
            char ** num_mas = new char * [2];
            num_mas[0] = new char[k]{0};
            num_mas[1] = new char[k]{0};
            // this->accuracy = (k/t)+1;
            accuracy = 0;
            megarecur(masi, num_mas, k-1, k-t, 1);
            if (done_flag) return;
            if (st.size() != 0) {
                if (bruh)
                    count_weight(masi, W_arr[now]);
                else{
                    if (now != k-1)
                        count_weight(masi, W_arr[now+1]);
                    else count_weight(masi, M);
                }
                finito_la_comedia();
            }
            // cout << "abobus2"; 
            delete[] num_mas[0];
            delete[] num_mas[1];
            delete[] num_mas;
            if(done_flag) return;
        }
        //cout << int(now);
        if (t - used > now+1) return; // t - used: сколько осталось
        if (now < 0) return;
        
        
        char ** ne_masi = create_mass_copy(masi);
        // 00
        if (sec_ed[now]){
            maska_requr_prime(now-1, used, ne_masi, true);
        }
        ne_masi[1][now] = 1; // 01
        maska_requr_prime(now-1, used, ne_masi);
        ne_masi[0][now] = 1; // 11
        maska_requr_prime(now-1, used+1,ne_masi);
        delete[] ne_masi[0];
        delete[] ne_masi[1];
        delete[] ne_masi;
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
        char imax = -1;
        double maxo = ech.count_decision_value(W_next,0,0,coinlost,zv), nw;
        for (char i = 0; i < st.size(); i++){
            if (maxo < (nw = ech.count_decision_value(W_now, W_next, st[i][1][0][0], coinlost, zv))){
                maxo = nw;
                imax = i;
            }
        }
        if (imax != -1){ 
            if (good_del(st[imax][1][0][0], st[imax][2]))
               hurray(st[imax][0]);
        }
        for (char i = 0; i < st.size(); i++){
            //добавить удаление строки массива
            delete[] st[i][0][0];
            delete[] st[i][0][1];
            for (char j = 0; j < st[i][1][0][0]; j++)
                delete [] st[i][2][j];
            delete[] st[i][1][0];
            delete[] st[i][0];
            delete[] st[i][1];
            delete[] st[i][2];
            delete[] st[i];
        }
        st.clear();
    }
    
    
    char ** attach_mas(char st, char howadd, char ** in_what_add, char ** what_add){
        char ** new_mas = new char *[st+howadd];// создание массива размера суммы двух
        if (st != 0){
            for(char l = 0;  l < st; l++){
                std::copy(&in_what_add[l][0], &in_what_add[l][0] + 3, &new_mas[l][0]);
                delete in_what_add[l];
            }
            delete in_what_add;
        }
        for(char l = st; l < howadd+st; l++){
            std::copy(&what_add[l][0], &what_add[l][0] + 3, &new_mas[l][0]);
            delete what_add[l];
        }
        delete what_add;
        return new_mas;
    }
    
    void megarecur(char ** maska, char** masi, char j, char gnum, char supchik, char ** del_node = NULL, char num_of_dell = 0){
        char super_supchik = supchik;
        if (done_flag) return;
        if (j != -1){
            // если по маске номер пропускается
            if (maska[0][j] == 1) {
                megarecur(maska, masi, j+1, gnum, super_supchik);
                return;
            }
            
            //вызов функции megarecur от всех номеров групп
            for (int z = 1; z <= supchik; z++){
                if (z == supchik) super_supchik++;
                char ** new_masi = create_mass_copy(masi);
                new_masi[0][j] = z;
                if (maska[1][j] == 0){
                    new_masi[1][j] = z;
                    if (mch.is_good(new_masi, j)){// тут вызовы проверки на массу и на ветки
                        char del_add; // передается Мише по ссылке
                        // вызов Миши
                        std::pair<bool, char**> bruh = ech.is_good_fast(new_masi, j, del_add);
                        if (bruh.first){ // .first
                            
                            //вызов функции склейки для del_node
                            if (del_add != 0){
                                char ** new_del_node = attach_mas(num_of_dell, del_add, del_node, bruh.second);
                                megarecur(maska, new_masi, j-1, gnum, super_supchik, new_del_node, num_of_dell + del_add);
                                for (char i = 0; i < num_of_dell+del_add;i++)
                                    delete[] new_del_node[i];
                            }
                            else megarecur(maska, new_masi, j-1, gnum, super_supchik, del_node, num_of_dell);
                            if (done_flag) return;
                            
                            if (j + accuracy >= k && num_of_dell == 0){
                                for (int i = 0; i < k;i++)
                                     cout << int(maska[0][i]);
                                 cout << "\n";
                                for (int i = 0; i < k;i++)
                                     cout << int(maska[1][i]);    
                                cout <<"\n\n";
                                make_max(new_masi, num_of_dell, del_node);
                                
                            }
                            
                        }
                        // delete &bruh;
                    }
                } 
                new_masi[1][j] = 0;
                if (mch.is_good(new_masi, j)){// тут вызовы проверки на массу и на ветки
                    char del_add; // передается Мише по ссылке
                    // вызов Миши
                    std::pair<bool, char**> bruh = ech.is_good_fast(new_masi, j, del_add);
                    if (bruh.first){ // .first
                        
                        //вызов функции склейки для del_node
                        if (del_add != 0){
                            char ** new_del_node = attach_mas(num_of_dell, del_add, del_node, bruh.second);
                            megarecur(maska, new_masi, j-1, gnum, super_supchik, new_del_node, num_of_dell + del_add);
                            for (char i = 0; i < num_of_dell+del_add;i++)
                                delete[] new_del_node[i];
                        }
                        else megarecur(maska, new_masi, j-1, gnum, super_supchik, del_node, num_of_dell);
                        if (done_flag) return;
                        
                        if (j + accuracy >= k && num_of_dell == 0){
                            
                            make_max(new_masi, num_of_dell, del_node);
                        }
                        
                    }
                } 
                delete[] new_masi[0];
                delete[] new_masi[1];
                delete[] new_masi;
            }
        } else {
            for (int i = 0; i < k;i++)
                                     cout << int(maska[0][i]);
                                 cout << "\n";
                                for (int i = 0; i < k;i++)
                                     cout << int(maska[1][i]);    
                                cout <<"\n\n";
            make_max(masi,num_of_dell, del_node);
        }
        
    }
    void generate(){
        t = 0;
        
        do{
            t++;
            cout << int(t) << "\n";
            char ** masi = new char * [2] ;
            masi[0] = new char[k]{0};
            masi[1] = new char[k]{0};
            maska_requr_prime(k-1, 0, masi);
        } while (!done_flag);
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
