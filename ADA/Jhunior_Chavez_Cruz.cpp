//Chavez Cruz Jhunior Kenyi

#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <cmath>
#include <math.h>
#include <fstream>

using namespace std;
typedef int num;
typedef vector<char> lista;

vector<int> crear(long int N){
	vector<int> A;
	while(N){
		int aleatorio= rand() % 10000 + 1;
		A.push_back(aleatorio);
		N--;
	}
	return A;
}

void mostrar(lista A){
	for (int i =0;i<A.size();i++){
		cout<<A[i]<<"";
	}
	cout<<endl;
}

int particiona(lista &A, int p, int r,int &cont){
	char x=A[r];
	int i=p-1;
	for (int j=p;j<=r-1;j++){
		if (A[j]< x){
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
	return i+1;
}

void quicksort(lista &A,int p,int r,int &cont){
	if (p<r){
		int q=particiona(A,p,r,cont);
		quicksort(A,p,q-1,cont);
		quicksort(A,q+1,r,cont);
	}

}

int swaps(string A){
  int cont=0;
  lista prueba;
  for (int i =0;i<A.length();i++){
    char x=A[i];
    //cout<<x<<endl;
    prueba.push_back(x);
  }
  mostrar(prueba);
  quicksort(prueba,0,prueba.size()-1,cont);
  //mostrar(prueba);
  return cont;
}

int main(){
  cout<<"------------"<<endl;
  vector<string> prueba={"AACE","DAAD","ZWQM"};
  for (int i=0;i<prueba.size();i++){
    string A =prueba[i];
    //Aqui hallo los swaps
    swaps(A);
  }


  /*int swaps=0;
  vector<char>A;
  ifstream input;
  ofstream output;
  int val;
  output.open("salida.txt");
  input.open("entrada.txt");
  string linea;
  int cont=0;
  vector<string> prueba;
  while(getline(input,linea)){

  }
  insertsort(prueba,cont);
  output<<cont;
  output.close();*/
  return 0;
}
