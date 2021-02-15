#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <map>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define ITER 200
#define N_HORMI 6
#define INITIAL_CITY 3
#define INITIAL_FERO 0.1

typedef int city;
typedef float num;
typedef vector<num> vec_num;

typedef struct{
      num distance = 0;
      vector<city> cities;
      string ruta="";
}ant;


vector<ant> poblation;
string s_ciudades= "ABCDEFGHIJ";
int n_ciudades = s_ciudades.length();
num phi= 0.99, alfa = 1.0, beta = 1.0, Q=1.0;

ofstream  file;
vec_num  visibility_Matrix, distances_Matrix, ferom_Matrix;

num content[] = {0,12,3,23,1,5,23,56,12,11,
                  12,0,9,18,3,41,45,5,41,27,
                  3,9,0,89,56,21,12,48,14,29,
                  23,18,89,0,87,46,75,17,50,42,
                  1,3,56,87,0,55,22,86,14,33,
                  5,41,21,46,55,0,21,76,54,81,
                  23,45,12,75,22,21,0,11,57,48,
                  56,5,48,17,86,76,11,0,63,24,
                  12,41,14,50,14,54,57,63,0,9,
                  11,27,29,42,33,81,48,24,9,0};

void iniMatrizFeromona(){
      int aux;
      for (int i = 0; i < n_ciudades; i++){
            aux = i*n_ciudades+i;
            ferom_Matrix[aux] = 0;
      }
}

void obtenerMatrizVisibilidad(){
      for (size_t i = 0; i < n_ciudades; i++){
            for (size_t j = 0; j < n_ciudades; j++){
                  if(i != j)
                        visibility_Matrix[i*n_ciudades+j] = 1/distances_Matrix[i*n_ciudades+j];
            }
      }
}

void show_cities(vec_num  &vec, int n){
      int city;
      for (size_t i = 0; i < n; i++){
            for (size_t j = 0; j < n; j++)
                  file <<vec[i*n+j]<< " ";
            file<<endl;      
      }
}

void show_route(ant &tmp){
      for (size_t i = 0; i < tmp.cities.size(); i++){
            file<<tmp.cities[i]<<" ";
      }
      file<<endl;      
}

void show_Poblation(){
      file<<"------------------------------------------------\n";
      for (size_t i = 0; i < poblation.size(); i++){
            file<<"Hormiga "<<i<<": "<<poblation[i].ruta<<" - Costo: "<<poblation[i].distance<<" dis: ";
            show_route(poblation[i]);
      }
      file<<"------------------------------------------------\n";
}

void iniMatrices(){
      unsigned tam = sizeof(content) / sizeof(num);
      vec_num M(content,content+tam);
      vec_num b(n_ciudades*n_ciudades,INITIAL_FERO);
      vec_num c(n_ciudades*n_ciudades,0);
      distances_Matrix = M;     ferom_Matrix = b;     visibility_Matrix = c;
      iniMatrizFeromona();
      obtenerMatrizVisibilidad();
      file<<"---------Matriz de distacias-----------\n";
      show_cities(distances_Matrix,n_ciudades);
      file<<"---------Matriz de visibilidad-----------\n";
      show_cities(visibility_Matrix,n_ciudades);
}


void crearHormigas(){
      for (size_t i = 0; i < N_HORMI; i++){
            ant new_ant;
            new_ant.cities.push_back(INITIAL_CITY);
            new_ant.ruta += s_ciudades[INITIAL_CITY];
            poblation.push_back(new_ant);
      }     
}

int actual_ind(vector<city> &vec, int x){   
      auto it = find(vec.begin(), vec.end(), x);
      if(it != vec.end())
            return  distance(vec.begin(), it);
}

float get_index(ant &tmp, int pos, int j){
      if(pos > 0 && pos <n_ciudades){
            if(tmp.cities[pos+1]== j || tmp.cities[pos+1]== j){
                  return  Q/tmp.distance;
            }
      }else if(pos == 0 ){
            if(tmp.cities[pos+1]== j)
                  return Q/tmp.distance;
      }else{
            if(tmp.cities[pos-1]== j)
                  return  Q/tmp.distance;
      }
}

