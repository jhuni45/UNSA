#include "piladinamica.h"

template <class T>
void Pila<T>::show_basic(){	
	Nodo <T>*aux=cima;
	if (cima==NULL){
		cout<<"la pila esta vacia"<<endl;
	}
	while(cima!=NULL){
		string cadena=get_cima();
		cout<<cadena<<"\t"<<endl;
		//delete aux;
		aux=aux->siguiente;
		cima=aux;
	}
}
template <class T>
T Pila<T>::get_cima(){
	return cima->dato;
}

template <class T>
void Pila<T>::push(T valor){
	if (cima==NULL){
		cima=new Nodo<T>(valor);
	}
	else{
		cima=new Nodo<T>(valor,cima);
	}
	//print();
}

template <class T>
void Pila<T>::pop1(){
	if(cima==NULL){
		cout<<"la pila ya esta vacia"<<endl;
	}
	else{
		Nodo <T> *aux=cima;
		aux=aux->siguiente;
		delete cima;
		cima=aux;
	}
	//print();
}
template <class T>
void Pila<T>::pop2(){
	Nodo <T>*aux=cima;
	while(cima!=NULL){
		delete cima;
		aux=aux->siguiente;
		//print();
		cima=aux;
	}
	
}
template <class T>
void Pila<T>::print(){
	if(cima==NULL)
		cout<<"la pila esta vacia"<<endl;
	Nodo<T>* aux=cima;
	while(aux!=NULL){
		cout<<aux->dato<<"->";
		aux=aux->siguiente;
	}
	cout<<endl;
}

int main (){
	Pila<string> a;
	int op;
	string valor;
	cout<<"\t*****Problema 15.3*****"<<endl;
	do{
        cout<<"[1] Agregar elementos\n[2] Mostrar elementos\n[3] Eliminar cima\n[4] Vaciar la pila\n[5] Mostrar (operaciones basicas)\n[6] Salir"<<endl;
        cin>>op;
        cout<<endl;
        if (op<1 || op>6){
            cout<<"opcion invalida"<<endl;
        }
        else{
            switch(op){
                case 1:
                	cout<<"Ingrese el valor: "<<endl;
                	cin>>valor;
                    a.push(valor);
                    cout<<endl;
                    break;
                case 2:
                    a.print();
                    cout<<endl;
                    break;
                case 3:
                	a.pop1();
                	cout<<endl;
                	break;
                case 4:
                	a.pop2();
                	cout<<endl;
                	break;
                case 5:
                	Pila <string>aux=a;
                	cout<<"contenido (operaciones basicas)"<<endl;
                	aux.show_basic();
                	cout<<endl;
                	break;
            }
        }
    }while(op!=6);
	return 0;
}