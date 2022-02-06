//
// Created by Sofy on 06/02/2022.
//

#ifndef MAZE_MAZESOLVERSEQ_H
#define MAZE_MAZESOLVERSEQ_H

#include "Particle.h"
#include "Maze.h"

class MazeSolverSeq{
public:
    Particle solve(Maze& maze, int numberOfParticles);
};

#endif //MAZE_MAZESOLVERSEQ_H
