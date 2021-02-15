#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <map>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define ITER 2
#define N_HORMI 4
#define INICIAL 4
#define INITIAL_FERO 0.1 

typedef int city;
typedef float num;
typedef vector<num> vec_num ;


enum CITIES{A,B,C,D,E,F,G,H,I,J};
typedef struct{
      float l = 0;
      vector<city> cities;
      string ruta="";
}ant;


class AntSystem{
      private:
            vector<ant> pop;
            int n_ciudades;
            int ciudadInicial;
            string s_ciudades;
            float phi,alfa,beta,e,Q;
            int mejor_global;
            float feromona;
            int n_hormigas;
            size_t iteraciones;
      public :
            ofstream  file;
            vec_num  Mv;
            vec_num  Md;
            vec_num  Mf;
            AntSystem(int, int,int, float);
            void iniMatrices();
            void iniMatrizFeromona();
            void iniMatrizVisibilidad();
            void printCities(vec_num &, int);
            void obtenerMatrizVisibilidad();
            void crearHormigas();
            void elegirSgtCiudad(ant&);
            void mostrarPop();
            void actualizarMatrizFeronoma();
            float nivelFeromona(int, int);
            int IndVector(vector<city> &,int);
            float buscar_ij(ant& , int, int);
            void inicio(string);
            void mostrarRuta(ant&);
};

AntSystem::AntSystem(int it, int n, int inicity, float f){
      s_ciudades = "ABCDEFGHIJ";
      ciudadInicial = inicity;
      n_ciudades = s_ciudades.length();

      phi = 0.99;
      alfa = 1.0;
      beta = 1.0;
      e = n_ciudades;
      Q = 1.0;
      feromona = f;
      n_hormigas = n;
      iteraciones = it;
      mejor_global = 0;
}

void AntSystem::iniMatrizFeromona(){
      int x;
      for (size_t i = 0; i < n_ciudades; i++){
            x = i*n_ciudades+i;
            Mf[x] = 0;
      }
      
}

void AntSystem::iniMatrices(){
      float a[] = {0,12,3,23,1,5,23,56,12,11,
                  12,0,9,18,3,41,45,5,41,27,
                  3,9,0,89,56,21,12,48,14,29,
                  23,18,89,0,87,46,75,17,50,42,
                  1,3,56,87,0,55,22,86,14,33,
                  5,41,21,46,55,0,21,76,54,81,
                  23,45,12,75,22,21,0,11,57,48,
                  56,5,48,17,86,76,11,0,63,24,
                  12,41,14,50,14,54,57,63,0,9,
                  11,27,29,42,33,81,48,24,9,0};

      unsigned tam = sizeof(a) / sizeof(num);

      vector<float> M(a,a+tam );
      vector<float> b(n_ciudades*n_ciudades,feromona);
      vector<float> c(n_ciudades*n_ciudades,0);
      Md = M;
      Mf = b;
      Mv = c;
      iniMatrizFeromona();
      obtenerMatrizVisibilidad();
      file<<"---------Matriz de distacias-----------\n";
      printCities(Md,n_ciudades);
      file<<"---------Matriz de visibilidad-----------\n";
      printCities(Mv,n_ciudades);
}

void AntSystem::printCities(vec_num  &vec, int n){
      int city;
      for (size_t i = 0; i < n; i++){
            for (size_t j = 0; j < n; j++)
                  file <<vec[i*n+j]<< " ";
            file<<endl;      
      }
      
}

void AntSystem::obtenerMatrizVisibilidad(){
      float num,dem;
      for (size_t i = 0; i < n_ciudades; i++){
            for (size_t j = 0; j < n_ciudades; j++){
                  if(i != j)
                        Mv[i*n_ciudades+j] = 1/Md[i*n_ciudades+j];
            }
      }
}

void AntSystem::crearHormigas(){
      for (size_t i = 0; i < n_hormigas; i++){
            ant a1;
            a1.cities.push_back(ciudadInicial);
            a1.ruta += s_ciudades[ciudadInicial];
            pop.push_back(a1);
      }
      
}

void AntSystem::mostrarPop(){
      file<<"------------------------------------------------\n";
      for (size_t i = 0; i < pop.size(); i++){
            file<<"Hormiga "<<i<<": "<<pop[i].ruta<<" - Costo: "<<pop[i].l<<" dis: ";
            mostrarRuta(pop[i]);
      }
      file<<"------------------------------------------------\n";
}

