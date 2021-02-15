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

#define POINTS 10
#define SIZE_P 7
#define SIZE_F 5
#define SIZE_PCLONE 15
#define SIZE_PHYPER 15
#define SIZE_S 5
#define SIZE_R 2
#define ITER 200

typedef int data;
typedef vector<data> lista;
typedef vector<lista> matriz;

int global_vert[] ={1,2,3,4,5,6,7,8,9,10};
string vert ="ABCDEFGHIJ";

matriz values (POINTS+1,lista(POINTS+1,0));
matriz initial_poblation (SIZE_P,lista(POINTS+1,0));
matriz poblation_R (SIZE_R,lista(POINTS+1,0)); 
matriz poblation_F, poblation_Pclone, poblation_S, poblation_SR;

matriz new_poblation = initial_poblation;
lista rand_list;


bool order(lista &p1, lista &p2){
 	return p1[POINTS] < p2[POINTS];
}

void show_list(){
	cout<<"[";
	for (int i = 0; i < rand_list.size(); i++){
		if (i%2==0 && i > 0)
			cout<<"] ; [";
		cout<< rand_list[i] <<" ";
	}
	cout<<"]"<<endl;
}
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


void get_fitnes( matriz & initial_poblation){
	data acum_fitness=0;
	for (int i=0;i<initial_poblation.size();i++){
		data acum=0;
		for (int j=0;j<POINTS-1;j++){
			acum+=values[initial_poblation[i][j]] [initial_poblation[i][j+1]];
		}
		(int)acum;
		initial_poblation[i][POINTS]=(data)acum;
		acum_fitness+=initial_poblation[i][POINTS+1];
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
	}while(next_permutation(global_vert,global_vert+POINTS) && iter<SIZE_P);
}

void read_file(){
	ifstream file;
	file.open("input.txt");
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

void get_poblationF(){
	for (int i =0; i< SIZE_F; i++){
		poblation_F.push_back(initial_poblation[i]);
	}
}

void get_Pclone(){
	int _PClone = SIZE_F;
	for (int i=0; i< SIZE_F; i++){
		for(int j=0; j< _PClone ; j++){
			poblation_Pclone.push_back(poblation_F[i]);
		}
		_PClone--;
	}
}

void generate_position(int size){
	for (int i=0; i< size; i++){
		int aux = rand()% POINTS;
		lista::iterator it;
		it = find(rand_list.begin(), rand_list.end(), aux);
		do{
			aux = rand()% POINTS;
			it = find(rand_list.begin(), rand_list.end(), aux);			
		}while (it != rand_list.end());			
		rand_list.push_back(aux);
	}
}

void get_Phyper(){
	int aux = 2;
	int pos = 0;
	int _PClone = SIZE_F;
	for (int i = 0 ; i < SIZE_F; i++){
		for (int j =0; j <_PClone; j++){
			generate_position(aux);
			for (int k = 0; k < rand_list.size(); k+=2){
				int auxi = poblation_Pclone[pos][rand_list[k]];
				poblation_Pclone[pos][rand_list[k]] = poblation_Pclone[pos][rand_list[k+1]];
				poblation_Pclone[pos][rand_list[k+1]] = auxi;
			}
			show_list();
			rand_list.clear();
			pos++;
		}
		aux+=2;
		_PClone--;
	}
	get_fitnes(poblation_Pclone);
	cout<<endl<<"Fitness de nueva generacion Phyper (sin orden)"<<endl;
	show_matrix(poblation_Pclone);
	cout<<endl<<"Ordenado Phyper"<<endl;
	sort(poblation_Pclone.begin(), poblation_Pclone.end(),order);
	show_matrix(poblation_Pclone);
}

void get_PS(){
	for (int i = 0 ; i<SIZE_S; i++ ){
		poblation_S.push_back(poblation_Pclone[i]);
	}
}
void get_PR(){
	int iter=0;
	sort(global_vert,global_vert+POINTS);
	int rand1= rand()% 100000 + 1;
	do{	
		for (int j =0 ;j< rand1; j++)
			next_permutation(global_vert,global_vert+POINTS);
		for (int k=0; k<POINTS;k++){
			poblation_R[iter][k]=global_vert[k];
			cout<<vert[global_vert[k]-1];
		}
		cout<<endl;
		iter++;
		for (int j =0 ;j< rand1; j++)
			next_permutation(global_vert,global_vert+POINTS);
	}while(next_permutation(global_vert,global_vert+POINTS) && iter<SIZE_R);
	cout<<"termine"<<endl;
}
void join_PSR(){
	poblation_SR=poblation_S;
	for (int i =0; i< SIZE_R; i++)
		poblation_SR.push_back(poblation_R[i]);
	sort(poblation_SR.begin(), poblation_SR.end(),order);
}
void update_poblation(){
	for (int i =0; i< SIZE_R; i++){
		initial_poblation[i]= poblation_F[i];
	}
	for (int i =0; i< SIZE_S; i++){
		initial_poblation[i+2] = poblation_S[i];
	}
	sort(initial_poblation.begin(), initial_poblation.end(), order);
}

void run(){
	read_file();
	permutation();
	get_fitnes(initial_poblation);
	cout<<endl<<"Poblacion P (ordenado menor a mayor)"<<endl;
	sort(initial_poblation.begin(), initial_poblation.end(),order);
	show_matrix(initial_poblation);
	int _iter =ITER;
	while(_iter){
		cout<<"**** Iteracion "<<ITER-_iter<<" ******"<<endl;
		
		get_poblationF();
		cout<<"** Poblacion F **"<<endl;
		show_matrix(poblation_F);
		
		get_Pclone();
		cout<<"** Poblacion PClone **"<<endl;
		show_matrix(poblation_Pclone);
		
		cout<<"** Poblacion Phyper ** "<<endl;
		get_Phyper();
		
		cout<<"** Poblacion S **"<<endl;
		get_PS();
		show_matrix(poblation_S);
		
		cout<<"** Poblacion R **"<<endl;
		get_PR();
		get_fitnes(poblation_R);
		show_matrix(poblation_R);

		join_PSR();
		cout<<"Union de S con R"<<endl;
		show_matrix(poblation_SR);
		
		cout<<"** Nueva Poblacion P **"<<endl;
		update_poblation();
		show_matrix(initial_poblation);
		poblation_F.clear();
		poblation_SR.clear();
		//poblation_R.clear();
		poblation_Pclone.clear();
		poblation_S.clear();
		_iter--;
	}
}

void get_letter(){
	for (int i =0 ; i< initial_poblation.size();i++){
		cout<<i+1<<")  ";
		for (int j=0; j< initial_poblation[0].size()-1;j++){
			cout<< vert[initial_poblation[i][j]-1];
		}
		cout<<endl;
	}
}
int main(){
	//setprecision(6);
	srand (time(NULL));
	cout<<"Parámetros:"<<endl
		<<"Tamano poblacion P: "<< SIZE_P<<endl
		<<"Tamano poblacion F: "<<SIZE_F<<endl
		<<"Tamano poblacion PClone y PHyper: "<<SIZE_PHYPER<<endl
		<<"Tamano poblacion S: "<<SIZE_S<<endl
		<<"Tamaño población R: "<<SIZE_R<<endl
		<<"Dimensiones del vector (anticuerpo): "<<POINTS<<endl
		<<"Cantidad de Iteraciones: "<<ITER<<endl;
	run();
	cout<<"============= respuesta en letras============="<<endl;
	get_letter();
	return 0;
}