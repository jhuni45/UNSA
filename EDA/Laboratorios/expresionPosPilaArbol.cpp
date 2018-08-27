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

vector<Arbol*> procesar(string expresion){
    vector<Arbol*> arbolito;
    for (int i=0;i<expresion.size();i++){
        char caracter=expresion[i];
        if (caracter>='a' || caracter<='z'){
            Arbol *aux=new Arbol(caracter);
            arbolito.push_back(aux);
        }
        mostrar()
        if (caracter=='+' ||caracter=='-' ||caracter=='*' ||caracter=='/' ){
            Arbol* A1=arbolito[arbolito.size()-2];
            Arbol* A2=arbolito[arbolito.size()-1];
            Arbol* padre=new Arbol(caracter,A1,A2);
            for (int i=0;i<2;i++){
                arbolito.pop_back();
            }
            arbolito.push_back(padre);
        }
    }
    return arbolito;
}
void print(Arbol* padre){
    if (padre==nullptr){
        return;
    }
    cout<<padre->dato<<"  ";
    print(padre->hijo_der);
    print(padre->hijo_izq);
}
void mostrar(vector<Arbol*> A){
    for (int i=0;i<A.size();i++){
        cout<<A[i]->dato<<"-> ";
    }
    cout<<endl;
}

int main(){
    string expresion;
    cout<<"ingrese expresion"<<endl;
    cin>>expresion;
    vector<Arbol*>A;
    A= procesar(expresion);
    mostrar(A);

    return 0;
}
