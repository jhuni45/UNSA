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

class Pila{
public:
	void push(int);
	void print();
	void pop1();
	void pop2(); //vaciar
	void show_cima();
	Pila(){
		cima=NULL;
	}
private:
	Nodo *cima;
};

void Pila::push(int valor){
	if (cima==NULL){
		cima=new Nodo(valor);
	}
	else{
		cima=new Nodo(valor,cima);
	}
	print();
}

void Pila::pop1(){
	if(cima==NULL){
		cout<<"la pila ya esta vacia"<<endl;
	}
	else{
		Nodo *aux=cima;
		aux=aux->siguiente;
		delete cima;
		cima=aux;
	}
	print();
}
void Pila::pop2(){
	Nodo *aux=cima;
	while(cima!=NULL){
		delete cima;
		aux=aux->siguiente;
		cima=aux;
		print();
	}
}
void Pila::print(){
	if(cima==NULL)
		cout<<"la pila esta vacia"<<endl;
	Nodo* aux=cima;
	while(aux!=NULL){
		cout<<aux->dato<<"->";
		aux=aux->siguiente;
	}
	cout<<endl;
}

int main (){
	Pila a;
	cout<<"insertando 1 .. 5"<<endl;
	a.push(1);
	a.push(2);
	a.push(3);
	a.push(4);
	a.push(5);
	cout<<"eliminar un elemento"<<endl;
	a.pop1();
	cout<<"vaciando la pila"<<endl;
	a.pop2();
	//a.pop1();
	return 0;
}
