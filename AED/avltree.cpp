/// AVL TREE
#include <iostream>
#include <vector>

using namespace std;

struct Node{
    int value;
    int nivel;
    Node *izq;
    Node *der;
    Node *padre;
    int altura_derecha;
    int altura_izquierda;
    int diferencia;
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
    void Esta(int);
    bool Help_Esta(Node*&,int);
    int Nro_hojas();
    void Help_Nro_hojas(Node*&);
    void estricto();
    void estrictobinario(Node*);
    bool tienehijos(Node*);
    void completofuncion(Node*,vector<Node*>&);
    void mostrarraiz();
    void completo();
    void eliminar(int);
    void Help_eliminar(Node*&,int);
    Node* predecesor(Node*);
    Node* sucesor(Node*);
    void definir_altura(Node *&);
    int altura(Node *);
    void AVL(Node *&);


};

Arbol::Arbol(){
    root=NULL;
    numero=0;
    bandera_predecesor=false;
}

void Arbol::Add(int valor){
    Help_Add(root,valor,0,root);
    definir_altura(root);
    cout<<"arrubab avl"<<endl;
    AVL(root);
}

void Arbol::Help_Add(Node *&raiz, int valor, int nivel,Node*& padre){
    cout<<"hola"<<valor<<endl;
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
        //cout<<"("<<raiz->nivel<<") "<<raiz->value<<" <->";
        cout<<"("<<raiz->altura_izquierda<<") "<<raiz->value<<" ("<<raiz->altura_derecha<<") "<<" <->";
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
        cout<<"("<<raiz->nivel<<") "<<raiz->value<<" <->";
    }
}
void Arbol::Help_display_In(Node *raiz){
    if(raiz==NULL) {
        return;
    }
    else{

        Help_display_In(raiz->izq);
        cout<<"("<<raiz->nivel<<") "<<raiz->value<<" <->";
        Help_display_In(raiz->der);

    }
}

void Arbol::Esta(int valor){
    cout<<Help_Esta(root,valor)<<endl;
}

bool Arbol::Help_Esta(Node *&raiz, int valor){
    if(raiz==NULL){
        return false;
    }
    else{
        if(valor==raiz->value){
            return true;
        }
        if(valor<raiz->value){
            Help_Esta(raiz->izq,valor);
        }
        else{
            Help_Esta(raiz->der,valor);
        }
    }
}

int Arbol::Nro_hojas(){
    Help_Nro_hojas(root);
    return numero-1;
}

void Arbol::Help_Nro_hojas(Node *&raiz){
    if(raiz==NULL){
        return;
    }
    else
    {
        Help_Nro_hojas(raiz->izq);
        numero++;
        Help_Nro_hojas(raiz->der);
    }
}

void Arbol::mostrarraiz(){
    cout<<"la raiz del arbol es "<<root->value;
}
bool Arbol::tienehijos(Node *aux){
    if (aux!=NULL)
        return true;
    return false;
}
void Arbol::estricto(){
    if (root==NULL){
        return;
    }
    estrictobinario(root);
}
void Arbol::estrictobinario(Node * raiz){
    if (raiz==NULL)
        return;
    bool aux=true;
    if (tienehijos(raiz->izq)== tienehijos(raiz->der)){
        aux=true;
    }
    else{
        cout<<endl<<"falla en: "<<raiz->value<<endl;
    }
    estrictobinario(raiz->izq);
    estrictobinario(raiz->der);
}
void Arbol::completo(){
	niveles=0;
	bool flag=true;
    if (root==NULL){
        return;
    }
    vector<Node*> lista;
    if (niveles==2){
    	cout<<"es completo"<<endl;
    	return;
    }
    else{
    	completofuncion(root,lista);
    	cout<<"el tamano:"<<lista.size()<<endl;
    	for (int i =0;i<lista.size();i++){
    	if (( tienehijos(lista[i]->izq)==false && tienehijos(lista[i]->der)==true )|| (tienehijos(lista[i]->izq)==true && tienehijos(lista[i]->der)==false) ||(tienehijos(lista[i]->izq)==false && tienehijos(lista[i]->der)==false) ){
    		flag=false;
    		cout<<"falla en :"<<lista[i]->value<<endl;
    	}
    }
    if (flag==true)
    	cout<<"el arbol es completo"<<endl;
    }
}
void Arbol::completofuncion(Node *raiz, vector<Node*> &lista){
	if (raiz==NULL)
		return;
	if (raiz->nivel>level){
		return;
	}
	if (raiz->nivel<=level){
		lista.push_back(raiz);
	}
	completofuncion(raiz->izq,lista);
	completofuncion(raiz->der,lista);
}

