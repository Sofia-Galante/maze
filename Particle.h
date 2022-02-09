//
// Created by Sofy on 06/02/2022.
//

#ifndef MAZE_PARTICLE_H
#define MAZE_PARTICLE_H

#include "Coordinate.h"
#include <vector>

class Particle{
public:
    explicit Particle(Coordinate start);

    void addStep(Coordinate point){
        steps++;
        path.push_back(point);
    }

    std::vector<Coordinate> getPath(){
        return path;
    }

    int getSteps(){
        return steps;
    }

private:
    std::vector<Coordinate> path;
    int steps;
};

#endif //MAZE_PARTICLE_H
