#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <algorithm>
#include <map>
#include <sstream>

using namespace std;

typedef double data;
typedef vector<string> lista;
typedef vector<vector<string>> matriz;

#define STATES 5
#define SIZE 8
#define ITER 3000

map<int, string> dicctionary ={{0, "A"}, {1, "B"}, {2, "C"}, {3, "D"}, {4, "E"} };

matriz 	initial_poblation (SIZE,vector<string>(STATES+3,"-"));
matriz  old_poblation= initial_poblation;
string prediction= "0111001010011100101001110010100111001010";

void show_matrix(matriz mat){
	for (int i=0;i<mat.size();i++){
		cout<<i+1<<")\t[ ";
		for (int j = 0; j <mat[0].size(); j++){
			cout<<mat[i][j]<< "  ";
		}
		cout<<" ]"<<endl;
	}
}

void show_vector(matriz mat, int pos){
	cout<<"[ ";
	for (int i=0; i<STATES;i++){
		cout<<mat[pos][i]<< " "; 
	}
	cout<<" ]"<<endl;
}

void show_map(){
	map<int,string>::iterator it = dicctionary.begin();
	for (it=dicctionary.begin(); it!=dicctionary.end(); ++it){
		cout << it->first << " => " << it->second <<endl;
	}
}

int randomWithProb(data p) {
    data rndDouble = (data)rand() / RAND_MAX;
    return rndDouble < p;
}


void get_mayor(matriz &aux_matrix){
	for (int i=0;i<SIZE/2;i++){
		data mayor=atof(aux_matrix[i][STATES+2].c_str());
		int pos_winner=0;
		for (int j=0;j< aux_matrix.size();j++){
			if (atof(aux_matrix[j][STATES+2].c_str())<mayor){
				mayor=atof(aux_matrix[j][STATES+2].c_str());
				pos_winner=j;
			}
		}
		aux_matrix.erase(aux_matrix.begin()+pos_winner);
	}
}


string compare(string value){
	data cont=0.0;
	for (int i =1 ;i< prediction.size();i++){
		if (prediction[i]==value[i-1])
			cont+=1;
	}
	//cout<<"contador :  "<<cont;
	cont = cont/prediction.size();
	//cout<<"   resukt:  "<<cont<<endl;
	

	return to_string(cont);
}
string create_state(int condition, int no_link){
	string initial= to_string(condition);
	if (randomWithProb(0.5)){
		initial+="01";
	}
	else{
		initial+="10";
	}
	
	//cout<<"auc   "<<initial;

	int cases= rand() % 3;
	switch(cases){
		case 0: initial+="01";	break;
		case 1: initial+="00";	break;
		case 2: initial+="10";	break;
		case 3: initial+="11";	break;
	}
	int out1 = rand() % STATES;
	int out2 = rand() % STATES;
	while (no_link==out1 || no_link==out2){
		out1 = rand() % STATES;
		out2 = rand() % STATES;
	}
	initial+=dicctionary[out1];
	initial+=dicctionary[out2];

	return initial;

}

void create_poblation(){
	//show_matrix(initial_poblation);
	for (int i = 0; i< SIZE ; i++){
		int  no_link=-1, initial = rand() % STATES;
		if (randomWithProb(0.5)) {
			no_link =rand() % STATES;
			while (no_link==initial){
				no_link =rand() % STATES;
			}
		}
		for (int j=0 ; j <STATES; j++) {
			if (j ==initial){
				initial_poblation[i][j] = create_state(2, no_link);
			}
			else if (j ==no_link){
				initial_poblation[i][j] = create_state(0, no_link);
			}
			else{
				initial_poblation[i][j] = create_state(1, no_link);
			}
		}
		initial_poblation[i][STATES]=to_string(initial);

	}
	show_matrix(initial_poblation);

}

