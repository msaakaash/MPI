#include <stdio.h>
#include "mpi.h"

int main(int argc,char** argv){
    //Initialize the MPI environment;
    MPI_Init(&argc,&argv);
    int rank;
    int world_size;
    //Getting the rank of the process 
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    //Getting the number of processes
    MPI_Comm_size(MPI_COMM_WORLD,&world_size);
    int d[] = {1,2,3,4,5,6,7,8,9,10};
    int l1 = sizeof(d) / sizeof(d[0]);
    int chunk_size = l1/world_size;
    int local_data[chunk_size];
    
    //Scattering 
    MPI_Scatter(d,chunk_size,MPI_INT,local_data,chunk_size,MPI_INT,0,MPI_COMM_WORLD);

    int local_max = local_data[0];
    for(int i=1;i<chunk_size;i++){
        if(local_max<local_data[i]) local_max = local_data[i];
    }
    for(int i=0;i<chunk_size;i++) printf("Process %d received %d\n",rank,local_data[i]);
    printf("The local max caculated by the process %d is :%d\n",rank,local_max);
    //Gather all individual results
    int all_max[world_size];
    MPI_Gather(&local_max,1,MPI_INT,all_max,1,MPI_INT,0,MPI_COMM_WORLD);
    int global_max = all_max[0];
    if(rank==0){
        for(int i=1;i<world_size;i++){
            if(global_max<all_max[i]) global_max = all_max[i];
        }
        printf("The maximum element is:%d\n",global_max);
    }
    MPI_Finalize();
    return 0;
}