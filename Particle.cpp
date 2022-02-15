//
// Created by Sofy on 06/02/2022.
//

#include "Particle.h"

#include <cstdlib>

Particle::Particle(Coordinate start, int id, Map map) : map(map) {
    steps = 0;
    ID = id;
    map.incrValue(start);
}


