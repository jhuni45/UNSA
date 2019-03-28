#include <iostream>
using namespace std;

void verificar(string cadena){
	int media=cadena.length()/2;
	if (cadena.length()%2==0){
		cout<<"La cadena no contiene inversa"<<endl;
		return;
	}
	if (cadena[media]!='&'){
		cout<<"El separador no es '&' . . . "<<endl;
	}
	for(int i=0;i<media;i++){
		if (cadena[i]!=cadena[cadena.length()-1-i]){
			cout<<"La cadena Y no es invesa de X"<<endl;
			return;
		}
	}
	cout<<"La cadena Y si es inversade de X"<<endl;

}
int main(){
	int op;
    string cadena;
	cout<<"****Problema 15.3*****\nIngresa una cadena de texto (Dividido por &)"<<endl;
	getline(cin,cadena);
    verificar(cadena);
    cout<<endl;
	return 0;
}