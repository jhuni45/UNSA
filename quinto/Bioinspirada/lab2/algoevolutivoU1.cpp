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
#define DELTA 0.2
#define MU 8
#define ITER 500
#define N 2
#define LAMBDA 12

data TRIANGULE_DELTA= 1.0000/(sqrt(2*sqrt(N)));

matriz initial_poblation (MU,vector<data>(5,0));

lista fitness_contariner;
matriz new_poblation (LAMBDA,vector<data>(5,0));
matriz aux_poblation=new_poblation;


data get_rand(){
	int aux_rand = rand() % MAX_RAND*2 + MIN_RAND;
	data multi_rand = (data)rand() / RAND_MAX*1.0 -1.0;
	data float_rand=double(aux_rand)+multi_rand;
	return float_rand;
}

void show_matrix(matriz initial_poblation){
	for (int i=0;i<initial_poblation.size();i++){
		cout<<"\t"<<i+1<<")  [ ";
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


data normal(double  x, double desviacion) {
    double numerador = exp(-0.5 * pow(x / desviacion, 2));
    double denominador = desviacion * sqrt(2 * M_PI);
    return numerador / denominador;
}


data valorX(double limInf, double limSup, double desviacion, double delta, double aleatorio){
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

void get_croos(int pos){
	//!: here to calculate the first parent
	int first = rand()% (MU);
	int second = rand()% (MU);
	int winner1=first;
	if (initial_poblation[first][4]>initial_poblation[second][4]){
		winner1=second;
	}
	int first2 = rand()% (MU);
	int second2 = rand()% (MU);
	int winner2=first2;
	if (initial_poblation[first2][4]>initial_poblation[second2][4]){
		winner2=second;
	}
	cout<<"\tCruzamiento"<<endl
		<<"\t  Padre 1: "<< first+1<<" - "<<second+1<<" => "<<winner1+1<<" ["
		<<initial_poblation[winner1][0]<<" - "<<initial_poblation[winner1][1]<<"] \t["
		<<initial_poblation[winner1][2]<<" - "<<initial_poblation[winner1][3]
		<<endl
		<<"\t  Padre 2: "<< first2+1<<" - "<<second2+1<<" => "<<winner2+1<<" ["
		<<initial_poblation[winner2][0]<<" - "<<initial_poblation[winner2][1]<<"] \t["
		<<initial_poblation[winner2][2]<<" - "<<initial_poblation[winner2][3]<<" ]"
		<<endl;
	new_poblation[pos][0]=(initial_poblation[winner1][0]+initial_poblation[winner2][0])/2.0;
	new_poblation[pos][1]=(initial_poblation[winner1][1]+initial_poblation[winner2][1])/2.0;
	new_poblation[pos][2]=sqrt(initial_poblation[winner1][2]*initial_poblation[winner2][2]);
	new_poblation[pos][3]=sqrt(initial_poblation[winner1][3]*initial_poblation[winner2][3]);
	cout<<"\tResultado de cruzamiento:"<<endl<<"  ";
	show_matrix(new_poblation);
	//!: here calculate new delta
	data first_rand = 1.0000 * (rand() % 10001) / 10000;
	data second_rand = 1.0000 * (rand() % 10001) / 10000;
	while (first_rand >= TRIANGULE_DELTA && second_rand>=TRIANGULE_DELTA){
		first_rand = 1.0000 * (rand() % 10001) / 10000;
		second_rand = 1.0000 * (rand() % 10001) / 10000;
	} 

	data _first= valorX(-10,10,TRIANGULE_DELTA,0.0001,first_rand);
	data _second= valorX(-10,10,TRIANGULE_DELTA,0.0001,second_rand);
	cout<<"\tMutacion"<<endl<<"\t  Aleatorios para los deltas"<<endl;
	cout<<"\t    Numero aleatorio 1:  "<<first_rand<<"\t Numero gaussiano 1:  "<<_first<<endl;
	cout<<"\t    Numero aleatorio 2:  "<<second_rand<<"\t Numero gaussiano 2:  "<<_second<<endl;
	new_poblation[pos][2]=new_poblation[pos][2]*exp(_first);
	new_poblation[pos][3]=new_poblation[pos][3]*exp(_second);
	
	// !: To calculare x and y
	first_rand = 1.0000 * (rand() % 10001) / 10000;
	second_rand = 1.0000 * (rand() % 10001) / 10000;
	while (first_rand >= new_poblation[pos][2] && second_rand>=new_poblation[pos][3]){
		first_rand = 1.0000 * (rand() % 10001) / 10000;
		second_rand = 1.0000 * (rand() % 10001) / 10000;
	}
	_first= valorX(-10,10,new_poblation[pos][2],0.001,first_rand);
	_second= valorX(-10,10,new_poblation[pos][3],0.001,second_rand);
	cout<<"\t  Aleatorios para los puntos x-y"<<endl;
	cout<<"\t    Numero aleatorio 1:  "<<first_rand<<"\t Numero gaussiano 1:  "<<_first<<endl;
	cout<<"\t    Numero aleatorio 2:  "<<second_rand<<"\t Numero gaussiano 2:  "<<_second<<endl;
	new_poblation[pos][0]=new_poblation[pos][0]+_first;
	new_poblation[pos][1]=new_poblation[pos][1]+_second;
}
void erase_minor(matriz &aux_matrix){
	cout<<"Borrando "<<LAMBDA<<" elemetos: "<<endl;
	for (int i=0;i<LAMBDA;i++){
		data mayor=aux_matrix[0][4];
		int pos_winner=0;
		for (int j=0;j< aux_matrix.size();j++){
			if (aux_matrix[j][4]>mayor){
				mayor=aux_matrix[j][4];
				pos_winner=j;
			}
		}
		aux_matrix.erase(aux_matrix.begin()+pos_winner);
	}
}

void run (){
	cout<<"Estrategia Mu , o (u,o)"<<endl<<"Parámetros"<<endl
		<<"- Cantidad de Individuos (Mu): "<<MU<<endl
		<<"- Cantidad de Descendientes (Lambda): "<<LAMBDA<<endl
		<<"- Cantidad de Genes por Individuo: 2"<<endl
		<<"- Selección por torneo (2)"<<endl
		<<"- Cantidad de Iteraciones: "<< ITER<<endl<<endl
		<<"Poblacion Inicial"<<endl;
	create(DELTA);
	show_matrix(initial_poblation);
	cout<<"Calcular la Aptitud para cada Individudo"<<endl;
	get_fit(initial_poblation);
	show_matrix(initial_poblation);
	int copy_iter=ITER;	
	while(copy_iter){
		int copy_lambda=LAMBDA;
		cout<<"****** Iteracion "<<ITER-copy_iter+1<<"******"<<endl<<"\tENTRADA:\n";
		show_matrix(initial_poblation);
		while(copy_lambda){
			cout<<"Generar descendiente "<<LAMBDA-copy_lambda<<endl;
			get_croos(LAMBDA- copy_lambda);
			get_fit(new_poblation);
			cout<<"\t Nuevo hijo:"<<endl;
			show_matrix(new_poblation);
			initial_poblation.push_back(new_poblation[LAMBDA- copy_lambda]);
			copy_lambda--;
		}		
		show_matrix(initial_poblation);
		erase_minor(initial_poblation);
		show_matrix(initial_poblation);
		new_poblation=aux_poblation;
		copy_iter--;	
	}


}

int main(){
	srand (time(NULL));
	run();
	return 0;
}