#include <iostream>
#include <mpi.h>

#include "strategy.hpp"
#include "game.hpp"

#define MCW MPI_COMM_WORLD


int main(int argc, char **argv){
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MCW, &rank);
    MPI_Comm_size(MCW, &size);
    srand(time(NULL) + rank);

    if(!rank){
        manage();
    } else if(rank == 1){
        MoneyStrategy strategy = MoneyStrategy();
        play(&strategy);
    } else {
        Strategy strategy = Strategy();
        play(&strategy);
    }

    MPI_Finalize();
}