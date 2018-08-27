#include <iostream>
#include <vector>

using namespace std;

typedef vector< vector<int> > matriz;

vector<int> pedir(){
	vector<int> AUX;
	string flag="si";
	while(flag=="si"){
		int a;
		cin>>a;
		AUX.push_back(a);
		cout<<"ingresar? si/no"<<endl;
		cin>>flag;
	}
	return AUX;
}
void mostrar (matriz A){
	for (int i=0;i< A.size();i++){
		for (int j=0;j<A[0].size();j++){
			cout<<A[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}
void cubetasort(vector<int> lista){
	matriz proceso(5,vector<int>(10,0));
	int numPro=3;
	cout<<"lista creada"<<endl;
	mostrar(proceso);
	int div=1;
	for (int i=0;i<numPro;i++){
		for (int j=0;j<lista.size();j++){
			int a=(lista[j]/div )% 10;
			cout<<"digito: "<<lista[j]<<endl;
			cout<<"numero: "<<a<<endl;
			proceso[4][a]=lista[j];
		}
			div=10;

	}
	cout<<"final"<<endl;
	mostrar(proceso);

}
int main (){
	vector<int> estatico={64,8,216,512,27,729,0,1,343,125};
	vector <int> listaN;
	listaN.push_back(10);
	//cout<<"Ingresa numeros"<<endl;
	//listaN=pedir();	
	cubetasort(estatico);
	return 0 ;

}
