#include <iostream>
using namespace std;

class NodoD{
public:
    char valor;
    NodoD *n_next;
    NodoD *n_back;
public:
    NodoD(char dato)    {
        this->valor=dato;
        this->n_next=0;
        this->n_back=0;
    }
};

class Lista_D_O
{
public:
    NodoD *m_head;
    NodoD *m_last;
public:
    Lista_D_O(){
        m_head=0;
        m_last=0;
    }
    void ordenar(char);
    void add_end(char);
    void generar(string);
    void alfabeto(NodoD*);
    void print();
};

void Lista_D_O::generar(string cadena){
    for(int i=0;i<cadena.length();i++){
        add_end(cadena[i]);
    }
}

void Lista_D_O::add_end(char dato){
    NodoD *nuevo=new NodoD(dato);
    if(!m_head){
        m_head=nuevo;
        m_last=nuevo;
    }
    else{
        NodoD *temp=m_last;
        temp->n_next=nuevo;
        nuevo->n_back=temp;
        m_last=nuevo;
    }
}

void Lista_D_O::ordenar(char dato){
    NodoD *nuevo=new NodoD(dato);
    if(!m_head){
        m_head=nuevo;
        m_last=nuevo;
    }
    else{
        NodoD *temp=m_head;
        while(temp->valor<dato && temp->n_next!=0){
            temp=temp->n_next;
        }
        if(temp->valor<dato){
            nuevo->n_back=temp;
            temp->n_next=nuevo;
            m_last=nuevo;
        }
        else{
            if(temp->n_back!=0){
                nuevo->n_next=temp;
                nuevo->n_back=temp->n_back;
                temp->n_back->n_next=nuevo;
                temp->n_back=nuevo;
            }
            else{
                nuevo->n_next=temp;
                temp->n_back=nuevo;
                m_head=nuevo;
            }
        }
    }
}

void Lista_D_O::print(){
    NodoD *temp=m_head;
    while(temp->n_next!=0){
        cout<<temp->valor<<" -> ";
        temp=temp->n_next;
    }
    cout<<temp->valor<<endl;
}

void Lista_D_O::alfabeto(NodoD *raiz){
    NodoD *temp=raiz;
    while(temp){
        ordenar(temp->valor);
        temp=temp->n_next;
    }
}
int main(){
    Lista_D_O A,B;
    int op;
    string cadena;
    cout<<"\t*****Problema 14.6*****"<<endl;
    cout<<"Ingrese una cadena de texto"<<endl;
    getline(cin,cadena);
    A.generar(cadena);
    do{
        cout<<"[1] Mostrar lista\n[2] Generar ordenada\n[3] Salir"<<endl;
        cin>>op;
        cout<<endl;
        if (op<1 || op>3){
            cout<<"opcion invalida"<<endl;
        }
        else{
            switch(op){
                case 1:
                    A.print();
                    cout<<endl;
                    break;
                case 2:
                    NodoD * aux=A.m_head;
                    B.alfabeto(aux);
                    B.print();
                    B.m_head=NULL;
                    cout<<endl;
                    break;
            }
        }
    }while(op!=3);
    return 0;
}
