//
// Created by Sofy on 06/02/2022.
//

#ifndef MAZE_MAZESOLVERSEQ_H
#define MAZE_MAZESOLVERSEQ_H

#include "MazeSolver.h"

class MazeSolverSeq : public MazeSolver {
public:
    explicit MazeSolverSeq(Maze m) : MazeSolver(m){};
    void solve(int numberOfParticles) override;

};

#endif //MAZE_MAZESOLVERSEQ_H