void Arbol::eliminar(int valor){
	Help_eliminar(root,valor);
    definir_altura(root);
    AVL(root);
}
Node * Arbol::predecesor(Node* raiz){
	Node *pred=raiz;
	while(pred->der!=NULL){
		pred=pred->der;
	}
	return pred;
}

Node * Arbol::sucesor(Node* raiz){
	Node *suc=raiz;
	while(suc->izq!=NULL){
		suc=suc->izq;
	}
	return suc;
}

void Arbol::Help_eliminar(Node *&raiz,int valor){
	cout<<"valores : "<<raiz->value<<" - "<<valor<<endl;
	if (raiz==NULL){
		cout<<"el arbol esta vacio"<<endl;
		return;
	}
	if (valor>raiz->value){
		cout<<"el valor es mayor a la raiz:"<<raiz->value<<">"<<valor<<endl;
		Help_eliminar(raiz->der,valor);
	}
	if (valor<raiz->value){
		cout<<"el valor es menor a la raiz"<<raiz->value<<"<"<<valor<<endl;
		Help_eliminar(raiz->izq,valor);
	}
	if (raiz->value==valor && tienehijos(raiz->izq)==false && tienehijos(raiz->der)==false){
		cout<<"ingreso sin hijos"<<endl;
		Node* temp=raiz->padre;
		if (temp->value>valor)
            temp->izq=NULL;
        else
            temp->der=NULL;
        /*if (valor==temp->izq->value &&temp->izq!=NULL ){
			temp->izq=NULL;
		}
		if(valor==temp->der->value && temp->der!=NULL)
			temp->der=NULL;
		//delete raiz;
        */
		return;

	}
	/// 1 solo hijo
	if (raiz->value==valor && ((tienehijos(raiz->izq)==false && tienehijos(raiz->der)==true)||(tienehijos(raiz->izq)==true && tienehijos(raiz->der)==false) ) ){
		cout<<"ingresa al 1 hijo"<<endl;
		if (tienehijos(raiz->der)==true){
			Node * temp=raiz;
			temp=raiz->padre;
			if (valor>temp->value){
				delete raiz;
				temp->der=raiz->der;
			}
			else{
				delete raiz;
				temp->izq=raiz->der;
			}
			return;
		}
		if (tienehijos(raiz->izq)==true){
			Node * temp=raiz;
			temp=raiz->padre;
			if (valor>temp->value){
				delete raiz;
				temp->der=raiz->izq;
			}
			else{
				delete raiz;
				temp->izq=raiz->izq;
			}
			return;
		}
	}
	/// 2 hijos
	if (raiz->value==valor && tienehijos(raiz->izq)==true &&tienehijos(raiz->der)==true){
		cout<<"ingresa a dos hijos"<<endl;
		if (bandera_predecesor==false){
			Node* suc=sucesor(raiz->der);
			int aux=raiz->value;
			raiz->value=suc->value;
			suc->value=aux;
			Help_eliminar(suc,valor);
		}
		else if (bandera_predecesor==true){
			Node* pred=predecesor(raiz->izq);
			int aux=raiz->value;
			raiz->value=pred->value;
			pred->value=aux;

			Help_eliminar(pred,valor);
		}
	}
	//cout<<"no se encontro el valor"<<endl;
}

int Arbol::altura(Node *aux){
    if (!aux)
        return 0;
    if (aux->der==NULL && aux->izq==NULL)
        return 1;
    int a=(altura(aux->der));
    int b=(altura(aux->izq));
    if (a>b)
        return 1+a;
    else
        return 1+b;
}

