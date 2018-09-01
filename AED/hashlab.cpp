#include <iostream>

using namespace std;

const int tam=8;

struct tablahash{
	int clave;
	tablahash *prox; 	
};

int funcion(int num){
	return num%tam;
}

void insertar(tablahash *tabla[],int pos, int n){
	tablahash* nuevo;
	nuevo= new tablahash();
	nuevo->clave=n;
	nuevo->prox=tabla[pos];
	tabla[pos]=nuevo;
}

void eliminar (tablahash *tabla[],int num){
	int pos=funcion(num);
	tablahash* aux;
	if(tabla[pos]!=NULL){
		if (tabla[pos]->clave==num){
			aux=tabla[pos];
			tabla[pos]=tabla[pos]->prox;
			delete aux;

		}
		else{
			aux=tabla[pos]->prox;
			tablahash *ant=tabla[pos];
			while(aux!=NULL && aux->clave!=num){
				ant=aux;
				aux=aux-> prox;
			}
			if (aux!=NULL){
				ant->prox=aux->prox;
				delete aux;
			}
			else{
				cout<<"numero no encontrado"<<endl;
			}
		}
	}
	else{
		cout<<"numerono encontrado"<<endl;
	}
}

int main(){
	tablahash*tabla[tam];
	int op,pos;
	int num ,i;
	for (i=0;i<tam;i++){
		tabla[i]=NULL;
	}
	do{
		cout<<"Menu de opciones\n1 insertar\n2 mostrar\n3 eliminar\n4 salir"<<endl;
		cin>>op;
		if (op<1 || op>4){
			cout<<"ocin invalida"<<endl;
		}
		else{
			switch(op){
				case 1:
					cout<<"digite un numero:";
					cin>>num;
					pos=funcion(num);
					insertar(tabla,pos,num);
					break;
				case 2:
					//mostrar(tabla);
					break;
				case 3:
					cout<<"digite  un numero: ";
					cin>>num;
					eliminar(tabla,num);
					break;
			}
		}
	}
	while(op!=4);
}