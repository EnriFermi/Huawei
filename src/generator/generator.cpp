//
//  main.cpp
//  generator
//
//  Created by Тимофей Санников on 02.05.2023.
//

#include <iostream>

// константа задающее кол-во искомых цепочек
#define num_of_good_chains 3
// предполагается что в базовом классе присутствуют:
// M - максимальное значение в группе
// int *W_arr - массив весов, отсортированных от минимума к максимуму
// Summall_p = ∑wp
// bool *Are_sec - массив обозначающий наличие второстепенного уровня для конкретного индекса


// ниже представлен заполненый класс core для тестов

int M = 13;
int W_arr[10] = {1,3,4,5,7,8,9,11,13,13};
long Summall_p = 74;


class Generator{
public:
    void generate_wurst(){
        long t = Summall_p/M; // 5
        long tempsum = 0;
        for(int i = 0; i < t; i++)
            tempsum += W_arr[i];
        t-= tempsum/M;
        t++;// t - кол-во нулей при идеальном распределении
        int num = num_of_good_chains;
        while (num != 0){
            
        }
    }
};

