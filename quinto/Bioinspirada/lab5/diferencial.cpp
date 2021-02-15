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
#define MAX_POBLATION 8
#define C_MUT 1.2
#define C_CROSS 0.5
#define ITER 2

//matriz initial_poblation (MAX_POBLATION,vector<data>(5,0));

matriz initial_poblation = {
{ 6.76492979, 4.96256547, 6.84467054, 2.5141087  },
{ 6.34118805, -4.08622839, 5.70461664, 9.95114942  },
{ -1.18766907, -0.02087546, 2.8925005, -9.76461926  },
{ 2.040909369, 1.94034545, -1.44980587, -7.96088503 },
{ -1.9546888, -7.74644854, 1.21461346, 1.83323939  },
{ -3.871868, 5.91565067, 2.6879638, -2.13548988   },
{ -6.48326847, 8.42080431, 7.0924261, -9.28208046 },
{ 2.71475488, -5.3263638, -9.64269313, 2.42840015  }
};

matriz new_poblation =initial_poblation;
lista fitness_contariner;

int randomWithProb(data p) {
    data rndDouble = (data)rand() / RAND_MAX;
    return rndDouble < p;
}

data function(data x, data y, data a, data b){
	return pow(x+2*y-7, 2) + pow(2*x+ y-5, 2) + pow(a + 2*b-7, 2) + pow(2*a+ b-5, 2);
	//return pow(x+2*y-7,2)+pow(2*x+y-5,2);
}

data get_rand(){
	int aux_rand = rand() % MAX_RAND*2 + MIN_RAND;
	data multi_rand = (data)rand() / RAND_MAX*1.0 -1.0;
	data float_rand=data(aux_rand)*multi_rand+multi_rand;
	return float_rand;
}


void show_container(){
	for (int i =0;i<fitness_contariner.size();i++)
		cout<< fitness_contariner[i]<<endl;
}

void show_matrix(){
	for (int i=0;i<initial_poblation.size();i++){
		cout<<i+1<<")\t[ ";
		for (int j = 0; j <4; j++){
			cout<<initial_poblation[i][j]<< ", ";
		}
		cout<<" ]"<<endl;
	}
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
}


void create(){
	for (int i=0 ; i<initial_poblation.size() ; i++){
		for (int j=0 ; j<4 ; j++){
			initial_poblation[i][j]=get_rand();
		}
	}
}
void suma(lista first, lista second, lista third){
	lista aux;
	cout<<"\nsuma :  ";
	for (int i=0; i< first.size(); i++){
		cout<<second[i]-third[i]<<" , ";
		aux.push_back(second[i]-third[i]);
	}
	cout<<endl;
	cout<<"constante =>  ";
	lista aux2;
	for (int i=0; i< first.size(); i++){
		cout<<1.2* aux[i]<<" , ";
		aux2.push_back(C_MUT*aux[i]);
	}
	cout<<endl;
	cout<<"rpta =>  ";
	lista aux3;
	for (int i=0; i< first.size(); i++){
		cout<<first[i]+ aux2[i]<<" , ";
		aux3.push_back(first[i]*aux[i]);
	}
	cout<<endl;
	cout<<"nuevo fitness  "<<setprecision(10)<<function(6.76492979, 4.96256547, 6.84467054, 2.5141087)<<endl;
	cout<<"nuevo fitness  "<<setprecision(10)<<function(6.34118805, -4.08622839, 5.70461664, 9.95114942)<<endl;
	cout<<"nuevo fitness  "<<setprecision(10)<<function(-1.18766907, -0.02087546, 2.8925005, -9.76461926)<<endl;
	cout<<"nuevo fitness  "<<setprecision(10)<<function(2.040909369, 1.94034545, -1.44980587, -7.96088503)<<endl;
	cout<<"nuevo fitness  "<<setprecision(10)<<function(-1.9546888, -7.74644854, 1.21461346, 1.83323939)<<endl;
	cout<<"nuevo fitness  "<<setprecision(10)<<function(-3.871868, 5.91565067, 2.6879638, -2.13548988)<<endl;
	cout<<"nuevo fitness  "<<setprecision(10)<<function(-6.48326847, 8.42080431, 7.0924261, -9.28208046)<<endl;
	cout<<"nuevo fitness  "<<setprecision(10)<<function(2.71475488, -5.3263638, -9.64269313, 2.42840015)<<endl;
	cout<<"gaaa  "<<setprecision(8)<<function(-1.18766907, -0.02087546, -14.9280479, 11.0043089)<<endl;
	//cout<<"nuevo fitness  "<<setprecision(8)<<function()<<endl;
	//cout<<"nuevo fitness  "<<setprecision(8)<<function()<<endl;
	//cout<<"nuevo fitness  "<<setprecision(8)<<function()<<endl;


}
void run(){
	//create();
	show_matrix();
	get_fitnes();
	cout<<endl<<endl;
	show_fitnes();

	suma(initial_poblation[6],initial_poblation[5], initial_poblation[7]);
	suma(initial_poblation[6],initial_poblation[4], initial_poblation[5]);
	suma(initial_poblation[7],initial_poblation[5], initial_poblation[6]);
	suma(initial_poblation[2],initial_poblation[7], initial_poblation[0]);
	suma(initial_poblation[7],initial_poblation[2], initial_poblation[3]);
	suma(initial_poblation[0],initial_poblation[6], initial_poblation[4]);
	suma(initial_poblation[7],initial_poblation[2], initial_poblation[6]);
	suma(initial_poblation[0],initial_poblation[4], initial_poblation[2]);
}

int main (){
	srand(time(NULL));
	run();
}