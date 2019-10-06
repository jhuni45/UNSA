///		Escuela Profesional de Ciencia de la Computacion
///		Matematica Aplicada a la Computacion 
///		Integrantes: Basurco Cayllahua Eduardo
/// 				 Chavez Cruz Jhunior
///		DETERMINANTE POR OPERACIONES ELEMENTALES


#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

typedef vector<float> lista;
typedef vector<lista> matriz;

int F=0;
int C=0;
bool flag;
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
	float det=1;
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

	for (int i=0;i<mat.size();i++){
		float aux=mat[i][i];
		if (aux==0){
			cout<<"resolver la matriz"<<endl;
			return 1;
		}
		else if (aux!=0){
			for (int j=i+1;j<mat.size();j++){
				if (mat[j][i]!=0){
					cout<<"resolver la matriz"<<endl;
					return 1;
				}
			}
		}
		det=det*aux;
	}
	return det;
}

///FUNCION QUE CAMBIAR LAS FILAS SI SON NECESARIAS (METODO DE PIVOTE)
void pivote(matriz &mat,int columna){
	float pivote=mat[columna][columna];
	int flag=columna;
	for (int i=columna;i<mat.size();i++){
		if (abs(mat[i][columna]) >pivote){
			pivote=mat[i][columna];
			flag=i;
		}
	}
	mat[columna].swap(mat[flag]);

}

///ESTA FUNCION HALLA LA DETERMINANTE
int determinante(matriz &mat){

	int signo=1;
	for (int iter =0;iter<mat.size();iter++){
		if (mat[iter][iter]==0){
			pivote(mat,iter);
			signo=signo*(-1);
		}
		for (int i=iter+1;i<mat.size();i++){
			if (mat[iter][iter]==0){
				return 0;
			}
            float multi=mat[i][iter]/mat[iter][iter];
            for (int k=0;k<mat[0].size();k++){
                mat[i][k]=(double)  ((double)(mat[i][k])  -(double) (multi*mat[iter][k] ))  ;
            }
        }
	}
	return verificar(mat)*signo;
}

void imprimir(matriz mat){
	for (int i=0;i<mat.size();i++){
		for (int j=0;j<mat[0].size();j++){
			cout<<mat[i][j]<<"\t";
		}
		cout<<endl;
	}
}

int main (){
	matriz A;
	int fila, col,opc;
	cout<<"DETERMINANTE POR OPERACIONES ELEMENTALES\n DIMENSIONES:\n FILA: ";
	cin>>fila;
	cout<<" COLUMNA: ";
	cin>>col;
	A=generar(fila,col);
	llenar(A);
	imprimir(A);
	
	if (verificar(A)==0)
		cout<<"la determinante es: "<<0<<endl;
	else if(verificar(A)==1)
		cout<<"entro a la determinante :"<<determinante(A)<<endl;
	else 
		cout<<"la determinante es else: "<<verificar(A)<<endl;
	imprimir(A);
	
	return 0;
}