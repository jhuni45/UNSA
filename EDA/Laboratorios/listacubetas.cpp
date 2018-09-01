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
			cout<<A[i][j]<<"\t";
		}
		cout<<endl;
	}
	cout<<endl;
}
matriz cubetasort(matriz lista,int div){
	int a;
	matriz proceso(lista.size(),vector<int>(lista.size(),-1));
	for (int i=0;i<lista.size();i++){
		for (int j=lista.size()-1;j>=0;j--){
			int aux=lista.size()-1;
			if (lista[j][i]!=-1){
				a=(lista[j][i]/div)%10;
				while(proceso[aux][a]!=-1){
					aux--;
				}
				proceso[aux][a]=lista[j][i];
			}
		}

	}
	mostrar(proceso);
	return proceso;
}
int main (){
	vector<int> estatico={64,8,216,512,27,729,0,1,343,125};
	matriz proceso(estatico.size(),vector<int>(estatico.size(),-1));
	proceso[estatico.size()-1]=estatico;
	cout<<"original"<<endl;	
	mostrar(proceso);
	int veces=3;
	int div=1;
	while(veces){
		cout<<"proceso: "<<veces<<endl;
		proceso=cubetasort(proceso,div);
		div*=10;
		veces--;
	}
	return 0 ;
}
