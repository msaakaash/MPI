#include <stdio.h>
#include "mpi.h"
#define size 8
int main(int argc,char** argv){
    //Initialize MPI environment
    MPI_Init(&argc,&argv);

    //Get the rank of the processes
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    //Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD,&world_size);
    //splits define the number of elements each process gets
    int splits = size/world_size;
    int data[size];
    int recv_data[splits];
    
    if(rank==0){
        for(int i=0;i<size;i++){
            data[i]=i+1;
        }
    }
    //Scattering data across processes
    MPI_Scatter(data,splits,MPI_INT,recv_data,splits,MPI_INT,0,MPI_COMM_WORLD);
    for(int i=0;i<splits;i++) printf("Process %d received %d\n",rank,recv_data[i]);
    //Finalize MPI environment
    MPI_Finalize();
    return 0;

}