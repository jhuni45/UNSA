#include "piladinamica.h"


int Pila::get_cima(){
	return cima->dato;
}

void Pila::push(int valor){
	if (cima==NULL){
		cima=new Nodo(valor);
	}
	else{
		cima=new Nodo(valor,cima);
	}
	//print();
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

void copiar_v1(Pila fuente,Pila &destino){
	Pila intermedia;
	if (fuente.cima==NULL){
		cout<<"No hay elementos para copiar"<<endl;
		return;
	}
	else{
		Nodo * aux=fuente.cima;
		while(aux!=NULL){
			intermedia.push(aux->dato);
			aux=aux->siguiente;
		}
		aux=intermedia.cima;
		while(aux!=NULL){
			destino.push(aux->dato);
			aux=aux->siguiente;
		}
	}
}
void copiar_v2(Pila fuente,Pila &destino){
	if (destino.cima!=NULL){
		destino.cima=NULL;
	}
	if (fuente.cima==NULL){
		cout<<"No hay elementos para copiar"<<endl;
		return;
	}
	else{
		Nodo * aux=fuente.cima;
		while(aux!=NULL){
			if (destino.cima==NULL){
				destino.cima=new Nodo(aux->dato);
			}
			else{
				Nodo * aux1=destino.cima;
				while(aux1->siguiente!=NULL){
					aux1=aux1->siguiente;
				}	
				aux1->siguiente=new Nodo(aux->dato);	
			}
			aux=aux->siguiente;
		}

	}

}
int main (){
	Pila a,b;
	int op;
	int valor;
	cout<<"\t*****Problema 15.1*****"<<endl;
	do{
        cout<<"[1] Agregar elementos\n[2] Mostrar pilas\n[3] Eliminar cima\n[4] Vaciar la pila\n[5] Copiar pila\n[6] Salir"<<endl;
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
                    b.print();
                    cout<<endl;
                    break;
                case 3:
                	a.pop1();
                	//b.pop1();
                	cout<<endl;
                	break;
                case 4:
                	a.pop2();
                	b.cima=NULL;
                	cout<<endl;
                	break;
                case 5:
               		copiar_v2(a,b);
                	cout<<endl;
                	break;
            }
        }
    }while(op!=6);
	return 0;
}