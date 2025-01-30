#include <stdio.h>
#include "mpi.h"

int main(int argc,char** argv){
    int d[] = {1,2,3,4,5,6,7,8,9,10};
    int l1 = sizeof(d) / sizeof(d[0]);
    //Initialize MPI environment
    MPI_Init(&argc,&argv);
    int rank;
    int world_size;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&world_size);
    int data[l1];
    int chunk_size = l1 / world_size;
    int remainder = l1 % world_size;
    int local_data[chunk_size];
    float local_sum=0.0,total_sum=0.0;
    if(rank==0){
        for(int i=0;i<l1;i++){
        data[i]=d[i];
        }
    }   
    MPI_Scatter(data,chunk_size,MPI_INT,local_data,chunk_size,MPI_INT,0,MPI_COMM_WORLD);

    for(int i=0;i<chunk_size;i++){
        local_sum+=local_data[i];
    }
    float all_sums[world_size];
    for(int i=0;i<chunk_size;i++) printf("Process %d received %d\n",rank,local_data[i]);
    printf("The local sum caculated by the process %d is :%f\n",rank,local_sum);
    MPI_Gather(&local_sum,1,MPI_FLOAT,all_sums,1,MPI_FLOAT,0,MPI_COMM_WORLD);
    
    if(rank==0){
        for(int i=0;i<world_size;i++) total_sum+=all_sums[i];
        for (int i = l1 - remainder; i < l1; i++) {
            total_sum += d[i];
        }
        float average = total_sum / l1;
        printf("Average: %f\n", average);
    }
    MPI_Finalize();
    return 0;
}