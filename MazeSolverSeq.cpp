//
// Created by Sofy on 06/02/2022.
//

#include "MazeSolverSeq.h"

void MazeSolverSeq::solve(int numberOfParticles) {
    std::vector<Particle> particles;

    printf("\n\nRisolvere il labirinto: modo sequenziale\n");
    //fa risolvere il labirinto a tutte le particelle
    for (int i = 0; i < numberOfParticles; i++) {
        printf("Particella n %d entra nel labirinto\n", i+1);
        Map map(maze.getWidth(), maze.getHeight());
        Particle p(maze.getStart(), i+1, map);
        bool inTime = moveParticle(p);
        if(inTime){
            particles.push_back(p);
            printf("Particella n %d uscita dal labirinto compiendo %d passi\n\n", i+1, p.getSteps());
        }
        else{
            printf("La particella n %d non ha trovato l'uscita\n\n", i+1);
        }
    }

    if(particles.empty())
        printf("Nessuna particella ha trovato l'uscita\n");
    else{
        //sceglie un vincitore
        auto winner = particles.begin();
        for(auto particle =  particles.begin()+1 ; particle != particles.end(); ++particle){
            if(particle->getSteps() < winner->getSteps())
                winner = particle;
        }
        //disegna il cammino del vincitore
        print(*winner);
    }
}


std::vector<Coordinate> MazeSolverSeq::validMoves(Coordinate now) {
    std::vector<Coordinate> moves;
    std::vector<Coordinate> rightMoves;
    moves.emplace_back(now.getX(), now.getY()+1);
    moves.emplace_back(now.getX()+1, now.getY());
    moves.emplace_back(now.getX(), now.getY()-1);
    moves.emplace_back(now.getX()-1, now.getY());

    for(auto it = moves.begin(); it != moves.end(); ++it)
        if(isPointValid(*it))
            rightMoves.push_back(*it);

    return rightMoves;
}

