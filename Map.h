//
// Created by Sofy on 15/02/2022.
//

#ifndef MAZE_MAP_H
#define MAZE_MAP_H

#include <vector>
#include <cassert>

#include "Coordinate.h"

class Map {
public:
    explicit Map(int width, int height);

    int getValue(Coordinate p) const{
        assert(p.getX() >= 0 && p.getY() >= 0 && p.getX() < width && p.getY() < height);
        return map[p.getX()+p.getY()*width];
    }

    void setValue(Coordinate p, int value){
        assert(p.getX() >= 0 && p.getY() >= 0 && p.getX() < width && p.getY() < height);
        map[p.getX()+p.getY()*width] = value;
    }

    void incrValue(Coordinate p){
        assert(p.getX() >= 0 && p.getY() >= 0 && p.getX() < width && p.getY() < height);
        map[p.getX()+p.getY()*width]++;
    }


private:
    std::vector<int> map;
    int width;
    int height;
};

#endif //MAZE_MAP_H