void get_aptitud(){
	for (int i =0 ; i<SIZE ; i++){
		string result="";
		string aux= initial_poblation[i][stoi(initial_poblation[i][STATES])];
		//cout<<"  ->   "<<aux<<endl;
		for (int j=0 ; j <prediction.size();j++){
			//cout<<"diccionario:  "<< prediction<<" => "<<prediction[j]<<endl;
			if ( prediction[j]==aux[1]){
				result+=aux[3];
				//cout<<" IF  value entrada  "<<aux[3];
				string str= "";
				str+=aux[5];
				//cout<<" salida  texto :  "<<str;
				for (auto it = dicctionary.begin(); it!=dicctionary.end();++it){
					if (it->second==str)
						aux=initial_poblation[i][it->first];
				}
				//cout<<"   nuevo: "<< aux<<endl;
			}
			else {
				result+=aux[4];
				//cout<<" EL  value entrada  "<<aux[4];
				string str= "";
				str+=aux[6];
				//cout<<" salida  texto :  "<<str;
				for (auto it = dicctionary.begin(); it!=dicctionary.end();++it){
					if (it->second==str)
						aux=initial_poblation[i][it->first];
				}
				//cout<<"   nuevo: "<< aux<<endl;
			}
			//cout<<" **** resu : "<<result<<endl;

		}
		initial_poblation[i][STATES+1]=result;
		initial_poblation[i][STATES+2]= compare(initial_poblation[i][STATES+1]);
		//cout<<"resiltado:  "<<result<<endl;
	}
	show_matrix(initial_poblation);
}

void mutation(data value, int pos){
	if (value>0.0 && value<0.1){
		show_vector(initial_poblation, pos);
		bool flag=false; int iter=0;
		string selected = initial_poblation[pos][iter];
		
		while(selected[0]!='1' && iter<STATES){
			selected = initial_poblation[pos][iter];
			iter++;
		}
		if(iter==STATES){
			data random = 1.0000 * (rand() % 10001) / 10000;
			while(random<0.1){
				random = 1.0000 * (rand() % 10001) / 10000;
			}
			mutation(random,pos);
		}
		else{
			cout<<"Desactivar un estado\n"<<"Estado elegido => "<<dicctionary[iter]<< endl;
			initial_poblation[pos][iter][0]='0';
			for (int i = 0;i<SIZE; i++ ){
				//string aux = initial_poblation[pos][i];
				if (initial_poblation[pos][i][5]==dicctionary[iter][0]){
					int iterator= rand()% STATES;
					while (initial_poblation[pos][iterator][0]=='0')
						iterator= rand()%STATES;
					initial_poblation[pos][i][5]= dicctionary[iterator][0];
				}
				if (initial_poblation[pos][i][6]==dicctionary[iter][0]){
					int iterator= rand()% STATES;
					while (initial_poblation[pos][iterator][0]=='0')
						iterator=rand()% STATES;
					initial_poblation[pos][i][6]= dicctionary[iterator][0];
				}
			}
		}
		show_vector(initial_poblation, pos);
	} 
		
	else if (value>0.1 && value<0.3){
		show_vector(initial_poblation, pos);
		int aux_rand = rand()% STATES;
		string selected = initial_poblation[pos][aux_rand];
		string initial = initial_poblation[pos][stoi(initial_poblation[pos][STATES])];
		while(selected[0]!='1'){
			aux_rand =rand()% STATES;
			selected = initial_poblation[pos][aux_rand];
		}
		cout<<"Cambiar estado inicial\nEstados elegidos => "<<dicctionary [stoi(initial_poblation[pos][STATES])]<< " - "<<dicctionary[aux_rand]<<endl;
		initial_poblation[pos][stoi(initial_poblation[pos][STATES])][0]='1';
		initial_poblation[pos][aux_rand][0]='2';
		initial_poblation[pos][STATES]=to_string(aux_rand);
		show_vector(initial_poblation, pos);
			
	}
	else if (value>0.3 && value<0.5){
		show_vector(initial_poblation, pos);
		int aux_rand = rand()% STATES;
		while(initial_poblation[pos][aux_rand][0]=='0'){
			aux_rand =rand()% STATES;
		}
		cout<<"Cambiar simbolo de entrada\nEstado elegido => "<<dicctionary[aux_rand]<<endl;
		char other=initial_poblation[pos][aux_rand][2];
		initial_poblation[pos][aux_rand][2]=initial_poblation[pos][aux_rand][1];
		initial_poblation[pos][aux_rand][1]=other;
		show_vector(initial_poblation, pos);

	}
	else if (value>0.5 && value<0.7){
		show_vector(initial_poblation, pos);
		int aux_rand = rand()% STATES;
		while(initial_poblation[pos][aux_rand][0]=='0'){
			aux_rand= rand()% STATES;
		}
		int pos_value= rand ()% 2;
		cout<<"Cambiar un simbolo de salida\nEstado elegido => "<<dicctionary[aux_rand]<<" - Simbolo de salida: "<<pos_value<<endl;
		if (pos_value==0){
			if (initial_poblation[pos][aux_rand][3]=='1')
				initial_poblation[pos][aux_rand][3]='0';
			else
				initial_poblation[pos][aux_rand][3]='1';
		}
		else{
			if (initial_poblation[pos][aux_rand][4]=='1')
				initial_poblation[pos][aux_rand][4]='0';
			else
				initial_poblation[pos][aux_rand][4]='1';	
		}
		show_vector(initial_poblation, pos);
	} 
	else if (value>0.7 && value<0.9){
		int aux_rand=rand() % STATES;
		while (initial_poblation[pos][aux_rand][0]=='0'){
			aux_rand=rand() % STATES;
		}
		int value = rand()% STATES;
		int choose = rand()% 2;
		show_vector(initial_poblation, pos);
		cout<<"Cambiar un estado de salida\nEstado elegido => "<<dicctionary[aux_rand]<<" - Estado de salida: "<<choose<<endl;
		while (initial_poblation[pos][value][0]=='0'){
			value = rand()% STATES;
		}
		if (choose==0){
			initial_poblation[pos][aux_rand][5]=dicctionary[value][0];
		}
		else{
			initial_poblation[pos][aux_rand][6]=dicctionary[value][0];
		}
		show_vector(initial_poblation, pos);

	} 
	else if (value>0.9 && value<1.0){
		bool exist=false;
		int i;
		for (i=0;i<STATES; i++){
			if (initial_poblation[pos][i][0]=='0' && exist==false){
				show_vector(initial_poblation,pos);
				cout<<"Activar un estado\nEstado elegido => "<<dicctionary[i]<<endl;
				exist=true;	
				initial_poblation[pos][i][0]='1';
				show_vector(initial_poblation,pos);
			}
		}
		if (exist==false){
			data random = 1.0000 * (rand() % 10001) / 10000;
			while(random>0.89){
				random = 1.0000 * (rand() % 10001) / 10000;
			}
			mutation(random,pos);
		}

	} 

} 

