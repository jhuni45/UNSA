#include<bits/stdc++.h>

using namespace std;

#define N 8
#define ITER 2

typedef int value;
typedef vector<value> lista;
typedef vector<lista> matriz;

matriz cromosomas;
matriz poblation;
ofstream out;

void show_matrx(matriz a){
	for (int i=0;i<a.size();i++){
		cout<<i+1<<") [";
		for (int j=0;j< a[0].size();j++){
			if (j%3==0 && j!=0){
				cout<<"]\t[";
				cout<<a[i][j]<< " ";
			}
			else
				cout<<a[i][j]<<" ";
		}		
		cout<<endl;
	}
	cout<<endl;
}

void show_list(lista a){
	for (int i =0; i< a.size();i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

lista adding(int a, int b, int c){
	lista temp;
	temp.push_back(a);
	temp.push_back(b);
	temp.push_back(c);

	return temp;
}

void read(){
	ifstream input;
	input.open("input.txt");
	int left, right, valor;
	while (input>>left>>right>>valor){
	 	cromosomas.push_back(adding(left,right,valor));
	}
	input.close();
	show_matrx(cromosomas);
}

void create(){
	for (int k=0; k<N; k++){
		lista newcromo;
		int acum=0;
		for (int j=0; j<cromosomas.size()/3; j++){
			int init = rand ()% cromosomas.size();
			for (int i=0; i < 3; i++){
				acum+=cromosomas[init][2];
				newcromo.push_back(init);
				int aleatorio = rand () % 1;
				init=cromosomas[init][aleatorio];
			}
		}
		newcromo.push_back(acum);
		poblation.push_back(newcromo);
	};
	
	show_matrx(poblation);
	
}

lista best(){
	int bes=poblation[0][poblation[0].size()-1], index=0;
	for (int i=0; i< poblation.size();i++){
		if (poblation[i][poblation[0].size()-1]>bes){
			index=i;
			bes=poblation[i][poblation[0].size()-1];
		}
	}
	lista temp=poblation[index];
	return temp;
}

void show_nodes(lista a){
	out.open("finalinput.txt");
	int index=0;
	for (int i=0 ;i< cromosomas.size()/3;i++){
		for (int j=0; j<3; j++){
			out<<i <<" "<<a[index]<<endl;
			index++;
		}
	}
	out.close();
}

void run (){
	lista best_list;
	create();
	best_list =best();
	cout<<"*** Mayor grado delictivo ***"<<endl;
	show_list(best_list);
	show_nodes(best_list);
}

int main (){
	srand(time(NULL));
	cout<<"***  Parametros  ****"<<endl;
	read();
	cout<<"tamano= "<<cromosomas.size()<<endl;
	run ();

	return 0;
}