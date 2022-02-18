#include <ctime>
#include <cstdlib>
#include <chrono>
#include <iostream>
#include <fstream>

#include "Maze.h"
#include "MazeSolverSeq.h"
#include "MazeSolverPar.h"

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

void dimTest(){

    printf("\n\nTEST 1: CAMBIO DIMENSIONE DEL LABIRINTO\n");

    int p = 50;
    int t = 10;

    std::ofstream csvFile;
    csvFile.open (R"(C:\Users\Sofy\CLionProjects\maze\test1.csv)");
    for(int i = 1; i <= 10; i++){
        printf("numero di particelle = %d\nnumero di thread = %d\ndimensione labirinto = %d\n", p, t, i*i*100);
        Maze maze(i*10, i*10);
        MazeSolverSeq seq(maze);
        MazeSolverPar par(maze, t, false);

        auto t1 = high_resolution_clock::now();
        seq.solve(p);
        auto t2 = high_resolution_clock::now();

        auto t3 = high_resolution_clock::now();
        par.solve(p);
        auto t4 = high_resolution_clock::now();

        duration<double, std::milli> seqTime = t2 - t1;
        duration<double, std::milli> parTime = t4 - t3;

        std::cout << "Tempo sequenziale: " << seqTime.count() << "ms" << std::endl;
        std::cout << "Tempo parallelo: " << parTime.count() << "ms" << std::endl;

        csvFile << i*i*100 << ";" << seqTime.count() << ";" << parTime.count() <<"\n";

    }
    csvFile.close();
}

void particlesTest(){

    printf("\n\nTEST 2: CAMBIO NUMERO DI PARTICELLE\n");

    int w = 50;
    int h = 50;
    int t = 10;

    Maze maze(w, h);
    MazeSolverSeq seq(maze);
    MazeSolverPar par(maze, t, false);

    std::ofstream csvFile;
    csvFile.open (R"(C:\Users\Sofy\CLionProjects\maze\test2.csv)");
    for(int p = 1; p <= 10; p++){
        printf("numero di particelle = %d\nnumero di thread = %d\ndimensione labirinto = %d\n", p*10, t, w*h);

        auto t1 = high_resolution_clock::now();
        seq.solve(p*10);
        auto t2 = high_resolution_clock::now();

        auto t3 = high_resolution_clock::now();
        par.solve(p*10);
        auto t4 = high_resolution_clock::now();

        duration<double, std::milli> seqTime = t2 - t1;
        duration<double, std::milli> parTime = t4 - t3;

        std::cout << "Tempo sequenziale: " << seqTime.count() << "ms" << std::endl;
        std::cout << "Tempo parallelo: " << parTime.count() << "ms" << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;


        csvFile << p*10 << ";" << seqTime.count() << ";" << parTime.count() << "\n";

    }
    csvFile.close();
}

void threadsTest(){


    printf("\n\nTEST 3: CAMBIO NUMERO DI THREAD\n");

    int w = 50;
    int h = 50;
    int p = 50;

    Maze maze(w, h);
    MazeSolverSeq seq(maze);

    auto t1 = high_resolution_clock::now();
    seq.solve(p);
    auto t2 = high_resolution_clock::now();

    duration<double, std::milli> seqTime = t2 - t1;

    std::ofstream csvFile;
    csvFile.open (R"(C:\Users\Sofy\CLionProjects\maze\test3.csv)");
    for(int t = 1; t <= 10; t++){
        printf("numero di particelle = %d\nnumero di thread = %d\ndimensione labirinto = %d\n", p, t*10, w*h);

        MazeSolverPar par(maze, t*10, false);

        auto t3 = high_resolution_clock::now();
        par.solve(p);
        auto t4 = high_resolution_clock::now();

        duration<double, std::milli> parTime = t4 - t3;

        std::cout << "Tempo sequenziale: " << seqTime.count() << "ms" << std::endl;
        std::cout << "Tempo parallelo: " << parTime.count() << "ms" << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;


        csvFile << t*10 << ";" << seqTime.count() << ";" << parTime.count() << "\n";

    }
    csvFile.close();
}

void lockTest() {

    printf("\n\nTEST 4: AGGIUNTA DEL LOCK\n");

    int w = 20;
    int h = 20;
    int p = 15;
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
    csvFile.open (R"(C:\Users\Sofy\CLionProjects\maze\test4.csv)");

    csvFile << seqTime.count() << ";" << parTime.count() << ";" << lockedTime.count() << "\n";
    csvFile.close();
}

int main() {
    srand(time(NULL));
    dimTest();
    particlesTest();
    threadsTest();
    lockTest();
    return 0;
}
