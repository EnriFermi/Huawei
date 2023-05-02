#include <algorithm>
#include <iostream>
#include <vector>
#include <cstring>
#include <ctime>
#include <time.h>

struct VertexInfo
{
    int weight;
    int lvlsCount;
    int primaryLvl, secondaryLvl = -1;
    std::vector<int> primaryEdges, secondaryEdges = {};
};

// std::vector<std::vector<int>> Solver(int N, int M, int L, std::vector<VertexInfo> infos);

std::vector<VertexInfo> infos;

class m_check
{
    int N, M, L;
    // int *W_arr = NULL;
    int *L_P_arr = NULL;
    int *L_S_arr = NULL;
    char *WEIGHT_C = NULL;
    char *INDEX_C = NULL;

public:
    m_check(int n, int m, int l, std::vector<VertexInfo> &std_struct, char *index_c, char *weight_c) : N(n), M(m), L(l)
    {
        for (int i = 0; i < N; i++)
        {
            std::cout << (int)weight_c[i] << ' ';
        }
        std::cout << std::endl;
        WEIGHT_C = weight_c;
        INDEX_C = index_c;
        // W_arr = new int[N];
        // std::cout << W_arr[0] << std::endl;
        // L_P_arr = new int *[L]; // инициализация массива массивов P вершин на каждом уровне
        // for (int i = 0; i < L; i++)
        L_P_arr = new int[N];
        // for (int i = 0; i < L; i++)
        //     for (int j = 0; j < N; j++)
        //         L_P_arr[i][j] = 0;
        // memset(L_P_arr[i], 0, N * sizeof(int));
        // L_S_arr = new int *[L]; // инициализация массива массивов S вершин на каждом уровне
        // for (int i = 0; i < L; i++)
        L_S_arr = new int[N];
        // for (int i = 0; i < L; i++)
        //     for (int j = 0; j < N; j++)
        //         L_S_arr[i][j] = 0;
        // memset(L_S_arr[i], 0, N * sizeof(int));
        for (int i = 0; i < N; i++) // могут вылезти ошибки ввиду архитектуры, надеемся что праймари всегда существует а секондари при отсутствии имеет уровень -1
        {
            // W_arr[i] = std_struct[i].weight;
            L_P_arr[i] = std_struct[index_c[i]].primaryLvl;
            // if (std_struct[index_c[i]].secondaryLvl >= 0)
            L_S_arr[i] = std_struct[index_c[i]].secondaryLvl;
        }

        // std::cout << "m_check()" << std::endl;
    }
    ~m_check()
    {
        // delete[] W_arr;
        // for (int i = 0; i < L; i++)
        // for (int i = 0; i < L; i++)
        delete[] L_S_arr;
        delete[] L_P_arr;
        // std::cout << "~m_check()" << std::endl;
    }

    void get_info()
    {
        std::cout << N << ' ' << M << ' ' << L << std::endl;
        // for (int i = 0; i < N; i++)
        // {
        //     std::cout << W_arr[i] << ' ';
        // }
        // std::cout << std::endl;
        // std::cout << std::endl;
        // for (int i = 0; i < L; i++)
        // {
        //     for (int j = 0; j < N; j++)
        //         std::cout << L_P_arr[i][j] << ' ';
        //     std::cout << std::endl;
        // }
        // std::cout << std::endl;
        // for (int i = 0; i < L; i++)
        // {
        //     for (int j = 0; j < N; j++)
        //         std::cout << L_S_arr[i][j] << ' ';
        //     std::cout << std::endl;
        // }
        for (int i = 0; i < N; i++)
        {
            std::cout << L_P_arr[i] << ' ';
        }
        std::cout << std::endl;
        for (int i = 0; i < N; i++)
        {
            std::cout << L_S_arr[i] << ' ';
        }
        std::cout << std::endl;
    }
    bool is_good(char **arr, char K)
    {
        char tmp_arr[K][L] = {0};
        for (int i = 0; i < K; i++)
        {
            if ((arr[0][i] > 0) && (L_P_arr[i] != -1))
            {
                tmp_arr[arr[0][i]][L_P_arr[i]] += WEIGHT_C[i];
                if (tmp_arr[arr[0][i]][L_P_arr[i]] > M)
                {
                    return false;
                }
            }
            if ((arr[1][i] > 0) && (L_S_arr[i] != -1))
            {
                tmp_arr[arr[1][i]][L_S_arr[i]] += WEIGHT_C[i];
                if (tmp_arr[arr[1][i]][L_S_arr[i]] > M)
                {
                    return false;
                }
            }
        }
        return true;
    }
};

int main()
{

    int N = 5, M = 10, L = 3;
    infos = {VertexInfo{/*weight=*/4, /*lvlsCount=*/2, /*primaryLvl=*/1, /*secondaryLvl=*/0,
                        /*primaryEdges=*/{0, 0, 0, 0, 2}, /*secondaryEdges=*/{0, 1, 0, 0, 0}},
             VertexInfo{/*weight=*/4, /*lvlsCount=*/2, /*primaryLvl=*/2, /*secondaryLvl=*/0,
                        /*primaryEdges=*/{0, 0, 0, 0, 0}, /*secondaryEdges=*/{1, 0, 0, 0, 0}},
             VertexInfo{/*weight=*/7, /*lvlsCount=*/2, /*primaryLvl=*/0, /*secondaryLvl=*/2,
                        /*primaryEdges=*/{0, 0, 0, 0, 0}, /*secondaryEdges=*/{0, 0, 0, 0, 3}},
             VertexInfo{/*weight=*/4, /*lvlsCount=*/1, /*primaryLvl=*/1, /*secondaryLvl=*/-1,
                        /*primaryEdges=*/{0, 0, 0, 0, 3}, /*secondaryEdges=*/{}},
             VertexInfo{/*weight=*/4, /*lvlsCount=*/2, /*primaryLvl=*/1, /*secondaryLvl=*/2,
                        /*primaryEdges=*/{2, 0, 0, 3, 0}, /*secondaryEdges=*/{0, 0, 3, 0, 0}}};
    std::vector<VertexInfo> convertedInfos = infos;
    for (int v = 0; v < N; ++v)
    {
        for (int &e : convertedInfos[v].primaryEdges)
        {
            if (e >= 2)
                e = -1;
        }
        for (int &e : convertedInfos[v].secondaryEdges)
        {
            if (e >= 2)
                e = -1;
        }
    }

    char weight_c[N] = {7, 4, 4, 4, 4};
    char index_c[N] = {2, 1, 0, 3, 4};
    char **num_mas = new char *[2];
    num_mas[0] = new char[5]{1, 0, 3, 3, 0};
    num_mas[1] = new char[5]{3, 2, 2, 0, 0};
    // unsigned int start_time = clock();
    // for (int i = 0; i < 100000; i++)
    // {
    //     m_check a1 = m_check(N, M, L, convertedInfos, index_c, weight_c);
    // }
    unsigned int start_time = clock();
    m_check a1 = m_check(N, M, L, convertedInfos, index_c, weight_c);
    unsigned int end_time = clock();
    a1.get_info();
    start_time = clock();
    for (int i = 0; i < 2000; i++)
    {
        a1.is_good(num_mas, 5);
    }
    end_time = clock();
    std::cout << 1000.0 * (end_time - start_time) / CLOCKS_PER_SEC << std::endl;
    delete[] num_mas[0];
    delete[] num_mas[1];
    delete[] num_mas;
    return 0;
}