#include "mpi.h"
#include <stdio.h>
#define array_size 5
int main(int argc,char** argv){
    MPI_Init(&argc,&argv);

    int rank,size;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if(size<2){
        printf("This program requires at least 2 processes.\n");
    }
    if(rank==0){
        int data[array_size] = {10,20,30,40,50};
        MPI_Send(data,array_size,MPI_INT,1,0,MPI_COMM_WORLD);
        printf("Process 0 sent array to Process 1:");
        for(int i=0;i<array_size;i++){
            printf("%d ",data[i]);
        }
        printf("\n");
    }else if(rank==1){
        int received_data[array_size];
        MPI_Recv(received_data,array_size,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("Process 1 received array from Process 0:");
        for(int i=0;i<array_size;i++){
            printf("%d ",received_data[i]);
        }
        printf("\n");
    }
    MPI_Finalize();
    return 0;
}