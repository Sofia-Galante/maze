//
// Created by Sofy on 06/02/2022.
//

#include "Particle.h"

#include <cstdlib>

Particle::Particle(Coordinate start, int id) {
    steps = 0;
    ID = id;
    path.push_back(start); //starting point
}


