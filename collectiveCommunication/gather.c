#include <stdio.h>
#include "mpi.h"

int main(int argc,char** argv){
    //Initialize MPI environment
    MPI_Init(&argc,&argv);
    //Getting the rank of the process 
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    //Getting the number of the process
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD,&world_size);

    int send_value = rank + 1;
    int recv_buffer[world_size];

    //Gathering
    MPI_Gather(&send_value,1,MPI_INT,recv_buffer,1,MPI_INT,0,MPI_COMM_WORLD);
    if(rank==0){
        printf("Gathered values: ");
        for (int i = 0; i < world_size; i++) {
            printf("%d ", recv_buffer[i]);
        }
        printf("\n");
    }
    MPI_Finalize();
    return 0;
}