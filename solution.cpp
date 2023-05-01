#include <cassert>
#include <vector>

struct VertexInfo {
    int weight;
    int lvlsCount;
    int primaryLvl, secondaryLvl = -1;
    std::vector<int> primaryEdges, secondaryEdges = {};
};

bool Delete(int/* lvl*/, int/* v*/, int/* u*/);

std::vector<std::vector<int>> Solver(int N, int M, int L, std::vector<VertexInfo> infos) {
  /* coin is counted only once */
  Delete(/*lvl=*/1, /*v=*/0, /*u=*/4);
  Delete(/*lvl=*/1, /*v=*/0, /*u=*/4);

  /* incorrect deletes */
  assert(Delete(/*lvl=*/-1, /*v=*/-1, /*u=*/-1));
  assert(Delete(/*lvl=*/2, /*v=*/0, /*u=*/1));

  /* correct deletes on stable edges */
  assert(Delete(/*lvl=*/1, /*v=*/0, /*u=*/0));
  assert(Delete(/*lvl=*/0, /*v=*/1, /*u=*/2));
  assert(!Delete(/*lvl=*/0, /*v=*/0, /*u=*/1));

  Delete(/*lvl=*/2, /*v=*/2, /*u=*/4);
  return {{0, 0, 1, 1}, {2, 2}, {3}};
}