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
int da = 4;
MPI_Scatter(d,chunk_size,MPI_INT,local,chunk_size,MPI_INT,0,MPI_COMM_WORLD);
int count = 0;

for(int i=0;i<chunk_size;i++){
if(local[i]==da) count = 1;
}

for(int i=0;i<chunk_size;i++) printf("Process %d received %d\n",rank,local[i]);
if(count == 1) printf("found at rank %d\n",rank);
else printf("not fount at rank %d\n",rank);
int all[size];
MPI_Gather(&count,1,MPI_INT,all,1,MPI_INT,0,MPI_COMM_WORLD);
int g = 0;

if(rank==0){
for(int i=0;i<size;i++){
 g += all[i];
}
if(g==0) printf("The element 3 does not exist.\n");
else printf("The element exists.\n");
}
MPI_Finalize();
return 0;
}
