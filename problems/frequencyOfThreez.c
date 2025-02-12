#include <stdio.h>
#include "mpi.h"

int main(int argc,char** argv){
MPI_Init(&argc,&argv);
int rank,size;
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Comm_size(MPI_COMM_WORLD,&size);
int d[] = {1,2,2,3,1,3,3,4,5,3};
int l1 = sizeof(d)/sizeof(d[0]);
int chunk_size = l1/size;
int local[chunk_size];
int da = 3;
MPI_Scatter(d,chunk_size,MPI_INT,local,chunk_size,MPI_INT,0,MPI_COMM_WORLD);
int count = 0;

for(int i=0;i<chunk_size;i++){
if(local[i]==3) count++;
}

for(int i=0;i<chunk_size;i++) printf("Process %d received %d\n",rank,local[i]);
printf("The local count caculated by the process %d is :%d\n",rank,count);

int all[size];
MPI_Gather(&count,1,MPI_INT,all,1,MPI_INT,0,MPI_COMM_WORLD);
int g = 0;

if(rank==0){
for(int i=0;i<size;i++){
 g += all[i];
}
printf("The frequency of element 3 is :%d\n",g);
}
MPI_Finalize();
return 0;
}
