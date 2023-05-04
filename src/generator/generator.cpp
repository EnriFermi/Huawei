//
//  main.cpp
//  generator
//
//  Created by Тимофей Санников on 02.05.2023.
//

#include <iostream>
#include <algorithm>
#include <iomanip>

//TODO сделать accuracy неконстантой
#define accuracy 2
#define zv 0.5
// константа задающее возможность принебречь точностью на


// M - максимальное значение в группе
// char *W_arr - массив весов, отсортированных от минимума к максимуму
// Summall_p = ∑wp
// bool *Are_sec - массив обозначающий наличие второстепенного уровня для конкретного индекса
// k - кол-во номеров вершин
// bool *sec_ed - массив где, если у вершины есть secondary edge = true в противном случае false

bool Delete(int/* lvl*/, int/* v*/, int/* u*/);
std::pair<bool, char**>& is_good_fast(char ** arr, char K, char &size);
bool is_good(char **arr, char K);

void print_mas(char ** mas, int a, int b){
    for (int i = 0; i < a; i++)
        for(int j = 0; j < b; j++)
            std::cout << int(mas[i][j]);
}

class generator{
//    generator(){}
public:
    char t;
    char k;
    char M;
    char pmax;
    char * W_arr;
    int Summall_p;
    bool *sec_ed;
    
    bool done_flag;
    char ** ans;
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
    
    // создание масок
    void maska_requr_prime(char now, char used, char** masi){
        if (done_flag) return;
        if (t - used <= now+1) return; // t - used: сколько осталось
        if (used == t){
                char ** num_mas = new char * [2];
                num_mas[0] = new char[k]{0};
                num_mas[1] = new char[k]{0};
                megarecur(masi, num_mas, k-1, k-t, 1);
                delete[] num_mas[0];
                delete[] num_mas[1];
                delete[] num_mas;
        }
        
        char ** ne_masi = create_mass_copy(masi);
        // 00
        maska_requr_prime(now--, used, ne_masi);
        ne_masi[1][now] = 1; // 01
        maska_requr_prime(now--, used, ne_masi);
        ne_masi[0][now] = 1; // 11
        maska_requr_prime(now--, used+1, ne_masi);
        delete[] ne_masi[0];
        delete[] ne_masi[1];
        delete[] ne_masi;
    }
    bool valid(char num_of_del){
        
        return true;
    }
    bool good_del(char num_of_del, char ** del_node){
        bool t = true;
        char iter = num_of_del;
        while (t & (iter >= 0)) {
            t = t && Delete(del_node[iter][0],del_node[iter][1],del_node[iter][2]);
            iter --;
        }
        return t;
    }
    void make_max(char ** a, char num_of_del, char ** del_node){
        // добавить delete проверку
        if (valid(num_of_del)){
            if (good_del(num_of_del, del_node)){
                done_flag = true;
                ans = create_mass_copy(a);
            }
        }
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
                if (maska[1][j] == 0) masi[1][j] = z;
                
                if (is_good(new_masi, j)){// тут вызовы проверки на массу и на ветки
                    char del_add; // передается Мише по ссылке
                    // вызов Миши
                    std::pair<bool, char**> bruh = is_good_fast(new_masi, j, del_add);
                    if (bruh.first){ // .first
                        
                        //вызов функции склейки для del_node
                        char ** new_del_node = attach_mas(num_of_dell, del_add, del_node, bruh.second);
                        megarecur(maska, new_masi, j-1, gnum, super_supchik, new_del_node, num_of_dell + del_add);
                        delete[] new_masi[0];
                        delete[] new_masi[1];
                        delete[] new_masi;
                        
                        if (done_flag) return;
                        
                        if (j + accuracy >= k){
                            make_max(new_masi, num_of_dell, del_node);
                        }
                        else{
                            //добавить удаление new_del_node
                            delete[] new_masi[0];
                            delete[] new_masi[1];
                            delete[] new_masi;
                        }
                        
                    }
                    delete &bruh;
                }
                else {
                    delete[] new_masi[0];
                    delete[] new_masi[1];
                    delete[] new_masi;
                }
                
            }
            } else make_max(masi,num_of_dell, del_node);
        
    }
    void generate(){
        t = Summall_p/M;
        int tempsum = 0;
        for(char i = 0; i < t; i++)
            tempsum += W_arr[i];
        t-= tempsum/M;
        
        do{
            t++;
            char ** masi = new char * [2] ;
            masi[0] = new char[k]{0};
            masi[1] = new char[k]{0};
            maska_requr_prime(k-1, 0, masi);
        } while (!done_flag);
    };
    generator(char * warr, char nk, char m, int sum, bool *sec_e){
        sec_ed = sec_e;
        k = nk;
        W_arr = warr;
        M = m;
        Summall_p = sum;
        done_flag = false;
    }
    generator(int t){
        k = t;
    }
    ~generator(){
        if (done_flag){
            delete[] ans[0];
            delete[] ans[1];
            delete[] ans;
        }
    }
};
