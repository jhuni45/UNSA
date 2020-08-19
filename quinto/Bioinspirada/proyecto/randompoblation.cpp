#include<bits/stdc++.h>

using namespace std;

ofstream out;

void generar(int limite){

	for (int i =0; i<limite;i++){
		int left = rand () % limite, right= rand()%limite;
		while ((left == i || right == i ) || left == right){
			left = rand () % limite;
			right= rand() % limite;
		}
		int valor = rand()% 50;
		out<<left<<" "<<right<<" "<<valor<<endl;
	}
}

int main(int argc,char* argv[]){
	out.open("input.txt");
	int limite=atoi(argv[1])-1;
	srand(time (NULL));
	generar(limite);
	out.close();
	return 0;
}