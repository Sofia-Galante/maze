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
    Coordinate move(std::vector<Coordinate> availableMoves); //Le possibili mosse sono scelte dal Solver e non dalla particella -> possibile paralelizzazione


private:
    std::vector<Coordinate> positions;
    int steps;
};

#endif //MAZE_PARTICLE_H
