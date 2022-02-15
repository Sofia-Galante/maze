//
// Created by Sofy on 15/02/2022.
//

#include "Map.h"

Map::Map(int width, int height) : width(width), height(height) {
    map = std::vector<int> (width*height, 0);
}