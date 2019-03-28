#include <iostream>

using namespace std;


struct Nodo{
    int dato;
    Nodo *siguiente;
    Nodo *anterior;
    Nodo (int dato){
        this->dato=dato;
    }
    Nodo (int dato,Nodo*siguiente){
        this->dato = dato;
        this->siguiente = siguiente;
    }

    Nodo (int dato, Nodo *siguiente, Nodo * anterior){
        this->dato=dato;
        this->anterior=anterior;
        this->siguiente=siguiente;
    }
};


class simpleNOC{
public:
    void add(int,char);
    void remove(int);
    void print();
    simpleNOC(){
        m_front=NULL;
        n=0;
    }

private:
    Nodo* m_front; // NULL if list is empty
    int n;
};


void simpleNOC::add(int valor, char X){
    cout<<"ingrese "<<endl;
    if(m_front==NULL){
        m_front=new Nodo(valor);
    	m_front->siguiente=m_front;
    	n++;
    	print();
    }
    else{
        if (X=='f'){
            Nodo *aux=m_front;
            int a=n-1;
            while(a){
                aux=aux->siguiente;
                a--;
            }
            aux->siguiente=new Nodo(valor,m_front);
            n++;
            print();
        }
        else{
            m_front=new Nodo(valor,m_front);
            Nodo *aux=m_front;
            int a=n-1;
            while(a){
                aux=aux->siguiente;
                a--;
            }
            aux->siguiente->siguiente=m_front;
            n++;
            print();
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
void simpleNOC::print (){
    cout<<"ingrese al"<<endl;
    Nodo*aux=m_front;
    for (int i=0;i<n;i++){
        cout<<aux->dato<<"->  ";
        aux=aux->siguiente;
    }
    cout<<endl;
}

class simpleOC{
public:
    void add(int);
    void remove(int);
    void print();
    simpleOC(){
        m_front=NULL;
        n=0;
    }
private:
    Nodo* m_front;
    int n;
};

void simpleOC::add(int valor){
    if(m_front==NULL){
        m_front=new Nodo(valor);
        m_front->siguiente=m_front;
        n++;
    }
    else{
        Nodo *aux=m_front;
        if(aux->dato>valor){
            m_front=new Nodo(valor,m_front);
            int a=n-1;
            while (a){
                aux=aux->siguiente;
                a--;
            }
            aux->siguiente=m_front;
            n++;
        }
        else {
            while(aux->dato<valor && n-1){
                aux=aux->siguiente;
            }
            aux->siguiente=new Nodo(valor,aux->siguiente);
            aux=m_front;
            n++;
            int a=n-1;
            while (a){
                aux=aux->siguiente;
                a--;
            }
            aux->siguiente=m_front;
        }
    }
}

void simpleOC::remove(int valor){
    Nodo *trash=NULL;
    if(m_front->dato==valor){
        trash=m_front;
        m_front=m_front->siguiente;
    }
    else{
        Nodo*aux=m_front;
        while(aux->dato!=valor){
            aux=aux->siguiente;
        }
        trash=aux->siguiente;
        aux->siguiente=aux->siguiente->siguiente;
        delete trash;
    }
}
void simpleOC::print (){
    cout<<"ingrese al"<<endl;
    Nodo*aux=m_front;
    for (int i=0;i<n;i++){
        cout<<aux->dato<<"->  ";
        aux=aux->siguiente;
    }
    cout<<endl;
}


class dobleNOC{
public:
    void add(int,char);
    void remove(int);
    void print();
    dobleNOC(){
        m_front=NULL;
        n=0;
    }
private:
    Nodo* m_front;
    int n;

};

void dobleNOC::add(int valor, char X){
    if(m_front==NULL){
        m_front=new Nodo(valor);
        m_front->siguiente=m_front;
        m_front->anterior=m_front;
        n++;
    }
    else{
        if (X=='f'){
            Nodo *aux=m_front;
            int a=n-1;
            while(a){
                aux=aux->siguiente;
                a--;
            }
            aux->siguiente=new Nodo(valor,m_front,aux);
            m_front->anterior=aux->siguiente;
            n++;
        }
        else{
            Nodo *aux=m_front;
            int a=n-1;
            while(a){
                aux=aux->siguiente;
                a--;
            }
            m_front=new Nodo(valor,m_front,aux);
            aux->siguiente=m_front;
            n++;
        }
    }
}

void dobleNOC::print (){
    cout<<"ingrese al"<<endl;
    Nodo*aux=m_front;
    for (int i=0;i<n;i++){
        cout<<aux->dato<<"->  ";
        aux=aux->siguiente;
    }
    cout<<endl;
}

class dobleOC{
public:
    void add(int);
    void remove(int);
    void print();
    dobleOC(){
        m_front=NULL;
        n=0;
    }
private:
    Nodo* m_front;
    int n;

};

void dobleOC::add(int valor){
    if(m_front==NULL){
        m_front=new Nodo(valor);
        m_front->anterior=m_front;
        m_front->siguiente=m_front;
        n++;
    }
    else{
        Nodo *aux=m_front;
        if(aux->dato>valor){
            int a=n-1;
            while(a){
                aux=aux->siguiente;
                a--;
            }
            m_front=new Nodo(valor,m_front,aux);
            aux->siguiente=m_front;
            n++;
        }
        else {
        int a=n-1;
            while(aux->dato<valor || a){
                aux=aux->siguiente;
                a--;
            }
            aux->siguiente=new Nodo(valor,aux->siguiente,aux);
            n++;
        }
    }
}

void dobleOC::print (){
    cout<<"ingrese al"<<endl;
    Nodo*aux=m_front;
    for (int i=0;i<n;i++){
        cout<<aux->dato<<"->  ";
        aux=aux->siguiente;
    }
    cout<<endl;
}

int main (){
//    simpleNOC a;
//    a.add(1,'f');
//    a.add(2,'f');
//    a.add(3,'f');
//    a.add(4,'i');
//    a.print();

//    simpleOC a;
//    a.add(2);
//    a.add(3);
//    a.add(1);
//    a.add(0);
//    a.print();
//
//    dobleNOC a;
//    a.add(3,'f');
//    a.add(2,'f');
//    a.add(1,'c');
//    a.print();

    dobleOC a;
    a.add(3);
    a.add(2);
    a.add(1);
    a.print();
	return 0;
}
