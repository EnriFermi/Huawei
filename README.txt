For a better understanding of testing process, we provide you with:
- simplified version of grader;
- solution file with examples of Delete implementation;
- executable file "run" with correct grader-solution linking;
- open testset with 2000 tests.
Please pay attention that grader given to you differs from the real one. The real grader reads 2000 tests from testset file one by one and runs Solver.
The format of testset file is following:
- In the first row number of tests (2000) is given. Each test have values N, M, L and list of infos for every vertex.
- For each index info contains: weight, lvlsCount, primaryLvl (and secondaryLvl if lvlsCount = 2), primaryEdges (and secondaryEdges if lvlsCount = 2).
- Each edges list has size of N and fulled with values from 0 to 3.
- Values 2-3 represents unstable edges (2 can be deleted, 3 cannot) while values 0-1 represent stable edges (0 no edge, 1 if edge exists).
We hope that after that clarifications you will not feel huge difficulties with input/output format.
Good luck!