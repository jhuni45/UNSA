#include <iostream>
#include <vector>

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
	void pop2();
	void show_cima();
	int get_cima();
	Pila(){
		cima=NULL;
	}
	Nodo *cima;
private:
	
};