void AntSystem::mostrarRuta(ant &tmp){
      for (size_t i = 0; i < tmp.cities.size(); i++){
            file<<tmp.cities[i]<<" ";
      }
      file<<endl;
      
}

int AntSystem::IndVector(vector<city> &vec,int x){   
      auto it = find(vec.begin(), vec.end(), x);
      if(it != vec.end())
            return  distance(vec.begin(), it);

}

float AntSystem::buscar_ij(ant &tmp, int pos, int j){
      if(pos > 0 && pos <n_ciudades){
            if(tmp.cities[pos+1]== j || tmp.cities[pos+1]== j)
                  return  Q/tmp.l;
      }else if(pos == 0 ){
            if(tmp.cities[pos+1]== j)
                  return Q/tmp.l;
      }else{
            if(tmp.cities[pos-1]== j)
                  return  Q/tmp.l;
      }
}

float AntSystem::nivelFeromona(int i, int j){
      float t_ij = 0;
      city pos;
      vector<city> tmp;
      for(size_t it=0; it<pop.size(); it++){
            pos = IndVector(pop[it].cities,i);
            t_ij += buscar_ij(pop[it],pos,j);
            file<<"  pos:  "<<t_ij<<"  "<<endl;
      }
      return t_ij;
}

void AntSystem::actualizarMatrizFeronoma(){
      for (size_t i = 0; i < n_ciudades; i++){
            for (size_t j = 0; j < n_ciudades; j++){
                  if(j != i){
                        file<<"i: "<<s_ciudades[i]<<"  -  j: "<<s_ciudades [j]<<" => "<<phi*Mf[i*n_ciudades+j]<<" + ";
                        if(tipo == true){
                              cout<<"en el true"<<endl;
                              file<<nivelFeromona(i,j)<<endl;
                              Mf[i*n_ciudades+j] = phi*Mf[i*n_ciudades+j]+nivelFeromona(i,j);
                        }
                        else{
                              float aux=nivelFeromona(i,j);
                              Mf[i*n_ciudades+j] = phi*Mf[i*n_ciudades+j]+aux;
                        }
                  }
            } 
      }
      
}

void AntSystem::elegirSgtCiudad(ant& h1){
      city ct = h1.cities.back(); 
      int pos_ct = ct * n_ciudades;
      num t_n=0;
      num sum=0;
      map<int,num> pb;
      for (size_t i =0; i < n_ciudades; i++)
      {
            auto it =find(h1.cities.begin(), h1.cities.end(), i);
            if(it == h1.cities.end()){
                  t_n = Mf[pos_ct+i]*Mv[pos_ct+i];
                  file << s_ciudades[ct]<<"-"<<s_ciudades[i]<<": t = "<<Mf[pos_ct+i]<<" n = "<<Mv[pos_ct+i]<<" t*n = "<<t_n<<endl;
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
      h1.l += Md[pos_ct+ id];
      h1.ruta += s_ciudades[id];
      file<<"Numero aleatorio para la probabilidad: "<<aleatorio<<endl;
      file<<"Ciudad siguiente: "<<s_ciudades[id]<<" ("<<Md[pos_ct+ id]<<")"<<endl;
      file<<"ruta: "<<h1.l<<endl;

}

void AntSystem::inicio(string filename){
      file.open(filename);
      iniMatrices();
      for (int it = 0; it < iteraciones; it++){
            mejor_global=0;
            file<<"---------Matriz de feromona-----------\n";
            printCities(Mf,n_ciudades);
            file<<"================ ITERACION "<<it<<"==================="<<endl;
            crearHormigas();  
            for (int k = 0; k < n_hormigas; k++){
                  file<<"--------------Hormiga "<<k<<"--------------"<<endl;
                  while(pop[k].cities.size()!=n_ciudades){
                        file<<"---------Elegir siguiente ciudad--------"<<endl;
                        elegirSgtCiudad(pop[k]);
                        
                  }
                  if(pop[mejor_global].l > pop[k].l) mejor_global=k;
                  file<<"camino: "<<pop[k].ruta<<endl;
            }            
            mostrarPop();
            file<<"Mejor Hormiga Global: "<<pop[mejor_global].ruta<<" - Costo: "<<pop[mejor_global].l<<endl;
            actualizarMatrizFeronoma();
            pop.clear();
      }
      cout<<" Finalizado "<<endl;
}


int main(){
      srand(time(NULL));
      string fileName= "ElitistAntSysOut.txt";
      cout<<"ElitistAntSystema \n";
      AntSystem r1(50,4,0,0.1,false);
      r1.inicio(fileName);
      
      
}