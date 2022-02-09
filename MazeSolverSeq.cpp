//
// Created by Sofy on 06/02/2022.
//

#include "MazeSolverSeq.h"

std::vector<Coordinate> MazeSolverSeq::solve(int numberOfParticles) {
    std::vector<Particle> particles;

    printf("\n\n Risolvere il labirinto: modo sequenziale\n");
    //fa risolvere il labirinto a tutte le particelle
    for (int i = 0; i < numberOfParticles; i++) {
        printf("Particella n %d entra nel labirinto\n", i+1);
        Particle p(maze.getStart());
        moveParticle(p);
        particles.push_back(p);
        printf("Particella n %d uscita dal labirinto compiendo %d passi\n\n", i+1, p.getSteps());
    }

    //sceglie un vincitore
    Particle * winner = &(*particles.begin());
    printf("\n\n");
    for(auto particle = particles.begin()+1 ; particle != particles.end(); ++particle){
        if(particle->getSteps() < winner->getSteps())
            winner = &(*particle);
    }


    //disegna il cammino del vincitore e lo restituisce al main
    print(winner);
    return winner->getPath();
}

//NOTA: Questa funzione chiama quella del Maze perché è sequenziale, nella versione parallela va riscritta
void MazeSolverSeq::moveParticle(Particle& particle) {
    std::vector<Coordinate> path;
    std::vector<Coordinate> possibleMoves;
    while(particle.getPath().back()!=maze.getEnd()) {
        path = particle.getPath();
        possibleMoves = maze.validMoves(path.back(), path);
        int i = 1;
        while(possibleMoves.empty()){
            i++;
            possibleMoves = maze.validMoves(path[path.size()-i], path);
            particle.addStep(path[path.size()-i]); //non dà noia nel loop perché path contiene la vecchia lista.
            printf("Indietro in %d, %d\n", particle.getPath().back().getX(), particle.getPath().back().getY());
        }
        particle.addStep(possibleMoves[rand()%possibleMoves.size()]);
        printf("Avanti in %d, %d\n", particle.getPath().back().getX(), particle.getPath().back().getY());
    }
}

void MazeSolverSeq::print(Particle * winner){
    std::vector<Coordinate> winnerPath = winner->getPath();
    std::vector<Coordinate> walls = maze.getWalls();
    Coordinate p;
    for(int j=maze.getHeight()-1; j>=0; j--){
        for(int i=0; i<maze.getWidth(); i++){
            p.setCoordinate(i, j);
            if(std::count(walls.begin(), walls.end(), p))
                printf("#");
            else if(p.operator==(maze.getStart()))
                printf("S");
            else if(p.operator==(maze.getEnd()))
                printf("E");
            else if(std::count(winnerPath.begin(), winnerPath.end(), p))
                printf("*");
            else
                printf("-");
        }
        printf("\n");
    }
}