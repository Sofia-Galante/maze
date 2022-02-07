//
// Created by Sofy on 06/02/2022.
//

#ifndef MAZE_MAZE_H
#define MAZE_MAZE_H

#include <vector>
#include "Coordinate.h"

class Maze {
public:
    explicit Maze(int w, int h);
    std::vector<Coordinate> getWalls();

    Coordinate getStart(){
        return start;
    }
    Coordinate getEnd(){
        return end;
    }

private:
    Coordinate setStartOrEnd();
    bool isPointValid(Coordinate point, std::vector<Coordinate> notValidPoints);
    std::vector<Coordinate> validMoves(Coordinate p, std::vector<Coordinate> previousMoves);
    void createValidPath();
    void placeWalls();

    int height;
    int width;
    std::vector<Coordinate> walls;
    std::vector<Coordinate> path;
    Coordinate start;
    Coordinate end;
};

#endif //MAZE_MAZE_H