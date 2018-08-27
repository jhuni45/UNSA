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

class simpleO{
public:
    void add(int);
    void remove(int);
    void print();
    simpleO(){
        m_front=NULL;
    }
private:
    Nodo* m_front; // NULL if list is empty

};

void simpleO::add(int valor){
    if(m_front==NULL)
        m_front=new Nodo(valor);
    else{
        Nodo *aux=m_front;
        if(m_front->dato>valor){
            m_front=new Nodo(valor,m_front);
        }
        else {
            while(aux->dato<valor && aux->siguiente!=NULL){
                aux=aux->siguiente;
            }
            aux->siguiente=new Nodo(valor,aux->siguiente);
        }

    }
}

void simpleO::remove(int valor){
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
void simpleO::print (){
    for (Nodo*aux=m_front;aux;aux=aux->siguiente){
        cout<<aux->dato<<"->  ";
    }
    cout<<endl;
}

class dobleNO{
public:
    void add(int,char);
    void remove(int);
    void print();
    dobleNO(){
        m_front=m_last=NULL;
    }
private:
    Nodo* m_front;
    Nodo* m_last;
};

void dobleNO::add(int valor, char X){
	Nodo*nuevo=new Nodo(valor);
    if(m_front==NULL){
        m_front=nuevo;
        m_front->anterior=NULL;
        m_last=nuevo;
    }
    else{
        if (X=='f'){
            Nodo *aux=m_last;
            aux->siguiente=nuevo;
            nuevo->anterior=aux;
            m_last=nuevo;
            /*Nodo *aux=m_front;
            while(aux->siguiente!=NULL){
                aux=aux->siguiente;
            }
            aux->siguiente=new Nodo(valor,m_front->siguiente,m_front);*/
        }
        else{
        	Nodo *aux=m_front;
            aux->anterior=nuevo;
            nuevo->siguiente=aux;
            m_front=nuevo;
        }
    }
}

void dobleNO::remove(int valor){
    Nodo *temp=m_front;
    while(temp->dato!=valor && temp->siguiente!=NULL){
    	temp=temp->siguiente;
    }
	if(temp->dato==valor){
        if(temp->siguiente!=NULL && temp->anterior!=NULL){
            Nodo *temp2=temp;
            temp=temp->anterior;
            temp->siguiente=temp2->siguiente;
            temp2->siguiente->anterior=temp;
            delete temp;
        }
        else{
        	if(temp->anterior==NULL){
        		m_front=temp->siguiente;
        		temp->siguiente->anterior=NULL;
        		delete temp;
        	}
        	else{
        		m_last=temp->anterior;
        		temp->anterior->siguiente=NULL;
        		delete temp;
        	}
        }

	}

}
void dobleNO::print (){
    for (Nodo*aux=m_front;aux;aux=aux->siguiente){
            cout<<aux->dato<<"->  ";
        }
        cout<<endl;
}

class dobleO{
public:
    void add(int);
    void remove(int);
    void print();
    dobleO(){
        m_front=NULL;
    }
private:
    Nodo* m_front;
    Nodo* m_last;
};

void dobleO::add(int valor){
	Nodo* nuevo=new Nodo(valor);
    if(m_front==NULL)
        m_front=nuevo;
   		m_front->anterior=NULL;
    	m_last=nuevo;
    else{
        Nodo *aux=m_front;
        if(m_front->dato>valor){
            m_front=new Nodo(valor,m_front,m_front->anterior);
        }
        else {
            while(aux->dato<valor || aux->siguiente!=NULL){
                aux=aux->siguiente;
            }
            aux->siguiente=new Nodo(valor,aux->siguiente,aux);
        }
    }
}

void dobleO::remove(int valor){
    Nodo *temp=m_front;
    while(temp->dato!=valor && temp->siguiente!=NULL){
    	temp=temp->siguiente;
    }
	if(temp->dato==valor){
        if(temp->siguiente!=NULL && temp->anterior!=NULL){
            Nodo *temp2=temp;
            temp=temp->anterior;
            temp->siguiente=temp2->siguiente;
            temp2->siguiente->anterior=temp;
            delete temp;
        }
        else{
        	if(temp->anterior==NULL){
        		m_front=temp->siguiente;
        		temp->siguiente->anterior=NULL;
        		delete temp;
        	}
        	else{
        		m_last=temp->anterior;
        		temp->anterior->siguiente=NULL;
        		delete temp;
        	}
        }

	}

}
void dobleO::print (){
    for (Nodo*aux=m_front;aux;aux=aux->siguiente){
            cout<<aux->dato<<"->  ";
        }
        cout<<endl;
}

int main (){

    simpleNO a;
    a.add(1,'f');
    a.add(2,'f');
    a.add(3,'f');
    a.add(4,'i');
    a.print();
    a.remove(2);
    a.print();

//    simpleO a;
//    a.add(2);
//    a.add(3);
//    a.add(1);
//    a.add(0);
//    a.print();
//    a.remove(3);
//    a.print();
//

/*
    dobleNO a;
    a.add(3,'f');
    a.add(2,'f');
    a.add(4,'c');
    a.add(1,'f');
    a.print();
    a.remove(1);
    a.print();
*/

/*
    dobleO a;
    a.add(3);
    a.add(2);
    a.add(1);
    a.add(0);
    a.print();
*/
    return 0;
}

