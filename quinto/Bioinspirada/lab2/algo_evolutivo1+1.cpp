#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <tuple>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <random>
#include <algorithm>

using namespace std;

typedef double data;
typedef vector<data> lista;
typedef vector<vector<data>> matriz;

#define MAX_RAND 10
#define MIN_RAND -10
#define ITER 300
#define DELTA 0.2

int MAX_POBLATION=1;

matriz initial_poblation (MAX_POBLATION,vector<data>(5,0));

lista fitness_contariner;
matriz new_poblation =initial_poblation;

data get_rand(){
	int aux_rand = rand() % MAX_RAND*2 + MIN_RAND;
	data multi_rand = (data)rand() / RAND_MAX*1.0 -1.0;
	data float_rand=double(aux_rand)+multi_rand;
	return float_rand;
}

void show_matrix(matriz initial_poblation){
	for (int i=0;i<initial_poblation.size();i++){
		cout<<i+1<<")  [ ";
		for (int j = 0; j <initial_poblation[0].size(); j++){
			cout<<initial_poblation[i][j];
			cout<<"  ,  ";
		}
		cout<<" ]"<<endl;
	}
	cout<<endl;
}

void create(data o_inicial){
	for (int i=0 ; i<initial_poblation.size() ; i++){
		for (int j=0 ; j<2 ; j++){
			initial_poblation[i][j]=get_rand();
			initial_poblation[i][j+2]=o_inicial;
		}
	}
}

data function(data x, data y){
	return -cos(x) * cos(y) * exp(-pow(x-M_PI,2)-pow(y-M_PI,2));
}


data a_distribution(data mu, data sigma, data x){
	return (1/(sigma*sqrt(2*M_PI))) * (exp (- (pow(x-mu,2))/(2*pow(sigma,2))  )  ) ;
}


data normal(double  x, double desviacion) {
	setprecision(5);
    double numerador = exp(-0.5 * pow(x / desviacion, 2));
    double denominador = desviacion * sqrt(2 * M_PI);
    return numerador / denominador;
}


data valorX(double limInf, double limSup, double desviacion, double delta, double aleatorio){
	setprecision(5);
	double area = 0;
	double baseMenor = normal(limInf, desviacion);
	double baseMayor;

	for(double i = limInf + delta ;i < limSup; i += delta){
		baseMayor = normal(i, desviacion);
		area += (baseMayor + baseMenor);
		if(area *(delta / 2) > aleatorio)
			return i;
		baseMenor = baseMayor;
	}
	return area ;
}

void get_fit(matriz &aux_poblation){
	for (int i=0;i<aux_poblation.size();i++){
		aux_poblation[i][aux_poblation[0].size()-1]=
			function(aux_poblation[i][0],aux_poblation[i][1]);
	}
}

void get_mutation(int pos){
	setprecision(5);
	data first = 1.0000 * (rand() % 10001) / 10000;
	data second = 1.0000 * (rand() % 10001) / 10000;
	data _first= valorX(-10,10,initial_poblation[pos][2],0.0001,first);
	data _second= valorX(-10,10,initial_poblation[pos][2],0.0001,second);
	cout<<"\tNumero aleatorio 1:  "<<first<<"\tNumero gaussiano 1:  "<<_first<<endl;
	cout<<"\tNumero aleatorio 2:  "<<second<<"\tNumero gaussiano 2:  "<<_second<<endl;
	new_poblation[pos][0]=initial_poblation[pos][0]+_first;
	new_poblation[pos][1]=initial_poblation[pos][1]+_second;
	cout<<"\t";
	get_fit(new_poblation);

	cout<<"Aptitud de hijo resultante"<<endl;
	cout<<"\t[ "<<new_poblation[pos][0]<<" , "<<new_poblation[pos][1]<<" ]\t"<<new_poblation[pos][4]<<endl; 
	if (new_poblation[pos][4]<=initial_poblation[pos][4]){
		cout<<"\tES MENOR"<<endl;
		initial_poblation[pos][4]=new_poblation[pos][4];
		initial_poblation[pos][2]=initial_poblation[pos][2]*1.5;
		initial_poblation[pos][3]=initial_poblation[pos][3]*1.5;
		initial_poblation[pos][0]=new_poblation[pos][0];
		initial_poblation[pos][1]=new_poblation[pos][1];
	}
	else{
		cout<<"\tES MAYOR"<<endl;
		initial_poblation[pos][2]=initial_poblation[pos][2]*pow(1.5,-1.0/4);
		initial_poblation[pos][3]=initial_poblation[pos][3]*pow(1.5,-1.0/4);
	}
	cout<<"\tSALIDA: "<<endl<<"\t =>  ";
	show_matrix(initial_poblation);
}

void run (){
	MAX_POBLATION=1;
	cout<<"Estrategia 1+1"<<endl<<"Parámetros"<<endl
		<<"- Cantidad de Individuos: "<<MAX_POBLATION<<endl
		<<"- Cantidad de Genes por Individuo: 2"<<endl
		<<"- Cantidad de Iteraciones: "<< ITER<<endl<<endl
		<<"Poblacion Inicial"<<endl;
	create(DELTA);
	cout<<"Calcular la Aptitud para cada Individudo"<<endl;
	get_fit(initial_poblation);
	show_matrix(initial_poblation);
	int copy_iter=ITER;
	while(copy_iter){
		cout<<"****** Iteracion "<<ITER-copy_iter+1<<"******"<<endl<<"\tENTRADA:\n\t =>  ";
		show_matrix(initial_poblation);
		get_mutation(0);
		copy_iter--;
	}
}
int main(){
	srand (time(NULL));
	MAX_POBLATION=1;
	run();
	return 0;
}