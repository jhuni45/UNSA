///14.8 problemas
///ejercicio 14.3

#include <iostream>
#include <cmath>

using namespace std;

struct Nodo{
	int valor;
    int potencia;
	Nodo* siguiente;
	Nodo (int valor,int potencia){
        this->valor=valor;
        this->potencia=potencia;
        this->siguiente=NULL;
    }
    Nodo (int valor,int potencia,Nodo*siguiente){
        this->potencia=potencia;
        this->valor = valor;
        this->siguiente = siguiente;
    }
};

void ingresar(Nodo *& m_front,int valor, int potencia){
    char X='f';
    if(m_front==NULL)
        m_front=new Nodo(valor, potencia);
    else{
        if (X=='f'){
            Nodo *aux=m_front;
            while(aux->siguiente!=NULL){
                aux=aux->siguiente;
            }
            aux->siguiente=new Nodo(valor, potencia);
        }
        else{
            m_front=new Nodo(valor,potencia,m_front);
        }
    }
}

Nodo* generar(string polinomio){
    Nodo* nuevo=NULL;
    string numero=" ",potencia=" ",base=" ";
    int coeficiente, exponente;
    for (int i =0;i<polinomio.length();i++){
        if (polinomio[0]=='x'){
            base="1";
        }
        if (polinomio[i]=='x' && (polinomio[i-1]=='+' || polinomio[i-1]=='-')){
            if(polinomio[i-1]=='-'){
                base="-1";
            } 
            if(polinomio[i-1]=='+'){
                base="1";
            }  
        }
        if (polinomio[i]=='x' && (polinomio[i+1]=='+' || polinomio[i+1]=='-' || i+1==polinomio.length()) ){
            potencia="1";
            coeficiente=atoi(base.c_str());
            exponente=atoi(potencia.c_str());
            ingresar(nuevo,coeficiente,exponente);
            base=" ";
            potencia=" ";
        }
        if (polinomio[i]!='x' && polinomio[i]!='+'){
            if (polinomio[i]=='^'){
                while(polinomio[i+1]!='x'&& polinomio[i+1]!='+' && polinomio[i+1]!='-'){
                    potencia+=polinomio[i+1];
                    i++;
                }
                coeficiente=atoi(base.c_str());
                exponente=atoi(potencia.c_str());
                ingresar(nuevo,coeficiente,exponente);
                base=" ";
                potencia=" ";
            }
            else{
                base+=polinomio[i];
                if ((i==polinomio.length()-1) && potencia==" "){
                    coeficiente=atoi(base.c_str());
                    ingresar(nuevo,coeficiente,0); 
                    base=" ";
                    potencia=" ";          
                }
            }        
        }
    }
    return nuevo;
}

void mostrar(Nodo * raiz){
    for (Nodo*aux=raiz;aux;aux=aux->siguiente){
            cout<<aux->valor<<" | "<<aux->potencia<<" ->  ";   
        }
    cout<<endl; 
}
void tabla(Nodo* raiz){
    float loop=0.0;
    cout<<"X\trespuesta"<<endl;
    while(loop<5.5){
        float respuesta=0;
        Nodo* aux=raiz;
        while(aux){
            respuesta+=aux->valor*(pow(loop,aux->potencia));
            aux=aux->siguiente;
        }
        cout<<loop<<"\t"<<respuesta<<endl;
        loop+=0.5;
    }
}
int main(){
    Nodo *A=NULL;
    int op;
    string poli;
    cout<<"Ingrese el polinomio (las varibles en minuscula)"<<endl;
    getline(cin,poli);
    A=generar(poli);
    do{
        cout<<"\t*****Problema 14.3*****\n[1] Mostrar lista\n[2] Generar tabla de valores\n[3] Salir"<<endl;
        cin>>op;
        cout<<endl;
        if (op<1 || op>3){
            cout<<"opcion invalida"<<endl;
        }
        else{
            switch(op){
                case 1:
                    mostrar(A);
                    cout<<endl;
                    break;
                case 2:
                    tabla(A);
                    cout<<endl;
                    break;
            }
        }
    }while(op!=3);
    
    return 0;
}
