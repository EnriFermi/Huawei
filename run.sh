#Deprecated
EXEC_O_PATH="exec/o"
EXEC_PATH="exec"
g++ -c -o $EXEC_O_PATH/grader.o -std=c++17 -O3 src/grader.cpp
g++ -c -o $EXEC_O_PATH/solution.o -std=c++17 -O3 src/solution.cpp
g++ -o $EXEC_PATH/solution -std=c++17 -O3 src/edge_check/edge_check.cpp $EXEC_O_PATH/grader.o $EXEC_O_PATH/solution.o
./$EXEC_PATH/solution > out.txt
