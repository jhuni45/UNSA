#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <map>
#include <stdlib.h>
#include <time.h>
#include <cmath>

using namespace std;

#define ITER 200
#define N_HORMI 6
#define INITIAL_FERO 0.1
#define N_CITIES 10

typedef int city;
typedef float num;
typedef vector<num> vec_num;

typedef struct{
      num distance = 0;
      vector<city> cities;
      string ruta="";
}my_ant;

int INITIAL_CITY;
ofstream  output;
my_ant mejor_global;
int mejor_local;
vector<my_ant> poblation;
string cities_list= "ABCDEFGHIJ";

num phi = 0.5, alfa = 1, beta = 1, Q=1, q0 = 0.5, qp = 0.5;
vec_num  visibility_Matrix, distances_Matrix, ferom_Matrix;

num content[] = { 0,12,3,23,1,5,23,56,12,11,
                  12,0,9,18,3,41,45,5,41,27,
                  3,9,0,89,56,21,12,48,14,29,
                  23,18,89,0,87,46,75,17,50,42,
                  1,3,56,87,0,55,22,86,14,33,
                  5,41,21,46,55,0,21,76,54,81,
                  23,45,12,75,22,21,0,11,57,48,
                  56,5,48,17,86,76,11,0,63,24,
                  12,41,14,50,14,54,57,63,0,9,
                  11,27,29,42,33,81,48,24,9,0};

void pheromone_matrix(){
      int aux;
      for (int i = 0; i < N_CITIES; i++){
            aux = i*N_CITIES+i;
            ferom_Matrix[aux] = 0;
      }
}

void get_visib_matrix(){
      for (size_t i = 0; i < N_CITIES; i++){
            for (size_t j = 0; j < N_CITIES; j++){
                  if(i != j)
                        visibility_Matrix[i*N_CITIES+j] = 1/distances_Matrix[i*N_CITIES+j];
            }
      }
}

void show_cities(vec_num  &vec, int n){
      int city;
      for (size_t i = 0; i < n; i++){
            for (size_t j = 0; j < n; j++)
                  output <<vec[i*n+j]<< " ";
            output<<endl;      
      }
}

void create_matrix(){
      unsigned tam = sizeof(content) / sizeof(num);
      vec_num M(content,content+tam);
      vec_num b(N_CITIES*N_CITIES,INITIAL_FERO);
      vec_num c(N_CITIES*N_CITIES,0);
      distances_Matrix = M;     ferom_Matrix = b;     visibility_Matrix = c;
      pheromone_matrix();
      get_visib_matrix();
      output<<"---------Matriz de distacias-----------\n";
      show_cities(distances_Matrix,N_CITIES);
      output<<"---------Matriz de visibilidad-----------\n";
      show_cities(visibility_Matrix,N_CITIES);
}

void show_route(my_ant &aux){
      for (size_t i = 0; i < aux.cities.size(); i++){
            output<<aux.cities[i]<<" ";
      }
      output<<endl;    
}

void show_Poblation(){
      output<<"------------------------------------------------\n";
      for (size_t i = 0; i < poblation.size(); i++){
            output<<"Hormiga "<<i<<": "<<poblation[i].ruta<<" - Costo: "<<poblation[i].distance<<" dis: ";
            show_route(poblation[i]);
      }
      output<<"------------------------------------------------\n";
}


void create_ant(){
      for (size_t i = 0; i < N_HORMI; i++){
            my_ant new_ant;
            new_ant.cities.push_back(INITIAL_CITY);
            new_ant.ruta += cities_list[INITIAL_CITY];
            poblation.push_back(new_ant);
      }     
}

int actual_ind(vector<city> &vec, int x){   
      auto it = find(vec.begin(), vec.end(), x);
      if(it != vec.end())
            return  distance(vec.begin(), it);
}

