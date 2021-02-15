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
typedef vector<vector<data>> matriz;
#define MAX_RAND 10
#define MIN_RAND -10
#define MAX_POBLATION 8
#define ALPHA 0.5
#define CROOS_PER 0.8
#define MUT_PER 0.05
#define ITER 1500

int randomWithProb(data p) {
    data rndDouble = (data)rand() / RAND_MAX;
    return rndDouble < p;
}

matriz initial_poblation (MAX_POBLATION,vector<data>(3,0));

matriz new_poblation =initial_poblation;
lista fitness_contariner;

data function(data x, data y){
	return -cos(x) * cos(y) * exp(-pow(x-M_PI,2)-pow(y-M_PI,2));
	//return pow(x+2*y-7,2)+pow(2*x+y-5,2);
}

data get_rand(){
	int aux_rand = rand() % MAX_RAND*2 + MIN_RAND;
	data multi_rand = (data)rand() / RAND_MAX*1.0 -1.0;
	data float_rand=double(aux_rand)*multi_rand+multi_rand;
	return float_rand;
}

data croosing_BLX(data x, data y){
	cout<<"valores recibidos"<< x<< "  "<<y<<endl;
	data beta=get_rand();
	while(beta>(1+ALPHA) || beta<(-ALPHA)){
		beta=get_rand();
	}
	cout<<"\tBeta: "<<beta<<endl;
	return x +(beta*(y-x));
}

void get_fitnes(){
	for (int i=0;i<initial_poblation.size();i++){
		initial_poblation[i][2]=function(initial_poblation[i][0],initial_poblation[i][1]);
	}
}

void show_container(){
	for (int i =0;i<fitness_contariner.size();i++)
		cout<< fitness_contariner[i]<<endl;
}
void create(){
	for (int i=0 ; i<initial_poblation.size() ; i++){
		for (int j=0 ; j<2 ; j++){
			initial_poblation[i][j]=get_rand();
		}
	}
}

void show_matrix(){
	for (int i=0;i<initial_poblation.size();i++){
		cout<<i+1<<")\t[ ";
		for (int j = 0; j <2; j++){
			cout<<initial_poblation[i][j];
			if(j==0)
				cout<<"  ,  ";
		}
		cout<<" ]"<<endl;
	}
}

void show_fitnes(){
	for (int i=0;i<initial_poblation.size();i++){
		cout<<i+1<<")\t[ ";
		for (int j = 0; j <2; j++){
			cout<<initial_poblation[i][j];
			if(j==0)
				cout<<"  ,  ";
		}
		cout<<" ]"<<"  =>  "<<initial_poblation[i][2]<<endl;
	}
}

