#include <iostream>
#include <vector>

using namespace std;
struct Arbol{
	char dato;
	Arbol* hijo_der;
    Arbol* hijo_izq;
	Arbol(char dato){
		this->dato=dato;
		this->hijo_der=hijo_izq=NULL;
	}
	Arbol(char dato, Arbol *hijo_der,Arbol *hijo_izq){
		this->dato=dato;
		this->hijo_der=hijo_der;
		this->hijo_izq=hijo_izq;
	}
};

void mostrar(vector<Arbol*> A){
    for (int i=0;i<A.size();i++){
        cout<<A[i]->dato<<"-> ";
    }
    cout<<endl;
}

vector<Arbol*> procesar(string expresion, Arbol *&raiz){
    vector<Arbol*> arbolito;
    cout<<"\n***Comportamiento de la Pila"<<endl;
    for (int i=0;i<expresion.size();i++){
        char caracter=expresion[i];
        if (caracter>='a' && caracter<='z'){
            Arbol *aux=new Arbol(caracter);
            arbolito.push_back(aux);
            mostrar(arbolito);
        }
        
        if (caracter=='+' ||caracter=='-' ||caracter=='*' ||caracter=='/' ){
        	cout<<"Signo hallado ... ["<<caracter<<"]\n"<<endl;
            Arbol* A1=arbolito[arbolito.size()-2];
            Arbol* A2=arbolito[arbolito.size()-1];
            Arbol* padre=new Arbol(caracter,A2,A1);
            //cout<<"sacando valores"<<endl;
            for (int i=0;i<2;i++){
                arbolito.pop_back();
                //mostrar(arbolito);
            }
            cout<<"Pila con raiz de subarbol"<<endl;
            arbolito.push_back(padre);
            raiz=arbolito[0];
            mostrar(arbolito);
        }
    }
    return arbolito;
}
void print(Arbol* padre){
    if (padre==nullptr){
        return;
    }
    print(padre->hijo_izq);
    cout<<padre->dato<<"  ";
    print(padre->hijo_der);
}

int main(){
	Arbol *raiz=nullptr;
    string expresion;
    cout<<"Ingrese expresion"<<endl;
    cin>>expresion;
    vector<Arbol*> A;
    A= procesar(expresion,raiz);
    cout<<"Arbol final"<<endl;
    print(raiz);	
    cout<<endl;
    //mostrar(A);

    return 0;
}
