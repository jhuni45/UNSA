#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <time.h>
#include <assert.h>
#define MASTER 0
#define FROM_MASTER 1
#define FROM_WORKER 2

int initializeMatrix(double **M, int NR,int NC){
  time_t t;
  srand((unsigned) time(&t));
  for(int i = 0; i<NR; ++i){
    for(int j = 0; j<NC; ++j){
      M[i][j] = rand();
    }
  }
  return(0);
}

int main(int argc, char **argv){
  int nprocs, myid, nworkers, source, dest, mtype, averow, extra, i,j, k, rc;
  int NRA,NCA,NCB;
  int rows, offset; 
  int *rows_m, *offset_m;
  MPI_Status status;
  MPI_Init(&argc,&argv);
  MPI_Errhandler_set(MPI_COMM_WORLD, MPI_ERRORS_RETURN); //Does not immediately abort
  MPI_Comm_rank(MPI_COMM_WORLD,&myid);
  MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
  nworkers = nprocs - 1;
  MPI_Status stat;
  MPI_Request *ireq;
  ireq = (MPI_Request *) malloc(3*nworkers);
  if(nprocs < 2 || argc != 4){
    if (myid == MASTER)
      printf("usage: main_matmul NRA NCA NCB \n NRA: number of rows in A \n NCA: number of columns in A \n NCB: number of rows in B \n (NRB == NCA) \n");
    MPI_Abort(MPI_COMM_WORLD, rc);
    exit(1);
  }
  /* Dynamically allocate matrices */
    NRA = atoi(argv[1]);
    NCA = atoi(argv[2]);
    NCB = atoi(argv[3]);

  /*Master task*/
  if (myid == MASTER){
    //Begin timing
    double time_s,time_f;
    time_s = MPI_Wtime();
    double **A,**B,**C; 
    double *dataA,*dataB,*dataC;
    //make contiguous multiarrays
    A = (double **) malloc(sizeof(double *)*NRA); 
    dataA = (double *) malloc(sizeof(double)*NRA*NCA); 
    B = (double **) malloc(sizeof(double *)*NCA); 
    dataB = (double *) malloc(sizeof(double)*NCA*NCB); 
    C = (double **) malloc(sizeof(double *)*NRA); 
    dataC = (double *) malloc(sizeof(double)*NRA*NCB); 
    for(int i=0; i<NRA; i++){
      A[i] = &(dataA[NCA*i]);
    }  
    for(int i=0; i<NCA; i++){
      B[i] = &(dataB[NCB*i]);
    }  
    for(int i=0; i<NRA; i++){
      C[i] = &(dataC[NCB*i]);
    }  
    initializeMatrix(A, NRA, NCA);
    initializeMatrix(B, NCA, NCB);
    MPI_Bcast(&(B[0][0]), NCA*NCB, MPI_DOUBLE, 0, MPI_COMM_WORLD); //Broadcast
    averow = NRA/nworkers;
    extra = NRA%nworkers;
    offset_m = (int *) malloc(sizeof(int)* nprocs);
    rows_m = (int *) malloc(sizeof(int)* nprocs);
    offset_m[0] = 0; 
    rows_m[0] = 0;
    mtype = FROM_MASTER;
    for(dest = 1; dest<nprocs; ++dest){
      offset_m[dest] = offset_m[dest-1] + rows_m[dest-1];
      rows_m[dest] = (dest <= extra) ? averow+1 : averow;      
      MPI_Send(&offset_m[dest], 1, MPI_INT, dest, mtype, MPI_COMM_WORLD);
      MPI_Send(&rows_m[dest], 1, MPI_INT, dest, mtype, MPI_COMM_WORLD);
      MPI_Send(&A[offset_m[dest]][0], rows_m[dest]*NCA, MPI_DOUBLE, dest, mtype, MPI_COMM_WORLD);
    }
    mtype = FROM_WORKER;
    for(source = 1; source < nprocs; ++source){
      MPI_Recv(&offset, 1, MPI_INT, source, mtype, MPI_COMM_WORLD, &stat);
      MPI_Recv(&rows, 1, MPI_INT, source, mtype, MPI_COMM_WORLD, &stat);
      MPI_Recv(&C[offset][0], rows*NCB, MPI_DOUBLE, source, mtype, MPI_COMM_WORLD, &stat);
      /* Ensure that we receive the same amount of info and positions as MASTER sent */
      assert(rows == rows_m[source]);
      assert(offset == offset_m[source]);
    }
    time_f = MPI_Wtime();
    printf("computation took %lf seconds \n",time_f-time_s);
   
  }else{ //Worker process
    double **B; 
    double *dataB;
    //make contiguous multiarrays
    B = (double **) malloc(sizeof(double *)*NCA); 
    dataB = (double *) malloc(sizeof(double)*NCA*NCB); 
    for(int i=0; i<NCA; i++){
      B[i] = &(dataB[NCB*i]);
    }  

    MPI_Bcast(&(B[0][0]), NCA*NCB, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    mtype = FROM_MASTER;
    MPI_Recv(&offset, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD, &stat);
    MPI_Recv(&rows, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD, &stat);
    double **A = (double **) malloc(rows*sizeof(double *));
    double *dataA = (double *) malloc(sizeof(double)*NCA*rows); 
    for(i = 0; i<rows; ++i){
      A[i] = &(dataA[NCA*i]);
    }
    MPI_Recv(&(A[0][0]), rows*NCA, MPI_DOUBLE, MASTER, mtype, MPI_COMM_WORLD, &stat); 
    double **C = (double **) malloc(rows*sizeof(double *));
    double *dataC = (double *) malloc(sizeof(double)*NCB*rows); 
    for(i = 0; i<rows; ++i){
      C[i] = &(dataC[NCB*i]);
    }
    for(k = 0; k<NCB; ++k){
      for(i = 0; i<rows; ++i){
	C[i][k] = 0.0;
	for(j = 0; j<NCA; ++j){
	  C[i][k] += A[i][j]*B[j][k];
	}
      }
    }
    mtype = FROM_WORKER;
    MPI_Send(&offset, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD);
    MPI_Send(&rows, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD);
    MPI_Send(&(C[0][0]), rows*NCB, MPI_DOUBLE, MASTER, mtype, MPI_COMM_WORLD);
  }  
  MPI_Finalize();
  return(0);
}