float nivelFeromona(int i, int j){
      float t_ij = 0, aux;
      city pos;
      vector<city> tmp;
      for(size_t it=0; it<poblation.size(); it++){
            pos = actual_ind(poblation[it].cities,i);
            aux = get_index(poblation[it],pos,j);
            t_ij += aux;
            if (aux<0.0000000001)
                  file <<"  +  0";
            else
                  file<<"  +  "<<aux;
      }
      return t_ij;
}

void actualizarMatrizFeronoma(){
      for (size_t i = 0; i < n_ciudades; i++){
            for (size_t j = 0; j < n_ciudades; j++){
                  if(j != i){
                        file<<s_ciudades[i]<<"  -  "<<s_ciudades [j]<<" => "<<phi*ferom_Matrix[i*n_ciudades+j];
                        num aux=nivelFeromona(i,j);
                        ferom_Matrix[i*n_ciudades+j] = phi*ferom_Matrix[i*n_ciudades+j]+aux;
                        file<<" => "<<ferom_Matrix[i*n_ciudades+j]<<endl;
                  }
            } 
      }
}

void elegirSgtCiudad(ant& h1){
      city ct = h1.cities.back(); 
      int pos_ct = ct * n_ciudades;
      num t_n=0;
      num sum=0;
      map<int,num> pb;
      for (size_t i =0; i < n_ciudades; i++){
            auto it =find(h1.cities.begin(), h1.cities.end(), i);
            if(it == h1.cities.end()){
                  t_n = ferom_Matrix[pos_ct+i]*visibility_Matrix[pos_ct+i];
                  file << s_ciudades[ct]<<"-"<<s_ciudades[i]<<": t = "<<ferom_Matrix[pos_ct+i]<<" n = "<<visibility_Matrix[pos_ct+i]<<" t*n = "<<t_n<<endl;
                  pb[i] = t_n;
                  sum+=t_n;
            }
      }
      file<<"suma: "<<sum<<endl;
      num aleatorio = ((num)rand() * (1-0)) /(num)RAND_MAX + 0;
      
      city id;
      num limite = 0;
      for(auto it = pb.begin();it != pb.end(); it++){
            it->second = it->second/sum;
            file<<s_ciudades[ct]<<"-"<<s_ciudades[it->first]<<": Prob =  "<<it->second<<endl;
            if(limite < aleatorio && aleatorio<limite +it->second)
                  id = it->first;
            limite += it->second; 
      }
      h1.cities.push_back(id);
      h1.distance += distances_Matrix[pos_ct+ id];
      h1.ruta += s_ciudades[id];
      file<<"Numero aleatorio para la probabilidad: "<<aleatorio<<endl;
      file<<"Ciudad siguiente: "<<s_ciudades[id]<<" ("<<distances_Matrix[pos_ct+ id]<<")"<<endl;
      file<<"ruta: "<<h1.distance<<endl;
}

void run(string filename){
      file.open(filename);
      file<<"Parametros:"<<endl
            <<"\tHormigas: "<<N_HORMI<<endl
            <<"\tphi: "<<phi<<endl
            <<"\talpha: "<<alfa<<endl
            <<"\tbeta: "<<beta<<endl
            <<"\tQ: "<<Q<<endl
            <<"\tIteraciones: "<<ITER<<endl<<endl;
      iniMatrices();
      for (int it = 0; it < ITER; it++){
            file<<"---------Matriz de feromona-----------\n";
            show_cities(ferom_Matrix,n_ciudades);
            file<<"================ ITERACION "<<it<<"==================="<<endl;
            crearHormigas();  
            for (int k = 0; k < N_HORMI; k++){
                  file<<"--------------Hormiga "<<k<<"--------------"<<endl;
                  while(poblation[k].cities.size()!=n_ciudades){
                        file<<"---------Elegir siguiente ciudad--------"<<endl;
                        elegirSgtCiudad(poblation[k]);
                        
                  }
                  file<<"camino: "<<poblation[k].ruta<<endl;
            }            
            show_Poblation();
            actualizarMatrizFeronoma();
            show_Poblation();
            poblation.clear();
      }
      cout<<" Finalizado "<<endl;
}


int main(){
      srand(time(NULL));
      string fileName= "AntOut.txt";
      run(fileName);      
}