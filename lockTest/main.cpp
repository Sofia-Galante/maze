#include <ctime>
#include <cstdlib>
#include <chrono>
#include <iostream>
#include <fstream>

#include "../Maze.h"
#include "../MazeSolverSeq.h"
#include "../MazeSolverPar.h"

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

void lockTest() {

    printf("\n\nTEST 4: AGGIUNTA DEL LOCK\n");

    int w = 20;
    int h = 20;
    int p = 10;
    int t = 10;

    Maze maze(w, h);
    MazeSolverSeq seq(maze);
    MazeSolverPar par(maze, t, false);
    MazeSolverPar locked(maze, t, true);

    auto t1 = high_resolution_clock::now();
    seq.solve(p);
    auto t2 = high_resolution_clock::now();

    auto t3 = high_resolution_clock::now();
    par.solve(p);
    auto t4 = high_resolution_clock::now();

    auto t5 = high_resolution_clock::now();
    locked.solve(p);
    auto t6 = high_resolution_clock::now();

    duration<double, std::milli> seqTime = t2 - t1;
    duration<double, std::milli> parTime = t4 - t3;
    duration<double, std::milli> lockedTime = t6 - t5;

    std::cout << "Tempo sequenziale: " << seqTime.count() << "ms" << std::endl;
    std::cout << "Tempo parallelo: " << parTime.count() << "ms" << std::endl;
    std::cout << "Tempo parallelo con lock: " << lockedTime.count() << "ms" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    std::ofstream csvFile;
    csvFile.open ("test4.csv");

    csvFile << "Sequenziale" << ";" << "Parallelo senza lock" << ";" << "Parallelo con lock" << "\n";
    csvFile << seqTime.count() << " ms" << ";" << parTime.count() << " ms" << ";" << lockedTime.count() << " ms";
    csvFile.close();
}

int main() {
    srand(time(NULL));
    lockTest();
    return 0;
}