void  Arbol::definir_altura(Node *&raiz){
    if (raiz==NULL){
        //cout<<"El arbol esta vacio"<<endl;
        return;
    }
    raiz->altura_derecha=altura(raiz->der);
    raiz->altura_izquierda=altura(raiz->izq);
    raiz->diferencia=raiz->altura_derecha - raiz->altura_izquierda;
    definir_altura(raiz->der);
    definir_altura(raiz->izq);
}
void Arbol::AVL(Node *& raiz){
    if (raiz==NULL)
        return ;
    if (raiz->diferencia==2){
        cout<<"dentro del 222"<<endl;
        Node *aux=raiz;
        //bien
        if (raiz->der->diferencia==1){
            cout<<"dentro del 111"<<endl;
            raiz=raiz->der;
            aux->der->izq=aux;
            aux->der=NULL;
            aux->izq=NULL;
            definir_altura(raiz);
            return;
        }
        //probar
        if (raiz->der->diferencia==0){
            cout<<"dentro del 000"<<endl;
            Node * cambiar=raiz->der->izq;
            raiz=raiz->der;
            aux->der->izq=aux;
            aux->der=cambiar;
            aux->izq=NULL;
            definir_altura(raiz);
            return;
        }
        //bien
        if (raiz->der->diferencia==-1){
            cout<<"dentro del ---111"<<endl;
            Node *cambiar=aux;
            raiz=aux->der->izq;
            aux->der->izq=NULL;
            raiz->der=aux->der;
            cambiar->der=NULL;
            raiz->izq=cambiar;
            definir_altura(raiz);
            return;
        }
    }
    if (raiz->diferencia==-2){
        cout<<"dentro del 222"<<endl;
        Node *aux=raiz;
        if (raiz->izq->diferencia==1){
            cout<<"dentro del ---111"<<endl;
            Node *cambiar=aux;
            raiz=aux->izq->der;
            aux->izq->der=NULL;
            raiz->izq=aux->izq;
            cambiar->izq=NULL;
            raiz->der=cambiar;
            definir_altura(raiz);
            return;
        }
        if (raiz->izq->diferencia==0){
            cout<<"dentro del 00000"<<endl;
            Node * cambiar=raiz->izq->der;
            raiz=raiz->izq;
            aux->izq->der=aux;
            aux->izq=cambiar;
            aux->der=NULL;
            definir_altura(raiz);
            return;
        }

        if (raiz->izq->diferencia==-1){
            cout<<"dentro del 111"<<endl;
            raiz=raiz->izq;
            aux->izq->der=aux;
            aux->der=NULL;
            aux->izq=NULL;
            definir_altura(raiz);
            return;
        }



    }
    if (raiz->diferencia!=2 || raiz->diferencia!=-2){
        AVL(raiz->der);
        AVL(raiz->izq);
    }
    else{
        cout<<"el arbol esta en forma AVL"<<endl;
    }

}
int main(){
    Arbol Tree;
    int op,valor;
    do{
        cout<<"Menu de opciones\n[1] insertar\n[2] mostrar pre-orden\n[3] mostrar informacion\n[4] Eliminar\n[5] salir"<<endl;
        cin>>op;
        cout<<endl;
        if (op<1 || op>5){
            cout<<"opcion invalida"<<endl;
        }
        else{
            switch(op){
                case 1:
                    cout<<"Ingrese el valor"<<endl;
                    cin>>valor;
                    Tree.Add(valor);
                    /*Tree.Add(55);
                    Tree.Add(56);
                    Tree.Add(6);
                    Tree.Add(21);
                    //cout<<"arbol hasta ahora "<<endl;
                    //Tree.display();
                    //Tree.eliminar(6);
                    //cout<<"eliminamos el 6"<<endl;
                    //Tree.display();
                    Tree.Add(28);
                    Tree.Add(47);
                    Tree.Add(63);
                    Tree.Add(31);
                    Tree.Add(44);
                    Tree.Add(82);
                    Tree.Add(90);
                    Tree.Add(27);
                    Tree.Add(64);
                    Tree.Add(38);
                    Tree.Add(8);
                    Tree.Add(2);
                    //cout<<"arbol hasta ahora "<<endl;
                    //Tree.display();
                    //Tree.eliminar(90);
                    //cout<<"eliminamos el 90"<<endl;
                    //Tree.display();
                    Tree.Add(17);
                    Tree.Add(29);
                    Tree.Add(3);
                    Tree.Add(33);
                    Tree.Add(68);
                    Tree.Add(30);
                    //cout<<"arbol hasta ahora "<<endl;
                    //Tree.display();
                    Tree.eliminar(21);
                    cout<<"eliminamosel 21"<<endl;
                    //Tree.display();
                    Tree.eliminar(56);
                    Tree.eliminar(31);
                    Tree.eliminar(3);
                    */
                    cout<<endl;
                    break;
                case 2:
                    Tree.display();
                    cout<<endl;
                    break;
                case 3:
                    Tree.mostrarraiz();
                    cout<<"********es estricto?"<<endl;
                    Tree.estricto();
                    cout<<"********es completo?"<<endl;
                    Tree.completo();
                    cout<<endl;
                    break;
                case 4:
                	cout<<"Ingrese el valor a eliminar"<<endl;
                	cin>>valor;
                	Tree.eliminar(valor);
                	cout<<endl;
                	break;
            }
        }
    }while(op!=5);
    return 0;
}
