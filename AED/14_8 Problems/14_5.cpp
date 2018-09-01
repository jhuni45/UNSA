#include <iostream>
#include <vector>

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

class Lista_C_O{
public:
    NodoD *m_head;
    NodoD *m_last;
    vector<int> valores;
public:
    Lista_C_O(){
        m_head=NULL;
        m_last=NULL;
    }
    void ingresar(int,int);
    void print();
    void generar(string);
    void generar_array(int);
    void print_array();
};

void Lista_C_O::print_array(){
    for (int i =0;i<valores.size();i++){
        cout<<valores[i]<<endl;
    }
    cout<<endl;
}
void Lista_C_O::generar_array(int num){
    bool flag=false;
    for (int i =0;i<valores.size();i++){
        if (num==valores[i]){
            flag=true;
        }
    }
    if (flag==false){
        valores.push_back(num);
    }
}

void Lista_C_O::ingresar(int dato,int exponente){
    NodoD *nuevo=new NodoD(dato,exponente);
    if(!m_head){
        m_head=nuevo;
        m_last=nuevo;
        nuevo->n_next=nuevo;
        nuevo->n_back=nuevo;
    }
    else{
        NodoD *temp=m_head;
        while(temp->potencia>exponente && temp!=m_last){
            temp=temp->n_next;
        }
        if(temp->potencia>exponente){
            nuevo->n_back=temp;
            temp->n_next->n_back=nuevo;
            temp->n_next=nuevo;
            nuevo->n_next=m_head;
            m_last=nuevo;
        }
        else{
            if(temp!=m_head){
                nuevo->n_next=temp;
                nuevo->n_back=temp->n_back;
                temp->n_back->n_next=nuevo;
                temp->n_back=nuevo;
            }
            else{
                nuevo->n_next=temp;
                temp->n_back->n_next=nuevo;
                temp->n_back=nuevo;
                nuevo->n_back=m_last;
                m_head=nuevo;
            }
        }
    }
    generar_array(exponente);
}
/*
void Lista_C_O::ingresar(int dato,int exponente){
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
    generar_array(exponente);
}
*/
void Lista_C_O::generar(string polinomio){
    string numero=" ",potencia=" ",base=" ";
    int coeficiente, exponente,cont=0;
    for (int i =0;i<polinomio.length();i++){
        cout<<"i "<<i<<endl;
        if (polinomio[0]=='x' && cont<1){
            cont++;
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

vector<int> fusion(vector<int> A, vector<int> B){
    cout<<"fusion"<<endl;
    vector<int> respuesta;
    respuesta=B;
    for (int i=0;i<A.size();i++){
        bool flag=false;
        for (int j =0;j<respuesta.size();j++){
            cout<<i<< "  "<<j<<endl;
            if (A[i]==respuesta[j]){
                flag=true;
            }
        }
        if (flag==false){
            respuesta.push_back(A[i]);
        }
    }
    return respuesta;
    
}

Lista_C_O multiplicacion(Lista_C_O A, Lista_C_O B){
    Lista_C_O aux;
    NodoD* temp=A.m_head;
    NodoD* temp2=B.m_head;
    while(temp!=A.m_last){
        while(temp2!=B.m_last){
            aux.ingresar(temp->valor*temp2->valor, temp->potencia+temp2->potencia);
            temp2=temp2->n_next;
        }
        aux.ingresar(temp->valor*temp2->valor, temp->potencia+temp2->potencia);
        temp=temp->n_next;
    }
    while(temp2!=B.m_last){
        aux.ingresar(temp->valor*temp2->valor, temp->potencia+temp2->potencia);
        temp2=temp2->n_next;
    }
    aux.ingresar(temp->valor*temp2->valor, temp->potencia+temp2->potencia);
    return aux;
}

Lista_C_O suma(Lista_C_O A, Lista_C_O B){
    Lista_C_O respuesta;
    
    vector<int> valores_R=fusion(A.valores,B.valores);
    for (int k=0;k<valores_R.size();k++){
        cout<<valores_R[k]<<"  ";
    }
    for (int i=0;i<valores_R.size();i++){
        cout<<"holaaaaa"<<endl;
        NodoD * temp=A.m_head;
        NodoD * temp2=B.m_head;
        int aux_v=0;
        while(temp!=A.m_last){
            if (temp->potencia==valores_R[i]){
                aux_v=aux_v+temp->valor;
            }
            temp=temp->n_next;
        }
        if (temp->potencia==valores_R[i]){
            aux_v=aux_v+temp->valor;
        }
        ///segundo polinomio
        while(temp2!=B.m_last){
            if (temp2->potencia==valores_R[i]){
                aux_v=aux_v+temp2->valor;
            }
            temp2=temp2->n_next;
        }
        if (temp2->potencia==valores_R[i]){
            aux_v=aux_v+temp2->valor;
        }
        respuesta.ingresar(aux_v,valores_R[i]);
    }
    return respuesta;
}

Lista_C_O derivada(Lista_C_O A){
    Lista_C_O  aux;
    for (int i=0;i<A.valores.size();i++){
        NodoD * temp=A.m_head;
        int aux_v=0,aux_p=0;
        if (A.valores[i]!=0){
            while (temp!=A.m_last){
                cout<<"hola"<<endl;
                if (temp->potencia==A.valores[i]){
                    aux_v=aux_v+(temp->valor * temp->potencia);
                }
                temp=temp->n_next;
            }
            if (temp->potencia==A.valores[i]){
                aux_v=aux_v+(temp->valor * temp->potencia);
            }
            aux_p=A.valores[i]-1;
            aux.ingresar(aux_v,aux_p);
        }
    }
    return aux;   
}
void Lista_C_O::print(){
    cout<<endl;
    NodoD *temp=m_head;
    //NodoD *temp1=m_last->n_next;
    while(temp!=m_last){
        cout<<temp->valor<<" | "<<temp->potencia<<" -> ";
        temp=temp->n_next;
    }
    cout<<temp->valor<<" | "<<temp->potencia<<endl;
}


int main(){
    Lista_C_O A,B,C,D,G;
    string poli;
    int op;
    cout<<"Ingrese el polinomio 1 (las varibles en minuscula)"<<endl;
    getline(cin,poli);
    A.generar(poli);

    cout<<"Ingrese el polinomio 2 (las varibles en minuscula)"<<endl;
    getline(cin,poli);
    B.generar(poli);
    do{
        cout<<"\t*****Problema 14.5*****\n[1] Mostrar polinomio 1 y 2\n[2] Mostrar la suma\n[3] Mostrar la derivada"<<endl;
        cout<<"[4] Mostrar el producto\n[5] Mostrar arrays\n[6] Salir"<<endl;
        cin>>op;
        cout<<endl;
        if (op<1 || op>6){
            cout<<"opcion invalida"<<endl;
        }
        else{
            switch(op){
                case 1:
                    cout<<"polinomio 1"<<endl;
                    A.print();
                    cout<<"polinomio 2"<<endl;
                    B.print();
                    cout<<endl;
                    break;
                case 2:
                    
                    G=suma(A,B);
                    G.print();
                    cout<<endl;
                    break;
                case 3:
                    
                    cout<<"[1] Polinomio 1\n[2] Polinomio 2"<<endl;
                    int j;
                    cin>>j;
                    if (j==1)
                        D=derivada(A);
                    else
                        D=derivada(B);
                    D.print();
                    cout<<endl;
                    break;
                case 4:
                    C=multiplicacion(A,B);
                    C.print();
                    cout<<endl;
                    break;
                case 5:
                    cout<<"polinomio 1"<<endl;
                    A.print_array();
                    cout<<"polinomio 2"<<endl;
                    B.print_array();
                    cout<<endl;
                    break;
            }
        }
    }while(op!=6);
    return 0;
}
