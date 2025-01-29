#include <stdio.h>
#include "mpi.h"

int main(int argc,char** argv){
    //Initialize the MPI environment
    MPI_Init(&argc,&argv);

    //Getting the rank of the process
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    //Getting the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD,&world_size); 
    
    //Atleast two process required
    if(world_size<2 || world_size>2){
        printf("This program requires exactly 2 processes\n");
        MPI_Finalize();
        return 0;
    }
    //Process 0 sends data to process 1
    if(rank==0){
        int data = 100;
        MPI_Send(&data,1,MPI_INT,1,0,MPI_COMM_WORLD);
        printf("Source:Process 0\n");
        printf("Destination:Process 1\n");
        printf("Data sent: %d\n",data);
    }
    //Process 1 receives data from process 0
    else if(rank==1){
        int data;
        MPI_Recv(&data,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("Source:Process 0\n");
        printf("Destination:Process 1\n");
        printf("Data received: %d\n",data);
    }
    //Finalize the MPI environment
    MPI_Finalize();
    return 0;
}