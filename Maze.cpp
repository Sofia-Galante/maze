//
// Created by Sofy on 06/02/2022.
//

#include "Maze.h"

char DIR[5] {'A', 'N', 'E', 'S', 'O'};

#include <cstdio>

Maze::Maze(int w, int h) : map(w, h){
    width = w;
    height = h;
    Coordinate p;

    setStartAndEnd();

    printf("Start = %d,%d\n", start.getX(), start.getY());
    printf("End = %d, %d\n", end.getX(), end.getY());

    printf("\n\n\n");
    //genera il labirinto
    createMaze();


}
void Maze::setStartAndEnd() {
    int wallS = rand() % 4; // 0 = up, 1 = right, 2 = down, 3 = left
    int wallE = (wallS + 2) % 4;
    start = setStartOrEnd(wallS);
    end = setStartOrEnd(wallE);
}
Coordinate Maze::setStartOrEnd(int wall){
    int x, y;
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
    return Coordinate(x, y);
}

void Maze::createMaze() {

    Coordinate p;

    //crea il contorno del labirinto
    for(int i = 0; i<width; i++){
        p.setCoordinate(i, 0);
        if(p.operator!=(start) && p.operator!=(end))
            map.setValue(p, -1);

        p.setCoordinate(i, height-1);
        if(p.operator!=(start) && p.operator!=(end))
            map.setValue(p, -1);
    }

    for(int j = 1; j<height-1; j++){
        p.setCoordinate(0, j);
        if(p.operator!=(start) && p.operator!=(end))
            map.setValue(p, -1);

        p.setCoordinate(width-1, j);
        if(p.operator!=(start) && p.operator!=(end))
            map.setValue(p, -1);
    }

    std::vector<Coordinate> moves;


    //crea il cammino dall'entrata all'uscita
    bool needRecovery = false;
    Coordinate prev = start;
    Coordinate now = validMoves(prev, false).front();
    map.setValue(now, getDirection(now, prev));
    map.setValue(prev, getDirection(now, prev));
    while(map.getValue(end) == 0) {
        moves = validMoves(now, false);
        while(moves.empty() && !needRecovery) { //rewind
            now = rewind(now);
            moves = validMoves(now, false);
            if(now==start)
                needRecovery = true;
        }
        if(needRecovery){
            printf("START RECOVERY\n");
            recovery();
            printf("END RECOVERY\n");
            needRecovery = false;
        }
        else if(std::count(moves.begin(), moves.end(), end)){
            //path.push_back(end);
            prev = now;
            now = end;
            map.setValue(now, getDirection(now, prev));
        }
        else {
            //espande il cammino
            //path.push_back(moves[rand()%moves.size()]);
            prev = now;
            now = moves[rand()%moves.size()];
            map.setValue(now, getDirection(now, prev));
            //printf("SCELTO %d, %d, dir = %c\n", now.getX(), now.getY(), DIR[map.getValue(now)]);
            //mette i muri se servono
            placeWalls(now);
        }
    }

    printf("Cammino valido creato!\n\n");

    maxSteps = 0;
    for(int w = 0; w < width; w++){
        for(int h = 0; h < height; h++){
            if(map.getValue(Coordinate(w, h)) > 0)
                maxSteps++;
        }
    }
    maxSteps = maxSteps*50;
    printf("Max Steps = %d\n", maxSteps);
    now = end;
    while(now != start){
        moves = validMoves(now, false);
        while(moves.empty() && now != start) {
            now = rewind(now);
            moves = validMoves(now, false);
        }
        if(now != start){
            prev = now;
            now = moves[rand()%moves.size()];
            map.setValue(now, getDirection(now, prev));
            //printf("SCELTO %d, %d con dir = %c\n", now.getX(), now.getY(), DIR[map.getValue(now)]);
            //mette i muri se servono
            placeWalls(now);
        }
    }

    //mette un muro nei posti non esplorati se ce ne sono
    for(int w = 0; w < width; w++)
        for(int h = 0; h < height; h++)
            if(map.getValue(Coordinate(w, h)) == 0)
                map.setValue(Coordinate(w, h), -1);

    print();
}

std::vector<Coordinate> Maze::validMoves(Coordinate p, bool inRecovery) {
    std::vector<Coordinate> moves;
    std::vector<Coordinate> rightMoves;
    moves.emplace_back(p.getX(), p.getY()+1);
    moves.emplace_back(p.getX()+1, p.getY());
    moves.emplace_back(p.getX(), p.getY()-1);
    moves.emplace_back(p.getX()-1, p.getY());

    for(auto it = moves.begin(); it != moves.end(); ++it){
        if(isPointValid(*it, inRecovery)) {
            rightMoves.push_back(*it);
        }
    }
    return rightMoves;
}
bool Maze::isPointValid(Coordinate point, bool inRecovery) {
    if(point.getX() < 0 || point.getX() >= width){
        return false;
    }
    if(point.getY() < 0 || point.getY() >= height){
        return false;
    }

    if (map.getValue(point) != 0 && !inRecovery){
        return false;
    }

    return true;
}

