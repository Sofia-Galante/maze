//
// Created by Sofy on 06/02/2022.
//

#include "Particle.h"

#include <cstdlib>

Particle::Particle(Coordinate start) {
    steps = 0;
    path.push_back(start); //starting point
}

Coordinate Particle::move(std::vector<Coordinate> availableMoves) {
    int n = rand() % availableMoves.size();
    path.push_back(availableMoves[n]);
    return availableMoves[n];
}


