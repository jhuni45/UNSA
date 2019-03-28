/*
Desarrollar un reconocedor ortografico en tiempo real haciendo uso de una tabla hash
1. mostrar un documento de texto plano para formar el diccionario de palabras correctamente escritas
2. en base al diccionario anterior detectar las palabras mal escritas en tiempo real
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

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

const int TABLE_SIZE = 321;

class HashMap{
private:
    LinkedHashEntry **table;
public:
    vector<string> posiblesP;
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
        int acum=1;
        for (int i=0;i<palabra.length();i++){
            aux+=palabra[i];
        }
        return aux;
    }

    void put(string key) {
        int hash=(sumaletras(key)%TABLE_SIZE);
        if (table[hash]==NULL)
            table[hash]=new LinkedHashEntry(key,sumaletras(key));
        else{
            LinkedHashEntry *aux=table[hash];
            while(aux->getNext()!=NULL){
                aux=aux->getNext();
            }
            aux->setNext(new LinkedHashEntry(key,sumaletras(key)));
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
    bool buscar(string key) {
        int hash = (sumaletras(key)% TABLE_SIZE);
        if (table[hash] == NULL){
            cout<<"el espacio no existe"<<endl;
            return false;
        }
        else {
            LinkedHashEntry *entry = table[hash];
                while (entry != NULL && entry->getKey() != key)
                    entry = entry->getNext();
                    if (entry == NULL){
                        cout<<"no se encontro la palabra"<<endl;
                        return false;
                    }
                    else{
                    	cout<<"Palabra Correcta\n"<<endl;
                        //cout<<entry->getKey()<<": "<<entry->getValue()<<endl<<endl;
                        return true;
                    }
        }
    }
    void hallarpalabra(int inicio){
    	int final =inicio+20;
    	if (inicio-20<0)
    		inicio=0;
    	if (inicio+20>TABLE_SIZE)
    		final=TABLE_SIZE;
        for (int i=inicio-20;i<final;i++){
            LinkedHashEntry *aux=table[i];
            //cout<<i<<" ";
            //if(aux==NULL)
            //    cout<<"NULL";
            while(aux!=NULL){
                //cout<<aux->getKey()<<" -> ";
                posiblesP.push_back(aux->getKey());
                aux=aux->getNext();
            }
            //cout<<endl;
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
void mostrarVector(vector<string> a){
	for (int i=0;i<a.size();i++){
		cout<<a[i]<<endl;
	}
	cout<<endl;
}
int levenshtein(const string &s1, const string &s2){
    int N1 = s1.size();
	int N2 = s2.size();
	int i, j;
	vector<int> T(N2+1);
    for ( i = 0; i <= N2; i++ )
    T[i] = i;
 	for ( i = 0; i < N1; i++ ) {
		T[0] = i+1;
		int corner = i;
		for ( j = 0; j < N2; j++ ) {
			int upper = T[j+1];
			if ( s1[i] == s2[j] )
				T[j+1] = corner;
			else
    			T[j+1] = min(T[j], min(upper, corner)) + 1;
			corner = upper;
		}
	}
	return T[N2];
}

vector<string> proceso(vector<string> a, string palabra){
	vector<string> alternativas;
	int menor=levenshtein(a[0],palabra);
	for (int i=0;i<a.size();i++){
		int aux=levenshtein(a[i],palabra);
		if (aux==0){
			alternativas.push_back(a[i]);
			return alternativas;
		}
		if (aux<menor)
			menor=aux;
	}
	for (int i=0;i<a.size();i++){
		int aux=levenshtein(a[i],palabra);
		if (aux==menor)
			alternativas.push_back(a[i]);
	}
	return alternativas;	
}
int main(){
	ifstream entrada;
	int opcion;
	//entrada.open("listado-general.txt");
	entrada.open("wordlist.txt");
	string letra;
    HashMap prueba;
    while(getline(entrada,letra)){
    	string aux;
    	for(int i=0;i<letra.length();i++){
    		if (letra[i]!=' '){	
    			aux+=letra[i];	
    		}
    	}
    	prueba.put(aux);
    }
    prueba.mostrar();
    entrada.close();
    string buscarP;
    do{
    	cout<<"DICCIONARIO\n[1] Ingresar\n[2] Salir"<<endl;
    	cin>>opcion;
    	if (opcion<1 || opcion>2)
    		cout<<"Opcion Invalida"<<endl;
    	else{
    		vector<string>aux;
    		switch(opcion){
                case 1:
                    cout<<"Ingrese palabra nueva: ";
                    cin>>buscarP;
                    bool bandera=prueba.buscar(buscarP);
                    if (bandera==false){
                    	prueba.hallarpalabra(prueba.sumaletras(buscarP)%TABLE_SIZE);
	                    aux=prueba.posiblesP;
	                    //mostrarVector(aux);
	                    cout<<"QUIZA QUISO DECIR . . ."<<endl;
	                    aux=proceso(aux,buscarP);
	                    mostrarVector(aux);	
                    }

                    
                    break;
            }
    	}
    }while(opcion!=2);


    return 0;
}