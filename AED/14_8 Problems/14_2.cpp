///14.8 problemas
///ejercicio 14.2

#include <iostream>
#include <fstream>
using namespace std;

struct Nodo{
	string valor;
    char tipo;
	Nodo* siguiente;
	Nodo (string valor, char tipo){
        this->valor=valor;
        this->tipo=tipo;
        this->siguiente=NULL;
    }
    Nodo (string valor,char tipo, Nodo*siguiente ){
        this->valor = valor;
        this->tipo=tipo;
        this->siguiente = siguiente;
    }
};
void ingresar(Nodo *& m_front,string palabra, char tipo){
    char X='f';
    if(m_front==NULL)
        m_front=new Nodo(palabra, tipo);
    else{
        if (X=='f'){
            Nodo *aux=m_front;
            while(aux->siguiente!=NULL){
                aux=aux->siguiente;
            }
            aux->siguiente=new Nodo(palabra, tipo);
        }
        else{
            m_front=new Nodo(palabra,tipo,m_front);
        }
    }
}
Nodo* leer_archivo(){
    Nodo *archivo=NULL;
    ifstream input;
    input.open("14.txt");
    string line;
    while(getline(input,line)){
        string aux=line;
        string agregar;
        for (int i=0;i< aux.length();i++){
            if (aux[i]!=' '){
                agregar+=aux[i];    
            }
            else{
                ingresar(archivo,agregar,'e');
                agregar="";
            }
        }
        ingresar(archivo,agregar,'f');
    }
    input.close();
    return archivo;
}
void mostrar(Nodo * raiz){
    for (Nodo*aux=raiz;aux;aux=aux->siguiente){
            cout<<aux->valor<<"->  ";
        }
    cout<<endl; 
}
void eliminar(Nodo *& raiz, string dato){
    if (raiz==NULL){
        cout<<"la lista esta vacia"<<endl;
        return;
    }
    else{
        Nodo *aux=raiz->siguiente;
        Nodo *anterior=raiz;
        while (aux!=NULL){
            if (aux->valor==dato){
                anterior->siguiente=aux->siguiente;
                delete aux;
                aux=anterior->siguiente;
            }
            else{
                aux=aux->siguiente;
                anterior=anterior->siguiente;
            }
        }
        if (raiz->valor==dato){
            raiz=raiz->siguiente;
        }
    }
}
void hacer_archivo(Nodo * raiz){
    Nodo* aux=raiz;
    ofstream fichero;
    fichero.open("14.txt");
    while(aux){
        fichero<<aux->valor<<" ";
        if (aux->tipo=='f' && aux->siguiente!=NULL){
            fichero<<endl;
        }
        aux=aux->siguiente;
    }
    fichero.close();
}
int main(){
    Nodo *A=NULL;
    int op;
    string valor;
    A=leer_archivo();
    do{
        cout<<"\t*****Problema 14.2*****\n[1] Mostrar la lista enlazada\n[2] Ingresar nueva palabra\n[3] Eliminar una palabra\n[4] Generar archivo\n[5] Salir"<<endl;
        cin>>op;
        cout<<endl;
        if (op<1 || op>5){
            cout<<"opcion invalida"<<endl;
        }
        else{
            switch(op){
                case 1:
                    mostrar(A);
                    cout<<endl;
                    break;
                case 2:
                    cout<<"Ingrese nueva palabra para el archivo"<<endl;
                    cin>>valor;
                    ingresar(A,valor,'f');
                    cout<<endl;
                    break;
                case 3:
                    cout<<"Ingrese la palabra a eliminar"<<endl;
                    cin>>valor;
                    eliminar(A,valor);
                    cout<<endl;
                    break;
                case 4:
                    cout<<"Se generó el archivo"<<endl;
                    hacer_archivo(A);
                    cout<<endl;
            }
        }
    }while(op!=5);
    
    return 0;
}
