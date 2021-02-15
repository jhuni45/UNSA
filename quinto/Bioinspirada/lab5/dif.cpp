#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <tuple>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

using namespace std;
typedef double data;
typedef vector<data> lista;
typedef vector<lista> matriz;
#define MAX_RAND 10
#define MIN_RAND -10
#define MAX_POBLATION 12
#define C_MUT 1.5
#define C_CROSS 0.6
#define ITER 200

matriz initial_poblation (MAX_POBLATION,vector<data>(5,0));

matriz new_poblation =initial_poblation;
lista fitness_contariner;

data function(data x, data y, data a, data b){
	return pow(x+2*y-7, 2) + pow(2*x+ y-5, 2) + pow(a + 2*b-7, 2) + pow(2*a+ b-5, 2);
}

data get_rand(){
	int aux_rand = rand() % MAX_RAND*2 + MIN_RAND;
	data multi_rand = (data)rand() / RAND_MAX*1.0 -1.0;
	data float_rand=double(aux_rand)*multi_rand+multi_rand;
	return float_rand;
}


void show_container(){
	for (int i =0;i<fitness_contariner.size();i++)
		cout<< fitness_contariner[i]<<endl;
}

void show_matrix(matriz initial_poblation){
	for (int i=0;i<initial_poblation.size();i++){
		cout<<i+1<<")\t[ ";
		for (int j = 0; j <4; j++){
			cout<<initial_poblation[i][j]<< ", ";
		}
		cout<<" ]"<<endl;
	}
	cout<<endl;
}

void get_fitnes(){
	for (int i=0;i<initial_poblation.size();i++){
		initial_poblation[i][4]=function(initial_poblation[i][0],initial_poblation[i][1],initial_poblation[i][2],initial_poblation[i][3]);
	}
}

void show_fitnes(){
	for (int i=0;i<initial_poblation.size();i++){
		cout<<i+1<<")\t[ ";
		for (int j = 0; j <4; j++){
			cout<<initial_poblation[i][j]<<" , ";
		}
		cout<<" ]"<<"  =>  "<<initial_poblation[i][4]<<endl;
	}
	cout<<endl;
}


void create(){
	for (int i=0 ; i<initial_poblation.size() ; i++){
		for (int j=0 ; j<4 ; j++){
			initial_poblation[i][j]=get_rand();
		}
	}
}

lista get_mutation(lista first, lista second, lista third){
	lista aux;
	cout<<"xk - kl (Vector de Diferencias): =>  [";
	for (int i=0; i< first.size()-1; i++){
		cout<<second[i]-third[i]<<" , ";
		aux.push_back(second[i]-third[i]);
	}
	cout<<" ]"<<endl;
	cout<<"F*(xk - xl) (Vector D Ponderado) =>  [";
	lista aux2;
	for (int i=0; i< first.size()-1; i++){
		cout<<C_MUT* aux[i]<<" , ";
		aux2.push_back(C_MUT*aux[i]);
	}
	cout<<" ]"<<endl;
	cout<<"xm + F*(xk - xl) (Vector Mutado) =>  [";
	lista aux3;
	for (int i=0; i< first.size()-1; i++){
		cout<<first[i]+ aux2[i]<<" , ";
		aux3.push_back(first[i]+aux2[i]);
	}
	cout<<" ]"<<endl<<endl;
	return aux3;
}

void get_cross(lista pos, lista mut, int x){
	lista mask;
	cout<<"Cruzamiento "<<endl;
	for (int i=0; i<mut.size(); i++){
		mask.push_back(1.0000 * (rand() % 10001) / 10000);
		cout<<mask[i]<<endl;
	}
	cout<<endl<<"Trial Vector => [  ";
	for (int i=0; i<mut.size(); i++){
		if (mask[i]>=C_CROSS)
			mut[i]=pos[i];
		cout<<mut[i]<<" , ";
	}
	data  fit=function(mut[0],mut[1],mut[2],mut[3]);
	cout<<"]\nNuevo fitness: "<<fit<<"\tFitness de vector actual: "<<pos[4]<<endl;
	if (fit < pos[4]){
		cout<<"El vector target es reemplazado por el vector trial en la siguiente población"<<endl;
		for (int i=0;i< mut.size();i++){
			pos[i] = mut[i];
		}
	}
	else{
		cout<<"El vector target continua en la siguiente problación."<<endl;
	}
	new_poblation[x]=pos;
	cout<<endl;
}

void run(){
	cout<<"Poblacion inicial"<<endl;
	create();
	show_matrix(initial_poblation);
	cout<<"Hallamos aptitud para cada individuo"<<endl;
	get_fitnes();
	show_fitnes();
	int c_iter=ITER;
	while (c_iter){
		cout<<"**** Iteracion "<<ITER-c_iter<<"****"<<endl;
		for (int i=0; i< initial_poblation.size();i++){
			cout<<"========================================="<<endl;
			cout<<"**** Vector "<<i+1<<" ****"<<endl;
			int rand1 = rand()% MAX_POBLATION, rand2 = rand()% MAX_POBLATION, rand3 = rand()% MAX_POBLATION;
			while (rand1==i){
				rand1=rand()% MAX_POBLATION;
			}
			while (rand1==rand2 || rand2==i){
				rand2=rand()% MAX_POBLATION;	
			}
			while(rand3==rand1 || rand3==rand2 || rand3==i){
				rand3=rand()% MAX_POBLATION;	
			}
			cout<<"xm = "<<rand1+1<<"\txk = "<<rand2+1<<"\txl = "<<rand3+1<<endl;
			lista aux=get_mutation(initial_poblation[rand1], initial_poblation[rand2], initial_poblation[rand3]);
			get_cross(initial_poblation[i], aux,i);
			
		}
		cout<<"Nueva poblacion"<<endl;
		initial_poblation=new_poblation;
		get_fitnes();
		show_fitnes();
		c_iter--;
	}
}

int main (){
	srand(time(NULL));
	cout<<"Parametros:"<<endl
		<<"\tPoblacion: "<<MAX_POBLATION<<endl
		<<"\tConstante de mutacion: "<<C_MUT<<endl
		<<"\tConstante de cruzamiento: "<<C_CROSS<<endl
		<<"\tIteraciones: "<<ITER<<endl<<endl;
	run();
}