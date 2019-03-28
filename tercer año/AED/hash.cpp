#include <iostream>

using namespace std;
///key -> string
///hash= suma de letras %TAM
///value=int
class LinkedHashEntry {
private:
    string key;
    int value;
    LinkedHashEntry *next;
public:
    LinkedHashEntry(string key, int value) {
        this->key = key;
        this->value = value;
        this->next = NULL;
    }
    string getKey() { return key; }
    int getValue() { return value; }
    LinkedHashEntry *getNext() {  return next;  }
    void setValue(int value) {  this->value = value;  }
    void setNext(LinkedHashEntry *next) {  this->next = next; }
};

const int TABLE_SIZE = 128;

class HashMap{
private:
    LinkedHashEntry **table;
    string alfabeto="abcdefghijklmnopqrstuvwxyz";
public:
    HashMap() {
        table = new LinkedHashEntry*[TABLE_SIZE];
        for (int i = 0; i<TABLE_SIZE; i++)
            table[i] = NULL;
    }
    int get(string key) {
        int hash = (sumaletras(key) % TABLE_SIZE);
        if (table[hash] == NULL)
            return -1;
        else {
            LinkedHashEntry *entry = table[hash];
                while (entry != NULL && entry->getKey() != key)
                    entry = entry->getNext();
                    if (entry == NULL)
                        return -1;
                    else
                        return entry->getValue();
        }
    }
    int sumaletras(string palabra){
        int aux=0;
        for (int i=0;i<palabra.length();i++){
            for (int j=0;j<alfabeto.length();j++){
                if (palabra[i]==alfabeto[j])
                    aux+=(j+1);
            }
        }
        return aux;
    }
    int sumaletrasv2(string palabra){
        int aux=0;
        for (int i=0;i<palabra.length();i++){
            aux+=palabra[i];
        }
        return aux;
    }

    void put(string key, int value) {
        int hash=(sumaletras(key)%TABLE_SIZE);
        if (table[hash]==NULL)
            table[hash]=new LinkedHashEntry(key,value);
        else{
            LinkedHashEntry *aux=table[hash];
            while(aux->getNext()!=NULL){
                aux=aux->getNext();
            }
            aux->setNext(new LinkedHashEntry(key,value));
        }


    }
    void remove(string key) {
        int hash=(sumaletras(key)%TABLE_SIZE);
        LinkedHashEntry *current=table[hash];
        LinkedHashEntry *trash;
        while (current!=NULL){
            if (current->getKey()==key){
                cout<<"hola"<<endl;
                trash=current->getNext();
                current->setNext(current->getNext()->getNext());
                delete trash;
            }
            current=current->getNext();

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
    //prueba.put("zaaa",54);
    prueba.put("zaaa",5);
    cout<<prueba.get("zaaa")<<endl;
    prueba.remove("zaaa");
    //cout<<prueba.get("aaaz");

    return 0;
}
