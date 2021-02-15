#include <vector>
#include <string>
#include <iostream>
#include <tgmath.h>
#include <algorithm>
#include <fstream>
using namespace std;


#define POBLATION 8
#define PER_CROOS 40
#define PER_REPRO 20
#define PER_MUTA  40
#define SIZE 7
#define ITER 1000

typedef double data;
typedef vector<int> lista;

int num_op=4;
int limit_op = SIZE - 4;
data total_fit = 0;

data entradas[]={0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9};
data salidas[]={0,0.005,0.02,0.045,0.08,0.125,0.18,0.245,0.32,0.405};
char operadores[] = {'+','-','*','/'};


typedef struct{
    string cadena= " ";
    data fitness = 0;
    data inv =0;
    lista valores;
    data porcent;
}indv;

vector<indv> initial_poblation;
vector<indv> new_poblation;

void mostrarValoresVec(lista v){
    cout<<"[ ";
    for (int i = 0; i < v.size(); ++i)
        cout<<v[i]<<" ";
    cout<<"] ";
}

void mostrarPoblacion(){
    for (int i = 0; i < initial_poblation.size(); ++i){   
        cout<<i<<") ";
        //mostrarValoresVec(initial_poblation[i].valores);
        cout<<initial_poblation[i].cadena<<"\t Fitness => "<<initial_poblation[i].fitness<<endl;
    }
}

bool ordenar(indv &a, indv &b){
    return a.fitness < b.fitness;
}


string leerValoresVec(lista &i, int pos){
    if(pos < SIZE){
        if(pos < limit_op){
            switch(i[pos]){
                case 0:
                    return "| "+leerValoresVec(i,pos*2+1) +" + "+ leerValoresVec(i,pos*2+2)+" |";
                case 1:
                    return "| "+leerValoresVec(i,pos*2+1) +" - "+ leerValoresVec(i,pos*2+2)+" |";
                case 2:
                    return "| "+leerValoresVec(i,pos*2+1) +" * "+ leerValoresVec(i,pos*2+2)+" |";
                case 3:
                    return "| "+leerValoresVec(i,pos*2+1) + " / "+leerValoresVec(i,pos*2+2)+" |";
                //case 4:
                //  return "|"+leerValoresVec(i,pos*2+1)+" / "+leerValoresVec(i,pos*2+2)+"|";
            }
        }else{
            int x = 20;
            if(i[pos] == x)
                return "x ";
            return to_string(i[pos])+" ";
        }
    }
}

indv crearIndividuo(){
    indv new_indv;
    int aux = 20;
    data aux_rand;
    for (int i = 0; i < SIZE; ++i){
        if( i < limit_op){
            aux_rand = rand()% num_op;
            new_indv.valores.push_back(aux_rand);
        }else{
            aux_rand = (data)(rand() % 101)/100;
            if(aux_rand <= 0.5)
                new_indv.valores.push_back(aux);
            else{
                aux_rand = (rand()% 11)-5;
                new_indv.valores.push_back(aux_rand);
            }
        }
    }
    return new_indv;
}

data validarIndividuo(lista &i, int pos, data v){
    if(pos < SIZE){
        if(pos < limit_op){
            switch(i[pos]){
                case 0:
                    return validarIndividuo(i,pos*2+1,v) +  validarIndividuo(i,pos*2+2,v);
                case 1:
                    return validarIndividuo(i,pos*2+1,v) -  validarIndividuo(i,pos*2+2,v);
                case 2:
                    return validarIndividuo(i,pos*2+1,v) *  validarIndividuo(i,pos*2+2,v);
                case 3:
                    return validarIndividuo(i,pos*2+1,v) /  validarIndividuo(i,pos*2+2,v);
                //case 4:
                  //  return validarIndividuo(i,pos*2+1,v) /  validarIndividuo(i,pos*2+2,v);
            }
        }else{
            int x = 20;
            if(i[pos] == x)
                return v;
            return i[pos];
        }
    }
}

data first_fit(lista &v){
    data suma=0,dif,s,n = 10;
    for (int j = 0; j < n; ++j){
        s= validarIndividuo(v,0,entradas[j]);
        dif = salidas[j]-s;
        suma += pow(dif,2);
        cout<<"\t"<<entradas[j]<< "\t"<<salidas[j]<<"\t"<<s<<" \t => "<<dif<<endl;
    }
    cout<<"Fitness: "<<suma/n<<endl;
    return suma / n;
}

