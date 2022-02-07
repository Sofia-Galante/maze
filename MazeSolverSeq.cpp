//
// Created by Sofy on 06/02/2022.
//

#include "MazeSolverSeq.h"

Particle MazeSolverSeq::solve(Maze& maze, int numberOfParticles) {
    Coordinate start = maze.getStart();
    std::vector<Particle> particles;

    for(int i = 0; i<numberOfParticles; i++) {
        Particle p(start);
        bool exit = false;
        //while(!exit){
            //TODO: seleziona la mossa giusta
            //Coordinate move = p.move();
            //if (move.operator==(maze.getEnd()))
                //exit = true;
        //}
        particles.push_back(p);
    }

    //TODO: seleziona un vincitore
}