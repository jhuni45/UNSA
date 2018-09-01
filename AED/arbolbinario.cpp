#include <iostream>
#include <vector>

///calculuas altura
///imprimir por niveles
///template <T>
///destructor

using namespace std;

template <class T>
struct Nodo{
    Nodo * child[2];
    T valor;
    Nodo(T valor){
        this->child[0]=child[1]=0;
        this->valor=valor;
    }
};

template <class T>
class bsl{
private:
    Nodo<T> * root;
public:
    bsl(){
        root=NULL;
    }
    void destructor(){
    	eliminar(root);
    }
    bool find(T);
	bool find(Nodo<T> **&n,T);
	bool insertar(T);
	int altura();
	int altura(Nodo<T> *);
	void print();
	void print(Nodo<T> *,vector<Nodo<T> *>);
	void vectorcito(vector<Nodo<T>*>);
	void eliminar(Nodo<T>*);
};

template <class T>
bool bsl<T>::find(T valor){
	Nodo<T> **n;
    return find(n,valor);
}

template <class T> 
bool bsl<T>::find(Nodo<T> **&n,T valor){
    n=&root;
    while((*n)){
       	if((*n)->valor==valor)
    		return true;
        n=&(*n)->child[(*n)->valor<valor];
    }
    return false;
}

template<class T>
bool bsl<T>::insertar(T valor){
    Nodo<T> **n;
    if (find(n,valor))
        return false;
    *n=new Nodo<T>(valor);
    return true;
}

template <class T>
int bsl<T>::altura(){
    return altura(root);
}

template <class T>
int bsl<T>::altura(Nodo<T> *aux){
    if (!aux)
        return 0;
    if (aux->child[0]==NULL && aux->child[1]==NULL)
        return 1;
    int a=(altura(aux->child[0]));
    int b=(altura(aux->child[1]));
    if (a>b)
        return 1+a;
    else
        return 1+b;
}

template<class T>
void bsl<T>::print(){
	vector<Nodo<T> *> v;
	v.push_back(root);
	print(root,v);
	cout<<endl;
}
template<class T>
void bsl<T>::vectorcito(vector<Nodo<T>*> v){
	for (int i=0;i<v.size();i++){
		cout<<v[i]->valor<<" "; 
	}
}
template<class T>
void bsl<T>::print(Nodo <T> * aux,vector<Nodo<T> *> v){
	if (v[0]==NULL && v.size()>1){
		v.erase(v.begin(),v.begin()+1);
		print(v[0],v); 
	}
	if (aux==NULL)
		return;
	cout<<aux->valor<<"-> ";
	v.erase(v.begin(),v.begin()+1);
	//if (aux->child[0])
		v.push_back(aux->child[0]);
	//if (aux->child[1])
		v.push_back(aux->child[1]);
	print(v[0],v);
}
template<class T>
void bsl<T>::eliminar(Nodo<T>* aux){
	if (aux==NULL)
		cout<<"vacio"<<endl;
	if (aux){
		cout<<"entre "<<endl;
		eliminar(aux->child[0]);
		eliminar(aux->child[1]);
		delete(aux);
	}
}
int main(){
    bsl<int> prueba;
    //prueba.insertar(5);
    //prueba.insertar(2);
    //prueba.insertar(8);
    //prueba.insertar(1);
    //prueba.insertar(3);
    //prueba.insertar(7);
    //prueba.insertar(1);
    cout<<"altura: "<<prueba.altura()<<endl;
    prueba.print();
    //prueba.destructor();
    //prueba.print();
    return 0;
}
