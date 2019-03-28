#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> lista;

int POS=0;
void print(lista A){
	if (POS==0){
		cout<<"**Pila vacia"<<endl;
		return;
	}
	for (int i=0; i<A.size();i++){
		cout<<A[i]<<"<-";	
	}
	cout<<endl;
}
bool estalleno(lista A){
	if (POS<A.size())
		return false;
	return true;
}
void push(lista &A, int dato){
	if (estalleno(A)){
		cout<<"**La pila esta llena"<<endl;
		return;
	}
	A[POS]=dato;
	POS++;	
	print(A);
}
void pop(lista &A){
	A[POS-1]=0;
	POS--;
	print(A);
}
void vaciar(lista &A){
	for (int i=POS-1;i>=0;i--){
		pop(A);
	}
}

int main(){
	lista Pila(5);	
	cout<<"tamanho estatico: "<<Pila.size()<<"\nInsertanto 1 .. "<<Pila.size()<<endl;	
	for (int i=1;i<=Pila.size();i++){
		push(Pila,i);
	}	
	cout<<"intentando insertar numero: "<<Pila.size()+1<<endl;
	push(Pila,Pila.size()+1);
	cout<<"eliminando un elemento"<<endl;
	pop(Pila);
	cout<<"intentando insertar numero: "<<Pila.size()+1<<endl;
	push(Pila,Pila.size()+1);
	cout<<"vaciar Pila"<<endl;
	vaciar(Pila);
	return 0;
}


