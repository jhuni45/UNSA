#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

template <class T>
struct Nodo{
    T dato;
    Nodo *siguiente;
    Nodo (T dato){
        this->dato=dato;
        this->siguiente=NULL;
    }
};

template< class T>
void agregar(Nodo<T> *&m_front, T valor){
	Nodo <T>*nuevo=new Nodo<T>(valor);
    Nodo <T>*aux1=m_front;
    Nodo <T>*aux2;
    while((aux1!=NULL)&&(aux1->dato<valor)){
        aux2=aux1;
        aux1=aux1->siguiente;
    }
    if(m_front==aux1)
        m_front=nuevo;
    else{
        aux2->siguiente=nuevo;
    }
    nuevo->siguiente=aux1;

}
template< class T>
void print (Nodo<T>* m_front){
	Nodo<T> *aux=m_front;
	while(aux!=NULL){
		cout<<aux->dato<<" -> ";
		aux=aux->siguiente;
	}
    cout<<endl;
}
template< class T>
Nodo<T> * fmezcla(Nodo<T>* front1, Nodo<T>* front2){
	Nodo<T> *aux1=front1;
	Nodo<T> *aux2=front2;
	Nodo<T> *salida=NULL;
	while (aux1!=NULL && aux2!=NULL){
		if (aux1->dato<aux2->dato){
			cout<<"1 menor"<<endl;
			Nodo<T>*nuevo=new Nodo<T>(aux1->dato);
			if (salida==NULL){
				salida=nuevo;
			}
			else{
				Nodo<T> *auxs=salida;
				while(auxs->siguiente!=NULL)
					auxs=auxs->siguiente;
				auxs->siguiente=nuevo;
			}
			aux1=aux1->siguiente;
		}
		else{
			cout<<"2 menor"<<endl;
			Nodo<T>*nuevo=new Nodo<T> (aux2->dato);
			if (salida==NULL){
				salida=new Nodo<T>(aux2->dato);
			}
			else{
				Nodo<T> *auxs=salida;
				while(auxs->siguiente!=NULL)
					auxs=auxs->siguiente;
				auxs->siguiente=nuevo;
			}
			aux2=aux2->siguiente;
		}
		if (aux1->siguiente==NULL){
			Nodo<T> *aux=aux2;
			Nodo<T> *auxs=salida; 
			while(auxs->siguiente!=NULL){
				auxs=auxs->siguiente;
			}
			auxs->siguiente=aux1;
			auxs=auxs->siguiente;
			while(aux2!=NULL){
				auxs->siguiente=aux2;
				auxs=auxs->siguiente;
				aux2=aux2->siguiente;
			}
			return salida;			
		}
		if (aux2->siguiente==NULL){
			Nodo<T> *aux=aux1;
			Nodo<T> *auxs=salida; 
			while(auxs->siguiente!=NULL){
				auxs=auxs->siguiente;
			}
			auxs->siguiente=aux2;
			auxs=auxs->siguiente;
			while(aux1!=NULL){
				auxs->siguiente=aux1;
				auxs=auxs->siguiente;
				aux1=aux1->siguiente;
			}
			return salida;			
		}
	}
}

int main(){
	srand(time(NULL));
	Nodo<int> *front1=NULL;
	Nodo<int> *front2=NULL;
	Nodo<int> *mezcla=NULL;
	for (int i=0;i<5;i++){
		int aux= rand() %100 + 0;
		cout<<"valores"<<aux<<endl;	
		agregar(front1,aux);
	}
	for (int i=0;i<5;i++){
		int aux=rand () %100 + 0;
		cout<<"valores"<<aux<<endl;	
		agregar(front2,aux);
	}
	cout<<"front1"<<endl;
	print(front1);
	cout<<"front2"<<endl;
	print(front2);
	mezcla=fmezcla(front1,front2);
	cout<<"mezcla"<<endl;
	print(mezcla);


	return 0;
	
}