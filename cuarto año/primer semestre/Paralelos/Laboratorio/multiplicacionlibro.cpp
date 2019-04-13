#include <iostream>
#include <vector>
#include <time.h>
#include <cmath>
#include <math.h>
#include <algorithm>

using namespace std;
typedef vector<vector<int>> matrix;
typedef vector<int> lista;

void first(matrix A,lista X, lista Y){
	for (int i=0;i<A.size();i++){
		for (int j = 0; j <A[0].size();j++){
			Y[i]+=A[i][j]*X[j];
		}
	}
}
void second(matrix A,lista X, lista Y){
	for (int j=0;j<A.size();j++){
		for (int i = 0; i <A[0].size();i++){
			Y[i]+=A[i][j]*X[j];
		}
	}
}

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

void clasic(matrix A, matrix B){
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
}
int main(){

	int N=100;
	matrix A(N,lista(N,0));
	matrix B(N,lista(N,0));
	lista X(N,0);
	lista Y(N,0);
	clock_t firstT, secondT,clasicT,sixforT;
	
	firstT=clock();
	first(A,X,Y);
	firstT=clock()-firstT;
	
	secondT=clock();
	second(A,X,Y);
	secondT=clock()-secondT;

	clasicT=clock();
	clasic(A,B);
	clasicT=clock()-clasicT;

	sixforT=clock();
	sixfor(A,B);
	sixforT=clock()-sixforT;

	cout<<"COMPARACIONES:"<<endl;
	cout<<"FIRST: "<<float(firstT)/CLOCKS_PER_SEC
		<<"\nSECOND: "<<float(secondT)/CLOCKS_PER_SEC
		<<"\nCLASICO: "<<float(clasicT)/CLOCKS_PER_SEC
		<<"\nBLOQUES: "<<float(sixforT)/CLOCKS_PER_SEC<<endl;
	return 0;	
}