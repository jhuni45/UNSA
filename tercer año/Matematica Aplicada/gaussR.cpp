///******************************************///
/// Alumno :    Chavez Cruz Jhunior Kenyi    ///
/// Cui    :    20143495                     ///
/// Escuela:    Ciencia de la Computacion    ///
/// Curso  :    Matematica Aplicada a la C.  ///
///******************************************///

#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

typedef int num;
typedef double real;
typedef vector<real> myvector;
typedef vector<myvector> matriz;

void mostrarMatriz(matriz &);

///crea espacio en la memoria
matriz generar(num row, num col){
    matriz mat(row);
    for (num i=0;i<row;i++){
        mat[i]=myvector(col);
    }
    return mat;
}
///llenamos nuestros datos de la MATRIZ AUMENTADA
void llenar (matriz& mat,num row,num col){
    for (num i=0;i <mat.size();i++){
        for(num j=0;j<mat[i].size();j++){
            real x;
            cout<<"valor:";
            cin>>x;
            mat[i][j]=x;
        }
    }
}

///esta funcion busca el A (columna, fila)
num buscarA(matriz mat, num columna){
    for (num j=columna;j<mat.size();j++){
        if (mat[j][columna]==0){
            return -1;
        }
    }
    return -2;
}
///volvemos la fila 1
void volveruno(myvector& vec, num inicio){
    real multi=vec[inicio];
    for (num i=inicio;i<vec.size();i++){
        vec[i]=(vec[i]/multi);
    }
}
///prueba los 3 casos : infinitas soluciones, no tiene solucion y si es una respuesta unica.
num probarrespuesta(myvector A){
    for (num i=0;i<A.size();i++){
        if (A[i]!=0){
            if (i==A.size()-1){
                cout<<"La familia de soluciones no tiene solucion"<<endl;
                return 0;
            }
            else
                return 2;
        }
    }
    cout<<"La familia de soluciones tiene soluciones infinitas"<<endl;
	return 1;
}

void gaussJordan(matriz &mat){
    for (num i=0;i<mat.size();i++){
        if (probarrespuesta(mat[mat.size()-1])==1 || probarrespuesta(mat[mat.size()-1])==0)
            break;
        num A=buscarA(mat,i);
        if (A==-1){
            cout<<"entre en "<<i<<endl;
            mat[i].swap(mat[i+1]);
            cout<<"cambiado:"<<endl;
            mostrarMatriz(mat);
        }
        volveruno(mat[i],i);
        ///aqui las filas debajo de 1 se hacen cero
        for (num h=i+1;h<mat.size();h++){
            real multi=mat[h][i];
            cout<<"multi"<<multi<<endl;
            for (num k=0;k<mat[0].size();k++){
                cout<<"posicion "<<mat[h][k]<<" posicion multiplicada "<<mat[i][k]<<endl;
                mat[h][k]=(double)((double)(mat[h][k])-(double)((double)multi*(double)mat[i][k]));
            }
        }
        ///aqui las filas arriba de 1 se hacen cero
        cout<<"la inversa********************"<<endl;
        for (num p=0;p<i;p++){
            real multi=mat[p][i];
            cout<<"multi "<<multi<<endl;
            for (num l=i;l<mat[0].size();l++){
                cout<<"posicion "<<mat[p][l]<<" posicion multiplicada "<<mat[i][l]<<endl;
                mat[p][l]=(double)((double)(mat[p][l])-(double)((double)multi*(double)mat[i][l]));
            }
        }
        cout<<"procesos: "<<endl;
        mostrarMatriz(mat);
        cout<<endl;
    }
    if (probarrespuesta(mat[mat.size()-1])==2){
        cout<<"La respuesta es unica y las varibles son:"<<endl;
        char Var='a';
        for(int i=0;i<mat.size();i++){
            cout<<Var<<" = "<<mat[i][mat[0].size()-1]<<endl;
            Var++;
        }
    }
}

void mostrarMatriz(matriz& A){
	for(int i = 0; i < A.size(); i++){
		for(int j = 0; j < A[i].size();j++){
			cout<<A[i][j]<<"\t";
		}
		cout<<endl;
	}
	cout<<endl;
}

void rango(matriz mat){
    num MA=0, M=0;
    for (num i=0;i<mat.size();i++){
        num j=0;
        bool AUX=true;
        while(AUX==true && j<mat[0].size()){
            if (mat[i][j]!=0){
                MA++;
                AUX=false;
            }
        j++;
        }
    }
    for (num i=0;i<mat.size();i++){
        num j=0;
        bool AUX=true;
        while(AUX==true && j<(mat[0].size()-1)){
            if (mat[i][j]!=0){
                M++;
                AUX=false;
            }
        j++;
        }
    }
    if (MA==M){
        cout<<"La matriz es consistente"<<endl;
    }
    else{
        cout<<"La matriz es inconsistente"<<endl;
    }


}

int main (){
    num fila,columna;
    matriz A;
    cout<<"**DIMESIONES"<<endl<<"Filas: ";
    cin>>fila;
    cout<<"Columnas: ";
    cin>>columna;
    A=generar(fila,columna);
    llenar(A,fila,columna);
    mostrarMatriz(A);
    cout<<"***Empieza Gauss***"<<endl;
    gaussJordan(A);
    cout<<endl<<"***Matriz final***"<<endl;
    mostrarMatriz(A);
    return 0;

}