data hallandoFitness(lista &v){
    data suma=0,dif,s,n = 10;
    for (int j = 0; j < n; ++j){
        s= validarIndividuo(v,0,entradas[j]);
        dif = salidas[j]-s;
        suma += pow(dif,2);
    }
    return suma / n;
}

void generarPorcentajes(){
    // file <<"hallando porcentajes: ("<<total_fit<<")"<<endl;
    for (int i = 0; i < initial_poblation.size(); ++i){
        cout<<initial_poblation[i].fitness<<" ";
        initial_poblation[i].porcent = (initial_poblation[i].fitness*100)/total_fit;
        cout<<initial_poblation[i].porcent<<endl;
    }
    total_fit = 0;
}

int metodoTorneo(int number){
    int p1, p2, p3;
    if (number ==2){
        p1 = rand()% initial_poblation.size();
        do{ 
            p2 = rand()% initial_poblation.size();
        }while(p1 == p2);
        cout<<"\tTorneo (2) : Seleccionados => "<< p1<< " - "<<p2<<endl;
        return (initial_poblation[p1].fitness < initial_poblation[p2].fitness)? p1: p2;
    }
    else{
        p1 = rand()% initial_poblation.size();
        do{
            p2 = rand()% initial_poblation.size();
        }while(p1 == p2);
        do{
            p3 = rand()% initial_poblation.size();
        }while(p3 == p2 || p3 == p1);
        cout<<"\tTorneo (3): Seleccionados => "<< p1<< " - "<<p2<< " - "<<p3<<endl;    
        if ((initial_poblation[p1].fitness  < initial_poblation[p2].fitness) && (initial_poblation[p1].fitness  < initial_poblation[p3].fitness))
            return p1;
        else if ((initial_poblation[p2].fitness  < initial_poblation[p1].fitness) && (initial_poblation[p2].fitness  < initial_poblation[p3].fitness))
            return p2;
        else if ((initial_poblation[p3].fitness  < initial_poblation[p2].fitness) && (initial_poblation[p3].fitness  < initial_poblation[p1].fitness))
            return p3;
    }

}

void crearPoblacion(){
    cout <<"Problacion inicial"<<endl;
    indv new_indv;
    for (int i = 0; i < POBLATION; ++i){
        do{
            new_indv = crearIndividuo();
        }while(isnan(validarIndividuo(new_indv.valores,0,0)) or isinf(validarIndividuo(new_indv.valores,0,0)));
        
        new_indv.cadena = leerValoresVec(new_indv.valores,0);
        cout<<i<<") "<<new_indv.cadena<<endl;
        //new_indv.fitness = hallandoFitness(new_indv.valores);
        // total_fit += new_indv.fitness;
        initial_poblation.push_back(new_indv);
    }
    //cout<<"Total fit:"<<total_fit<<endl;
}

void get_fitness(){
    cout<<"Calcular la Aptitud para cada Individudo"<<endl;
    for (int i=0; i<POBLATION;i++){
        cout<<i<<") "<<initial_poblation[i].cadena<<endl;
        initial_poblation[i].fitness=first_fit(initial_poblation[i].valores);
        total_fit += initial_poblation[i].fitness;

    }
    cout<<"Total fit:"<<total_fit<<endl<<endl;;

}
void mutacion(){
    cout <<"*** Mutacion ***"<<endl;
    // srand( time( NULL ) );
    int id = metodoTorneo(3), pos, val, n = -1;
    indv aux;
    data c;
    // mostrarValoresVec( pob[id].valores);file<<endl;
    do{
        aux = initial_poblation[id];
        pos=rand() % SIZE;
        if(pos < limit_op){
            val = rand()% num_op;            
            aux.valores[pos] = val;
        }else{          
            c = (data)(rand() % 101)/100;
            if(c <= 0.5){
                aux.valores[pos]=20;              
            }
            else{
                val = (rand()% 11)-5;
                aux.valores[pos]=val;                
            }
        }
        n++;
        c = validarIndividuo(aux.valores,0,0);
    }while(isnan(c) or isinf(c));

    //mostrarValoresVec(aux.valores);
    cout<<endl;
    // file <<"Repeticiones: "<<n<<endl;
    cout<<"\tGanador: "<<id<<endl;
    aux.cadena = leerValoresVec(aux.valores,0);
    aux.fitness = hallandoFitness(aux.valores);
    cout<<"\tPadre 1: "<<initial_poblation[id].cadena<<endl;
    cout<<"\tPosicion a cambiar : "<<pos<<endl;
    cout<<"\tMutacion generada: "<<aux.cadena<<endl;
    new_poblation.push_back(aux);
}

