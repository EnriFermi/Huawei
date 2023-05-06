#Deprecated
EXEC_O_PATH="exec/o"
EXEC_PATH="exec"
#g++ -c -o $EXEC_O_PATH/grader.o -std=c++17 -O3 src/grader.cpp
g++ -c -o $EXEC_O_PATH/edge_check.o -std=c++17 -O3 src/edge_check/edge_check.cpp
g++ -c -o $EXEC_O_PATH/m_check.o -std=c++17 -O3 src/m_check/m_check.cpp
# g++ -c -o $EXEC_O_PATH/parser.o -std=c++17 -O3 src/parser.cpp
g++ -c -o $EXEC_O_PATH/solution.o -std=c++17 -O3 src/solution.cpp
g++ -o $EXEC_PATH/main -std=c++17 -O3 main.cpp $EXEC_O_PATH/m_check.o $EXEC_O_PATH/edge_check.o $EXEC_O_PATH/solution.o 
./$EXEC_PATH/solution > out.txt
