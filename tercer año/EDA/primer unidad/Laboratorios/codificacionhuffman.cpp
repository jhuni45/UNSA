/*
---Codificacion de Huffman
Idea: Asociar los caracteres con mayor frecuencia a cadenas cortas y los de menos frecuencia a cadenas largas en un arbol 		binario
Observaciones: 
	* Principio de "codigo prefijo" Ninguna de las cadenas P es prefija de otra cadena de P
	* La 'Z' no aparece mucho
	* Gastar la memoria lo menos posible
	* Usado en comprecion y encriptacion
Ejemplo:
	Caracteres: X	Y 	*	+	(	)
	Frecuencia: 10	10	15	25	20	20

	Ordenamos: 10	10	15	20	20	25
	Foto celular
*/

#include <iostream>
#include <algorithm>
#include <map>
#include <fstream>

using namespace std;

struct Nodo{
    int dato;
    char key;
    int punto;
    Nodo *siguiente;
    Nodo *padre;
    Nodo *izq;
    Nodo *der;
    Nodo (int dato, char key){
        this->dato=dato;
        this->key=key;
        this->siguiente=NULL;
    }
    Nodo (int dato, char key, Nodo*siguiente){
        this->dato = dato;
        this->key=key;
        this->siguiente = siguiente;
        this->padre=NULL;
    }
};


char pchar=166;

class simpleO{
public:
    void add(int,char);
    void print();
    void remove(char key);
    void generarvector(vector<Nodo*>&);
    simpleO(){
        m_front=NULL;
    }
private:
    Nodo* m_front;
};

void simpleO::add(int valor, char key){
    Nodo *nuevo=new Nodo(valor,key);
    Nodo *aux1=m_front;
    Nodo *aux2;
    while((aux1!=NULL)&&(aux1->dato<valor)){
        aux2=aux1;
        aux1=aux1->siguiente;
    }

    if(m_front==aux1)
        m_front=nuevo;
    else{
        aux2->siguiente=nuevo;
    }
    nuevo->siguiente=aux1;
}
void simpleO::remove(char clave){
    if (!m_front){
        cout<<"vacio"<<endl;
    }
    else{
        Nodo *temp=m_front;
        Nodo *temp2=m_front;
        bool cambio=false;
        while(temp){
            if(temp->key==clave){
                cambio=true;
                if(temp==temp2){
                    m_front=temp->siguiente;
                    delete temp;
                }
                else{
                    temp2->siguiente=temp->siguiente;
                    delete temp;
                }
            }
            temp2=temp;
            temp=temp->siguiente;
        }
        if(!cambio){
            cout<<"no se elimino"<<endl;
        }
        else
            cout<<"eliminado"<<endl;
    }
}
void simpleO::print (){
    for (Nodo*aux=m_front;aux;aux=aux->siguiente){
        cout<<"("<<aux->dato<<","<<aux->key<<") ->";
    }
    cout<<endl;
}

void mostrar_map(map<char,int> T_frecuency, simpleO &raiz){
    map<char,int>::iterator it;
    for (it=T_frecuency.begin(); it!=T_frecuency.end(); ++it){
        cout << it->first << " => " << it->second << '\n';
        raiz.add(it->second,it->first);
    }
}
void simpleO::generarvector(vector<Nodo*> &accesos){
    for (Nodo*aux=m_front;aux;aux=aux->siguiente){
        accesos.push_back(aux);
    }
    cout<<endl;
}
void ordenar(vector<Nodo*> &accesos){
    bool bandera=true;
    while (bandera){
        Nodo *AUX;
        for(int j=0;j<accesos.size()-1;j++){
            if (accesos[j]->dato>accesos[j+1]->dato){
                AUX=accesos[j];
                accesos[j]=accesos[j+1];
                accesos[j+1]=AUX;
                bandera=false;
            }
        }
        if (bandera==false){
            bandera=true;
        }
        else
            bandera=false;
    }
}

void mostrar_vector(vector<Nodo*> lista){
    for (int i=0;i<lista.size();i++){
        cout<<lista[i]->dato<< " ";
    }
    cout<<endl;
}

