#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>

struct parser
{
    static void do_something(vector<vector<int>>(*func)(int, int, int, vector<VertexInfo>))
    {
        vector<VertexInfo> convertedInfos = infos;
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
        /*vector<vector<int>> result = */func(N, M, L, convertedInfos);

        // cout << result.size() << endl;
        // for (auto group : result)
        // {
        //     sort(group.begin(), group.end());
        //     cout << group.size() << " ";
        //     for (size_t i = 0; i < group.size(); ++i)
        //     {
        //         cout << group[i];
        //         if (i + 1 != group.size())
        //         {
        //             cout << " ";
        //         }
        //     }
        //     cout << endl;
        // }
        // cout << p << endl;
    }

public:
    static void parse(char *filename, /*vector<vector<int>>*/void (*func)(int, int, int, vector<VertexInfo>))
    {
        ifstream in_file;
        int x;
        in_file.open("open.txt");
        in_file >> A;
        for (int i = 0; i < A; i++)
        {
            in_file >> N >> M >> L;
            for (int j = 0; j < M; j++)
            {
                VertexInfo vertex;
                in_file >> vertex.weight >> vertex.lvlsCount >> vertex.primaryLvl;
                if (vertex.lvlsCount > 1)
                    in_file >> vertex.secondaryLvl;
                for (int k = 0; k < N; k++)
                {

                    in_file >> x;
                    vertex.primaryEdges.push_back(x);
                }
                if (vertex.lvlsCount > 1)
                    for (int k = 0; k < N; k++)
                    {
                        in_file >> x;
                        vertex.secondaryEdges.push_back(x);
                    }
                infos.push_back(vertex);
            }
            do_something(infos, Solver);
            infos.clear();
        }
    }
};
