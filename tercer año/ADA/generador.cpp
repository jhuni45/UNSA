#include <iostream>
#include <time.h>
#include <stdlib.h> 
using namespace std;

int main (){
	//vector<int> myvector;
	srand (time(NULL));
	int valor;
	for (int i=0;i<1000;i++){
		for (int j=0;j<i;j++){
			valor = rand ()% 100 + 0;
			cout<<valor<<" ";
			//myvector.push_back(valor);
		}
		cout<<endl;
	}
	
}
//tiempo
//clock_t;
//((float)TBubble)/CLOCKS_PER_SEC

//leer archivo
/*
ifstream input;
input.open("archivo.txt");
string linea;
while(getline(input,letra)){
	letra tiene la linea;
}
//para ofstream
ofstream output;
output.open("archivo.txt");
output<<"cadena"<<endl;

*/
