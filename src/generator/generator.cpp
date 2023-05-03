//
//  main.cpp
//  generator
//
//  Created by Тимофей Санников on 02.05.2023.
//

#include <iostream>
#include <algorithm>
#include <iomanip>
#define accuracy 2
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
    int t;
    int k;
    int M;
    char * W_arr;
    int Summall_p;
    bool *sec_ed;
    
    bool done_flag;
    const char gnum_start = 3; // TODO вывести нормальную формулу для минимального числа групп
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
    void maska_requr_prime(char now, char used, char* masi){
        if (done_flag) return;
        if (t - used <= now+1) return; // t - used: сколько осталось
        if (used == t){
            for (char gnum = gnum_start; gnum < k/2 + 1; gnum++){
                // больше чем k/2 + 1 - боль + не имеет смысла
                char ** num_mas = new char * [2];
                num_mas[0] = new char[k]{0};
                num_mas[1] = new char[k]{0};
                megarecur(masi, num_mas, 0, gnum);
                delete[] num_mas[0];
                delete[] num_mas[1];
                delete[] num_mas;
            }
        }
        
        maska_requr_prime(now--, used, masi);
        if (done_flag) return;
        char * new_masi = create_mass_copy(masi);
        new_masi[now] = 1;
        maska_requr_prime(now--, used+1, new_masi);
        delete[] new_masi;
    }
    void make_max(char ** a){
        done_flag = true;
        ans = create_mass_copy(a);
    }
    void megarecur(char * maska, char** masi, char j, char gnum){
        if (done_flag) return;
            if (j != k){
                // если по маске номер пропускается
                if (maska[j] == 0) megarecur(maska, masi, j+1, gnum);
                
                //вызов функции megarecur от всех номеров групп
                for (int z = 1; z <= gnum; z++){
                    char ** new_masi = create_mass_copy(masi);
                    new_masi[0][j] = z;
                    
                    if (sec_ed[j]){// проверка на существование sub для этого номера
                        char ** new_new_masi = create_mass_copy(new_masi);
                        new_new_masi[1][j] = z;
                            if (1){// тут вызовы проверки на массу и на ветки
                                megarecur(maska, new_new_masi, j+1, gnum);
                                delete[] new_new_masi[0];
                                delete[] new_new_masi[1];
                                delete[] new_new_masi;
                                if (done_flag) return;
                                if (j + accuracy >= k){
                                    make_max(new_new_masi);
                                }
                            }
                            else {
                                delete[] new_masi[0];
                                delete[] new_masi[1];
                                delete[] new_masi;
                            }
                    }
                    
                    if (1){// тут вызовы проверки на массу и на ветки
                        megarecur(maska, new_masi, j+1, gnum);
                        delete[] new_masi[0];
                        delete[] new_masi[1];
                        delete[] new_masi;
                        if (done_flag) return;
                        if (j + accuracy >= k){
                            make_max(new_masi);
                        }
                    }
                    else {
                        delete[] new_masi[0];
                        delete[] new_masi[1];
                        delete[] new_masi;
                    }
                    
                }
            } else make_max(masi);
        
    }
    void generate(){
        t = Summall_p/M;
        int tempsum = 0;
        for(char i = 0; i < t; i++)
            tempsum += W_arr[i];
        t-= tempsum/M;
        
        do{
            t++;
            char * masi = new char[k]{0};
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