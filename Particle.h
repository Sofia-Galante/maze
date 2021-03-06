//
// Created by Sofy on 06/02/2022.
//

#ifndef MAZE_PARTICLE_H
#define MAZE_PARTICLE_H

#include "Coordinate.h"
#include "Map.h"
#include <vector>

class Particle{
public:
    explicit Particle(Coordinate start, int id, Map map);

    void addStep(Coordinate point){
        steps++;
        map.incrValue(point);
    }
    Map getMap() const{
        return map;
    }
    int getSteps() const{
        return steps;
    }
    int getID() const{
        return ID;
    }

private:
    Map map;
    int steps;
    int ID;
};

#endif //MAZE_PARTICLE_H
