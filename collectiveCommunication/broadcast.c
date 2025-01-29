#include <stdio.h>
#include "mpi.h"

int main(int argc,char** argv){
    //Initialize MPI environment
    MPI_Init(&argc,&argv);

    //Get the rank of the process
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    //Get the size of the communicator
    int size;
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    //Broadcast the data value of rank 0 to all other processes
    int data = (rank == 0) ? 100 : 0;
    if(rank == 0) printf("Process %d has data %d\n",rank,data);
    MPI_Bcast(&data,1,MPI_INT,0,MPI_COMM_WORLD);
    if(rank != 0) printf("Process %d received data %d from Process 0\n",rank,data);

    //Finalize MPI environment
    MPI_Finalize();
    return 0;
}