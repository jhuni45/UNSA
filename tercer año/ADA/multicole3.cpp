//forma vertical C

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
	int indice=0;
	for (int i =multiplicador.size()-1;i>=0;i--){
		int faltante=0;
		int indice_fila=0+indice;
		for (int j=cifras.size()-1;j>=0;j--){
			int producto=(multiplicador[i]*cifras[j])+faltante;
			costo+=1.01;
			if (j==0){
				datos[indice_fila][indice]=producto%10;
				indice_fila++;
				datos[indice_fila][indice]=producto/10;
			}
			else{
				faltante=producto/10;
				datos[indice_fila][indice]=producto%10;		
			}
			indice_fila++;
		}
		costo-=0.01;
		indice++;
	}
	
	int faltante_suma=0;
	int aux_result;
	for (int i=0;i<datos.size();i++){
		int suma_fila=0;
		for (int j=0;j<datos[0].size()-1;j++){
			suma_fila+=datos[i][j];
			costo+=0.01;
		}
		costo+=0.01;
		suma_fila+=faltante_suma;
		faltante_suma=suma_fila/10;
		aux_result=suma_fila%10;
		datos[i][datos[0].size()-1]=aux_result;	
		
	}
	return costo;
}

int main(){
	lista cifras ={1,2,3,4,5,6,7,8,9,0};
	lista multiplicador={1,2,3,4,5};
	int filas=cifras.size()+multiplicador.size();
	
	matriz datos(filas,lista(multiplicador.size()+1));
	mostrar(datos);
	cout<<endl;
	cout<<multicole(datos,cifras,multiplicador)<<endl;
	mostrar(datos);
	return 0;
}