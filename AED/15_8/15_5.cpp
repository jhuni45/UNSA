#include <iostream>
#include <fstream>

using namespace std;

struct Nodo{
	char dato;
	Nodo* siguiente;
	Nodo(char dato){
		this->dato=dato;
		this->siguiente=NULL;
	}
	Nodo(char dato, Nodo* siguiente){
		this->dato=dato;
		this->siguiente=siguiente;
	}
};

class Pila{
public:
	void push(char);
	void print();
	void pop1();
	void pop2();
	char get_cima();
	Pila(){
		cima=NULL;
	}
	Nodo *cima;
private:
};

char Pila::get_cima(){
	return cima->dato;
}
void Pila::push(char valor){
	if (cima==NULL){
		cima=new Nodo(valor);
	}
	else{
		cima=new Nodo(valor,cima);
	}
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
}

void Pila::pop2(){
	Nodo *aux=cima;
	while(cima!=NULL){
		delete cima;
		aux=aux->siguiente;
		cima=aux;
	}
}

void Pila::print(){
	if(cima==NULL)
		cout<<"la pila esta vacia"<<endl;
	Nodo* aux=cima;
	cout<<"|* Pila\t*|\n___________"<<endl;
	while(aux!=NULL){
		cout<<"| "<<aux->dato<<"\t |"<<endl;
		aux=aux->siguiente;
	}
	cout<<endl;
}

class fila
{
public:
	fila(){
		inicio=fin=NULL;
	}
	void push(char);
	void pop1();
	void pop2();
	void print();
	char get_inicio();
	Nodo *inicio;
	Nodo *fin;
private:
		
};

char fila::get_inicio(){
	return inicio->dato;
}
void fila::push(char valor){
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
		}
	}
	
}

void fila::print(){
	if(inicio==NULL)
		cout<<"la fila esta vacia"<<endl;
	Nodo *aux=inicio;
	cout<<"|* Fila\t*|\n___________"<<endl;
	while(aux!=NULL){
		cout<<"| "<<aux->dato<<"\t |"<<endl;
		aux=aux->siguiente;
	}
}
void probar (Pila A, fila B){
	while(A.cima!=NULL){
		if (A.get_cima()==B.get_inicio()){
			A.pop1();
			B.pop1();
		}
		else{
			cout<<"[ No ] ";
			return;
		}
	}
	cout<<"[ Si ] ";
}

void generar(){
		ifstream input;
        input.open("palindrome.txt");
        string line;
        int i=1;
        while(getline(input,line)){
            string aux=line;
            Pila A;
			fila B;
            for (int i=0;i< aux.length();i++){
                A.push(aux[i]);
                B.push(aux[i]);
            }
            /*int op;
            cout<<"Desea ver la Fila y Pila?\n[1] Si \n[2] No"<<endl;
            cin>>op;
            if (op==1){
            	A.print();
            	cout<<endl;
            	B.print();
            }*/
            probar(A,B);
            cout<<line<<endl;
        }
        input.close();
}
int main(){
	cout<<"\t*****Problema 15.5*****"<<endl;
	generar();
	return 0;
}