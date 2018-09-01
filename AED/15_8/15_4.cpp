#include <iostream>
#include <vector>

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
	void generar(string);
	char get_cima();
	Pila(){
		cima=NULL;
	}
	
private:
	Nodo *cima;
};
	
void Pila::generar(string cadena){
	for (int i =0;i<cadena.length();i++){
		if (cadena[i]=='(' || cadena[i]==')' || cadena[i]=='[' || cadena[i]==']' || cadena[i]=='{' || cadena[i]=='}'){
			if (cadena[i]=='(' || cadena[i]=='{' || cadena[i]=='['){
				push(cadena[i]);
			}
			if (cadena[i]=='}' || cadena[i]==')' || cadena[i]==']'){
				if (cadena[i]=='}'){
					if (get_cima()=='{'){
						pop1();
					}
					else{
						cout<<"No hay equilibrio "<<endl;
						return;
					}
				}
				if (cadena[i]==')'){
					if (get_cima()=='('){
						pop1();
					}
					else{
						cout<<"No hay equilibrio "<<endl;
						return;
					}
				}
				if (cadena[i]==']'){
					if (get_cima()=='['){
						pop1();
					}
					else{
						cout<<"No hay equilibrio "<<endl;
						return;
					}
				}
			}
		}
	}
	if (cima==NULL){
		cout<<"La cadena tiene equilibrio"<<endl;
		return;
	}
	else{
		cout<<"No hay equilibrio "<<endl;
		return;
	}
}

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
		Nodo*aux=cima;
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
		//print();
		cima=aux;
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
	int op;
	string cadena;
	cout<<"\t*****Problema 15.4*****"<<endl;
	do{
        cout<<"[1] Ingresar nueva cadena\n[2] Salir"<<endl;
        cin>>op;
        cout<<endl;
        if (op<1 || op>2){
            cout<<"opcion invalida"<<endl;
        }
        else{
            switch(op){
                case 1:
                	Pila a;
                	cout<<"Ingrese la cadena "<<endl;
                	cin>>cadena;
                	a.generar(cadena);
                    cout<<endl;
                    break;
            }
        }
    }while(op!=2);
	return 0;
}