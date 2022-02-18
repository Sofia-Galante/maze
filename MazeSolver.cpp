//
// Created by Sofy on 08/02/2022.
//

#include "MazeSolver.h"

void MazeSolver::print(Particle &winner){
    printf("VINCE LA PARTICELLA %d CON %d PASSI\n", winner.getID(), winner.getSteps());

    Coordinate p;
    for(int j=maze.getHeight()-1; j>=0; j--){
        for(int i=0; i<maze.getWidth(); i++){
            p.setCoordinate(i, j);
            if(maze.getMap().getValue(p) == -1)
                printf("#");
            else if(p.operator==(maze.getStart()))
                printf("S");
            else if(p.operator==(maze.getEnd()))
                printf("E");
            else if(winner.getMap().getValue(p) > 0)
                printf("*", winner.getMap().getValue(p));
            else
                printf("-");
        }
        printf("\n");
    }
}

bool MazeSolver::moveParticle(Particle &particle) {
    Coordinate now = maze.getStart();
    std::vector<Coordinate> possibleMoves;
    bool inTime = true;

    while(particle.getMap().getValue(maze.getEnd()) == 0 && inTime) {
        possibleMoves = validMoves(now);
        now = possibleMoves[rand()%possibleMoves.size()];
        particle.addStep(now);
        inTime = particle.getSteps() < maze.getMaxSteps();
    }
    return inTime;
}

bool MazeSolver::isPointValid(Coordinate next) {
    if(next.getX() < 0 || next.getX() >= maze.getWidth())
        return false;
    if(next.getY() < 0 || next.getY() >= maze.getHeight())
        return false;
    if(maze.getMap().getValue(next) == -1)
        return false;
    return true;
}

std::vector<Coordinate> MazeSolver::validMoves(Coordinate now) {
    std::vector<Coordinate> moves;
    std::vector<Coordinate> rightMoves;
    moves.emplace_back(now.getX(), now.getY()+1);
    moves.emplace_back(now.getX()+1, now.getY());
    moves.emplace_back(now.getX(), now.getY()-1);
    moves.emplace_back(now.getX()-1, now.getY());

    for(auto it = moves.begin(); it != moves.end(); ++it)
        if(isPointValid(*it))
            rightMoves.push_back(*it);

    return rightMoves;
}