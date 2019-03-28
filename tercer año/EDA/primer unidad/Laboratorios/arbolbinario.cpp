//implementar el arbol binario y mostrarlo graficamente (DOI)

#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <stack>
using namespace std;

struct Node{
    int value;
    int nivel;
    Node *izq;
    Node *der;
    Node *padre;
};

class Arbol
{
private:
    Node *root;
    int numero;
    int niveles;
    bool bandera_predecesor;
public:
    Arbol();
    void Add(int);
    void Help_Add(Node*&,int,int,Node *&);
    void help_Generador();
    void GenerarDot(Node*,ofstream&);
    void hel_inorden();
    void inorden(Node*);
};

Arbol::Arbol(){
    root=NULL;
    numero=0;
    bandera_predecesor=false;
}

void Arbol::Add(int valor){
    Help_Add(root,valor,0,root);
}

void Arbol::help_Generador(){
	ofstream salida;
	salida.open("arbol_binario.dot");
	salida<<"digraph G {"<<endl;
	GenerarDot(root,salida);
	salida<<"}";
	salida.close();
}
void Arbol::GenerarDot(Node* raiz, ofstream &salida){
	if (raiz==NULL)
		return;
	else{
		if (raiz->izq!=NULL){
			salida<<raiz->value<<" -> "<<raiz->izq->value<<endl;
				
		}
		if (raiz->der!=NULL){
			salida<<raiz->value<<" -> "<<raiz->der->value<<endl;
		}
		GenerarDot(raiz->izq,salida);
		GenerarDot(raiz->der,salida);
	}
}

void Arbol::Help_Add(Node *&raiz, int valor, int nivel,Node*& padre){
    if(raiz==NULL){
        Node *temp=new Node();
        temp->value=valor;
        temp->nivel=nivel;
        temp->padre=padre;
        raiz = temp;
        if (niveles<nivel){
        	niveles=nivel;
        }
    }
    else{
        if(valor>raiz->value){
            Help_Add(raiz->der,valor,raiz->nivel+1,raiz);
        }
        else{
            Help_Add(raiz->izq,valor,raiz->nivel+1,raiz);
        }
    }

}
void Arbol::hel_inorden(){
	inorden(root);
}
void Arbol::inorden(Node* r){
	stack<Node*> pila;
	Node *aux = r;
    do{
        if(!pila.empty() && aux == NULL){
            cout<<pila.top()->value<<" ";
        }
        if(aux != NULL){
            pila.push(aux);
            aux = aux->izq;
        }
        else if(!pila.empty()){
            aux = pila.top();
            pila.pop();
            aux = aux->der;
        }
    }while(!pila.empty() || aux != NULL);
}

int main(){
    srand (time(NULL));
    Arbol tree;
    int valor;
    for (int i=0;i<10;i++){
        valor = rand ()% 100 + 0;
        tree.Add(valor);
    }
    //tree.display();
    tree.help_Generador();
    tree.hel_inorden();

	return 0;
}	
