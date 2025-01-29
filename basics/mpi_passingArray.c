#include <stdio.h>
#include "mpi.h"
#define SIZE 5
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
    if(world_size!=2){
        printf("This program requires exactly 2 processes\n");
        MPI_Finalize();
        return 0;
    }
    
    //Process 0 sends data array to process 1
    if(rank==0){
        int data[SIZE];
        for(int i=0;i<SIZE;i++){
            data[i] = (i+1);
        }
        MPI_Send(data,SIZE,MPI_INT,1,0,MPI_COMM_WORLD);
        printf("Source:Process 0\n");
        printf("Destination:Process 1\n");
        printf("Data sent: ");
        for(int i=0;i<SIZE;i++){
            printf("%d ",data[i]);
        }
        printf("\n");
    }

    //Process 1 receives data array from process 0
    else if(rank==1){
        int data[SIZE];
        MPI_Recv(data,SIZE,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("Source:Process 0\n");
        printf("Destination:Process 1\n");
        printf("Data received: ");
        for(int i=0;i<SIZE;i++){
            printf("%d ",data[i]);
        }
        printf("\n");
    }
    //Finalize the MPI environment
    MPI_Finalize();
    return 0;
}