void mating_pool(){
	int copy_maxpoblation=MAX_POBLATION;
	while(copy_maxpoblation){
		int first = rand()% (MAX_POBLATION) +1;
		int second = rand()% (MAX_POBLATION) +1;
		int winner=first;
		if (initial_poblation[first-1][2]>initial_poblation[second-1][2])
			winner=second;
		fitness_contariner.push_back(winner);
		
		copy_maxpoblation--;
		cout<<first<<"  -  "<<second<<"\t=>\t"<<winner<<"\t=>\t[ "<<initial_poblation[winner-1][0]<<" , "<<initial_poblation[winner-1][1]<<" ]"<<endl;
	}
	cout<<endl;
	//show_container();
}
void select_parents(){
	int copy_maxpoblation=MAX_POBLATION;
	int iterator=0;
	while (copy_maxpoblation){
		int mutation_pos= iterator%2;
		int first = rand()% (MAX_POBLATION) +1;
		int second = rand()% (MAX_POBLATION) +1;
		while(second==first)
			second = rand()% (MAX_POBLATION) +1;
		
		cout<<"["<<iterator+1<<"] "<<"Selección de Padres"<<endl
			<<"\t"<<first<<" - "<<second<<" => "<< fitness_contariner[first-1]<< " - "<<fitness_contariner[second-1]<< " => ["
			<<initial_poblation[(fitness_contariner[first-1])-1][0]<<" , "<<initial_poblation[(fitness_contariner[first-1])-1][1]<<"] - ["
			<<initial_poblation[(fitness_contariner[second-1])-1][0]<< " - "<< initial_poblation[(fitness_contariner[second-1])-1][1]<<"]"<<endl;
		//!: HERE APPLYING PROB OF CROSSING OF [CROSS_PER] 
		if (randomWithProb(CROOS_PER)){
			cout<<"Con Cruzamiento"<<endl;
			new_poblation[iterator][0]=croosing_BLX(initial_poblation[(fitness_contariner[first-1])-1][0],initial_poblation[(fitness_contariner[second-1])-1][0]);
			new_poblation[iterator][1]=croosing_BLX(initial_poblation[(fitness_contariner[first-1])-1][1],initial_poblation[(fitness_contariner[second-1])-1][1]);
			cout<<"\t["<<new_poblation[iterator][0]<<" , "<<new_poblation[iterator][1]<<"]"<<endl;
		}
		else {
			cout<<"Sin Cruzamiento"<<endl;
			if (initial_poblation[first-1][2]<initial_poblation[second-1][2]){
				new_poblation[iterator][0]=initial_poblation[(fitness_contariner[first-1])-1][0];
				new_poblation[iterator][1]=initial_poblation[(fitness_contariner[first-1])-1][1];
			}
			else{
				new_poblation[iterator][0]=initial_poblation[(fitness_contariner[second-1])-1][0];
				new_poblation[iterator][1]=initial_poblation[(fitness_contariner[second-1])-1][0];
			}
			cout<<"\t["<<new_poblation[iterator][0]<<" , "<< new_poblation[iterator][1]<<"]"<<endl<<endl;
		}
		//!: HERE APPLYING PROB OF MUTATION [MUT_PER]
		if (randomWithProb(MUT_PER)){
			cout<<"Con Mutacion"<<endl;
			new_poblation[iterator][mutation_pos]=get_rand();
			cout<<"\t["<<new_poblation[iterator][0]<<" , "<< new_poblation[iterator][1]<<"]"<<endl<<endl;
		}
		else 
			cout<<"Sin Mutacion"<<endl<<endl;
		copy_maxpoblation--;
		iterator++;
		
	}
	initial_poblation=new_poblation;
	cout<<"Nueva Poblacion"<<endl;
	show_matrix();
}

void run(){
	create();
	show_matrix();
	int copy_iter=ITER;
	while(copy_iter){
		cout<<endl<<"Calcular la Aptitud para cada Individudo"<<endl;
		get_fitnes();
		show_fitnes();
		cout<<endl<<"**** Iteración "<<(ITER-copy_iter)+1<<"****"<<endl
			<<"Creación de Mating Pool"<<endl;
		mating_pool();
		select_parents();
		copy_iter--;
		fitness_contariner.clear();
	}
	cout<<endl<<"*******  Resultado final  *******"<<endl;
	get_fitnes();
	show_fitnes();
}


int main(){
	setprecision(6);
	srand (time(NULL));
	cout<<"Parámetros"<<endl<<"- Cantidad de Individuos: "<<MAX_POBLATION<<endl
		<<"- Cantidad de Genes por Individuo: 2"<<endl
		<<"- Selección por torneo (2)"<<endl
		<<"- Probabilidad de Cruzamiento: " <<CROOS_PER<<endl
		<<"- Cruzamiento BLX-Alpha, Alpha= "<< ALPHA<<endl
		<<"- Probabilidad de Mutación: "<<MUT_PER<<endl
		<<"- Mutación Uniforme"<<endl
		<<"- Cantidad de Iteraciones: "<< ITER<<endl<<endl
		<<"Poblacion Inicial"<<endl;
	run();
	return 0;
}