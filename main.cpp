#include <omp.h>
#include <time.h>
#include <cstdlib>

#include "Maze.h"
//TODO: algoritmo che risolva il labirinto in modo sequenziale
//TODO: algoritmo che risolva il labirinto in modo parallelo

int main() {
    srand(time(NULL));
    Maze m(10, 7);
}
