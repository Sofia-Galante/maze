#include <time.h>
#include <cstdlib>
#include <chrono>
#include <iostream>

#include "Maze.h"
#include "MazeSolverSeq.h"
#include "MazeSolverPar.h"


int main() {
    srand(time(NULL));
    Maze m(50, 50);

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now();
    MazeSolverSeq seq(m);
    seq.solve(1000);
    std::cout << m.getMaxSteps() <<std::endl;
    auto t2 = high_resolution_clock::now();

    auto t3 = high_resolution_clock::now();
    MazeSolverPar par(m);
    par.solve(1000);
    auto t4 = high_resolution_clock::now();

    duration<double, std::milli> seqTime = t2 - t1;
    duration<double, std::milli> parTime = t4 - t3;

    std::cout << "Tempo sequenziale: " << seqTime.count() << "ms" << std::endl;
    std::cout << "Tempo parallelo: " << parTime.count() << "ms" << std::endl;

    std::cout << "MaxSteps = " << m.getMaxSteps();
    return 0;
}
