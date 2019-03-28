#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

class LinkedHashEntry {
private:
    string key;
    string descripcion;
    LinkedHashEntry *next;
public:
    LinkedHashEntry(string key, string value) {
        this->key = key;
        this->descripcion = value;
        this->next = NULL;
    }
    string getKey() { return key; }
    string getValue() { return descripcion; }
    LinkedHashEntry *getNext() {  return next;  }
    void setValue(string descripcion) {  this->descripcion = descripcion;  }
    void setNext(LinkedHashEntry *next) {  this->next = next; }
};

const int TABLE_SIZE = 5;

class HashMap{
private:
    LinkedHashEntry **table;
public:
    HashMap() {
        table = new LinkedHashEntry*[TABLE_SIZE];
        for (int i = 0; i<TABLE_SIZE; i++)
            table[i] = NULL;
    }

    void buscar(string key) {
        int hash = (sumaletrasv2(key)% TABLE_SIZE);
        if (table[hash] == NULL){
            cout<<"el espacio no existe"<<endl;
            return;
        }
        else {
            LinkedHashEntry *entry = table[hash];
                while (entry != NULL && entry->getKey() != key)
                    entry = entry->getNext();
                    if (entry == NULL){
                        cout<<"no se encontro la palabra"<<endl;
                        return;
                    }
                    else{
                        cout<<entry->getKey()<<": "<<entry->getValue()<<endl<<endl;
                    }
        }
    }
    

    int sumaletrasv2(string palabra){
        int aux=0;
        for (int i=0;i<palabra.length();i++){
            aux+=palabra[i];
        }
        return aux;
    }

    void put(string key, string value) {
        LinkedHashEntry *nuevo=new LinkedHashEntry(key, value);
        
        int hash=(sumaletrasv2(key)%TABLE_SIZE);
        if (table[hash]==NULL)
            table[hash]=nuevo;
        else{
            LinkedHashEntry *aux=table[hash];
            nuevo->setNext(aux);
            table[hash]=nuevo;
        }

    }
    void remove(string key) {
        int hash=(sumaletrasv2(key)%TABLE_SIZE);
        LinkedHashEntry *current=table[hash];
        LinkedHashEntry *trash;
        if(current!=NULL){
            if(current->getKey()==key){
                trash=current;
                current=current->getNext();
                delete trash;
            }
            else{
                trash=current->getNext();
                LinkedHashEntry * aux=current;
                while(trash!=NULL && trash->getKey()!=key){
                    aux=trash;
                    trash=trash->getNext();
                }
                if(trash!=NULL){
                    aux->setNext(trash->getNext());
                    delete trash;
                }
                else{
                    cout<<"no se encontro la palabra"<<endl;
                }
            }
        }
        else{
            cout<<"espacio vacio"<<endl;
        }
    }

    void mostrar(){
        for (int i=0;i<TABLE_SIZE;i++){
            LinkedHashEntry *aux=table[i];
            cout<<i<<" ";
            if(aux==NULL)
                cout<<"NULL";
            while(aux!=NULL){
                cout<<aux->getKey()<<" -> ";
                aux=aux->getNext();
            }
            cout<<endl;
        }
    }
    ~HashMap() {
        for (int i = 0; i < TABLE_SIZE; i++)
            if (table[i] != NULL) {
                LinkedHashEntry *prevEntry = NULL;
                LinkedHashEntry *entry = table[i];
                while (entry != NULL) {
                    prevEntry = entry;
                    entry = entry->getNext();
                    delete prevEntry;
                }
            }
            delete[] table;
    }
};

int main(){
    HashMap prueba;
    int op;
    string clave="", descripcion="",aux="";

    do{
        cout<<"DICCIONARIO\n[1] Ingresar\n[2] Mostrar\n[3] Eliminar\n[4] Buscar\n[5]Salir"<<endl;
        cin>>op;
        cout<<endl;
        if (op<1 || op>5){
            cout<<"opcion invalida"<<endl;
        }
        else{
            switch(op){
                case 1:
                    cout<<"Ingrese palabra nueva: ";
                    cin>>clave;
                    cout<<"Ingrese su descripcion: "<<endl;
                    cin>>descripcion;
                    prueba.put(clave,descripcion);
                    cout<<endl;
                    break;
                case 2:
                    prueba.mostrar();
                    cout<<endl;
                    break;
                case 3:
                    cout<<"Ingrese la palabra a eliminar: ";
                    cin>>clave;
                    prueba.remove(clave);
                    cout<<endl;
                    break;
                case 4:
                    cout<<"Ingrese la palabra a buscar: ";
                    cin>>clave;
                    prueba.buscar(clave);
                    cout<<endl;
                    break;
            }
        }
    }while(op!=5);
      
    return 0;

}
