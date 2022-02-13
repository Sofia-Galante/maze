//
// Created by Sofy on 06/02/2022.
//

#include <omp.h>

#include "MazeSolver.h"

#ifndef MAZE_MAZESOLVERPAR_H
#define MAZE_MAZESOLVERPAR_H

class MazeSolverPar : public MazeSolver{
public:
    explicit MazeSolverPar(Maze m) : MazeSolver(m) {}
    std::vector<Coordinate> solve(int numberOfParticles) override;

private:
    void moveParticle(Particle& p) override;
    std::vector<Coordinate> validMoves(Coordinate p, std::vector<Coordinate> previousMoves);
    bool isPointValid(Coordinate point, std::vector<Coordinate> notValidPoints);
};

#endif //MAZE_MAZESOLVERPAR_H
