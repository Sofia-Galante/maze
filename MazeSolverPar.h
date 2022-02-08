//
// Created by Sofy on 06/02/2022.
//

#include "MazeSolver.h"

#ifndef MAZE_MAZESOLVERPAR_H
#define MAZE_MAZESOLVERPAR_H

class MazeSolverPar : public MazeSolver{
public:
    explicit MazeSolverPar(Maze m) : MazeSolver(m) {}
    std::vector<Coordinate> solve(int numberOfParticles) override;

private:
    void moveParticle(Particle& p) override;
};

#endif //MAZE_MAZESOLVERPAR_H
