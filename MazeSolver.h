//
// Created by Sofy on 08/02/2022.
//
#include <cstdio>

#include "Particle.h"
#include "Maze.h"

#ifndef MAZE_MAZESOLVER_H
#define MAZE_MAZESOLVER_H

class MazeSolver{
public:
    explicit MazeSolver(Maze m) : maze(m){};
    virtual std::vector<Coordinate> solve(int numberOfParticles) = 0;


protected:
    virtual void moveParticle(Particle& p) = 0;
    virtual void print(Particle &p);
    Maze maze;
};

#endif //MAZE_MAZESOLVER_H
