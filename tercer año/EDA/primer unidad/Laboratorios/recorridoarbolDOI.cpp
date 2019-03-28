      //implementar un arbol y mostrar sus recorridos
#include <iostream>
#include <vector>
 
using namespace std;

struct Node{
    int value;
    Node *hijo;
    Node *hermano_der;
    Node *padre;
    Node(int value){
        this->value=value;
        this->hijo=hermano_der=NULL;
    }
    Node (int value, Node *padre){
        this->value=value;
        this->padre=padre;
        this->hijo=hermano_der=NULL;
    }
};


class Arbol
{
private:
    Node *root;
    vector<Node*> lista;
public:
    Arbol();
    void Add(int,int,char);
    void prefija(Node*);
    void infija(Node*);
    void posfija(Node*);
    void help_display();
    void Help_Add(Node*&,int,int,char);
    Node* buscar_padre(int);
    void cola();

};

Arbol::Arbol(){
    root=NULL;
}
void Arbol::cola(){
    for (int i =0;i<lista.size();i++){
        cout<<lista[i]->value<<" ";
    }
    cout<<endl;
}

void Arbol::help_display(){
    cout<<"Prefija:"<<endl;
    prefija(root);
    cout<<"\nInfija:"<<endl;
    infija(root);
    cout<<"\nPosfija"<<endl;
    posfija(root);
    cout<<endl;
}

void Arbol::prefija(Node *raiz){
    if (raiz==NULL)
        return;
    else{
        cout<<raiz->value<<" ";
        prefija(raiz->hijo);
        prefija(raiz->hermano_der);    
    }
}

void Arbol::infija(Node *raiz){
    if (raiz==NULL)
        return;
    else{
        infija(raiz->hijo);
        cout<<raiz->value<<" ";
        infija(raiz->hermano_der);    
    }
}

void Arbol::posfija(Node *raiz){
    if (raiz==NULL)
        return;
    else{
        posfija(raiz->hijo);
        posfija(raiz->hermano_der);
        cout<<raiz->value<<" ";    
    }
}

Node * Arbol::buscar_padre(int valor){
    for (int i=0;i<lista.size();i++){
        if (lista[i]->value==valor)
            return lista[i];
    }
}

void Arbol::Add(int valor, int padre, char opcion){
    Help_Add(root,valor,padre,opcion); 
}

void Arbol::Help_Add(Node *&raiz, int valor,int padre, char opcion){
    if (raiz==NULL){
        raiz=new Node(valor);
        raiz->padre=raiz;
        lista.push_back(raiz);
    }
    if (opcion=='c'){
        Node *aux=buscar_padre(padre);
        Node *nuevo=new Node(valor,aux);
        aux->hijo=nuevo;
        lista.push_back(nuevo);
    }
    if (opcion=='b'){
        Node *aux=buscar_padre(padre);
        Node *aux_der=aux->hijo;
        while(aux_der->hermano_der!=NULL){
            aux_der=aux_der->hermano_der;
        }
        Node *nuevo=new Node(valor,aux);
        aux_der->hermano_der=nuevo;
        lista.push_back(nuevo);
    }
}

int main(){
    Arbol tree;
    tree.Add(1,1,'r');
    tree.Add(2,1,'c');
    tree.Add(3,1,'b');
    tree.Add(4,1,'b');
    tree.Add(5,3,'c');
    tree.Add(6,3,'b');
    tree.Add(7,3,'b');
    tree.Add(10,2,'c');
    tree.help_display();
    //tree.cola();

    return 0;
}
