//
// Created by Sofy on 06/02/2022.
//

#include "MazeSolverSeq.h"

std::vector<Coordinate> MazeSolverSeq::solve(int numberOfParticles) {
    std::vector<Particle> particles;

    printf("\n\nRisolvere il labirinto: modo sequenziale\n");
    //fa risolvere il labirinto a tutte le particelle
    for (int i = 0; i < numberOfParticles; i++) {
        printf("Particella n %d entra nel labirinto\n", i+1);
        Particle p(maze.getStart(), i+1);
        moveParticle(p);
        particles.push_back(p);
        printf("Particella n %d uscita dal labirinto compiendo %d passi\n\n", i+1, p.getSteps());
    }

    //sceglie un vincitore
    auto winner = particles.begin();
    //printf("\n\n");
    for(auto particle =  particles.begin()+1 ; particle != particles.end(); ++particle){
        //printf("%d vs %d\n", winner->getSteps(), (particle)->getSteps());
        if(particle->getSteps() < winner->getSteps())
            winner = particle;
    }


    //disegna il cammino del vincitore e lo restituisce al main
    print(*winner);
    return winner->getPath();
}

//NOTA: Questa funzione chiama quella del Maze perché è sequenziale, nella versione parallela va riscritta
void MazeSolverSeq::moveParticle(Particle& particle) {
    std::vector<Coordinate> path;
    std::vector<Coordinate> possibleMoves;
    bool exit = false;
    while(particle.getPath().back()!=maze.getEnd() && !exit) {
        path = particle.getPath();
        possibleMoves = maze.validMoves(path.back(), path);
        int i = 1;
        while(possibleMoves.empty() && !exit){
            i++;
            possibleMoves = maze.validMoves(path[path.size()-i], path);
            particle.addStep(path[path.size()-i]); //non dà noia nel loop perché path contiene la vecchia lista.
            //printf("Indietro in %d, %d\n", particle.getPath().back().getX(), particle.getPath().back().getY());
            exit = particle.getPath().size() > maze.getMaxSteps();
        }
        if(!exit){
            particle.addStep(possibleMoves[rand()%possibleMoves.size()]);
            exit = particle.getPath().size() > maze.getMaxSteps();
        }

        //printf("Avanti in %d, %d\n", particle.getPath().back().getX(), particle.getPath().back().getY());
    }
}

