#include <cassert>
#include <vector>
#include <algorithm>
#include "m_check/m_check.cpp"
#include "edge_check/edge_check.cpp"
#include "generator/generator.cpp"
bool Delete(int/* lvl*/, int/* v*/, int/* u*/);

std::vector<std::vector<int>> Solver(int N, int M, int L, std::vector<VertexInfo>&  infos) {
    //Preprocessing
    //TODO sort
    
    char * index_c;
    char * weight_c;
    //Checkers initialising 
    m_check m_checker(N, M, L, infos, index_c, weight_c);
    edge_check edge_checker(N, M, L, infos);


    //Generation
    //TODO change sort output(maybe postprocessing)
    generator().generate();

    return;
}