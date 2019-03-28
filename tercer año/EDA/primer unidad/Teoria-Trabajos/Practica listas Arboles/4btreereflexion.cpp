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
    int numero;
    int niveles;
    bool bandera_predecesor;
public:
    Node *root;
    Arbol();
    void Add(int);
    void Help_Add(Node*&,int,int,Node *&);;
    void help_Generador();
    void help_Generador2();
    void GenerarDot(Node*,ofstream&);
    void help_generarVector();
    void generarVector(Node*,vector<Node*>&, Node*&);
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

void Arbol::help_Generador2(){
    ofstream salida;
    salida.open("arbol_binario2.dot");
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
void Help_Add2(Node *&raiz, int valor,Node*& padre){
    if(raiz==NULL){
        Node *temp=new Node();
        temp->value=valor;
        temp->padre=padre;
        raiz = temp;
    }
    else{
        if(valor<raiz->value){
            Help_Add2(raiz->der,valor,raiz);
        }
        else{
            Help_Add2(raiz->izq,valor,raiz);
        }
    }
}
void Add2(int valor,Node*&raiz){
    Help_Add2(raiz,valor,raiz);
}

void Arbol::help_generarVector(){
    Arbol tree2;
    vector <Node*> aux;
    Node * v=tree2.root;
    aux.push_back(root);
    generarVector(root,aux,v);
    tree2.root=v;
    //cout<<"hola peero "<<endl;
    cout<<v->value<<endl;
    tree2.help_Generador2();
}

void Arbol::generarVector(Node* aux,vector<Node*> &v,Node *&raiz2){
    if (v[0]==NULL && v.size()>1){
        v.erase(v.begin(),v.begin()+1);
        generarVector(v[0],v,raiz2); 
    }
    if (aux==NULL)
        return;
    cout<<aux->value<<"-> ";
    Add2(aux->value,raiz2);
    v.erase(v.begin(),v.begin()+1);
    //if (aux->child[0])
        v.push_back(aux->izq);
    //if (aux->child[1])
        v.push_back(aux->der);
    generarVector(v[0],v,raiz2);
}

void ver(vector<int> a){
    for(int i=0;i<a.size();i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
}
int main(){
    srand (time(NULL));
    Arbol tree;
    Arbol tree2;
    int valor;
    for (int i=0;i<10;i++){
        valor = rand ()% 50 + 0;
        tree.Add(valor);
    }
    vector<int> aux;
    //tree.display();
    tree.help_Generador();
    tree.help_generarVector();
    //tree2.help_Generador2();
    //ver(aux);
    //tree2.reflexion(tree);
    return 0;
}   