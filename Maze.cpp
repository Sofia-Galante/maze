//
// Created by Sofy on 06/02/2022.
//

#include "Maze.h"
#include <cstdlib>
#include <algorithm>

Maze::Maze(int h, int w) {
    width = w;
    height = h;
    Coordinate p;
    //TODO: algoritmo che genera il labirinto

    //sceglie il punto di partenza
    p = setStartOrEnd();
    start.setCoordinate(p.getX(), p.getY());
    end.setCoordinate(p.getX(), p.getY()); //placeholder

    //posizioni non valide per l'uscita
    std::vector<Coordinate> notValidExit;
    for(int i = start.getX()-2; i<=start.getX()+2; i++){
        for(int j = start.getY()-2; j<=start.getY()+2; j++){
            notValidExit.emplace_back(i, j);
        }
    }

    //sceglie il punto di arrivo e controlla sia valido
    while(!isEndValid(notValidExit)){
        p = setStartOrEnd();
    }
    end.setCoordinate(p.getX(), p.getY());

    //genera il cammino valido


}

Coordinate Maze::setStartOrEnd() {
    int x, y;
    int wall = rand() % 4; // 0 = up, 1 = right, 2 = down, 3 = left
    if(wall == 0){
        x = rand()%(width-1)+1;
        y = height-1;
    }
    else if (wall == 1){
        x = width-1;
        y = rand()%(height-1)+1;
    }
    else if (wall == 2){
        x = rand()%(width-1)+1;
        y = 0;
    }
    else {
        x = 0;
        y = rand()%(height-1)+1;
    }

    Coordinate point(x, y);
    return point;
}

void Maze::createValidPath() {

}


bool Maze::isEndValid(std::vector<Coordinate> p){
    if (std::count(p.begin(), p.end(), end)) {
        return false;
    }
    return true;
}

std::vector<Coordinate> Maze::getWalls() {
    return walls;
}