#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

//valgrind --tool=callgrind my_program [programm arguments]
//kcachegrind callgrind.out.x
//valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=bloque.txt ./bloque 
using namespace std;
typedef vector<vector<int>> matrix;
typedef vector<int> lista;


void sixfor(matrix A, matrix B){
	matrix C(A.size(),lista(B[0].size(),0));
	float T=sqrt(4);
	for (int I=0;I<A.size();I+=T){
		for (int J = 0; J < B[0].size(); J+=T){
			for (int K = 0; K < A[0].size(); K+=T){

				for (int i = I; i < (I+T,A.size()); i++){
					for (int j = J ; j<min (J+T,(float)B[0].size()); j++){
						int sum=0;
						for (int k = K; k < min(K+T,(float)A[0].size()); k++){
							sum+=sum+A[i][k]*B[k][j];							
						}
						C[i][j]=C[i][j]+sum;
					}
				}
			
			}
		}
	}	

}

int main(){

	int N=100;
	matrix A(N,lista(N,0));
	matrix B(N,lista(N,0));
	matrix C;
	//sixforT=clock();
	sixfor(A,B);
	//sixforT=clock()-sixforT;

	return 0;	
}