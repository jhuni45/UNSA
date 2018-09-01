#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>

using namespace std;

class Nodo {
private:
    char key;
    string palabra;
    Nodo *next;
public:
    Nodo(char key, string value) {
        this->key = key;
        this->palabra = value;
        this->next = NULL;
    }
    char getKey() { return key; }
    string getValue() { return palabra; }
    Nodo *getNext() {  return next;  }
    void setValue(string palabra) {  this->palabra = palabra;  }
    void setNext(Nodo *next) {  this->next = next; }
};

const int TABLE_SIZE = 26;

class Cola{
private:
    Nodo **lista;
public:
    Cola() {
        lista = new Nodo*[TABLE_SIZE];
        for (int i = 0; i<TABLE_SIZE; i++)
            lista[i] = NULL;
    }

    void generar(){
        ifstream input;
        input.open("textocorrido.txt");
        string line;
        while(getline(input,line)){
            string aux=line;
            string agregar;
            for (int i=0;i< aux.length();i++){
                if (aux[i]!=' '){
                    agregar+=aux[i];    
                }
                else{
                    put(agregar[0],agregar);
                    agregar="";
                }
            }
            put(agregar[0],agregar);  
        }
        input.close();
    }
    
    void put(char key, string value) {
        Nodo *nuevo=new Nodo(key, value);
        int resta;
        if (key>='a' && key<='z'){
            resta=key-71;
        }
        if (key>='A' && key<='Z'){
            resta=key-39;
        }
        int hash=(resta%TABLE_SIZE);
        if (lista[hash]==NULL)
            lista[hash]=nuevo;
        else{
            Nodo *aux=lista[hash];
            nuevo->setNext(aux);
            lista[hash]=nuevo;
        }

    }
    void hacer_archivo(){
        ofstream fichero;
        fichero.open("ordenado.txt");
        for (int i=0;i<TABLE_SIZE;i++){
            Nodo *aux=lista[i];
            //cout<<i<<" ";
            if(aux==NULL){
                char x;
                x=i+97;
                fichero<<"["<<x<<"]"<<" [Sin palabras]"<<endl;
            }
            while(aux!=NULL){
                fichero<<aux->getValue()<<endl;
                //cout<<aux->getKey()<<" -> ";
                aux=aux->getNext();
            }
            //cout<<endl;
        }
        fichero.close();
    }
    void mostrar(){
        for (int i=0;i<TABLE_SIZE;i++){
            Nodo *aux=lista[i];
            cout<<i<<" ";
            if(aux==NULL)
                cout<<"NULL";
            while(aux!=NULL){
                cout<<aux->getValue()<<" -> ";
                aux=aux->getNext();
            }
            cout<<endl;
        }
    }
};

int main(){
    Cola prueba;
    int op;
    string clave="", palabra="",aux="";
    cout<<"****Problema 15.2*****"<<endl;
    do{
        cout<<"[1] Generar la cola\n[2] Mostrar la cola\n[3] Generar nuevo archivo\n[4]Salir"<<endl;
        cin>>op;
        cout<<endl;
        if (op<1 || op>4){
            cout<<"opcion invalida"<<endl;
        }
        else{
            switch(op){
                case 1:
                    prueba.generar();
                    cout<<endl;
                    break;
                case 2:
                    prueba.mostrar();
                    cout<<endl;
                    break;
                case 3:
                    prueba.hacer_archivo();
                    cout<<endl;
                    break;
            }
        }
    }while(op!=4);
    return 0;

}
