#include <iostream>
#include <vector>

using namespace std;

template <class T>
struct Nodo{
	T dato;
	Nodo* siguiente;
	Nodo(T dato){
		this->dato=dato;
		this->siguiente=NULL;
	}
	Nodo(T dato, Nodo* siguiente){
		this->dato=dato;
		this->siguiente=siguiente;
	}
};

template <class T>
class Pila{
public:
	void push(T);
	void print();
	void pop1();
	void pop2();
	void show_cima();
	void generar();
	void show_basic();
	void print_funcion();
	T get_cima();
	Pila(){
		cima=NULL;
	}
private:
	Nodo<T> *cima;
	vector<T> numeros;
};