//
// Created by Sofy on 06/02/2022.
//

#include "MazeSolverPar.h"

std::vector<Coordinate> MazeSolverPar::solve(int numberOfParticles) {
    std::vector<Particle> particles;

    printf("\n\nRisolvere il labirinto: modo parallelo\n");
    //fa risolvere il labirinto a tutte le particelle
    omp_set_nested(3);
    std::vector<int> seeds;

    //genera i seeds per la rand()
    for(int i = 0; i < numberOfParticles; i++){
        seeds.push_back(rand());
    }

#pragma omp parallel default(none) shared(particles) firstprivate(numberOfParticles, seeds)
    {
        //fa risolvere il labirinto a tutte le particelle
#pragma omp for
        for (int i = 0; i < numberOfParticles; i++) {
            srand(seeds[i]);
            printf("THREAD %d -> Particella n %d entra nel labirinto\n", omp_get_thread_num(), i + 1);
            Particle p(maze.getStart(), i + 1);
            moveParticle(p);
            particles.push_back(p);
            printf("THREAD %d -> Particella n %d uscita dal labirinto compiendo %d passi\n\n", omp_get_thread_num(), i + 1,
                   p.getSteps());
        }

        //sceglie un vincitore

    }


    auto winner = particles.begin();
    printf("\n\n");

#pragma omp parallel for default(none) firstprivate(particles) shared(winner)
    for(auto particle =  particles.begin()+1 ; particle != particles.end(); ++particle){
        //printf("%d vs %d\n", winner->getSteps(), (particle)->getSteps());
        if(particle->getSteps() < winner->getSteps())
#pragma omp critical
            winner = particle;
    }

    print(*winner);
    return winner->getPath();
}

void MazeSolverPar::moveParticle(Particle &particle) {

    std::vector<Coordinate> path;
    std::vector<Coordinate> possibleMoves;
    bool exit = false;

    while(particle.getPath().back()!=maze.getEnd() && !exit) {
        path = particle.getPath();
        possibleMoves = maze.validMoves(path.back(), path); //PARALLELIZZAZIONE
        int i = 1;
        while(possibleMoves.empty() && !exit){
            i++;
            possibleMoves = maze.validMoves(path[path.size()-i], path);
            particle.addStep(path[path.size()-i]);
            exit = particle.getPath().size() > maze.getMaxSteps();
            //printf("PARTICELLA %d: Indietro in %d, %d\n", particle.getID(), particle.getPath().back().getX(), particle.getPath().back().getY());
        }
        if(!exit){
            particle.addStep(possibleMoves[rand()%possibleMoves.size()]);
            exit = particle.getPath().size() > maze.getMaxSteps();
        }

        //printf("PARTICELLA %d: Avanti in %d, %d\n", particle.getID(), particle.getPath().back().getX(), particle.getPath().back().getY());
    }
}

std::vector<Coordinate> MazeSolverPar::validMoves(Coordinate p, std::vector<Coordinate> previousMoves) {
    std::vector<Coordinate> moves;
    std::vector<Coordinate> rightMoves;
    moves.emplace_back(p.getX(), p.getY()+1);
    moves.emplace_back(p.getX()+1, p.getY());
    moves.emplace_back(p.getX(), p.getY()-1);
    moves.emplace_back(p.getX()-1, p.getY());

#pragma omp parallel for default(none) firstprivate(moves, previousMoves) shared(rightMoves)
    for(auto it = moves.begin() ; it != moves.end(); ++it){
        //printf("MOSSA %d, %d\n", it->getX(), it->getY());
        if(isPointValid(*it, previousMoves))
            rightMoves.push_back(*it);
    }

    return rightMoves;
}

bool MazeSolverPar::isPointValid(Coordinate point, std::vector<Coordinate> notValidPoints) {
    bool valid = true;
    std::vector<Coordinate> walls = maze.getWalls();

#pragma omp parallel sections default(none) shared(valid) firstprivate(point, notValidPoints, walls)
    {
#pragma omp section
        {
            if(point.getX() < 0 || point.getX() >= maze.getWidth()){
                //printf("Sono in sezione 1 (%d,%d)\n", point.getX(), point.getY());
                valid = false;
            }
        }

#pragma omp section
        {
            if(point.getY() < 0 || point.getY() >= maze.getHeight()){
                //printf("Sono in sezione 2 (%d,%d)\n", point.getX(), point.getY());
                valid = false;
            }
        }
#pragma omp section
        {
            if (std::count(notValidPoints.begin(), notValidPoints.end(), point)){
                //printf("Sono in sezione 3 (%d,%d)\n", point.getX(), point.getY());
                valid = false;
            }
        }

#pragma omp section
        {
            if (std::count(walls.begin(), walls.end(), point)){
                //printf("Sono in sezione 4 (%d,%d)\n", point.getX(), point.getY());
                valid = false;
            }
        }
    }
    return valid;
}