void cruzamiento(){
    cout <<"*** Cruzamiento ***"<<endl;
    cout<<"\tcapacidad: "<<initial_poblation.size()-new_poblation.size()<<endl;
    int p1, p2, n = -1, r = 2;
    data v1,v2;
    indv h1, h2;
    
    do{
        p1 = metodoTorneo(2);
        do{
            p2 = metodoTorneo(2);
        }while (p1 == p2);
        h1 = initial_poblation[p1]; h2 = initial_poblation[p2];
        h1.valores[r] = initial_poblation[p2].valores[r];
        h1.valores[r*2+1] = initial_poblation[p2].valores[r*2+1] ;
        h1.valores[r*2+2] = initial_poblation[p2].valores[r*2+2] ;
        h2.valores[r] = initial_poblation[p1].valores[r];
        h2.valores[r*2+1] = initial_poblation[p1].valores[r*2+1] ;
        h2.valores[r*2+2] = initial_poblation[p1].valores[r*2+2] ;
        v1 = validarIndividuo(h1.valores,0,0);
        v2 = validarIndividuo(h2.valores,0,0);
        n++;
    }while(isnan(v1) or isnan(v2) or isinf(v1) or isinf(v2));
    
    cout<<"\tGanador 1: "<<p1<<" Ganador 2: "<<p2<<endl;
    h1.cadena = leerValoresVec(h1.valores,0);
    h1.fitness = hallandoFitness(h1.valores);
    h2.cadena = leerValoresVec(h2.valores,0);
    h2.fitness =  hallandoFitness(h2.valores);
    new_poblation.push_back(h1);
    new_poblation.push_back(h2); 
    cout<<"\tPadre 1: "<<initial_poblation[p1].cadena<<endl<<"\tPadre 2: "<<initial_poblation[p2].cadena<<endl;
    cout<<"\tPunto de corte 4"<<endl;
    cout<<"\tHijo 1: "<<h1.cadena<<endl<<"\tHijo 2: "<<h2.cadena<<endl;

}

void Reproduccion(){
    cout <<"*** Reproduccion ***"<<endl;
    int alt = metodoTorneo(3);
    cout<<"\tGanador: "<<alt<<endl;
    cout <<"\tInsertar individuo : "<< initial_poblation[alt].cadena<<endl;
    new_poblation.push_back(initial_poblation[alt]);
}

void selecionandoOperacion(){   
    int op;
    srand( time( NULL ) );
    cout <<"Operando ... "<<endl;
    while(new_poblation.size() < initial_poblation.size()) {
        op = rand()%101;
        //cout<<"tam: "<<new_poblation.size()<<endl;
        cout<<"\n[Aleatorio: "<<op/100.0<<" ]"<<endl;
        if(op <= PER_MUTA)
            mutacion();
        else if((op > PER_MUTA && op <=  PER_MUTA + PER_CROOS) && (initial_poblation.size()-new_poblation.size())> 1 )
            cruzamiento();
        else
            Reproduccion();
    }
    initial_poblation = new_poblation;
    new_poblation.clear();
}



void run(){
    for(int i=0; i < ITER; ++i){        
        if(initial_poblation.size() > 0){
            //generarPorcentajes();
            //mostrarPoblacion();
            // break;
            cout <<"Poblacion ordenada "<<endl;
            sort(initial_poblation.begin(), initial_poblation.end(),ordenar);
            mostrarPoblacion();
            cout<<"\n\t*** Iteracion "<<i<<" ***"<<endl;
            // while(pob.size() > num_poblacion) pob.pop_back();
            selecionandoOperacion();
        }else
            crearPoblacion();
            get_fitness();
            mostrarPoblacion();
        // mostrarPoblacion();
    }
}

int main(){
	srand(time(NULL));
    cout<<"Parámetros"<<endl<<"- Cantidad de Individuos: "<<POBLATION<<endl
        <<"- Cantidad de genes: "<<SIZE<<endl
        <<"- Selección por torneo (2)"<<endl
        <<"- Probabilidad de Cruzamiento: " <<PER_CROOS/100.0<<endl
        <<"\t Seleccion para cruzamiento: Torneo 2"<<endl
        <<"- Probabilidad de Mutacion: " <<PER_MUTA/100.0<<endl
        <<"\t Seleccion para mutacion: Torneo 3"<<endl
        <<"\t Mutacion simple"<<endl
        <<"- Probabilidad de Reproduccion: " <<PER_REPRO/100.0<<endl
        <<"\t Seleccion para reproduccion: Torneo 3"<<endl
        <<"- Cantidad de Iteraciones: "<< ITER<<endl<<endl;
    run();
    
}