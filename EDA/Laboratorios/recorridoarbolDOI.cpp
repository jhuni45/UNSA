//implementar un arbol y mostrar sus recorridos

struct Node{
    char value;
    int nivel;
    Node *hijo;
    Node *hermano_izq;
    Node *hermano_der;
    Node *padre;
    Node(char value){
        this->hijo=hermano_der=hermano_izq=NULL;
    }
    Node(char value, Node *hijo){
        this->hijo=hijo;
    }
    Node (char value, Node *padre, Node *hermano_izq, Node *hermano_der){
        this->hermano_izq=hermano_izq;
        this->hermano_der=hermano_der;
        this->padre=padre;
    }
};


class Arbol
{
private:
    Node *root;
    int level;
public:
    Arbol();
    void Add(char);
    void display();
    void add_hermano();
    void add_hijo();
    void Help_display_Pos(Node*);
    void Help_display_Pre(Node*);
    void Help_display_In(Node*);
    void Help_Add(Node*&,char,Node *&);
};

Arbol::Arbol(){
    root=NULL;
    numero=0;
}

void Arbol::Add(char valor, char aux){
    Help_Add(root,valor,aux);
}

Node * buscar (char valor, Node *root){
    if (raiz==NULL)
        return raiz;
    if (raiz->value==valor)
        return
    buscar(valor, raiz->hijo);
    buscar(valor, raiz->hermano_der);
    
}
void Arbol::Help_Add(Node *&raiz, char valor,char opcion, char aux){
    if (raiz==NULL){
        raiz=new Node(valor);
        raiz->padre=raiz;
    }
    if (opcion=='s'){
        Node *aux=buscar(valor,raiz);
        
    }
    if (aux=='h')
}

