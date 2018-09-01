#include <iostream>
#include <time.h>
#include <vector>
#include <cmath>
#include <string>
#include <math.h>
#include <gmp.h>
#include <fstream>
#include <time.h>
#include <cstdio>

using namespace std;

typedef vector<vector<int>> matriz;

void mostrar(vector<vector<int>> A){
	for (int i=0;i<A.size();i++){
		for (int j = 0; j < A[0].size(); j++)
		{
			cout<<A[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

int fibonacci(int N){
	if (N<2){
		return N;
	}
	else{
		return fibonacci(N-1)+fibonacci(N-2);
	}
}


double  fibonacci_iterativo(int N){
	vector<double> datos={0,1};
	if (N<2){
		return datos[N];
	}
	for (int i=1;i<N;i++){
		datos.push_back(fmod( datos[i],pow(2,20)) + fmod(datos[i-1],pow(2,20)));
	}
	return  fmod(datos[datos.size()-1],pow(2,20));
}

void fibonacci_iterativo2 (mpz_t &result, int N){
	mpz_t fant;
	mpz_init(fant);
	mpz_set_ui(fant,0);
	mpz_t fact;
	mpz_init(fact);
	mpz_set_ui(fact,1);
	int i=1;
	while(i<N){
		mpz_t fprox;
		mpz_init(fprox);
		mpz_mod_ui(fant,fant,pow(2,20));
		mpz_mod_ui(fact,fact,pow(2,20));
		mpz_add(fprox,fant,fact);
		
		mpz_set(fant,fact);
		mpz_set(fact,fprox);
		/*fant=fact;
		fact=fprox;*/
		i++;
	}
	gmp_printf("numero %Zd \n",fact);
	mpz_set(result,fact);
}

int fib(int N){
	int fant=0;
	int fact=1;
	int i=1;
	while(i<N){
		int fprox=fmod(fant,pow(2,20))+fmod(fact,pow(2,20));
		fant=fact;
		fact=fprox;
		i++;
	}
	return fmod(fact,pow(2,20));
}

matriz multi(matriz aux , matriz A){
	matriz result=aux;
	result[0][0]=aux[0][0]*A[0][0]+aux[0][1]*A[1][0];
	result[0][1]=aux[0][0]*A[0][1]+aux[0][1]*A[1][1];
	result[1][0]=aux[1][0]*A[0][0]+aux[1][1]*A[1][0];
	result[1][1]=aux[1][0]*A[0][1]+aux[1][1]*A[1][1];
	return result;
}
int fibonacci_matriz(int N){
	matriz aux={{1,1},{1,0}};
	matriz result=aux;
	for (int i =2;i<N;i++){
		result=multi (result,aux);
	}
	return result[0][0];
}

matriz matriz_recursivo(int N){
	matriz aux={{1,1},{1,0}};
	if (N<2){
		return aux;
	}
	else{
		matriz result=matriz_recursivo(N/2);
		return multi(result,result);
	}
}


int main(){
	int MT =100000;
	int MF =90;
	clock_t Normal,Iter1,Iter2,Matriz;
/*
	mpz_t(result);
	mpz_init(result);
*/
	ofstream graficar;
	graficar.open("fibonacci.csv");
	graficar<<"N iter1 iter2 matriz"<<endl;
    srand(time(NULL));
	//cout<<"["<< MF<<"]"<< fmod(fibonacci_iterativo2(MF), pow(2,20))<<endl;
	/*fibonacci_iterativo2(result ,1000000);
	cout<<endl;
	gmp_printf("valor: %Zd\n",result);
	mpz_mod_ui(result,result, pow(2,20));
	gmp_printf("valor mod: %Zd\n",result);*/
	int aux=1;
	while (MT){
		/*Normal=clock();
		fibonacci(aux);
		Normal=clock()-Normal;
		*/Iter1=clock();
		fibonacci_iterativo(aux);
		Iter1=clock()-Iter1;
		Iter2=clock();
		fib(aux);
		Iter2=clock()-Iter2;
		Matriz=clock();
		fibonacci_matriz(aux);
		Matriz=clock()-Matriz;
		graficar<<aux<<" "<<((float)Iter1)/CLOCKS_PER_SEC<<" "<<((float)Iter2)/CLOCKS_PER_SEC<<" "<<((float)Matriz)/CLOCKS_PER_SEC<<endl;
		MT--;
		aux++;
	}
	graficar.close();
	
	return 0;
}