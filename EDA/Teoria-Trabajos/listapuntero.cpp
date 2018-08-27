#include <iostream>

using namespace std;

struct Nodo{
    int dato;
    Nodo *siguiente;
    Nodo *anterior;
    Nodo (int dato){
        this->dato=dato;
        this->siguiente=siguiente;
    }
    Nodo (int dato,Nodo*siguiente){
        this->dato = dato;
        this->siguiente = siguiente;
    }
};

class simpleNO{
public:
    void add(int,char );
    void remove(int);
    void print();
    simpleNO(){
        m_front=NULL;
    }

private:
    Nodo* m_front; // NULL if list is empty
};


void simpleNO::add(int valor, char X){
    if(m_front==NULL)
        m_front=new Nodo(valor);
    else{
        if (X=='f'){
            Nodo *aux=m_front;
            while(aux->siguiente!=NULL){
                aux=aux->siguiente;
            }
            aux->siguiente=new Nodo(valor);
        }
        else{
            m_front=new Nodo(valor,m_front);
        }
    }
}

void simpleNO::remove(int valor){
    if (!m_front){
		cout<<"no existe"<<endl;
	}
	else{
		Nodo *temp=m_front;
		Nodo *temp2=m_front;
		bool cambio=false;
		while(temp){
			if(temp->dato==valor){
				cambio=true;
				if(temp==temp2){
                    m_front=temp->siguiente;
                    delete temp;
				}
				else{
                    temp2->siguiente=temp->siguiente;
                    delete temp;
                }
			}
			temp2=temp;
			temp=temp->siguiente;

		}
		if(!cambio){
			cout<<"no se elimino"<<endl;
		}
		else
			cout<<"eliminado"<<endl;
	}

}
void simpleNO::print (){
    for (Nodo*aux=m_front;aux;aux=aux->siguiente){
            cout<<aux->dato<<"->  ";
        }
        cout<<endl;
}

int main (){
    simpleNO a;
	cout<<"insertando 1 .. 5 inicio, fin, inicio, fin . . ."<<endl;
    a.add(1,'i');
    a.add(2,'f');
    a.add(3,'i');
    a.add(4,'f');
	a.add(5,'i');
    a.print();
	cout<<"eliminar el numero 2"<<endl;
    a.remove(2);
    a.print();
	cout<<"eliminar el numero 5"<<endl;
	a.remove(5);
	a.print();
	return 0;
}