float get_index(my_ant &aux, int pos, int j){
      if(pos > 0 && pos <N_CITIES){
            return (aux.cities[pos+1]== j || aux.cities[pos+1]== j) ? Q/aux.distance : 0;
      }else if(pos == 0 ){
            return (aux.cities[pos+1]== j)? Q/aux.distance : 0;
      }else{
            return (aux.cities[pos-1]== j) ? Q/aux.distance : 0;
      }
}

float pheromone(int i, int j){
      float t_ij = 0;
      city pos;
      vector<city> aux;
      pos = actual_ind(mejor_global.cities,i);
      return get_index(mejor_global,pos,j);
}

void arc_update(int i, int j){
      output<<"Actualizamos el arco: "<<cities_list[i]<<" - "<<cities_list[j]<<" (v) (1-"<<qp<<") * "<<ferom_Matrix[i*N_CITIES+j]<<" + "<<qp<<" * "<<ferom_Matrix[i*N_CITIES+j]<<" = ";
      ferom_Matrix[i*N_CITIES+j] = ((1-qp)*ferom_Matrix[i*N_CITIES+j])+(qp*ferom_Matrix[i*N_CITIES+j]);
      output<<ferom_Matrix[i*N_CITIES+j]<<endl<<endl;
}

void actualizarMatrizFeronoma(){
      for (size_t i = 0; i < N_CITIES; i++){
            for (size_t j = 0; j < N_CITIES; j++){
                  if(j != i){
                        num aux=pheromone(i,j);
                        output<<cities_list[i]<<"  -  "<<cities_list [j];
                        if (aux==0){
                              output<<" => "<<ferom_Matrix[i*N_CITIES+j]<< " + "<<aux;
                              ferom_Matrix[i*N_CITIES+j] = ferom_Matrix[i*N_CITIES+j]+aux;       
                        }
                        else{
                              output<<" => "<<ferom_Matrix[i*N_CITIES+j]*(1-phi)<<" + "<<aux*phi;
                              //ferom_Matrix[i*N_CITIES+j] = phi*ferom_Matrix[i*N_CITIES+j]+aux;
                              ferom_Matrix[i*N_CITIES+j] = (ferom_Matrix[i*N_CITIES+j]*(1-phi))+ (aux*phi);
                        }
                        output<<" => "<<ferom_Matrix[i*N_CITIES+j]<<endl;
                  }
            } 
      }
}


void intensification(my_ant &h1, int c_city,int &next_city){
      output<<"Recorrido por Intensificacion\n";
      num arg_max = 0;
      int pos_ct = c_city * N_CITIES;
      map<int,num> probabilities;
      city id_city;
      for (size_t i =0; i < N_CITIES; i++){
            auto it =find(h1.cities.begin(), h1.cities.end(), i);
            if(it == h1.cities.end()){
                  probabilities[i]=pow(ferom_Matrix[pos_ct+i],alfa)*pow(visibility_Matrix[pos_ct+i],beta);
                  output << cities_list[c_city]<<"-"<<cities_list[i]<<": t = "<<ferom_Matrix[pos_ct+i]<<" n = "<<visibility_Matrix[pos_ct+i]<<" t*n = "<<probabilities[i]<<endl;
                  if(arg_max < probabilities[i]){
                        arg_max = probabilities[i];
                        next_city = i;
                  }
            }
      }
}

