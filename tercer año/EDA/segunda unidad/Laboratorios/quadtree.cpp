#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct nodo{
	int valor;
	nodo *uno;
	nodo *dos;
	nodo *tres;
	nodo *cuatro;
	nodo(){
		this->uno=dos=tres=cuatro=NULL;
	}

};

void mostrar_matriz(vector<vector<int>> imagen){
	for (int i=0;i<imagen.size();i++){
		for (int j=0;j<imagen[0].size();j++){
			cout<<imagen[i][j]<<" ";
		}
		cout<<endl;
	}
}


class Quadtree{
public:
	Quadtree(vector<vector<int>>image){
		root=NULL;
		imagen=image;
	};
	void help_arbolito();
	void arbolito(nodo*&,vector<vector<int>>);
	//void mostrar_matriz();
	int calc_valor(vector<vector<int>>);
	vector<vector<int>> calc_matriz(int,int,int,int);
	int calcular(int,int,int,int);
	void help_show();
	void show(nodo*);

private:
	nodo *root;
	vector<vector<int>> imagen;
};

void Quadtree::help_show(){
	show(root);
}
void Quadtree::show(nodo* raiz){
	if (raiz==NULL)
		return;
	else{
		cout<<raiz->valor<<" ";
		show(raiz->uno);
		show(raiz->dos);
		show(raiz->tres);
		show(raiz->cuatro);
	}
}
void Quadtree::arbolito(nodo *&raiz,vector<vector<int>> image){
	//cout<<"EL ARBOL"<<endl;
	//	help_show();
	int value=calc_valor(image);
	cout<<"para dimension: "<<image.size()<<"valor: "<<value<<endl;
	nodo *nuevo= new nodo();
	if (raiz==NULL){
		cout<<"creee"<<endl;
		raiz=nuevo;
		raiz->valor=value;
	}
	if(value==0 || value==1){
		cout<<"fianl"<<endl;
		return;
	}
	if (value==-1){
		cout<<"hola qw"<<endl;
		vector<vector<int>> uno_v(image.size()/2,vector<int>(image[0].size()/2));
		vector<vector<int>> dos_v(image.size()/2,vector<int>(image[0].size()/2));
		vector<vector<int>> tres_v(image.size()/2,vector<int>(image[0].size()/2));
		vector<vector<int>> cuatro_v(image.size()/2,vector<int>(image[0].size()/2));
		
		uno_v=calc_matriz(0,image.size()/2,0,image[0].size()/2);
		dos_v=calc_matriz(0,image.size()/2,image[0].size()/2,image.size());
		tres_v=calc_matriz(image.size()/2,image.size(),image[0].size()/2,image[0].size());
		cuatro_v=calc_matriz(image.size()/2,image.size(),0,image[0].size()/2);
		
		/*cout<<"matriz 1"<<endl;
		mostrar_matriz(uno_v);
		cout<<"matriz 2"<<endl;
		mostrar_matriz(dos_v);
		cout<<"matriz 3"<<endl;
		mostrar_matriz(tres_v);
		cout<<"matriz 4"<<endl;
		mostrar_matriz(cuatro_v);
		*/
		arbolito(raiz->uno,uno_v);
		arbolito(raiz->dos,dos_v);
		arbolito(raiz->tres,tres_v);
		arbolito(raiz->cuatro,cuatro_v);
	}

}

void Quadtree::help_arbolito(){
	arbolito(root,imagen);
}
/*
int Quadtree::calcular(int inicio_f,int fin_f,int inicio_c,int fin_c){
	int aux=imagen[0][0];	
	for (int i=inicio_f;i<fin_f;i++){
		for (int j=inicio_c;j<fin_c;j++){
			if (imagen[i][j]!=aux)
				return -1;
		}
	}
	return aux;
}
*/
vector<vector<int>> Quadtree::calc_matriz(int inicio_f,int fin_f,int inicio_c,int fin_c){
	vector<vector<int>> nueva(fin_f-inicio_f,vector<int>(fin_c-inicio_c));
	int h=0;
	for (int i=inicio_f;i<fin_f;i++){
		int k=0;
		for (int j=inicio_c;j<fin_c;j++){
			nueva[h][k]=imagen[i][j];
			k++;
		}
		h++;
	}
	return nueva;
}

int Quadtree::calc_valor(vector<vector<int>> image){
	int aux=image[0][0];
	for (int i=0;i<image.size();i++){
		for (int j=0;j<image[0].size();j++){
			if (image[i][j]!=aux)
				return -1;
		}
	}
	return aux;
}


int main (){
	srand(time(NULL));
	vector<vector<int>> imagen ={{1,1,1,1,0,0,0,0},
						 		 {0,1,1,1,0,0,0,0},
								 {1,0,1,0,0,0,0,0},
								 {1,1,0,1,0,0,0,0},
								 {0,0,1,0,1,1,0,1},
								 {1,0,0,1,1,0,1,0},
								 {0,1,0,1,0,1,0,1},
								 {1,0,1,1,1,0,1,1}};
	Quadtree prueba(imagen);
	prueba.help_arbolito();
	prueba.help_show();
	/*mostrar_matriz(imagen);
	vector<vector<int>> div(4,vector<int>(4));
	div=prueba.calc_matriz(imagen.size()/2,imagen.size(),imagen[0].size()/2,imagen[0].size());
	mostrar_matriz(div);
	*/
	return 0;
}
