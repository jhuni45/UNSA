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

class HashC{
public:
	void add(int);
	void remove(int);
	void print();
	int funcion(int);
	Nodo * crear(int);
    void test();
	HashC(int x){
		N=x;
		front=new Nodo(NULL);
		front->siguiente=crear(N-1);
   	}
private:
	int N;
	bool P=true;
	Nodo *front;
};

void HashC::test(){
    for (Nodo *aux=front;aux!=NULL;aux=aux->siguiente){
        if (aux->clave=='O')
            P=false;
    }
}
Nodo* HashC::crear(int x){
    if(!x)
        return 0;
    Nodo *nuevo=new Nodo(NULL);
    nuevo->siguiente=crear(x-1);
    return nuevo;
}
int HashC::funcion(int val){
    if (val<0)
        return ((N + (val%N)) % N);
    cout<<"modulo"<<val%N<<endl;
    return val%N;
}
void HashC::add(int val){
    if (P==false){
        cout<<"la tabla esta llena, no se inserto!"<<endl;
    }
    else{
        //cout<<"hola"<<endl;
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
            int tam=1;
            while(aux->clave=='O'){
                cout<<"tam "<<tam<<"para: "<<val<<endl;
                for (int i=0;i<tam;i++){
                    if(aux->siguiente==NULL)
                        aux=front;
                    else
                        aux=aux->siguiente;
                }
                tam++;
            }
            aux->clave='O';
            aux->valor=val;
        }
    }
}
void HashC::remove(int val){
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

void HashC::print(){
    for (Nodo *aux=front;aux!=NULL;aux=aux->siguiente){
        cout<<aux->clave<<" -> "<<aux->valor<<endl;
    }
    cout<<endl;
}

int main (){
    HashC A(10);
    A.add(77);
    A.add(50);
    A.add(14);
    A.add(45);
    A.remove(14);
    A.add(28);
    A.add(18);
    A.add(26);
    A.add(60);
    A.add(75);
    A.add(34);
    A.add(88);
//    A.remove(75);
//    A.remove(34);
//    A.add(52);
    A.print();

	return 0;


}
