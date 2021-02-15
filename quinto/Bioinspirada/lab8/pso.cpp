#include<bits/stdc++.h>
using namespace std;

typedef int num;
typedef float numf;

num np = 6;
num iteraciones = 100;
numf phi1 = 2, phi2 = 2;
numf rand1, rand2;
numf w;
pair<numf, numf> g;
numf pBest_fitness;
numf lim_inf=-10, lim_sup=10;


numf myfunction(numf x, numf y){
    return pow(x+(2*y)-7,2)+ pow((2*x)+y-5,2);
}

typedef struct{
    numf x1, x2;
    numf v1, v2;
    numf fitness_x;
    numf pBest1, pBest2;
}particle;

vector<particle> vp;

bool order(particle &p1, particle &p2){
    return p1.fitness_x < p2.fitness_x;
}

void generate_x_y(particle &p){
    p.x1=((numf)rand() * (lim_sup-lim_inf)) /(numf)RAND_MAX + lim_inf;
    p.x2=((numf)rand() * (lim_sup-lim_inf)) /(numf)RAND_MAX + lim_inf;
    int aux= rand() % 2, sign=1;
    if(aux==1)
        sign=-1;
    p.v1=(((numf)rand() * (1-0)) /(numf)RAND_MAX + 0)*sign;
    p.v2=(((numf)rand() * (1-0)) /(numf)RAND_MAX + 0)*sign;
    p.pBest1 = p.x1;
    p.pBest2 = p.x2;
}

void update_particle(particle &p){
    int cont=0;
    numf vel1, vel2, _x1, _x2, _fit;
    rand1 = ((numf)rand() * (1-0)) /(numf)RAND_MAX + 0;
    rand2 = ((numf)rand() * (1-0)) /(numf)RAND_MAX + 0;
    cout<<endl<<"rand1 = "<<rand1<<"  rand2 = "<<rand2<<endl;
    cout<<"\t v1= "<<w<<"*"<<p.v1<<"+"<<phi1<<"*"<<rand1<<"*"<<"("<<p.pBest1<<"-"<<p.x1<<") +"<<phi2<<"*"<<rand2<<"*"<<"("<<g.first<<"-"<<p.x1<<")"<<endl;
    vel1= w*p.v1 + phi1*rand1*(p.pBest1-p.x1) +phi2*rand2*(g.first-p.x1);
    cout<<"\t v2= "<<w<<"*"<<p.v2<<"+"<<phi1<<"*"<<rand1<<"*"<<"("<<p.pBest2<<"-"<<p.x2<<") +"<<phi2<<"*"<<rand2<<"*"<<"("<<g.second<<"-"<<p.x2<<")"<<endl;
    vel2= w*p.v2 + phi1*rand1*(p.pBest2-p.x2) +phi2*rand2*(g.second-p.x2);
    cout <<"v1= "<<p.v1<<"  v2= "<<p.v2<<endl;
    _x1 = p.x1 + vel1;
    _x2 = p.x2 + vel2;
    cout <<"x1= "<< _x1<<"   x2=  "<<_x2<<endl;
    cont++;
    _fit = myfunction(_x1,_x2);
    if(myfunction(p.pBest1,p.pBest2) > _fit){
        cout<<"*****Se cambio el mejor local*****"<<endl;
        p.pBest1 = p.x1;
        p.pBest2 = p.x2;
        p.v1 = vel1;    p.v2 = vel2;
        p.x1 = _x1;     p.x2 = _x2;
        p.fitness_x = _fit;
    }
}

void create_particle(){
    for(size_t i=0; i<np; i++){
        particle tmp;
        generate_x_y(tmp);
        tmp.fitness_x = myfunction(tmp.x1, tmp.x2);
        vp.push_back(tmp);   
    }
}

void show_poblation(){
    for(size_t i=0; i<vp.size();i++)
        cout<<"#"<<i+1<<" x("<<vp[i].x1<<","<<vp[i].x2<<") v("<<vp[i].v1<<" , "<<vp[i].v2<<") fit= "<<vp[i].fitness_x<<endl;
}

void update(){
    for (size_t i = 0; i < vp.size(); i++){
        cout<<"\nParticula: "<<i+1;
        update_particle(vp[i]);
    }   
}


void inicio(){
    for(size_t i=0; i <= iteraciones;i++){
        if(vp.size() > 0){
            w = ((numf)rand() * (1-0)) /(numf)RAND_MAX + 0;
            cout<<"\nOriginal"<<endl;
            show_poblation();
            sort(vp.begin(), vp.end(),order);
            cout<<"\nOrdenado"<<endl;
            show_poblation();
            cout<<"\n--------Iteracion "<<i<<" -----------"<<endl;
            g.first = vp[0].x1;
            g.second = vp[0].x2;
            pBest_fitness = vp[0].fitness_x;
            cout<<"Mejor: x("<<g.first<<" , "<<g.second<<") fit= "<<pBest_fitness<<endl;
            cout<<"W= "<<w<<endl;
            update();
        }else{
            cout<<"\n------Poblacion inicial---------\n";
            create_particle(); 
        }
    }
    cout<<"\nMejor global FINAL: x("<<g.first<<" , "<<g.second<<") fit= "<<pBest_fitness<<endl;
}

int main(){
    srand(time(NULL));
    cout<<"Parametros :"<<endl
        <<"- Tamaño de poblacion: "<<np<<endl
        <<"- Valores iniciales para $v_i$ entre -1.0 y 1.0"<<endl
        <<"- w: número aleatorio entre 0.0 y 1.0 para cada iteración"<<endl
        <<"- rand_1, rand_2: número aleatorio entre 0.0 y 1.0 para cada individuo"<<endl
        <<"- C_1, C_2$: "<<phi2<<endl
        <<"- Cantidad de Iteraciones: "<<iteraciones<<endl;
    inicio();
}