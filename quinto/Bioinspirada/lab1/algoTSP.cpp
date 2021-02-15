#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <tuple>
#include <stdlib.h>
#include <time.h>
#include <algorithm> 
#include <iomanip>

using namespace std;
typedef double data;
typedef vector<data> lista;
typedef vector<vector<data>> matriz;

#define POINTS 10
#define MAX_POBLATION 8
#define ALPHA 0.5
#define CROOS_PER 0.9
#define MUT_PER 0.05
#define ITER 1000
//!: this represent ABCDEFGHIJ
int global_vert[] ={1,2,3,4,5,6,7,8,9,10};
string vert ="ABCDEFGHIJ";
matriz values (POINTS+1,vector<data>(POINTS+1,0));

matriz initial_poblation (MAX_POBLATION,vector<data>(POINTS+3,0));


matriz new_poblation =initial_poblation;
lista fitness_container;

lista _initial_poblation2;
lista _initial_poblation;

data MAX_RAND=0;

void show_fitnes(matriz mat){
	for (int i=0;i<mat.size();i++){
		cout<<i+1<<")\t[ ";
		for (int j = 0; j <mat[0].size(); j++){
			cout<<mat[i][j]<< "  ";
		}
		cout<<" ]"<<endl;
	}
}
void show_matrix(matriz mat){
	for (int i=0;i<mat.size();i++){
		cout<<i+1<<")\t[ ";
		for (int j = 0; j <mat[0].size(); j++){
			cout<<mat[i][j]<< "  ";
		}
		cout<<" ]"<<endl;
	}
}

int randomWithProb(data p) {
    data rndDouble = (data)rand() / RAND_MAX;
    return rndDouble < p;
}

void see_poblation(){
	cout<<"Nueva Poblacion"<<endl;
	for (int i=0;i<MAX_POBLATION;i++){
		cout<<i+1<<") ";
		for (int j=0; j<POINTS;j++){
			cout<<vert[initial_poblation[i][j]-1];
		}
		cout<<endl;

		
	}
}

void permutation(){
	sort(global_vert,global_vert+POINTS);
	int iter=0;
	int rand1= rand()% 100000 + 1;
	int rand2= rand()% 200000 + 1;
	do{
		for(int i=0;i<rand1;i++)
			next_permutation(global_vert,global_vert+POINTS);
		cout<<iter+1<<") ";
		for (int i=0; i<POINTS;i++){
			initial_poblation[iter][i]=global_vert[i];
			cout<<vert[global_vert[i]-1];
		}
		cout<<endl;
		iter++;
		for(int i=0;i<rand2;i++)
			next_permutation(global_vert,global_vert+POINTS);
	}while(next_permutation(global_vert,global_vert+POINTS) && iter<MAX_POBLATION);
}



data get_rand(){
	data multi_rand = (data)rand() / RAND_MAX*1.0 +0.0;
	return multi_rand;
}

void get_fitnes(){
	data acum_fitness=0;
	for (int i=0;i<initial_poblation.size();i++){
		data acum=0;
		for (int j=0;j<POINTS-1;j++){
			acum+=values[initial_poblation[i][j]] [initial_poblation[i][j+1]];
		}
		(int)acum;
		initial_poblation[i][POINTS]=(data)acum;
		initial_poblation[i][POINTS+1]=1/initial_poblation[i][POINTS];
		acum_fitness+=initial_poblation[i][POINTS+1];
	}
	for (int i =0;i<initial_poblation.size();i++){
		initial_poblation[i][POINTS+2]=initial_poblation[i][POINTS+1]/acum_fitness;
		MAX_RAND += initial_poblation[i][(POINTS+2)];
	}
	cout<<endl<<"Calcular la Aptitud para cada Individudo"<<endl;
	show_matrix(initial_poblation);
}

void show_container(){
	for (int i =0;i<fitness_container.size();i++)
		cout<< fitness_container[i]<<endl;
}

void mating_pool(){
	//!: POR TORNEO
	int copy_maxpoblation=MAX_POBLATION;
	while(copy_maxpoblation){
		int first = rand()% (MAX_POBLATION) +1;
		int second = rand()% (MAX_POBLATION) +1;
		int winner=first;
		if (initial_poblation[first-1][POINTS]>initial_poblation[second-1][POINTS])
			winner=second;
		fitness_container.push_back(winner);
		
		copy_maxpoblation--;
		cout<<first<<"  -  "<<second<<"\t=>\t"<<winner<<"\t=>\t[ "<<" , "<<initial_poblation[winner-1][POINTS]<<" ]"<<endl;
	}
	cout<<endl;

	//!: POR RULETA 
		
	// for (int i=0;i<MAX_POBLATION;i++){
	// 	data rand_value=get_rand();
	// 	data value_to_eval=initial_poblation[0][POINTS+2];
	// 	int iter=1;
	// 	while(rand_value>value_to_eval){
	// 		value_to_eval+=initial_poblation[iter][POINTS+2];
	// 		iter++;
	// 	}
	// 	cout<<rand_value<<" => "<<iter<<" => ";
	// 	for (int i=0;i<POINTS;i++){
	// 		cout<<vert[int(initial_poblation[iter-1][i])-1];
	// 	}	
	// 	fitness_container.push_back(iter);
	// 	cout<<endl;
	// }
}
void simple_mutation(lista &to_change, int pos1, int pos2){
	data first=to_change[pos1];
	cout<<first<<endl;
	to_change[pos1]=to_change[pos2];
	to_change[pos2]=first;
}

void show_list(lista a){
	for (int i = 0; i < a.size()-3; i++){
		cout<<a[i]<< " ";
	}
	cout<<endl;
}

