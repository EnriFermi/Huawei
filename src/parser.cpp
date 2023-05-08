#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
long double timer = 0;
struct parser
{
    static void do_something(vector<vector<int>> (*func)(int, int, int, vector<VertexInfo>))
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
        unsigned int start_time = clock();
        vector<vector<int>> result = func(N, M, L, convertedInfos);
        unsigned int end_time = clock();
        timer+=1000.0 * (end_time - start_time)/CLOCKS_PER_SEC;
        cout << "\n";
        cout << result.size() << endl;
        for (auto group : result)
        {
            sort(group.begin(), group.end());
            cout << group.size() << " ";
            for (size_t i = 0; i < group.size(); ++i)
            {
                cout << group[i];
                if (i + 1 != group.size())
                {
                    cout << " ";
                }
            }
            cout << endl;
        }
        cout << "stanzia zalupka" << "\n";
    }

public:
    static void parse(char *filename, vector<vector<int>>(*func)(int, int, int, vector<VertexInfo>))
    {
        // ifstream in_file;
        // int x;
        // in_file.open("open.txt");
        // in_file >> A;
        // for (int i = 0; i < A; i++)
        // {
        //     in_file >> N >> M >> L;
        //     // cout << N << M << L << "\n";
        //     for (int j = 0; j < N; j++)
        //     {
        //         VertexInfo vertex;
        //         in_file >> vertex.weight >> vertex.lvlsCount >> vertex.primaryLvl;
        //         // cout << vertex.weight << vertex.lvlsCount << vertex.primaryLvl << "\n";
        //         if (vertex.lvlsCount > 1)
        //             in_file >> vertex.secondaryLvl;
        //         for (int k = 0; k < N; k++)
        //         {

        //             in_file >> x;
        //             vertex.primaryEdges.push_back(x);
        //         }
        //         if (vertex.lvlsCount > 1)
        //             for (int k = 0; k < N; k++)
        //             {
        //                 in_file >> x;
        //                 vertex.secondaryEdges.push_back(x);
        //             }
        //         infos.push_back(vertex);
        //         // cout << infos[0].primaryEdges.size() << "\n";
        //     }
        //     // for (int i = 0; i < infos.size(); i++)
        //     //     {
        //     //         for (int j = 0; j < N; j++){
        //     //             cout << int(infos[i].secondaryEdges[j]) << "\n";
        //     //         }
        //     //         cout << "\n";
        //     //     }
        //     do_something(Solver);
        //     infos.clear();
        // }
        //!
        N = 5, M = 10, L = 3, A = 1;
        // infos = {VertexInfo{/*weight=*/4, /*lvlsCount=*/2, /*primaryLvl=*/1, /*secondaryLvl=*/0,
        //                     /*primaryEdges=*/{0, 0, 0, 0, 2}, /*secondaryEdges=*/{0, 1, 0, 0, 0}},
        //          VertexInfo{/*weight=*/4, /*lvlsCount=*/2, /*primaryLvl=*/2, /*secondaryLvl=*/0,
        //                     /*primaryEdges=*/{0, 0, 0, 0, 0}, /*secondaryEdges=*/{1, 0, 0, 0, 0}},
        //          VertexInfo{/*weight=*/4, /*lvlsCount=*/2, /*primaryLvl=*/0, /*secondaryLvl=*/2,
        //                     /*primaryEdges=*/{0, 0, 0, 0, 0}, /*secondaryEdges=*/{0, 0, 0, 0, 3}},
        //          VertexInfo{/*weight=*/4, /*lvlsCount=*/1, /*primaryLvl=*/1, /*secondaryLvl=*/-1,
        //                     /*primaryEdges=*/{0, 0, 0, 0, 3}, /*secondaryEdges=*/{}},
        //          VertexInfo{/*weight=*/7, /*lvlsCount=*/2, /*primaryLvl=*/1, /*secondaryLvl=*/2,
        //                     /*primaryEdges=*/{2, 0, 0, 3, 0}, /*secondaryEdges=*/{0, 0, 3, 0, 0}}};
        infos = {VertexInfo{/*weight=*/4, /*lvlsCount=*/2, /*primaryLvl=*/1, /*secondaryLvl=*/0,
                            /*primaryEdges=*/{0, 0, 0, 0, 1}, /*secondaryEdges=*/{0, 1, 0, 0, 0}},
                 VertexInfo{/*weight=*/4, /*lvlsCount=*/2, /*primaryLvl=*/2, /*secondaryLvl=*/0,
                            /*primaryEdges=*/{0, 0, 0, 0, 0}, /*secondaryEdges=*/{1, 0, 0, 0, 0}},
                 VertexInfo{/*weight=*/4, /*lvlsCount=*/2, /*primaryLvl=*/0, /*secondaryLvl=*/2,
                            /*primaryEdges=*/{0, 0, 0, 0, 0}, /*secondaryEdges=*/{0, 0, 0, 0, 1}},
                 VertexInfo{/*weight=*/4, /*lvlsCount=*/1, /*primaryLvl=*/1, /*secondaryLvl=*/-1,
                            /*primaryEdges=*/{0, 0, 0, 0, 1}, /*secondaryEdges=*/{}},
                 VertexInfo{/*weight=*/7, /*lvlsCount=*/2, /*primaryLvl=*/1, /*secondaryLvl=*/2,
                            /*primaryEdges=*/{1, 0, 0, 1, 0}, /*secondaryEdges=*/{0, 0, 1, 0, 0}}};
        // // for (int i = 0; i < 50; i++)do_something(func);
        do_something(func); 
    }
};
