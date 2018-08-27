#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> lista;

int cont=0;
void print(lista A){
	if (cont==0){
		cout<<"**Lista vacia"<<endl;
		return;
	}
	for (int i=0; i<A.size();i++){
		cout<<A[i]<<"<-";	
	}
	cout<<endl;
}
bool estalleno(lista A){
	for (int i=0;i<A.size();i++){
		if (A[i]==0)
			return false;
	}
	return true;
}
void add(lista &A, int dato,int pos){
	if (estalleno(A)){
		cout<<"**La Lista esta llena"<<endl;
		return;
	}
	if (A[pos]!=0){
		cout<<"la posicion esta ocupada"<<endl;
		return;
	}
	A[pos]=dato;
	cont++;
	print(A);
}
int buscar (lista A,int dato){
	for (int i=0;i<A.size();i++){
		if (A[i]==dato){
			cout<<"elemento encontrado"<<endl;
			return i;
		}
	}
	cout<<"elemento no encontrado"<<endl;
	return -1;
}
void eliminar(lista &A, int dato){
	int aux=buscar(A,dato);
	if (aux!=-1){
		A[aux]=0;
		cont--;	
	}
}
void vaciar(lista &A){
	for (int i=0;i<A.size();i++){		
		print(A);		
		A[i]=0;
		cont--;		
	}
	print(A);

}

int main(){
	lista Lista(5);	
	cout<<"tamanho estatico: "<<Lista.size()<<"\nInsertanto 1 .. "<<Lista.size()<<endl;	
	for (int i=1;i<=Lista.size();i++){
		add(Lista,i,i-1);
	}
	cout<<"**elimando el numero 5"<<endl;
	eliminar(Lista,5);
	print(Lista);
	cout<<"**intentando insertar numero: "<<Lista.size()+1<<" en la posicion 3"<<endl;
	add(Lista,Lista.size()+1,2);
	cout<<"**eliminando numero 3"<<endl;
	eliminar(Lista,3);
	print(Lista);
	cout<<"**intentando insertar numero: "<<Lista.size()+1<<" en la posicion 3"<<endl;
	add(Lista,Lista.size()+1,2);
	cout<<"**vaciar Lista"<<endl;
	vaciar(Lista);
	return 0;
}


