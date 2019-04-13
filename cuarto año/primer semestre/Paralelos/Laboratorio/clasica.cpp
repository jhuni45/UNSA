#include <iostream>
#include <vector>
#include <time.h>
#include <cmath>
#include <math.h>
#include <algorithm>

using namespace std;
typedef vector<vector<int>> matrix;
typedef vector<int> lista;
matrix clasic(matrix A, matrix B){
	matrix C(A.size(),lista (B[0].size(),0));
	for (int i=0;i<A.size();i++){
		for (int j=0;j<B[0].size();j++){
			int sum=0;
			for(int k=0;k<A[0].size();k++){
				sum+=sum+A[i][k]*B[k][j];
			}
			C[i][j]=sum;
		}
	}
	return C;
}
int main(){

	int N=100;
	matrix A(N,lista(N,0));
	matrix B(N,lista(N,0));
	matrix C;
	C=clasic(A,B);
	return 0;	
}