void join_mat(matriz old){
	for (int i=0;i<SIZE/2;i++){
		initial_poblation.push_back(old[i]);
	}
}

void generate(matriz mat){
	ofstream out;
	out.open("grafica.txt");
	for (int i=0;i <SIZE;i++){
		string a= dicctionary [stoi(mat[i][STATES])];
		out<<"digraph a {"<<endl<<"\trankdir=LR;"<<endl<<"\tsize=\"8,5\""<<endl;
		out<<"\tnode [shape = doublecircle]; "<<dicctionary[stoi(mat[i][STATES])]<<";"<<endl;
		out<<"\tnode [shape = circle];"<<endl;
		for (int j=0 ;j <STATES; j++){
			if (mat[i][j][0]!='0'){
				out<<"\t"<<dicctionary[j]<< " -> "<< mat[i][j][5]<<" [ label = \""<<mat[i][j][1]<<"-"<< mat[i][j][3]<<"\"] ;"<<endl;
				out<<"\t"<<dicctionary[j]<< " -> "<< mat[i][j][6]<<" [ label = \""<<mat[i][j][2]<<"-"<< mat[i][j][4]<<"\"] ;"<<endl;
			}
		}
		out<<"}"<<endl<<endl;
	}
	out.close();
}
void run (){
	create_poblation();
	get_aptitud();
	int copy_iter=ITER;
	while (copy_iter){
		old_poblation = initial_poblation;
		cout<<"===== Iteracion "<<ITER-copy_iter<<" =====\n"
			<<"Proceso de mutacion"<<endl;
		for (int i=0;i< SIZE; i++){
			cout<<"Mutacion "<<i+1<<endl;
			data first_rand = 1.0000 * (rand() % 10001) / 10000;
			cout<< "Aleatorio :   "<<first_rand<<endl;
			mutation(first_rand,i);
			cout<<endl;
		}
		cout<<"Ascendientes"<<endl;
		show_matrix(old_poblation);
		get_mayor(old_poblation);
		cout<<"Mejores Ascendientes"<<endl;
		show_matrix(old_poblation);
		
		cout<<endl<<"Descendientes"<<endl;
		get_aptitud();
		get_mayor(initial_poblation);
		cout<<"Mejores Descendientes"<<endl;
		show_matrix(initial_poblation);
		copy_iter--;
		join_mat(old_poblation);
		cout<<"Nueva poblacion"<<endl;
		show_matrix(initial_poblation);
	}
	generate(initial_poblation);
}

int main(int argc, char *argv[]){
	srand (time (NULL));
	cout<<"Parametros "<<endl
		<<"\t- Cantidad de Individuos: "<<SIZE
		<<"\t- Cantidad Máxima de Estados: "<<STATES
		<<"\t- Cantidad de Iteraciones: "<<ITER<<endl;
	run ();
	return 0;
}