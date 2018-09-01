#include <iostream>
#include <cmath>
using namespace std;

class NodoD{
public:
    int valor;
    int potencia;
    NodoD *n_next;
    NodoD *n_back;
public:
    NodoD(int dato,int exponente){
        this->valor=dato;
        this->potencia=exponente;
        this->n_next=0;
        this->n_back=0;
    }
};

class Lista_C_NO{
public:
    NodoD *m_head;
    NodoD *m_last;
public:
    Lista_C_NO(){
        m_head=NULL;
        m_last=NULL;
    }
    void ingresar(int,int);
    void print();
    void generar(string);
    void tabla();
};


void Lista_C_NO:: tabla(){
    float loop=0.0;
    cout<<"X\trespuesta"<<endl;
    while(loop<5.5){
        float respuesta=0;
        NodoD* aux=m_head;
        while(aux!=m_last){
            respuesta+=aux->valor*(pow(loop,aux->potencia));
            aux=aux->n_next;
        }
        cout<<loop<<"\t"<<respuesta<<endl;
        loop+=0.5;
    }
}
void Lista_C_NO::print(){
    cout<<endl;
    NodoD *temp=m_head;
    while(temp!=m_last){
        cout<<temp->valor<<" | "<<temp->potencia<<" -> ";
        temp=temp->n_next;
    }
    cout<<temp->valor<<" | "<<temp->potencia<<endl;
}
void Lista_C_NO::ingresar(int dato,int exponente){
    NodoD *nuevo=new NodoD(dato,exponente);
    if(!m_head){
        m_head=nuevo;
        m_last=nuevo;
        nuevo->n_next=nuevo;
        nuevo->n_back=nuevo;
    }
    else{
        NodoD *temp=m_last;
        temp->n_next->n_back=nuevo;
        temp->n_next=nuevo;
        nuevo->n_back=temp;
        m_last=nuevo;
        nuevo->n_next=m_head;
    }
}
void Lista_C_NO::generar(string polinomio){
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
            ingresar(coeficiente,exponente);
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
                ingresar(coeficiente,exponente);
                base=" ";
                potencia=" ";
            }
            else{
                base+=polinomio[i];
                if ((i==polinomio.length()-1) && potencia==" "){
                    coeficiente=atoi(base.c_str());
                    ingresar(coeficiente,0); 
                    base=" ";
                    potencia=" ";          
                }
            }        
        }
    }
}

int main(){
    Lista_C_NO A;
    string poli;
    int op;
    cout<<"Ingrese el polinomio (las varibles en minuscula)"<<endl;
    getline(cin,poli);
    A.generar(poli);
    cout<<"\t*****Problema 14.3****"<<endl;
    do{
        cout<<"[1] Mostrar lista\n[2] Generar tabla de valores\n[3] Salir"<<endl;
        cin>>op;
        cout<<endl;
        if (op<1 || op>3){
            cout<<"opcion invalida"<<endl;
        }
        else{
            switch(op){
                case 1:
                    A.print();
                    cout<<endl;
                    break;
                case 2:
                    A.tabla();
                    cout<<endl;
                    break;
            }
        }
    }while(op!=3);
    
    return 0;
}
