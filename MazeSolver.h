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
    virtual void solve(int numberOfParticles) = 0;


protected:
    bool moveParticle(Particle& p);
    virtual std::vector<Coordinate> validMoves(Coordinate now);
    bool isPointValid(Coordinate next);
    void print(Particle &p);
    Maze maze;
};

#endif //MAZE_MAZESOLVER_H
