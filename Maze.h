//
// Created by Sofy on 06/02/2022.
//

#ifndef MAZE_MAZE_H
#define MAZE_MAZE_H

#include <vector>
#include "Coordinate.h"

class Maze {
public:
    explicit Maze(int h, int w);
    std::vector<Coordinate> getWalls();

    Coordinate getStart(){
        return start;
    }
    Coordinate getEnd(){
        return end;
    }

private:
    Coordinate setStartOrEnd();
    bool isEndValid(std::vector<Coordinate> p);
    void createValidPath();

    int height;
    int width;
    std::vector<Coordinate> walls;
    Coordinate start;
    Coordinate end;
};

#endif //MAZE_MAZE_H