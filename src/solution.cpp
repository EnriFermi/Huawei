#include <cassert>
#include <vector>
#include <algorithm>
#include <iostream>
// #include "m_check/m_check.cpp"
// #include "edge_check/edge_check.cpp"
// #include "generator/generator.cpp"
bool Delete(int /* lvl*/, int /* v*/, int /* u*/);

struct VertexInfo
{
    int weight;
    int lvlsCount;
    int primaryLvl, secondaryLvl = -1;
    std::vector<int> primaryEdges, secondaryEdges = {};
};

std::vector<VertexInfo> infos;

/*std::vector<std::vector<int>>*/ void Solver(int N, int M, int L, std::vector<VertexInfo> &infos)
{
    // Preprocessing
    // TODO sort

    for (int i = 0; i < N; i++)
    {
        std::cout << infos[i].weight << ' ';
    }
    std::cout << std::endl;
    char index_c[N];
    for (int i = 0; i < N; i++)
        index_c[i] = i;
    bool comp(const VertexInfo &x, const VertexInfo &y){
        return x.weight < y.weight;
    };


    for (int i = 0; i < N; i++)
    {
        std::cout << infos[i].weight << ' ';
    }

    char *weight_c;
    // Checkers initialising
    //! m_check m_checker(N, M, L, infos, index_c, weight_c);
    //! edge_check edge_checker(N, M, L, infos);

    // Generation
    // TODO change sort output(maybe postprocessing)
    //! generator().generate();

    return;
}
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
    Solver(N, M, L, convertedInfos);
    // char weight_c[N] = {4, 4, 7, 4, 4};
    // char index_c[N] = {0, 1, 2, 3, 4};
    // char **num_mas = new char *[2];
    // num_mas[0] = new char[5]{2, 0, 1, 3, 3};
    // num_mas[1] = new char[5]{2, 2, 2, 0, 3};
    // m_check a1 = m_check(N, M, L, convertedInfos, index_c, weight_c);
    // a1.get_info();
    // unsigned int start_time = clock();
    // for (int i = 0; i < 2000000; i++)
    // {
    //     // a1.is_good(num_mas, 0);
    //     // m_check a1 = m_check(N, M, L, convertedInfos, index_c, weight_c);
    //     // std::cout << a1.is_good_fast(num_mas, 4) << std::endl;
    //     // a1.is_good_fast(num_mas, 0);
    // }
    // unsigned int end_time = clock();
    // std::cout << 1000.0 * (end_time - start_time) / CLOCKS_PER_SEC << std::endl;
    // delete[] num_mas[0];
    // delete[] num_mas[1];
    // delete[] num_mas;
    return 0;
}