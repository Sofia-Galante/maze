//
// Created by Sofy on 08/02/2022.
//

#include "MazeSolver.h"

void MazeSolver::print(Particle &winner){
    std::vector<Coordinate> winnerPath = winner.getPath();
    std::vector<Coordinate> walls = maze.getWalls();
    Coordinate p;
    for(int j=maze.getHeight()-1; j>=0; j--){
        for(int i=0; i<maze.getWidth(); i++){
            p.setCoordinate(i, j);
            if(std::count(walls.begin(), walls.end(), p))
                printf("#");
            else if(p.operator==(maze.getStart()))
                printf("S");
            else if(p.operator==(maze.getEnd()))
                printf("E");
            else if(std::count(winnerPath.begin(), winnerPath.end(), p))
                printf("*");
            else
                printf("-");
        }
        printf("\n");
    }
}