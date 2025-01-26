#include <stdio.h>
#include "mpi.h"

int main(int argc,char** argv){
    MPI_Init(&argc,&argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if(rank==0){
    //process 0:send a message to process 1
    int data = 43;
    MPI_Send(&data,1,MPI_INT,1,0,MPI_COMM_WORLD);
    printf("Process 0 sent data %d to process 1\n",data);
    }
    else if(rank==1){
    //process 1:receive a message from process 0
    int received_data;
    MPI_Recv(&received_data,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    printf("Process 1 received data %d from process 0\n",received_data);
    }
    MPI_Finalize();
}