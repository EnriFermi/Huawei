// Created by Nikita Kyazhin 03.05.23
// m_check

#include <algorithm>
#include <iostream>
#include <vector>
#include <cstring>
#include <ctime>
#include <time.h>


// std::vector<VertexInfo> infos;

class m_check
{
    int N, M, L;
    // int *W_arr = NULL;
    char *L_P_arr = NULL;
    char *L_S_arr = NULL;
    char *WEIGHT_C = NULL;
    char *INDEX_C = NULL;

public:
    m_check(int n, int m, int l, std::vector<VertexInfo> &std_struct, char *index_c, char *weight_c) : N(n), M(m), L(l), WEIGHT_C(weight_c), INDEX_C(index_c)
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

    bool is_good_fast(char **arr, char K)
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
//     if ((first_p_grup == first_s_grup) && (first_p_grup != 0))
//     {
//         char tmp_arr[L];
//         memset(tmp_arr, 0, L);
//         while (K >= 0)
//         {
//             if (arr[0][K] == first_p_grup)
//             {
//                 char b = L_P_arr[K];
//                 tmp_arr[b] += WEIGHT_C[K];
//                 if (tmp_arr[b] > M)
//                 {
//                     return false;
//                 }
//             }
//             if (arr[1][K] == first_s_grup)
//             {
//                 char b = L_S_arr[K];
//                 tmp_arr[b] += WEIGHT_C[K];
//                 if (tmp_arr[b] > M)
//                 {
//                     return false;
//                 }
//             }
//             K--;
//         }
//         return true;
//     }
//     if ((first_s_grup == 0) && (first_p_grup != first_s_grup))
//     {
//         char tmp_arr[L];
//         memset(tmp_arr, 0, L);
//         while (K >= 0)
//         {
//             if (arr[0][K] == first_p_grup)
//             {
//                 char b = L_P_arr[K];
//                 tmp_arr[b] += WEIGHT_C[K];
//                 if (tmp_arr[b] > M)
//                 {
//                     return false;
//                 }
//             }
//             K--;
//         }
//     }
//     return true;
// }

// int main()
// {

//     int N = 5, M = 10, L = 3;
//     infos = {VertexInfo{/*weight=*/4, /*lvlsCount=*/2, /*primaryLvl=*/1, /*secondaryLvl=*/0,
//                         /*primaryEdges=*/{0, 0, 0, 0, 2}, /*secondaryEdges=*/{0, 1, 0, 0, 0}},
//              VertexInfo{/*weight=*/4, /*lvlsCount=*/2, /*primaryLvl=*/2, /*secondaryLvl=*/0,
//                         /*primaryEdges=*/{0, 0, 0, 0, 0}, /*secondaryEdges=*/{1, 0, 0, 0, 0}},
//              VertexInfo{/*weight=*/7, /*lvlsCount=*/2, /*primaryLvl=*/0, /*secondaryLvl=*/2,
//                         /*primaryEdges=*/{0, 0, 0, 0, 0}, /*secondaryEdges=*/{0, 0, 0, 0, 3}},
//              VertexInfo{/*weight=*/4, /*lvlsCount=*/1, /*primaryLvl=*/1, /*secondaryLvl=*/-1,
//                         /*primaryEdges=*/{0, 0, 0, 0, 3}, /*secondaryEdges=*/{}},
//              VertexInfo{/*weight=*/4, /*lvlsCount=*/2, /*primaryLvl=*/1, /*secondaryLvl=*/2,
//                         /*primaryEdges=*/{2, 0, 0, 3, 0}, /*secondaryEdges=*/{0, 0, 3, 0, 0}}};
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

//     char weight_c[N] = {4, 4, 7, 4, 4};
//     char index_c[N] = {0, 1, 2, 3, 4};
//     char **num_mas = new char *[2];
//     num_mas[0] = new char[5]{2, 0, 1, 3, 3};
//     num_mas[1] = new char[5]{2, 2, 2, 0, 3};
//     m_check a1 = m_check(N, M, L, convertedInfos, index_c, weight_c);
//     a1.get_info();
//     unsigned int start_time = clock();
//     for (int i = 0; i < 10000; i++)
//     {
//         // a1.is_good(num_mas, 0);
//         // m_check a1 = m_check(N, M, L, convertedInfos, index_c, weight_c);
//         // std::cout << a1.is_good_fast(num_mas, 4) << std::endl;
//         a1.is_good_fast(num_mas, 0);
//     }
//     unsigned int end_time = clock();
//     std::cout << 1000.0 * (end_time - start_time) / CLOCKS_PER_SEC << std::endl;
//     delete[] num_mas[0];
//     delete[] num_mas[1];
//     delete[] num_mas;
//     return 0;
// }