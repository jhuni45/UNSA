#include <iostream>

using namespace std;

struct Nodo{
	int dato;
	Nodo* siguiente;
	Nodo(int dato){
		this->dato=dato;
		this->siguiente=NULL;
	}
	Nodo(int dato, Nodo* siguiente){
		this->dato=dato;
		this->siguiente=siguiente;
	}
};

class fila
{
public:
	fila(){
		inicio=fin=NULL;
	}
	void push(int);
	void pop1();
	void pop2();
	void print();
private:
	Nodo *inicio;
	Nodo *fin;	
};

void fila::push(int valor){
	Nodo *nuevo=new Nodo(valor);
	if (inicio==NULL){
		inicio=nuevo;
		fin=nuevo;
	}
	else{
		fin->siguiente=nuevo;
		nuevo->siguiente=NULL;
		fin=nuevo;
	}
	print();
	cout<<endl;
}

void fila::pop1(){
	if(inicio==NULL)
		cout<<"la fila esta vacia"<<endl;
	else{
		Nodo *aux=inicio;
		aux=aux->siguiente;
		delete inicio;
		inicio=aux;
	}
	print();
	cout<<endl;
}
void fila::pop2(){
	Nodo *aux=inicio;
	if(inicio==NULL)
		cout<<"la fila esta vacia"<<endl;
	else{
		while(aux!=NULL){
			aux=aux->siguiente;
			delete inicio;
			inicio=aux;	
			print();
	cout<<endl;
		}
	}
	
}
void fila::print(){
	if(inicio==NULL)
		cout<<"la fila esta vacia"<<endl;
	Nodo *aux=inicio;
	while(aux!=NULL){
		cout<<aux->dato<<"->";
		aux=aux->siguiente;
	}
}
int main(){
	fila a;
	cout<<"insertando 1 .. 5"<<endl;
	a.push(1);
	a.push(2);
	a.push(3);
	a.push(4);
	a.push(5);
	cout<<"eliminando un elemento"<<endl;
	a.pop1();
	cout<<"vaciando cola"<<endl;
	a.pop2();
	return 0;
}
