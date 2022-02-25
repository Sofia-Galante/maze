//
// Created by Sofy on 06/02/2022.
//

#ifndef MAZE_MAZE_H
#define MAZE_MAZE_H

#include <vector>
#include <tuple>
#include <cstdlib>
#include <algorithm>
#include "Coordinate.h"
#include "Map.h"


class Maze {
public:
    explicit Maze(int w, int h);

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
    int getMaxSteps(){
        return maxSteps;
    }
    Map getMap(){
        return map;
    }



private:
    void createMaze();
    void setStartAndEnd();
    Coordinate setStartOrEnd(int wall);
    std::vector<Coordinate> validMoves(Coordinate now, bool inRecovery);
    bool isPointValid(Coordinate point, bool inRecovery);
    void placeWalls(Coordinate now);
    void placeWall(Coordinate p, int x, int y);
    Coordinate rewind(Coordinate now);

    int getDirection(Coordinate now, Coordinate prev);

    void recovery();
    std::vector<Coordinate> findWallsToRemove(Coordinate now);
    void print();

    int height;
    int width;
    Coordinate start;
    Coordinate end;
    int maxSteps;
    Map map; // -1 = wall, {1, 2, 3, 4} = {nord, est, sud, ovest}
};

#endif //MAZE_MAZE_H