Coordinate Maze::rewind(Coordinate now){
    //{1, 2, 3, 4} = {nord, est, sud, ovest}
    int direction = map.getValue(now);
    //printf("Sono in %d, %d con d = %d e vado in ", now.getX(), now.getY(), direction);
    if(direction == 1 || direction == -2)
        now.setCoordinate(now.getX(), now.getY()-1);
    else if(direction == 2 || direction == -3)
        now.setCoordinate(now.getX()-1, now.getY());
    else if(direction == 3 || direction == -4)
        now.setCoordinate(now.getX(), now.getY()+1);
    else
        now.setCoordinate(now.getX()+1, now.getY());
    //printf("%d, %d\n", now.getX(), now.getY());
    return now;
}

void Maze::placeWalls(Coordinate now){
    Coordinate ne(now.getX()+1, now.getY()+1); //nord-est
    Coordinate se(now.getX()+1, now.getY()-1); //sud-est
    Coordinate sw(now.getX()-1, now.getY()-1); //sud-ovest
    Coordinate nw(now.getX()-1, now.getY()+1); //nord-ovest

    placeWall(ne, -1, -1);
    placeWall(se, -1, +1);
    placeWall(sw, 1, 1);
    placeWall(nw, 1, -1);
}
void Maze::placeWall(Coordinate p, int x, int y) {
    Coordinate point;

    if(map.getValue(p) > 0) {
        point.setCoordinate(p.getX(), p.getY()+y);
        //printf("Possibile muro in %d, %d\n", point.getX(), point.getY());
        if(map.getValue(point) == 0){
            map.setValue(point, -1);
            //printf("Ho messo un muro in %d, %d\n", point.getX(), point.getY());
        }

        point.setCoordinate(p.getX()+x, p.getY());
        if(map.getValue(point) == 0){
            //printf("Possibile muro in %d, %d\n", point.getX(), point.getY());
            map.setValue(point, -1);
            //printf("Ho messo un muro in %d, %d\n", point.getX(), point.getY());
        }

    }
}



void Maze::print() {
    //funzione provvisoria solo per capire come è fatto questo labirinto
    Coordinate p;
    printf("\n\nLABIRINTO\n");
    for(int j=height-1; j>=0; j--){
        for(int i=0; i<width; i++){
            p.setCoordinate(i, j);
            if(map.getValue(p) == -1)
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
    std::vector<Coordinate> moves;
    std::vector<int> directions;
    std::vector<Coordinate> wallsToRemove;
    Coordinate now = end;
    Coordinate next;
    bool isPathRecovered = false;

    while(!isPathRecovered) {
        wallsToRemove = findWallsToRemove(now);
        moves = validMoves(now, true);

        for (auto it = moves.begin(); it != moves.end(); ++it) {
            if (!isPathRecovered && map.getValue(*it) > 0) {
                isPathRecovered = true;
                next = now;
                now = *it;
                map.setValue(next, -1-getDirection(next, now));
            }
        }

        if(!isPathRecovered){
            //cerca il muro e lo abbatte
            while(wallsToRemove.empty()){
                while(moves.empty()){
                    //moves = findRecoveryMove(recovery[recovery.size()-i], recovery);
                    now = rewind(now);
                }
                next = now;
                now = moves[rand()%moves.size()];
                map.setValue(next, -1-getDirection(next, now));
                //printf("Vado in (%d, %d)\n", now.getX(), now.getY());
                wallsToRemove = findWallsToRemove(now);
                //moves = findRecoveryMove(recovery.back(), recovery);
                moves = validMoves(now, true);
            }
            next = now;
            now = wallsToRemove[rand()%wallsToRemove.size()];
            //printf("Muro in %d, %d\n", now.getX(), now.getY());
            map.setValue(next, -1-getDirection(next, now));
            map.setValue(now, 0);
        }

    }
    //uscita e entrata sono collegate -> inserisco il recovery nel path
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            Coordinate p(i, j);
            int value = map.getValue(p);
            if(value<-1)
                map.setValue(p, -(value+1));
        }
    }

}

std::vector<Coordinate> Maze::findWallsToRemove(Coordinate now) {
    std::vector<Coordinate> moves;
    std::vector<Coordinate> wallsToRemove;
    moves.emplace_back(now.getX(), now.getY()+1);
    moves.emplace_back(now.getX()+1, now.getY());
    moves.emplace_back(now.getX(), now.getY()-1);
    moves.emplace_back(now.getX()-1, now.getY());

    for(auto it = moves.begin() ; it != moves.end(); ++it){
        if(it->getX() > 0 && it->getX() < width-1 && it->getY() > 0 && it->getY() < height-1)//non deve essere al confine o oltre
            if (map.getValue(*it) == -1) //deve essere un muro
                wallsToRemove.push_back(*it);
    }
    return wallsToRemove;
}

int Maze::getDirection(Coordinate now, Coordinate prev) {
    //{1, 2, 3, 4} = {nord, est, sud, ovest}
    if(prev.getX() == now.getX()){
        if(prev.getY() == now.getY()-1)
            return 1;
        else
            return 3;
    }
    else {
        if(prev.getX() == now.getX()-1)
            return 2;
        else
            return 4;
    }
}
