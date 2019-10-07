///		Escuela Profesional de Ciencia de la Computacion
///		Matematica Aplicada a la Computacion 
///		Integrantes: Basurco Cayllahua Eduardo
/// 				 Chavez Cruz Jhunior
///		DETERMINANTE POR METODO DE COFACTORES

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

typedef vector<float> lista;
typedef vector<lista> matriz;

int F=1;
int C=1;
bool flag=true;
void imprimir(matriz);

matriz generar(int fila, int columna){
	matriz A(fila);
	if (fila!=columna){
		cout<<"debe ser una matriz cuadrada"<<endl;
		return A;
	}
	for (int i =0;i<columna;i++){
		A[i]=lista(columna);
	}
	return A;
}

void llenar(matriz &aux){
	for (int i=0;i<aux.size();i++){
		for (int j=0;j<aux[0].size();j++){
			float x;
            cout<<"valor:";
            cin>>x;
            aux[i][j]=x;
		}
	}
}

///FUNCION PARA VERIFICAR SI HAY FILAS O COLUMNAS CON CEROS 
int verificar(matriz mat){
	for (int i=0;i<mat.size();i++){
		int aux=0;
		int aux2=0;
		for (int j=0;j<mat.size();j++){
			if(mat[i][j]==0)
				aux++;
			if (mat[j][i]==0)
				aux2++;
		}
		if (aux==mat.size()){
			cout<<"hay una fila con ceros"<<endl;
			return 0;
		}
		if (aux2==mat.size()){
			cout<<"hay un columna con ceros"<<endl;
			return 0;
		}
	}
	cout<<"la matriz no tiene filas o columnas con ceros"<<endl;
	return 1;
}

///ESTA FUNCION ELIMINA LAS FILAS Y LAS COLUMNAS 
matriz reducir(matriz mat, int fila, int columna){
	mat.erase(mat.begin()+fila,mat.begin()+fila+1);
	for (int i =0;i<mat.size();i++){
		mat[i].erase(mat[i].begin()+columna,mat[i].begin()+columna+1);
	}
	//imprimir(mat);
	//cout<<endl;
	return mat;
}

///ESTA FUNCION HALLA LA DETERMINANTE
float determinante(matriz mat){
	if (mat.size()==2){
		return ((mat[0][0]*mat[1][1])-(mat[1][0]*mat[0][1]));
	}
	float det=0;
	matriz aux=mat;
	for (int i=0;i<mat.size();i++){
		/// para hallar la determinante por filas
		if (flag==true){
			aux=reducir(mat,F-1,i);
			cout<<" valorrr:"<<pow(-1,(F-1+i))<<endl;
			float cofactor=(pow(-1,(F-1+i)))*determinante(aux);
			det+=mat[F-1][i]*cofactor;
		}
		/// para hallar la determinante por columnas
		else{
			aux=reducir(mat,i,C-1);
			float cofactor=(pow(-1,(i+C-1)))*determinante(aux);
			det+=mat[i][C-1]*cofactor;
		}

	}
	return det;
}

matriz matrizcofactores(matriz mat){
	matriz A=mat;
	matriz aux=mat;
	for (int i =0;i<mat.size();i++){
		for (int j=0;j<mat.size();j++){
			aux=reducir(mat,i,j);
			A[i][j]=pow(-1,i+j+2)*determinante(aux);
		}
	}
	return A;
}

void adjunta(matriz &mat ){
	for (int i=0;i<mat.size();i++){
		for(int j=i;j<mat.size();j++){
			float aux=mat[i][j];
			mat[i][j]=mat[j][i];
			mat[j][i]=aux;
		}
	}
}

void multiplicar(matriz &mat, float det){
	for (int i =0;i<mat.size();i++){
		for (int j=0;j<mat.size();j++){
			mat[i][j]=mat[i][j]*det;
		}
	}
}
matriz matrizinversa(matriz mat){
	matriz inversa=mat;
	float det_A=determinante(mat);
	float constante=(double)1/det_A;
	if (mat.size()==2){
		inversa[0][0]=mat[1][1];
		inversa[0][1]=mat[1][0];
		inversa[1][0]=mat[0][1];
		inversa[1][1]=mat[0][0];
		cout<<"matriz inversa (sin multiplicar) 1/"<<det_A<<" :\n A[]="<<endl;
		imprimir(inversa);
		cout<<endl;
		multiplicar(inversa,constante);
		return inversa;
	}
	inversa=matrizcofactores(mat);
	adjunta(inversa);
	cout<<"matriz inversa (sin multiplicar) 1/"<<det_A<<" :\n A[]="<<endl;
	imprimir(inversa);
	cout<<endl;
	multiplicar(inversa,constante);
	return inversa;
}

void imprimir(matriz mat){
	for (int i=0;i<mat.size();i++){
		for (int j=0;j<mat[0].size();j++){
			cout<<mat[i][j]<<"\t";
		}
		cout<<endl;
	}
}
int main(){
	matriz p1,inversa;
	int fila, col;
	cout<<"INVERSA POR COFACTORES Y ADJUNTA\n DIMENSIONES:\n FILA: ";
	cin>>fila;
	cout<<" COLUMNA: ";
	cin>>col;
	p1=generar(fila,col);
	llenar(p1);
	imprimir(p1);
	if(verificar(p1)==0){
			cout<<"la determinante es :"<<0<<endl;
			cout<<"la matriz no tiene inversa"<<endl;
			return 0;
	}
	inversa=matrizinversa(p1);
	cout<<"la matriz inversa es:"<<endl;
	imprimir(inversa);
		
	return 0;
}
