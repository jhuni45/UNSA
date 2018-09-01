#include <iostream>

using namespace std;

struct Nodo{
	char clave;
	int valor;
	Nodo * siguiente;
	Nodo (int valor){
        this->valor=valor;
        this->clave='L';
        this->siguiente=NULL;
	}
};

class HashL{
public:
	void add(int);
	void remove(int);
	void print();
	int funcion(int);
	Nodo * crear(int);
	HashL(int x){
		N=x;
		front=new Nodo(NULL);
		front->siguiente=crear(N-1);
   	}
private:
	int N;
	Nodo *front;
};

Nodo* HashL::crear(int x){
    if(!x)
        return 0;
    Nodo *nuevo=new Nodo(NULL);
    nuevo->siguiente=crear(x-1);
    return nuevo;
}
int HashL::funcion(int val){
    if (val<0)
        return ((N + (val%N)) % N);
    return val%N;
}
void HashL::add(int val){
    int cont=1;
    int pos=funcion(val);
    Nodo *aux=front;
    for (int i=0;i<pos;i++){
        aux=aux->siguiente;
    }
    if(aux->clave!='O'){
        aux->clave='O';
        aux->valor=val;
    }
    else if (aux->clave=='O'){
        while(aux->clave=='O' && cont<N){
            if (aux->siguiente==NULL)
                aux=front;
            else
                aux=aux->siguiente;
            cont++;
        }
        if(cont==N){
            cout<<"la lista esta llena, no se puede insertar"<<endl;
        }
        else{
            aux->clave='O';
            aux->valor=val;
        }
    }
}
void HashL::remove(int val){
    bool flag=false;
    for (Nodo *aux=front;aux!=NULL;aux=aux->siguiente){
        if (aux->valor==val){
            aux->valor=NULL;
            aux->clave='R';
            flag=true;
        }
    }
    if (flag==false)
        cout<<"el elemento no se encuentra"<<endl;
}

void HashL::print(){
    for (Nodo *aux=front;aux!=NULL;aux=aux->siguiente){
        cout<<aux->clave<<" -> "<<aux->valor<<endl;
    }
    cout<<endl;
}

int main (){
    HashL A(9);
    A.add(50);
    A.add(9);
    A.add(50);
    A.add(50);
    A.add(50);
    A.add(50);
    A.add(9);
    A.add(9);
    A.add(9);
    A.remove(50);
    A.add(50);
    A.print();

	return 0;


}
