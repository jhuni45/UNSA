#include <cuda.h>



void vecAdd(float *A, float *B, float *C, int n){
	int size=n*sizeof(float);
	float *d_A, *d_B, *d_C;
	cudaMalloc((void**)&d_A,size);
	cudaMemcpy(d_A,A,size,cudaMempcyHostToDevice);
	cudaMempcy(d_B,B,size,cudaMempcyHostToDevice);

	cudaMalloc((void**)&d_C,size);
	vecAddKernel<<<cel(n/256,0),256>>> (d_A,d_B,d_C,n);
	cudaMempcy(C,d_C,size,cudaMempcyDeviceToHost);

	cudaFree(d_A);
	cudaFree(d_B);
	cudaFree(d_C);
}

int main(){

	return 0;	
}
