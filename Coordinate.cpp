//
// Created by Sofy on 06/02/2022.
//

#include "Coordinate.h"

Coordinate::Coordinate(int x, int y) {
    setCoordinate(x, y);
}

void Coordinate::setCoordinate(int x, int y) {
    point[0] = x;
    point[1] = y;
}
