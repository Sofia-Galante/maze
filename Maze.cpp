//
// Created by Sofy on 06/02/2022.
//

#include "Maze.h"
#include <cstdlib>
#include <algorithm>

#include <cstdio>

Maze::Maze(int w, int h) {
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
    while(!isPointValid(p, notValidExit)){
        p.setCoordinate(setStartOrEnd());
    }
    end.setCoordinate(p.getX(), p.getY());

    printf("Start = %d,%d\n", start.getX(), start.getY());
    printf("End = %d, %d\n", end.getX(), end.getY());

    printf("\n\n\n");
    //genera il cammino valido
    createValidPath();

    //riempe il resto del labirinto


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
        y = rand()%(height-2) + 1;
    }
    else if (wall == 2){
        x = rand()%(width-2)+1;
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
    //std::vector<Coordinate> path;
    path.push_back(start);
    Coordinate p;

    //crea il contorno del labirinto
    for(int i = 0; i<width; i++){
        p.setCoordinate(i, 0);
        if(p.operator!=(start) && p.operator!=(end))
            walls.push_back(p);

        p.setCoordinate(i, height-1);
        if(p.operator!=(start) && p.operator!=(end))
            walls.push_back(p);
    }

    for(int j = 1; j<height-1; j++){
        p.setCoordinate(0, j);
        if(p.operator!=(start) && p.operator!=(end))
            walls.push_back(p);

        p.setCoordinate(width-1, j);
        if(p.operator!=(start) && p.operator!=(end))
            walls.push_back(p);
    }


    std::vector<Coordinate> moves;

    //imposta le mura intorno all'uscita per non creare un deadlock
    Coordinate inFrontOfExit = validMoves(end, path).front();
    Coordinate possibleWall;
    std::vector<Coordinate> possibleWalls;
    for(int i = inFrontOfExit.getX()-1; i<=inFrontOfExit.getX()+1; i++){
        for(int j = inFrontOfExit.getY()-1; j<=inFrontOfExit.getY()+1; j++){
            possibleWall.setCoordinate(i, j);
            if(possibleWall != inFrontOfExit && !std::count(walls.begin(), walls.end(), possibleWall)){
                possibleWalls.push_back(possibleWall);
            }
        }
    }
    for(auto it = possibleWalls.begin() ; it != possibleWalls.end(); ++it){
        if(it->getX()!=inFrontOfExit.getX() && it->getY()!=inFrontOfExit.getY())
            walls.push_back(*it);
    }


    //crea il cammino dall'entrata all'uscita
    int i;
    while(path.back()!=end) {
        moves = validMoves(path.back(), path);
        i=1;
        while(moves.empty()) {
            printf("TORNO INDIETRO\n");
            moves = validMoves(path[path.size()-i], path);
            i++;
        }
        if(std::count(moves.begin(), moves.end(), inFrontOfExit)){
            path.push_back(inFrontOfExit);
            path.push_back(end);
        }
        else {
            //espande il cammino
            path.push_back(moves[rand()%moves.size()]);
            //mette i muri se servono
            placeWalls();
        }
        printf("SCELTO %d, %d\n", path.back().getX(), path.back().getY());
    }

    for(int i=0; i<path.size(); i++){
        printf("(%d, %d)", path[i].getX(), path[i].getY());
    }

    printf("\n\nMURA\n");
    for(auto it = walls.begin() ; it != walls.end(); ++it)
        printf("(%d, %d) ", it->getX(), it->getY());
    printf("\n");
}

void Maze::placeWalls(){
    Coordinate ne(path.back().getX()+1, path.back().getY()+1); //nord-est
    Coordinate se(path.back().getX()+1, path.back().getY()-1); //sud-est
    Coordinate sw(path.back().getX()-1, path.back().getY()-1); //sud-ovest
    Coordinate nw(path.back().getX()-1, path.back().getY()+1); //nord-ovest

    if(std::count(path.begin(), path.end(), ne)) {
        walls.emplace_back(ne.getX(), ne.getY()-1);
        walls.emplace_back(ne.getX()-1, ne.getY());
    }
    if(std::count(path.begin(), path.end(), se)) {
        walls.emplace_back(se.getX(), se.getY()+1);
        walls.emplace_back(se.getX()-1, se.getY());
    }
    if(std::count(path.begin(), path.end(), sw)) {
        walls.emplace_back(sw.getX(), sw.getY()+1);
        walls.emplace_back(sw.getX()+1, sw.getY());
    }
    if(std::count(path.begin(), path.end(), nw)) {
        walls.emplace_back(nw.getX(), nw.getY()-1);
        walls.emplace_back(nw.getX()+1, nw.getY());
    }
}

std::vector<Coordinate> Maze::validMoves(Coordinate p, std::vector<Coordinate> previousMoves) {
    std::vector<Coordinate> moves;
    std::vector<Coordinate> rightMoves;
    moves.emplace_back(p.getX(), p.getY()+1);
    moves.emplace_back(p.getX()+1, p.getY());
    moves.emplace_back(p.getX(), p.getY()-1);
    moves.emplace_back(p.getX()-1, p.getY());

    for(auto it = moves.begin() ; it != moves.end(); ++it){
        if(isPointValid(*it, previousMoves))
            rightMoves.push_back(*it);
    }
    return rightMoves;
}

bool Maze::isPointValid(Coordinate point, std::vector<Coordinate> notValidPoints){
    if(point.getX() < 0 || point.getX() >= width){
        return false;
    }
    if(point.getY() < 0 || point.getY() >= height){
        return false;
    }

    if (std::count(notValidPoints.begin(), notValidPoints.end(), point)){
        return false;
    }
    if (std::count(walls.begin(), walls.end(), point)){
        return false;
    }
    return true;
}

std::vector<Coordinate> Maze::getWalls() {
    return walls;
}