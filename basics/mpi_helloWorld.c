#include <stdio.h>
#include "mpi.h"

int main(int argc,char **argv){
    //Initialize the MPI environment 
    MPI_Init(&argc,&argv);

    //Getting the rank of the process
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    //Getting the number of procecess
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD,&world_size);

    printf("Hello World from process %d out of %d processes\n",rank,world_size);
    // Finalize the MPI environment.
    MPI_Finalize();
    return 0;
}