//forma horizontal A

#include <iostream>
#include <vector>

using namespace std;
typedef vector<int> lista;
typedef vector<vector<int>> matriz;

void mostrar(matriz A){	
	for (int i=0;i<A.size();i++){
		for (int j=0;j<A[0].size();j++){
			cout<<A[i][j]<<" ";
		}
		cout<<endl;
	}
}
double multicole(matriz &datos, lista cifras, lista multiplicador){
	double costo=0.0;
	int indice_fila=0;
	for (int i =multiplicador.size()-1;i>=0;i--){
		int faltante=0;
		int indice=0+indice_fila;
		for (int j=cifras.size()-1;j>=0;j--){
			int producto=(multiplicador[i]*cifras[j])+faltante;
			costo+=1.01;
			if (j==0){
				datos[indice_fila][datos[0].size()-1-indice]=producto%10;
				indice++;
				datos[indice_fila][datos[0].size()-1-indice]=producto/10;
			}
			else{
				faltante=producto/10;
				datos[indice_fila][datos[0].size()-1-indice]=producto%10;		
			}
			indice++;
		}
		costo-=0.01;
		indice_fila++;
	}
	int faltante_suma=0;
	int aux_result;
	for (int j=datos[0].size()-1;j>=0;j--){
		int suma_col=0;
		for (int i=datos.size()-1;i>=0;i--){
			suma_col+=datos[i][j];
			costo+=0.01;
		}
		costo+=0.01;
		suma_col+=faltante_suma;
		faltante_suma=suma_col/10;
		aux_result=suma_col%10;
		datos[datos.size()-1][j]=aux_result;	
		
	}
	return costo;
}

int main(){
	lista cifras ={1,2,3,4,5,6,7,8,9,0};
	lista multiplicador={1,2,3,4,5};
	int columnas=cifras.size()+multiplicador.size();
	
	matriz datos(multiplicador.size()+1,lista(columnas));
	mostrar(datos);
	cout<<endl;
	cout<<multicole(datos,cifras,multiplicador)<<endl;
	mostrar(datos);
	return 0;
}