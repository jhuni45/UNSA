#include "piladinamica.h"

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
		numeros.erase(numeros.begin()+ numeros.size()-1);
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
		numeros.erase(numeros.begin()+ numeros.size()-1);
	}
	
}
template <class T>
void Pila<T>::print(){
	int opc;
	if(cima==NULL){
		cout<<"La pila esta vacia por lo tanto el array tambien"<<endl;
		return;
	}
	cout<<"[1] Mostrar pila\n[2] Mostrar Array"<<endl;
	cin>>opc;
	if (opc==1){
		Nodo<T>* aux=cima;
		cout<<"|* Pila\t*|\n___________"<<endl;
		while(aux!=NULL){
			cout<<"| "<<aux->dato<<"\t |"<<endl;
			aux=aux->siguiente;
		}
	}
	else{
		cout<<"\n Contenido del Array:"<<endl;
		if (!numeros.size()){
			cout<<"El array esta vacio"<<endl;
		}
		cout<<"|*Array\t*|\n__________"<<endl;
		for (int i =0;i <numeros.size();i++){
			cout<<"| "<<numeros[i]<<"\t |"<<endl;
		}
		cout<<endl;	
	}
	
}

template <class T>
void Pila<T>:: generar(){
	int auxnu,a=10;
	while(a){
		auxnu=rand() %1000 +1;
		T valor=(double)auxnu/2;
		numeros.push_back(valor);
		push(valor);
		a--;
	}
}

template <class T>
void Pila<T>:: print_funcion(){
	if (cima==NULL){
		cout<<"la pila esta vacia, por lo tanto el array tambien"<<endl;
		return;
	}
	Nodo <T>*aux=cima;
	while(cima!=NULL){
		T contenido=get_cima();
		cout<<contenido<<" ->" ;
		delete cima;
		aux=aux->siguiente;
		//print();
		cima=aux;
		numeros.erase(numeros.begin()+ numeros.size()-1);
	}
}
int main (){
	srand (time(NULL));
	Pila<float> a;
	int op;
	cout<<"\t*****Problema 15.4*****"<<endl;
	do{
        cout<<"[1] Generar elementos\n[2] Mostrar array y pila\n[3] Eliminar cima\n[4] Vaciar la pila\n[5] Mostrar (funcion)\n[6] Salir"<<endl;
        cin>>op;
        cout<<endl;
        if (op<1 || op>6){
            cout<<"opcion invalida"<<endl;
        }
        else{
            switch(op){
                case 1:
                	a.generar();
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
                	a.print_funcion();
                	cout<<endl;
                	break;
                
            }
        }
    }while(op!=6);
	return 0;
}