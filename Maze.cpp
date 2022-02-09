//
// Created by Sofy on 06/02/2022.
//

#include "Maze.h"


#include <cstdio>
#include <iostream>

Maze::Maze(int w, int h) {
    width = w;
    height = h;
    Coordinate p;
    //TODO: pulizia nel codice

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
    //genera il labirinto
    createMaze();


}
Coordinate Maze::setStartOrEnd() {
    int x, y;
    int wall = rand() % 4; // 0 = up, 1 = right, 2 = down, 3 = left
    if(wall == 0){
        x = rand()%(width-2)+1;
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
        y = rand()%(height-2)+1;
    }

    Coordinate point(x, y);
    return point;
}
void Maze::createMaze() {

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

    //crea il cammino dall'entrata all'uscita
    int i;
    bool needRecovery = false;
    while(path.back()!=end) {
        moves = validMoves(path.back(), path);
        i=1;
        while(moves.empty()) {
            i++;
            printf("TORNO INDIETRO\n");
            moves = validMoves(path[path.size()-i], path);
            if(path[path.size()-i].operator==(start))
                needRecovery = true;
        }
        if(needRecovery){
            printf("START RECOVERY\n");
            recovery();
            printf("END RECOVERY\n");
            needRecovery = false;
        }
        else if(std::count(moves.begin(), moves.end(), end)){
            //path.push_back(inFrontOfExit);
            path.push_back(end);
        }
        else {
            //espande il cammino
            path.push_back(moves[rand()%moves.size()]);
            printf("SCELTO %d, %d\n", path.back().getX(), path.back().getY());
            //mette i muri se servono
            placeWalls();
        }
    }

    printf("Cammino valido creato!\n\n");

    //genera il resto del labirinto
    Coordinate now;
    std::vector<Coordinate> alreadyControlled;
    for(auto it = path.begin() ; it != path.end(); ++it)
        alreadyControlled.push_back(*it);

    //cammina indietro riempendo tutto il resto del labirinto fino all'uscita

    while(alreadyControlled.back().operator!=(start)){
        moves = validMoves(alreadyControlled.back(), path);
        while(moves.empty() && alreadyControlled.back().operator!=(start)){
            alreadyControlled.pop_back();
            moves = validMoves(alreadyControlled.back(), path);
            i++;
        }
        if(alreadyControlled.back().operator!=(start)){
            //espande il cammino o mette un muro a random
            path.push_back(moves[rand()%moves.size()]);
            alreadyControlled.push_back(path.back());
            //mette i muri se servono
            placeWalls();
        }
    }

    //mette un muro nei posti non esplorati se ce ne sono
    if(width*height != walls.size()+path.size()){
        for(int w = 0; w < width; w++){
            for(int h = 0; h < height; h++){
                now.setCoordinate(w, h);
                if(!std::count(path.begin(), path.end(), now) && !std::count(walls.begin(), walls.end(), now))
                    walls.push_back(now);
            }
        }
    }

    printf("\n\nCAMMINO\n");
    for(int i=0; i<path.size(); i++){
        printf("(%d, %d)", path[i].getX(), path[i].getY());
    }

    printf("\n\nMURA\n");
    for(auto it = walls.begin() ; it != walls.end(); ++it)
        printf("(%d, %d) ", it->getX(), it->getY());
    printf("\n");

    print();
}
void Maze::placeWalls(){
    Coordinate ne(path.back().getX()+1, path.back().getY()+1); //nord-est
    Coordinate se(path.back().getX()+1, path.back().getY()-1); //sud-est
    Coordinate sw(path.back().getX()-1, path.back().getY()-1); //sud-ovest
    Coordinate nw(path.back().getX()-1, path.back().getY()+1); //nord-ovest

    Coordinate point;

    if(std::count(path.begin(), path.end(), ne)) {
        point.setCoordinate(ne.getX(), ne.getY()-1);
        if(!std::count(path.begin(), path.end(), point) && !std::count(walls.begin(), walls.end(), point))
            walls.push_back(point);
        point.setCoordinate(ne.getX()-1, ne.getY());
        if(!std::count(path.begin(), path.end(), point) && !std::count(walls.begin(), walls.end(), point))
            walls.push_back(point);
    }
    if(std::count(path.begin(), path.end(), se)) {
        point.setCoordinate(se.getX(), se.getY()+1);
        if(!std::count(path.begin(), path.end(), point) && !std::count(walls.begin(), walls.end(), point))
            walls.push_back(point);
        point.setCoordinate(se.getX()-1, se.getY());
        if(!std::count(path.begin(), path.end(), point) && !std::count(walls.begin(), walls.end(), point))
            walls.push_back(point);
    }
    if(std::count(path.begin(), path.end(), sw)) {
        point.setCoordinate(sw.getX(), sw.getY()+1);
        if(!std::count(path.begin(), path.end(), point) && !std::count(walls.begin(), walls.end(), point))
            walls.push_back(point);
        point.setCoordinate(sw.getX()+1, sw.getY());
        if(!std::count(path.begin(), path.end(), point) && !std::count(walls.begin(), walls.end(), point))
            walls.push_back(point);
    }
    if(std::count(path.begin(), path.end(), nw)) {
        point.setCoordinate(nw.getX(), nw.getY()-1);
        if(!std::count(path.begin(), path.end(), point) && !std::count(walls.begin(), walls.end(), point))
            walls.push_back(point);
        point.setCoordinate(nw.getX()+1, nw.getY());
        if(!std::count(path.begin(), path.end(), point) && !std::count(walls.begin(), walls.end(), point))
            walls.push_back(point);
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

void Maze::print() {
    //funzione provvisoria solo per capire come è fatto questo labirinto
    Coordinate p;
    printf("\n\nLABIRINTO\n");
    for(int j=height-1; j>=0; j--){
        for(int i=0; i<width; i++){
            p.setCoordinate(i, j);
            if(std::count(walls.begin(), walls.end(), p))
                printf("#");
            else if(p.operator==(start))
                printf("S");
            else if(p.operator==(end))
                printf("E");
            else
                printf("-");
        }
        printf("\n");
    }
}


void Maze::recovery() {
    std::vector<Coordinate> recovery;
    std::vector<Coordinate> moves;
    std::vector<Coordinate> wallsToRemove;
    Coordinate wall;
    Coordinate inFrontOfExit;
    int i;
    recovery.push_back(end);

    //guarda se il muro è davanti all'uscita e in caso lo abbatte
    if(end.getX() == 0)
        inFrontOfExit.setCoordinate(1, end.getY());
    else if(end.getX() == width-1)
        inFrontOfExit.setCoordinate(width-2, end.getY());
    else if(end.getY() == 0)
        inFrontOfExit.setCoordinate(end.getX(), 1);
    else if(end.getY() == height-1)
        inFrontOfExit.setCoordinate(end.getX(), height-2);

    if(std::count(walls.begin(), walls.end(), inFrontOfExit)){
        std::remove(walls.begin(), walls.end(), inFrontOfExit); //elimina il muro che blocca l'uscita
    }
    recovery.push_back(inFrontOfExit);
    printf("Vado in (%d, %d)\n", recovery.back().getX(), recovery.back().getY());

    bool isPathRecovered = std::count(path.begin(), path.end(), recovery.back());
    while(!isPathRecovered){

        wallsToRemove = findWallsToRemove(recovery);
        moves = findRecoveryMove(recovery.back(), recovery);

        for(auto it = moves.begin(); it != moves.end(); ++it){
            if(!isPathRecovered && std::count(path.begin(), path.end(), *it)){
                isPathRecovered = true;
            }
        }

        if(!isPathRecovered){
            //cerca il muro e lo abbatte
            while(wallsToRemove.empty()){
                i = 1;
                while(moves.empty()){
                    i++;
                    moves = findRecoveryMove(recovery[recovery.size()-i], recovery);
                }
                recovery.push_back(moves[rand()%moves.size()]);
                printf("Vado in (%d, %d)\n", recovery.back().getX(), recovery.back().getY());
                wallsToRemove = findWallsToRemove(recovery);
                //placeWalls();
                moves = findRecoveryMove(recovery.back(), recovery);
            }
            wall = wallsToRemove[rand()%wallsToRemove.size()];
            std::remove(walls.begin(), walls.end(), wall);
            recovery.push_back(wall);
        }
    }

    //uscita e entrata sono collegate -> inserisco il recovery nel path
    for(auto it = recovery.end()-1; it != recovery.begin()-1; --it){
        printf("%d, %d\n", it->getX(), it->getY());
        path.push_back(*it);
    }
}

std::vector<Coordinate> Maze::findRecoveryMove(Coordinate p, std::vector<Coordinate> recovery) {
    std::vector<Coordinate> moves;
    std::vector<Coordinate> rightMoves;
    moves.emplace_back(p.getX(), p.getY()+1);
    moves.emplace_back(p.getX()+1, p.getY());
    moves.emplace_back(p.getX(), p.getY()-1);
    moves.emplace_back(p.getX()-1, p.getY());

    for(auto it = moves.begin() ; it != moves.end(); ++it){
        if (!std::count(recovery.begin(), recovery.end(), *it))
            if(it->getX() != 0 && it->getX() != width-1 && it->getY() != 0 && it->getY() != height-1)
                rightMoves.push_back(*it);
    }
    return rightMoves;
}

std::vector<Coordinate> Maze::findWallsToRemove(std::vector<Coordinate> recovery) {
    std::vector<Coordinate> moves;
    std::vector<Coordinate> wallsToRemove;
    moves.emplace_back(recovery.back().getX(), recovery.back().getY()+1);
    moves.emplace_back(recovery.back().getX()+1, recovery.back().getY());
    moves.emplace_back(recovery.back().getX(), recovery.back().getY()-1);
    moves.emplace_back(recovery.back().getX()-1, recovery.back().getY());

    for(auto it = moves.begin() ; it != moves.end(); ++it){
        if (std::count(walls.begin(), walls.end(), *it)) //deve essere un muro
            if(it->getX() != 0 && it->getX() != width-1 && it->getY() != 0 && it->getY() != height-1) //non deve essere un muro di confine
                wallsToRemove.push_back(*it);
    }
    return wallsToRemove;
}