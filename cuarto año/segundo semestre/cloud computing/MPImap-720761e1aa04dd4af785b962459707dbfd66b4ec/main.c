#include <stdio.h>
#include "mpi.h"

void main(int argc, char **argv){
  int nprocs, myid;

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&myid);
  MPI_Comm_size(MPI_COMM_WORLD,&nprocs);

  printf("hello world %d\n",myid); 
  MPI_Finalize();
  return;

}
