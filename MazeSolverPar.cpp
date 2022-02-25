//
// Created by Sofy on 06/02/2022.
//

#include "MazeSolverPar.h"

void MazeSolverPar::solve(int numberOfParticles) {
    std::vector<Particle> particles;

    printf("\n\nRisolvere il labirinto: modo parallelo\n");

    omp_set_nested(3);
    std::vector<int> seeds;

    //genera i seeds per la rand()
    for(int i = 0; i < numberOfParticles; i++){
        seeds.push_back(rand());
    }

#pragma omp parallel for default(none) shared(particles) firstprivate(numberOfParticles, seeds, maze) num_threads(threads)
    //fa risolvere il labirinto a tutte le particelle
    for (int i = 0; i < numberOfParticles; i++) {
        srand(seeds[i]);
        std::vector<Particle> localParticles;
        printf("THREAD %d -> Particella n %d entra nel labirinto\n", omp_get_thread_num(), i+1);
        Map map(maze.getWidth(), maze.getHeight());
        Particle p(maze.getStart(), i+1, map);
        bool inTime = moveParticle(p);
        if(inTime){
            localParticles.push_back(p);
            printf("THREAD %d -> Particella n %d uscita dal labirinto compiendo %d passi\n\n", omp_get_thread_num(), i+1, p.getSteps());
        }
        else{
            printf("THREAD %d -> La particella n %d non ha trovato l'uscita\n\n", omp_get_thread_num(), i+1);
        }
#pragma omp critical
        particles.insert(particles.end(), localParticles.begin(), localParticles.end());
    }

    if(particles.empty())
        printf("Nessuna particella ha trovato l'uscita\n");
    else{
        //sceglie un vincitore
        Particle winner = *particles.begin();
#pragma omp parallel for default(none) firstprivate(particles) shared(winner) num_threads(threads)
        for(int i = 0; i < particles.size(); i++){
#pragma omp flush(winner)
            if(particles[i].getSteps() < winner.getSteps())
#pragma omp critical
                winner = particles[i];
#pragma omp flush(winner)
        }
        //disegna il cammino del vincitore
        print(winner);
    }
}


std::vector<Coordinate> MazeSolverPar::validMoves(Coordinate now) {
    if(withLock)
        return validMovesLock(now);
    return MazeSolver::validMoves(now);
}

std::vector<Coordinate> MazeSolverPar::validMovesLock(Coordinate now) {
    std::vector<Coordinate> moves;
    std::vector<Coordinate> rightMoves;
    moves.emplace_back(now.getX(), now.getY()+1);
    moves.emplace_back(now.getX()+1, now.getY());
    moves.emplace_back(now.getX(), now.getY()-1);
    moves.emplace_back(now.getX()-1, now.getY());

    omp_lock_t lock;
    omp_init_lock(&lock);

#pragma omp parallel for default(none) firstprivate(moves, maze) shared(rightMoves, lock) num_threads(4)
    for(int i = 0; i < 4; i++){
        if(isPointValid(moves[i])){
            omp_set_lock(&lock);
            rightMoves.push_back(moves[i]);
            omp_unset_lock(&lock);
        }
    }
    omp_destroy_lock(&lock);

    return rightMoves;
}