void diversification(my_ant &h1, int c_city,int &next_city){
      output<<"Recorrido por Diversificacion\n";
      int pos_ct = c_city * N_CITIES;
      num sum=0;
      map<int,num> probabilities;
      city id_city;
      for (size_t i =0; i < N_CITIES; i++){
            auto it =find(h1.cities.begin(), h1.cities.end(), i);
            if(it == h1.cities.end()){
                  probabilities[i] = pow(ferom_Matrix[pos_ct+i],alfa)*pow(visibility_Matrix[pos_ct+i],beta);
                  output << cities_list[c_city]<<"-"<<cities_list[i]<<": t = "<<ferom_Matrix[pos_ct+i]<<" n = "<<visibility_Matrix[pos_ct+i]<<" t*n = "<<probabilities[i]<<endl;
                  sum+=probabilities[i];
            }
      }
      output<<"suma: "<<sum<<endl;
      num random = ((num)rand() * (1-0)) /(num)RAND_MAX + 0;
      num limite = 0;
      for(auto it = probabilities.begin();it != probabilities.end(); it++){
            it->second = it->second/sum;
            output<<cities_list[c_city]<<"-"<<cities_list[it->first]<<": Prob =  "<<it->second<<endl;
            if(limite < random && random<limite +it->second){
                  next_city = it->first;
            }
            limite += it->second; 
      }
      output<<"Numero aleatorio para la probabilidad: "<<random<<endl;      
}

void next_city(my_ant& h1){
      city c_city = h1.cities.back(); 
      city next_city;
      num rand_prob = ((num)rand() * (1-0)) /(num)RAND_MAX + 0;
      output<<"valor de q: "<<rand_prob<<endl;
      if( rand_prob <= q0)
            intensification(h1,c_city,next_city);
      else
            diversification(h1,c_city,next_city);
      h1.cities.push_back(next_city);
      h1.distance += distances_Matrix[c_city*N_CITIES+ next_city];
      h1.ruta += cities_list[next_city];
      output<<"Ciudad siguiente: "<<cities_list[next_city]<<" ("<<distances_Matrix[c_city*N_CITIES+ next_city]<<")"<<endl;
      output<<"ruta: "<<h1.distance<<endl;
      arc_update(c_city,next_city);
}

void run(string outputname){
      output.open(outputname);
      output<<"Parametros:"<<endl
            <<"\tHormigas: "<<N_HORMI<<endl
            <<"\tphi: "<<phi<<endl
            <<"\talpha: "<<alfa<<endl
            <<"\tbeta: "<<beta<<endl
            <<"\tQ: "<<Q<<endl
            <<"\tq0: "<<q0<<endl
            <<"\tqp: "<<qp<<endl
            <<"\tIteraciones: "<<ITER<<endl<<endl;
      create_matrix();
      for (int it = 0; it < ITER; it++){
            mejor_local=0;
            output<<"---------Matriz de feromona-----------\n";
            show_cities(ferom_Matrix,N_CITIES);
            output<<"================ ITERACION "<<it<<" ==================="<<endl;
            create_ant();
            for (int k = 0; k < N_HORMI; k++){
                  output<<"--------------Hormiga "<<k<<"--------------"<<endl;
                  while(poblation[k].cities.size()!=N_CITIES){
                        output<<"---------Elegir siguiente ciudad--------"<<endl;
                        next_city(poblation[k]);
                  }
                  if(poblation[mejor_local].distance > poblation[k].distance)
                        mejor_local=k;
                  if(mejor_global.distance == 0)
                        mejor_global = poblation[mejor_local];
                  else
                        if(mejor_global.distance > poblation[mejor_local].distance) mejor_global = poblation[mejor_local];
                  output<<"camino: "<<poblation[k].ruta<<endl;
            }            
            show_Poblation();
            output<<"Mejor Hormiga local: "<<poblation[mejor_local].ruta<<" - Costo: "<<poblation[mejor_local].distance<<endl;
            output<<"Mejor global: "<< mejor_global.ruta <<" - Costo:"<<mejor_global.distance<<endl;
            actualizarMatrizFeronoma();
            show_Poblation();
            output<<"Mejor global: "<< mejor_global.ruta <<" - Costo:"<<mejor_global.distance<<endl;
            poblation.clear();
      }
      cout<<" Finalizado "<<endl;
}


int main(){
      srand(time(NULL));
      INITIAL_CITY = rand()% N_CITIES;
      string outputName= "OutLab7.txt";
      run(outputName);      
}