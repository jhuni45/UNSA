//implementar el arbol binario y mostrarlo graficamente (DOI)

#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <fstream>
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
    int level;
    bool bandera_predecesor;
public:
    Arbol();
    void Add(int);
    void display();
    void Help_display_Pos(Node*);
    void Help_display_Pre(Node*);
    void Help_display_In(Node*);
    void Help_Add(Node*&,int,int,Node *&);
    void eliminar(int);
    void Help_eliminar(Node*&,int);
    void help_Generador();
    void GenerarDot(Node*,ofstream&);
    Node* predecesor(Node*);
    Node* sucesor(Node*);
    

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
		//cout<<"hola"<<endl;
		if (raiz->izq!=NULL){
			//cout<<"qu onda"<<endl;
			salida<<raiz->value<<" -> "<<raiz->izq->value<<endl;
				
		}
		if (raiz->der!=NULL){
			//cout<<"qu onda2222"<<endl;
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
        	level=nivel-2;
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

void Arbol::display(){	
	int op;
    cout<<"Mostrar en:\n[1] Pre-orden\n[2] Post-orden\n[3] In-orden"<<endl;
    cin>>op;
    if (op>3 || op<1)
    	cout<<"no es una ocion valida"<<endl;
    else if (op==1)
    	Help_display_Pre(root);
    else if (op==2)
    	Help_display_Pos(root);
    else if (op==3)
    	Help_display_In(root);

}

void Arbol::Help_display_Pre(Node *raiz){
    if(raiz==NULL) {
        return;
    }
    else{
        cout<<raiz->value<<" ";
        Help_display_Pre(raiz->izq);
        Help_display_Pre(raiz->der);
    }
}
void Arbol::Help_display_Pos(Node *raiz){
    if(raiz==NULL) {
        return;
    }
    else{
        Help_display_Pos(raiz->izq);
        Help_display_Pos(raiz->der);
        cout<<raiz->value<<" ";
    }
}
void Arbol::Help_display_In(Node *raiz){
    if(raiz==NULL) {
        return;
    }
    else{
        
        Help_display_In(raiz->izq);
        cout<<raiz->value<<" ";
        Help_display_In(raiz->der);
        
    }
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

	return 0;
}