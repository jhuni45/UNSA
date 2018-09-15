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
#include <vector>
#include <map>

using namespace std;
struct Nodo{
	int elemento;
	int valor;
	Nodo *padre;
	Nodo *izq;
	Nodo *der;
	Nodo(int elemento){
		this->elemento=elemento;
		this->padre=izq=der=NULL;
	}
	Nodo(int elemento, Nodo *padre, Nodo *der, Nodo *izq){
		this->elemento=elemento;
		this->padre=padre;
		this->der=der;
		this->izq=izq;
	}
};
void ordenar (vector<int> &lista){
	sort(lista.begin(),lista.end());
}
void proceso(vector<int> lista,Nodo *raiz){
	while (!lista.empty()){

	}

}

int main(){
	Nodo *root=NULL;
	map<char,int> T_frecuency;
	vector<int> frecuencia;
  	string cadena="a caballo regalado no se le mira los dientes";
	for (int i=0;i<cadena.size();i++){
		char aux=cadena[i];
		T_frecuency[aux]+=1;
	}
  	cout<<"mostrado"<<endl;
  	map<char,int>::iterator it;
  	for (it=T_frecuency.begin(); it!=T_frecuency.end(); ++it){
    	cout << it->first << " => " << it->second << '\n';
    	frecuencia.push_back(it->second);
  	}
  	cout<<"vector ordenado"<<endl;
  	ordenar(frecuencia);
  	for (int i =0;i<frecuencia.size();i++)
  		cout<<frecuencia[i]<<" ";
	return 0;
} 