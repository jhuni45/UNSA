#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
///507 jill's ride
using namespace std;

void mostrar (vector<int> A){
	cout<<"vecor..asdasdas"<<endl;
	for (int i =0;i<A.size();i++){
		cout<<A[i]<<" ";
	}
	cout<<endl;
}
int sumamaxima(vector<int> A,int p,int r){
	if (p==r){
		return max(0,A[p]);
	}
	int maxizq, maxder,maxder2,maxizq2,suma;
	int q=floor((p+r)/2);
	maxizq=sumamaxima(A,p,q);
	maxder=sumamaxima(A,q+1,r);
	suma=A[q];
	maxizq2=suma;
	for (int i=q-1;i>=p;i--){
		suma=suma+A[i];
		maxizq2=max(maxizq2,suma);
	}
	suma=A[q+1];
	maxder2=suma;
	for (int f=q+2;f<=r;f++){
		suma=suma+A[f];
		maxder2=max(maxder2,suma);
	}
	int maxcruz;
	maxcruz=maxizq2+maxder2;
	return max(maxizq,max(maxcruz,maxder));
}
int main(){
	vector<int> A={-3,-2,1,5,8};
	cout<<sumamaxima(A,0,A.size()-1);
	cout<<endl;
	int ruta,parada,puntos;
	cin>>ruta;
	while(ruta){
		cin>>parada;
		vector<int> listapuntos;
		while(parada-1){
			cin>>puntos;
			listapuntos.push_back(puntos);
			//sumamaxima(listapuntos);
			parada--;
		}
		mostrar(listapuntos);

		ruta--;
	}
	return 0;
}