void proceso(vector<Nodo*> &accesos){
    cout<<"entre"<<endl;
    if (accesos.size()<2){
        accesos[0]->padre=NULL;
        return;
    }
    else {
        mostrar_vector(accesos);
        Nodo *aux1=accesos[0];
        Nodo *aux2=accesos[1];
        Nodo *padre=new Nodo(aux1->dato+aux2->dato,pchar);
        pchar++;
        padre->izq=aux1;
        padre->der=aux2;
        aux1->punto=1;
        aux2->punto=0;
        aux2->padre=aux1->padre=padre;
        accesos.erase(accesos.begin()+0);
        accesos.erase(accesos.begin()+0);
        accesos.push_back(padre);
        ordenar(accesos);
        proceso(accesos);
    }
}

class Arbol
{
private:
    Nodo *root;
public:
    Arbol(Nodo*);
    void help_Generador();
    void GenerarDot(Nodo*,ofstream&);

};
Arbol::Arbol(Nodo* arbolito){
    root=arbolito;
}

void Arbol::GenerarDot(Nodo* raiz, ofstream &salida){
    if (raiz==NULL)
        return;
    else{
        if (raiz->izq!=NULL){
            if(raiz->key==' ')
                salida<<"esp"<<" -> "<<raiz->izq->key<<endl;
            if (raiz->izq->key==' ')
                salida<<raiz->key<<" -> "<<"esp"<<endl;
            if (raiz->der->key==' ')
                salida<<raiz->key<<" -> "<<"esp"<<endl;
            else 
                salida<<raiz->key<<" -> "<<raiz->izq->key<<endl;
                
        }
        if (raiz->der!=NULL){
            salida<<raiz->key<<" -> "<<raiz->der->key<<endl;
        }
        GenerarDot(raiz->izq,salida);
        GenerarDot(raiz->der,salida);
    }
}

void Arbol::help_Generador(){
    ofstream salida;
    salida.open("Huffman.dot");
    salida<<"digraph G {"<<endl;
    GenerarDot(root,salida);
    salida<<"}";
    salida.close();
}

map<char,string> codificacion(vector<Nodo*> lista){
    map<char,string> mapa;
    for (int i =0;i<lista.size();i++){
        string codigo=" ";
        Nodo *aux=lista[i];
        //cout<<"para :"<<lista[i]->key<<endl;
        while(aux!=NULL){
            cout<<lista[i]->punto<<endl;
            codigo+=lista[i]->punto;
            aux=aux->padre;
        }
        //cout<<"los contenidos"<<codigo<<endl;
        mapa[lista[i]->key]=codigo;
    }
    return mapa;
}

void mostrar_map2(map<char,string> codificacion){
    map<char,string>::iterator it;
    for (it=codificacion.begin(); it!=codificacion.end(); ++it){
        cout << it->first << " => " << it->second << '\n';
    }   
}

int main(){
    //cout<<"n -> 1111\ni -> 0111\nd -> 0011\nt -> 10011\nm -> 00011\nl -> 101\ne -> 001\ng -> 11110\nc -> 01110\ns -> 0110\na -> 010\n  -> 100\nb -> 11000\nr -> 01000\no -> 0000"<<endl;
    simpleO tabla;
	map<char,int> T_frecuency;
    vector<Nodo*> accesos;
  	string cadena="a caballo regalado no se le mira los dientes";
    //string cadena="hoolaaa";
    for (int i=0;i<cadena.size();i++){
		char aux=cadena[i];
		T_frecuency[aux]+=1;
	}
  	cout<<"mostrado"<<endl;
  	mostrar_map(T_frecuency,tabla);
  	cout<<"vector ordenado"<<endl;
    tabla.generarvector(accesos);
    tabla.print();
    cout<<"vector"<<endl;
    mostrar_vector(accesos);
    vector<Nodo*> accesos2=accesos;
    proceso(accesos);
    cout<<"final"<<endl;
    mostrar_vector(accesos);
    Arbol arbolito(accesos[0]);
    arbolito.help_Generador();
    map<char,string> code;
    code=codificacion(accesos2);
    mostrar_map2(code);

	return 0;
} 
