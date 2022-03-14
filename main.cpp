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

void dimTest(std::string const &testName){
    printf("\n\nTEST 1: CAMBIO DIMENSIONE DEL LABIRINTO (50 PARTICELLE)\n");

    int p = 50;
    int t = 10;

    std::ofstream csvFile;
    std::string filename = "dimTest/" + testName;
    csvFile.open (filename);
    for(int i = 5; i <= 100; i++){
        printf("numero di particelle = %d\nnumero di thread = %d\ndimensione labirinto = %d\n", p, t, i*i);
        Maze maze(i, i);
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

        csvFile << i*i << ";" << seqTime.count() << ";" << parTime.count() <<"\n";

    }
    csvFile.close();
}
void dimTestV2(std::string const &testName){
    printf("\n\nTEST 1v2: CAMBIO DIMENSIONE DEL LABIRINTO + NUMERO DI THREAD (50 PARTICELLE)\n");

    int p = 50;
    int th1 = 2;
    int th2 = 10;

    std::ofstream csvFile;
    std::string filename = "dimTestV2/" + testName;
    csvFile.open (filename);
    for(int i = 50; i <= 100; i+=5){
        printf("numero di particelle = %d\ndimensione labirinto = %d\n", p, i*i);
        Maze maze(i, i);
        MazeSolverSeq seq(maze);
        MazeSolverPar par1(maze, th1, false);
        MazeSolverPar par2(maze, th2, false);

        auto t1 = high_resolution_clock::now();
        seq.solve(p);
        auto t2 = high_resolution_clock::now();

        auto t3 = high_resolution_clock::now();
        par1.solve(p);
        auto t4 = high_resolution_clock::now();

        auto t5 = high_resolution_clock::now();
        par2.solve(p);
        auto t6 = high_resolution_clock::now();


        duration<double, std::milli> seqTime = t2 - t1;
        duration<double, std::milli> par1Time = t4 - t3;
        duration<double, std::milli> par2Time = t6 - t5;


        std::cout << "Tempo sequenziale: " << seqTime.count() << "ms" << std::endl;
        std::cout << "Tempo parallelo - 5 threads: " << par1Time.count() << "ms" << std::endl;
        std::cout << "Tempo parallelo - 10 threads: " << par2Time.count() << "ms" << std::endl;

        csvFile << i*i << ";" << seqTime.count() << ";" << par1Time.count() << ";" << par2Time.count() <<"\n";

    }
    csvFile.close();
}
void particlesTest(std::string const &testName){

    printf("\n\nTEST 2: CAMBIO NUMERO DI PARTICELLE\n");

    int w = 50;
    int h = 50;
    int t = 10;

    Maze maze(w, h);
    MazeSolverSeq seq(maze);
    MazeSolverPar par(maze, t, false);

    std::ofstream csvFile;
    std::string filename = "particlesTest/" + testName;
    csvFile.open (filename);
    for(int p = 1; p <= 501; p=p+10){
        printf("numero di particelle = %d\nnumero di thread = %d\ndimensione labirinto = %d\n", p, t, w*h);

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
        std::cout << std::endl;
        std::cout << std::endl;


        csvFile << p << ";" << seqTime.count() << ";" << parTime.count() << "\n";

    }
    csvFile.close();
}
void threadsTest(std::string const &testName){
    printf("\n\nTEST 3: CAMBIO NUMERO DI THREAD\n");

    int w = 50;
    int h = 50;
    int p = 100;

    Maze maze(w, h);
    MazeSolverSeq seq(maze);

    auto t1 = high_resolution_clock::now();
    seq.solve(p);
    auto t2 = high_resolution_clock::now();

    duration<double, std::milli> seqTime = t2 - t1;

    std::ofstream csvFile;
    std::string filename = "threadsTest/" + testName;
    csvFile.open (filename);
    for(int t = 1; t <= 100; t++){
        printf("numero di particelle = %d\nnumero di thread = %d\ndimensione labirinto = %d\n", p, t, w*h);

        MazeSolverPar par(maze, t, false);

        auto t3 = high_resolution_clock::now();
        par.solve(p);
        auto t4 = high_resolution_clock::now();

        duration<double, std::milli> parTime = t4 - t3;

        std::cout << "Tempo sequenziale: " << seqTime.count() << "ms" << std::endl;
        std::cout << "Tempo parallelo: " << parTime.count() << "ms" << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;

        csvFile << t << ";" << seqTime.count() << ";" << parTime.count() << "\n";

    }
    csvFile.close();
}
void threadsTestV2(std::string const &testName){

    printf("\n\nTEST 3v2: STUDIO SUL NUMERO DI THREAD\n");

    int w = 50;
    int h = 50;
    int th1 = 10;
    int th2 = 100;
    int th3 = 500;

    Maze maze(w, h);

    MazeSolverPar par1(maze, th1, false);
    MazeSolverPar par2(maze, th2, false);
    MazeSolverPar par3(maze, th3, false);

    std::ofstream csvFile;
    std::string filename = "threadsTestV2/" + testName;
    csvFile.open (filename);
    for(int p = 1; p <= 1001; p=p+100){
        printf("numero di particelle = %d\n", p);


        auto t1 = high_resolution_clock::now();
        par1.solve(p);
        auto t2 = high_resolution_clock::now();

        auto t3 = high_resolution_clock::now();
        par2.solve(p);
        auto t4 = high_resolution_clock::now();

        auto t5 = high_resolution_clock::now();
        par3.solve(p);
        auto t6 = high_resolution_clock::now();


        duration<double, std::milli> par1Time = t2 - t1;
        duration<double, std::milli> par2Time = t4 - t3;
        duration<double, std::milli> par3Time = t6 - t5;

        std::cout << th1 << " thread: " << par1Time.count() << "ms" << std::endl;
        std::cout << th2 << " thread: " << par2Time.count() << "ms" << std::endl;
        std::cout << th3 << " thread: " << par3Time.count() << "ms" << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;


        csvFile << p << ";" << par1Time.count() << ";" << par2Time.count() << ";" << par3Time.count() << "\n";

    }
    csvFile.close();
}
void lockTest(std::string const &testName) {

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
    std::string filename = "lockTest/" + testName;
    csvFile.open (filename);

    csvFile << 0 << ";" << seqTime.count() << ";" << parTime.count() << ";" << lockedTime.count();
    csvFile.close();
}

int main(int argc, char *argv[]) {
    if(argc != 2){
        printf("Manca il parametro\n");
        return 1;
    }
    srand(time(NULL));

    std::string testName = argv[1];
    dimTest(testName);
    dimTestV2(testName);
    particlesTest(testName);
    threadsTest(testName);
    threadsTestV2(testName);
    lockTest(testName);
    return 0;
}
