///14.8 problemas
///ejercicio 14.1

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>  
using namespace std;

struct Nodo{
	int valor;
	Nodo* siguiente;
	Nodo (int valor){
        this->valor=valor;
        this->siguiente=NULL;
    }
    Nodo (int valor,Nodo*siguiente){
        this->valor = valor;
        this->siguiente = siguiente;
    }
};

///Esta funcion genera lista enlazada con numero aleatorios

Nodo * generar(int lop){
	char X='f';
	Nodo *raiz=NULL;
	int azar;
	cout<<"se generaran numeros aleatorios entre 1 y 100"<<endl;
	while (lop>0){
		azar = rand() % 100 + 1;
		if (raiz==NULL){
			raiz=new Nodo(azar);
		}
		else{
			///en caso se inserte hasta el final
			if (X=='f'){
            	Nodo *aux=raiz;
            	while(aux->siguiente!=NULL){
                	aux=aux->siguiente;
            	}
            	aux->siguiente=new Nodo(azar);
        	}
        	///en caso se inserte al inicio
        	else{
        		raiz=new Nodo(azar,raiz);		
        	}
		}
		lop--;
	}
	return raiz;	
}

void mostrar(Nodo * raiz){
	if (raiz==NULL){
		cout<<"la lista esta vacia"<<endl;
		return;
	}
	for (Nodo*aux=raiz;aux;aux=aux->siguiente){
            cout<<aux->valor<<"->  ";
        }
    cout<<endl;	
}
///esta funcion elimina valores superiores a N
void eliminar(Nodo *& raiz, int dato){
	if (raiz==NULL){
		cout<<"la lista esta vacia"<<endl;
		return;
	}
	else{
		Nodo *aux=raiz->siguiente;
		Nodo *anterior=raiz;
		while (aux!=NULL){
			if (aux->valor>dato){
				anterior->siguiente=aux->siguiente;
				delete aux;
				aux=anterior->siguiente;
			}
			else{
				aux=aux->siguiente;
				anterior=anterior->siguiente;
			}
		}
		if (raiz->valor>dato){
			raiz=raiz->siguiente;
		}
	}
}

int main(){
	srand (time(NULL));
	Nodo *A=NULL;
	int lop,op,valor;
	cout<<"tamano de la lista enlazada: "<<endl;
	cin>>lop;
	A=generar(lop);
	do{
		cout<<"\t*****Problema 14.1*****\n[1] Mostrar\n[2] Eliminar\n[3] Salir"<<endl;
		cin>>op;
        cout<<endl;
        if (op<1 || op>3){
            cout<<"opcion invalida"<<endl;
        }
        else{
            switch(op){
                case 1:
                    mostrar(A);
                    cout<<endl;
                    break;
                case 2:
                	cout<<"Ingrese el N para eliminar sus superiores"<<endl;
                    cin>>valor;
                    eliminar(A,valor);
                    cout<<endl;
                    break;
			}
		}
	}while(op!=3);
	return 0;
}
