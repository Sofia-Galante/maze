//
// Created by Sofy on 06/02/2022.
//

#ifndef MAZE_MAZE_H
#define MAZE_MAZE_H

#include <vector>
#include <cstdlib>
#include <algorithm>
#include "Coordinate.h"


class Maze {
public:
    explicit Maze(int w, int h);

    std::vector<Coordinate> getWalls(){
        return walls;
    }
    //std::vector<Coordinate> getPath(){
        //return path;
    //}
    Coordinate getStart(){
        return start;
    }
    Coordinate getEnd(){
        return end;
    }
    int getWidth(){
        return width;
    }
    int getHeight(){
        return height;
    }

    std::vector<Coordinate> validMoves(Coordinate p, std::vector<Coordinate> previousMoves);

private:
    Coordinate setStartOrEnd();
    bool isPointValid(Coordinate point, std::vector<Coordinate> notValidPoints);
    void createMaze();
    void placeWalls();

    void recovery();
    std::vector<Coordinate> findWallsToRemove(std::vector<Coordinate> recovery);
    std::vector<Coordinate> findRecoveryMove(Coordinate p, std::vector<Coordinate> recovery);

    void print();

    int height;
    int width;
    std::vector<Coordinate> walls;
    std::vector<Coordinate> path;
    Coordinate start;
    Coordinate end;
};

#endif //MAZE_MAZE_H