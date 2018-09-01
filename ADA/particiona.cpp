#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <cmath>
#include <math.h>
//sera que la cantidad de swaps en el particiona de QUICKSORT, tambien se asemeja
//a n ln(n) , n log(n)?

using namespace std;

typedef vector<int> lista;

double log_neperiano(int n){
	return n*log(n);
}

double log_normal(int n){
	return n*log10(n);
}

void mostrar(lista A){
	for (int i =0;i<A.size();i++){
		cout<<A[i]<<" ";
	}
	cout<<endl;
}
int particiona(lista &A, int p, int r,int &cont){
	int x=A[r];
	int i=p-1;
	for (int j=p;j<=r-1;j++){
		if (A[j]<= x){
			i++;
			int aux=A[i];
			A[i]=A[j];
			A[j]=aux;
			cont++;
		}
	}
	int aux2=A[i+1];
	A[i+1]=A[r];
	A[r]=aux2;
	cont++;
	//cout<<"[particiona]:" <<cont<<endl;
	return i+1;
}
/*
void sin_ordenar(lista A, int N){
	int aux=particiona(A,0,A.size()-1,0);
	while(N<aux){
		A.erase(A.begin()+aux,A.end());
		aux=particiona(A,0,A.size()-1,0);
		mostrar(A);
	}
	cout<<A[aux+1];
}
*/
vector<int> crear(long int N){
	vector<int> A;
	while(N){
		int aleatorio= rand() % 10000 + 1;
		A.push_back(aleatorio);
		N--;
	}
	return A;
}

void quicksort(lista &A,int p,int r,int &cont){
	if (p<r){
		//cout<<"[quick]: "<<cont<<endl;
		int q=particiona(A,p,r,cont);
		quicksort(A,p,q-1,cont);
		quicksort(A,q+1,r,cont);
	}
}

int main(){
	//lista A={99,33,55,77,11,22,88,66,33,44};
	srand(time(NULL));
	//lista A={15,10,12,4,6,13,1,5,2,9,10,7,8};
	//mostrar(A);
	int veces=100;
	for(int i=0;i<10;i++){
		int tam=rand() %10000 +1;
		cout<<"tamano: "<<tam<<"\nSwaps:"<<endl;
		double promedio=0;
		for (int j=0;j<veces;j++){
			int contador=0;
			vector<int>A=crear(tam);
			quicksort(A,0,A.size()-1,contador);
			promedio+=contador;
			cout<<"["<<j<<"]"<<contador<<endl;
		}
		promedio=promedio/double(veces);
		cout<<"n*ln(n): "<<log_neperiano(tam)<<"\tn*log(n): "<<log_normal(tam)<<endl;
		cout<<"Promedio: "<<"\t"<<promedio<<endl;
	}
	//sin_ordenar(A,3);

	//quicksort(A,0,A.size()-1,contador);
	//mostrar(A);
	//particiona(A,0,A.size()-1)<<" "<<endl;
	//mostrar(A);

	return 0;
}
