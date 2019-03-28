#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> lista;

int POS=0;
void print(lista A){
	if (POS==0){
		cout<<"**Cola vacia"<<endl;
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
		cout<<"**La Cola esta llena"<<endl;
		return;
	}
	A[POS]=dato;
	POS++;	
	print(A);
}
void pop(lista &A){
	A[0]=0;
	POS--;
	for (int i=0;i<POS;i++){
		A[i]=A[i+1];
		A[i+1]=0;
	}	
	print(A);
}
void vaciar(lista &A){
	for (int i=POS-1;i>=0;i--){
		pop(A);
	}
}

int main(){
	lista Cola(5);	
	cout<<"tamanho estatico: "<<Cola.size()<<"\nInsertanto 1 .. "<<Cola.size()<<endl;	
	for (int i=1;i<=Cola.size();i++){
		push(Cola,i);
	}	
	cout<<"intentando insertar numero: "<<Cola.size()+1<<endl;
	push(Cola,Cola.size()+1);
	cout<<"eliminando un elemento"<<endl;
	pop(Cola);
	cout<<"intentando insertar numero: "<<Cola.size()+1<<endl;
	push(Cola,Cola.size()+1);
	cout<<"vaciar Cola"<<endl;
	vaciar(Cola);
	return 0;
}


