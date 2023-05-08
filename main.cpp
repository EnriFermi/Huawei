#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct VertexInfo
{
    int weight;
    int lvlsCount;
    int primaryLvl, secondaryLvl = -1;
    std::vector<int> primaryEdges, secondaryEdges = {};
};

int N, M, L, A;

long long int p;

vector<VertexInfo> infos;

bool Delete(int lvl, int v, int u) {
  if (lvl < 0 || lvl >= L ||
      v < 0 || v >= N ||
      u < 0 || u >= N) {
    return true;
  }
  if (infos[v].primaryLvl != lvl && infos[v].secondaryLvl != lvl) {
    return true;
  }
  int edge = (infos[v].primaryLvl == lvl ? infos[v].primaryEdges[u] : infos[v].secondaryEdges[u]);
  if (edge >= 2) {
    p++;
    if (infos[v].primaryLvl == lvl) {
      infos[v].primaryEdges[u] -= 2;
    } else {
      infos[v].secondaryEdges[u] -= 2;
    }
    if (infos[u].primaryLvl == lvl) {
      infos[u].primaryEdges[v] -= 2;
    } else {
      infos[u].secondaryEdges[v] -= 2;
    }
  }
  return edge % 2 == 0;
}
//Подключаем все файлы
// #include "src/edge_check/edge_check.cpp"
// #include "src/m_check/m_check.cpp"
// #include "src/generator/generator.cpp"
// #include "src/solution.cpp"
#include "res.cpp"
#include "src/parser.cpp"


int main() {
  parser::parse("open.txt", *Solver);
  cout << timer << endl;
  // N = 5, M = 10, L = 3;
  // infos = {VertexInfo{/*weight=*/4, /*lvlsCount=*/2, /*primaryLvl=*/1, /*secondaryLvl=*/0,
  //                  /*primaryEdges=*/{0, 0, 0, 0, 2}, /*secondaryEdges=*/{0, 1, 0, 0, 0}},
  //          VertexInfo{/*weight=*/4, /*lvlsCount=*/2, /*primaryLvl=*/2, /*secondaryLvl=*/0,
  //                  /*primaryEdges=*/{0, 0, 0, 0, 0}, /*secondaryEdges=*/{1, 0, 0, 0, 0}},
  //          VertexInfo{/*weight=*/7, /*lvlsCount=*/2, /*primaryLvl=*/0, /*secondaryLvl=*/2,
  //                  /*primaryEdges=*/{0, 0, 0, 0, 0}, /*secondaryEdges=*/{0, 0, 0, 0, 3}},
  //          VertexInfo{/*weight=*/4, /*lvlsCount=*/1, /*primaryLvl=*/1, /*secondaryLvl=*/-1,
  //                  /*primaryEdges=*/{0, 0, 0, 0, 3}, /*secondaryEdges=*/{}},
  //          VertexInfo{/*weight=*/4, /*lvlsCount=*/2, /*primaryLvl=*/1, /*secondaryLvl=*/2,
  //                  /*primaryEdges=*/{2, 0, 0, 3, 0}, /*secondaryEdges=*/{0, 0, 3, 0, 0}}};
  // std::vector<VertexInfo> convertedInfos = infos;
  // for (int v = 0; v < N; ++v) {
  //   for (int& e : convertedInfos[v].primaryEdges) {
  //     if (e >= 2) e = -1;
  //   }
  //   for (int& e : convertedInfos[v].secondaryEdges) {
  //     if (e >= 2) e = -1;
  //   }
  // }
  // std::vector<std::vector<int>> result = Solver(N, M, L, convertedInfos);
  // std::cout << result.size() << std::endl;
  // for (auto group : result) {
  //   std::sort(group.begin(), group.end());
  //   std::cout << group.size() << " ";
  //   for (size_t i = 0; i < group.size(); ++i) {
  //     std::cout << group[i];
  //     if (i + 1 != group.size()) {
  //       std::cout << " ";
  //     }
  //   }
  //   std::cout << std::endl;
  // }
  // std::cout << p << std::endl;
  // return 0;
}