void croos_OBX(lista aux_croos, int parent1, int parent2){
	
	cout<<endl;
	_initial_poblation=initial_poblation[parent1];
	_initial_poblation2=initial_poblation[parent2];

	int pointer=0;

	lista aux_croos_temp=aux_croos;

	for (int i=0;i<POINTS;i++ ){
		if (i==aux_croos[pointer]){
			for (int j=0;j<POINTS;j++){
				int k=0;
				bool flag=false;
				while (k<aux_croos_temp.size()){
					if(initial_poblation[parent2][j]!=initial_poblation[parent1][aux_croos_temp[k]]){
						k++;	
					}
					else{
						_initial_poblation[i]=initial_poblation[parent2][j];
						aux_croos_temp.erase(aux_croos_temp.begin()+k);
						flag=true;	break;					
					}
				}
				if (flag==true) break;	
			}
			pointer++;
		}
		else{
			_initial_poblation[i]=initial_poblation[parent1][i];
		}
		
	}
	pointer=0;
	aux_croos_temp=aux_croos;
	for (int i=0;i<POINTS;i++ ){
		if (i==aux_croos[pointer]){
			for (int j=0;j<POINTS;j++){
				int k=0;
				bool flag=false;
				while (k<aux_croos_temp.size()){
					if(initial_poblation[parent1][j]!=initial_poblation[parent2][aux_croos_temp[k]]){
						k++;	
					}
					else{
						_initial_poblation2[i]=initial_poblation[parent1][j];
						aux_croos_temp.erase(aux_croos_temp.begin()+k);
						flag=true;	break;					
					}
				}
				if (flag==true) break;	
			}
			pointer++;
		}
		else{
			_initial_poblation2[i]=initial_poblation[parent2][i];
		}
	}
	cout<<"nuevas posicinones en 1 =>  ";
		show_list(_initial_poblation);
	cout<<"nuevas posicinones en 2 =>  ";
		show_list(_initial_poblation2);


}

void select_parents(){
	int copy_maxpoblation=MAX_POBLATION/2;
	int iterator=0;
	while (copy_maxpoblation){
		int mutation_pos= iterator%2;
		int first = rand()% (MAX_POBLATION) +1;
		int second = rand()% (MAX_POBLATION) +1;
		while(second==first)
			second = rand()% (MAX_POBLATION) +1;
		cout<<"["<<copy_maxpoblation<<"] "<<"Selección de Padres"<<endl
			<<"\t"<<first<<" - "<<second<<" => "<< fitness_container[first-1]<< " - "<<fitness_container[second-1]<< " => ";
		for (int i=0;i<POINTS;i++){
			cout<<vert[int(initial_poblation[fitness_container[first-1]-1][i])-1];
		}
		cout<< " - ";
		for (int i=0;i<POINTS;i++){
			cout<<vert[int(initial_poblation[fitness_container[second-1]-1][i])-1];
		}
		cout<<endl;
		copy_maxpoblation--;
		lista aux_croos;
		for (int i=0;i<POINTS;i++){
			if (randomWithProb(0.3)){
				aux_croos.push_back(i);
			}
		}
		_initial_poblation=initial_poblation[fitness_container[first-1]-1,fitness_container[second-1]-1];
		_initial_poblation2=initial_poblation[fitness_container[first-1]-1,fitness_container[second-1]-1];
		cout<< " ***Posiciones a cambiar  "<<endl;
		for(int i=0;i<aux_croos.size();i++)
			cout<<aux_croos[i]+1<<" ";
		if (aux_croos.size()>0)
			croos_OBX(aux_croos,fitness_container[first-1]-1,fitness_container[second-1]-1);
		aux_croos.clear();
		cout<<"****"<<endl;
		cout<<"MUTACIONES"<<endl;
		if (randomWithProb(MUT_PER)){
			cout<<"Con mutacion 1"<<endl;
			int first = rand()% (POINTS);
			int second = rand()% (POINTS);
			cout<<"\t"<< first+1<<" - "<<second+1<<endl;
			simple_mutation(_initial_poblation,first,second);
		}
		else{
			cout<<"Sin mutacion 1"<<endl;
		}
		if (randomWithProb(MUT_PER)){
			cout<<"Con mutacion 2"<<endl;
			int first = rand()% (POINTS);
			int second = rand()% (POINTS);
			cout<<"\t"<< first+1<<" - "<<second+1<<endl;
			simple_mutation(_initial_poblation2,first,second);
		}
		else{
			cout<<"Sin mutacion 2"<<endl;
		}

		new_poblation[iterator]=_initial_poblation;
		new_poblation[iterator+1]=_initial_poblation2;
		iterator+=2;
	}
}
void read_file(){
	ifstream file;
	file.open("inputTSP.txt");
	string word;
	int col=0;
	int row=0;
	while(file>>word){
		if (col>POINTS){
			row++;
			col=0;
		}
		values[row][col]=stoi(word);
		col++;
	}
	show_matrix(values);
}

void run(){
	read_file();
	permutation();
	int copy_iter=ITER;
	while(copy_iter){
		get_fitnes();
		cout<<endl<<"**** Iteración "<<(ITER-copy_iter)+1<<"****"<<endl
			<<"Creación de Mating Pool"<<endl;
		mating_pool();
		select_parents();
		copy_iter--;
		initial_poblation=new_poblation;		
		see_poblation();
		fitness_container.clear();
	}
	cout<<endl<<"*******  Resultado final  *******"<<endl;
	get_fitnes();
}


int main(){
	//setprecision(6);
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