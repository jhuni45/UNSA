#include <stdlib.h>
#include <stdio.h>

#define N 4	
#define T 2


//__global__ void sum_matrix(int**&d_mat_a, int**&dd_mat_a,int**&d_mat_b, int**&dd_mat_b,int**&d_mat_c, int**&dd_mat_c, int n, int m){

__global__ void sum_matrix(int** d_mat_a, int** dd_mat_a,int**d_mat_b, int**dd_mat_b,int**d_mat_c, int**dd_mat_c, int n, int m){

    //sum_matrix<<<grid,blockNum>>>(d_mat_a,dd_mat_a,d_mat_b,dd_mat_b,d_mat_c,dd_mat_c,n,m);

				//int x = threadIdx.x + blockIdx.x*blockDim.x;
				//int y = threadIdx.y + blockIdx.y*blockDim.y;
				d_mat_c[0][0] = -1;
				d_mat_c[0][1] = -2;
				d_mat_c[0][2] = -3;

				dd_mat_c[1][0] = -1;
				dd_mat_c[1][1] = -2;
				dd_mat_c[1][2] = -3;
				
}

void create(int**&mat,int n){
	mat = (int **)malloc(sizeof(int*)*n);	
	int i;
	for(i=0;i<n;i++){
		mat[i] = (int*)malloc(sizeof(int)*n);
	}
}

void create2(int** & mat,int n, int m){
	mat = (int** )malloc(sizeof(int*)*n);	
	mat[0] = (int* )malloc(sizeof(int)*n*m);	
	int i;
	for(i=1;i<=n;i++){
		mat[i] = (*mat+i*m);
	}
}

void fill(int** mat,int n){
	int i,j; 
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
			mat[i][j] = rand()%10;
	}
}

void fill_zero(int** mat,int n, int value=0){
	int i,j; 
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			mat[i][j] = value;
}



void print(int** mat,int n){
	int i,j; 
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
			printf("%d",mat[i][j]);
		printf("\n");
	}
}

/*
 void create_matrix(int**&mat, int**&h_mat, int**&d_mat, int n, int m){
	int size_n=sizeof(int)*n;
	int size_m=sizeof(int)*m;

	h_mat = (int**)malloc(size_n);

	int i;
	for(i=0;i<n;i++){
		printf(">>>>>\n");
		cudaMalloc((void**)& h_mat[i],size_n);
		cudaMemcpy(h_mat[i],&mat[i][0],size_m,cudaMemcpyHostToDevice);
	}

	cudaMalloc((void*** )& d_mat,size_n);
	cudaMemcpy(d_mat,h_mat,size_n,cudaMemcpyHostToDevice);

}*/






int main(){

	int   n = N;
	int   m = N;

	int** h_mat_a;
		create2(h_mat_a,n,m);
		fill(h_mat_a,n);
		print(h_mat_a,n);
	printf("//////////////////\n");

	int** h_mat_b;
		create2(h_mat_b,n,m);
		fill(h_mat_b,n);
		print(h_mat_b,n);
	printf("//////////////////\n");

	int** h_mat_c;
		create2(h_mat_c,n,m);
		//fill_zero(h_mat_c,n);
		fill(h_mat_c,n);
		print(h_mat_c,n);
	printf("//////////////////\n");


	int ** d_mat_a;	int ** dd_mat_a; 
	int ** d_mat_b;	int ** dd_mat_b; 
	int ** d_mat_c;	int ** dd_mat_c; 
	
	int i;
	 
	///////////////////////

    d_mat_a = (int** )malloc(sizeof(int*)*n);
    cudaMalloc((void** )& d_mat_a[0], n*sizeof(int)*m);
    cudaMemcpy(d_mat_a[0],h_mat_a[0],n*sizeof(int)*m,cudaMemcpyHostToDevice);
    for(i=0;i<n;i++){
    	printf(">wwww>>>>\n");
    	d_mat_a[1]= (*h_mat_a+i*m);
    }
    	
    cudaMalloc((void*** )& dd_mat_a,sizeof(int*)*n);
    cudaMemcpy(dd_mat_a,h_mat_a,sizeof(int)*n,cudaMemcpyHostToDevice);    
 
    ///

    d_mat_b = (int** )malloc(sizeof(int*)*n);
    cudaMalloc((void** )& d_mat_b[0], n*sizeof(int)*m);
    cudaMemcpy(d_mat_b[0],h_mat_b[0],n*sizeof(int)*m,cudaMemcpyHostToDevice);
    for(i=0;i<n;i++){
    	printf(">wwww>>>>\n");
    	d_mat_b[1]= (*h_mat_b+i*m);
    }
    	
    cudaMalloc((void*** )& dd_mat_b,sizeof(int*)*n);
    cudaMemcpy(dd_mat_b,h_mat_b,sizeof(int)*n,cudaMemcpyHostToDevice);    

	///

    d_mat_c = (int** )malloc(sizeof(int*)*n);
    cudaMalloc((void** )& d_mat_c[0], n*sizeof(int)*m);
    cudaMemcpy(d_mat_c[0],h_mat_c[0], n*sizeof(int)*m,cudaMemcpyHostToDevice);
    for(i=0;i<n;i++){
    	printf(">wwww>>>>\n");
    	d_mat_c[1]= (*h_mat_c+i*m);
    }
    	
    cudaMalloc((void*** )& dd_mat_c,sizeof(int*)*n);
    cudaMemcpy(dd_mat_c,h_mat_c,sizeof(int)*n,cudaMemcpyHostToDevice);    
  	
    //////////////////////////

	dim3 grid(ceil(N/T),ceil(N/T),1);
	dim3 blockNum(T,T,1);

	sum_matrix<<<grid,blockNum>>>(d_mat_a,dd_mat_a,d_mat_b,dd_mat_b,d_mat_c,dd_mat_c,n,m);

	cudaMemcpy(h_mat_c[0],d_mat_c[0],n*sizeof(int)*m,cudaMemcpyDeviceToHost);	
	

	printf("///////CCCCCC///////////\n");
	print(h_mat_c,n);


	return 0;
}