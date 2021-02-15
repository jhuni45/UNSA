#include<bits/stdc++.h>
using namespace std;

typedef int num;
typedef float numf;

num iteraciones = 50;
num NS = 3;
num D = 2;
num L = (NS*D);
numf lim_inf = -10;
numf lim_sup = 10;
num k, j;
numf phi;
numf Sumfit=0;

typedef struct{
     num id;
     numf x1, x2;
     numf fx=0;
     numf fit=0;
     num cont=0;
     numf prob=0;
}source;

vector<source> vectorS;
source bestS;


numf functionFX(numf x, numf y){
    return pow(x+(2*y)-7,2)+ pow((2*x)+y-5,2);
}

numf fit(numf fx){
    return (fx >= 0)? 1.0/(1.0+fx) : 1.0+abs(fx);
}

void create(){
    source newS;
    bestS.fx=10000.0;
    for(size_t i=0; i< NS ; i++){
        newS.id = i;
        newS.x1=((numf)rand() * (lim_sup-lim_inf)) /(numf)RAND_MAX + lim_inf;
        newS.x2=((numf)rand() * (lim_sup-lim_inf)) /(numf)RAND_MAX + lim_inf;
        newS.fx =functionFX(newS.x1,newS.x2);
        newS.fit = fit(newS.fx);
        
        if(newS.fx < bestS.fx){ 
            bestS = newS;
        }
        vectorS.push_back(newS);        
    }
}

void show_solution(){
    for(size_t i=0; i<vectorS.size(); i++){
        cout<<vectorS[i].id<<" ("<<vectorS[i].x1<<", "<<vectorS[i].x2<<") f(x):"<<vectorS[i].fx<<" fit:"<<vectorS[i].fit<<" prob:"<<vectorS[i].prob<<" cont:"<<vectorS[i].cont<<endl;
    }
}

void get_aleatory(num i){
    do k=rand()%(NS+1); while(k==i);
    j=1+rand()%(D);
    // phi=((numf)rand() * (1-(-1))) /(numf)RAND_MAX + (-1);
}
void get_probability(){
    Sumfit=0;
    for (size_t i = 0; i < vectorS.size(); i++){
        Sumfit += vectorS[i].fit ;
    }
    // cout<<"SumFit: "<<Sumfit<<endl;
    for (size_t i = 0; i < vectorS.size(); i++){
        vectorS[i].prob = vectorS[i].fit / Sumfit;
    }
    cout<<"Suma de fitness:  "<<Sumfit<<endl;
    show_solution();
}
void explora_bee(source &m){
    numf r;
    if(m.cont >= L){
        cout<<"**Fuente abandonada***\n";
        cout<<m.id<<" ("<<m.x1<<", "<<m.x2<<") f(x):"<<m.fx<<" fit:"<<m.fit<<" p:"<<m.prob<<" c:"<<m.cont<<endl;
        r = ((numf)rand() * (1-0)) /(numf)RAND_MAX + 0;
        m.x1 = lim_inf + r*(lim_sup-lim_inf);
        r = ((numf)rand() * (1-0)) /(numf)RAND_MAX + 0;
        m.x2 = lim_inf + r*(lim_sup-lim_inf);
        m.fx = functionFX(m.x1,m.x2);
        m.fit= fit(m.fx);
        m.cont = 0;
        get_probability();
        cout<<m.id<<" ("<<m.x1<<", "<<m.x2<<") f(x):"<<m.fx<<" fit:"<<m.fit<<" p:"<<m.prob<<" c:"<<m.cont<<endl;
    }
    else{
        cout<<"no se modifica"<<endl;
    }
}
void calcu_solutions(source& st,num i){
    bool t = false;
    get_aleatory(i);
    do{
        phi=((numf)rand() * (1-(-1))) /(numf)RAND_MAX + (-1);
        if(j == 1)
            st.x1 = vectorS[i].x1 + phi*(vectorS[i].x1 - vectorS[k].x1);
        else
            st.x2 = vectorS[i].x2 + phi*(vectorS[i].x2 - vectorS[k].x2);
    }while((st.x1 <lim_inf or st.x1>lim_sup) or (st.x2 <lim_inf or st.x2>lim_sup));
    st.fx = functionFX(st.x1,st.x2);
    st.fit = fit(st.fx);
    string flag;
    if(st.fx < vectorS[i].fx){
        flag="Si";
        t=1;
        st.cont = 0;
        vectorS[i] = st;
        if(vectorS[i].fx < bestS.fx) bestS = vectorS[i];
        // bestS = (st.fx > vectorS[it].fx)? st: vectorS[it];
    }else{
        flag="No";  
        t=0;
        st.cont++;
        vectorS[i].cont++;
        //explora_bee(vectorS[i]);
    }
    cout<<"k: "<<k<<" j: "<<j<<" phi: "<<phi<<" ("<<st.x1<<", "<<st.x2<<") f(x): "<<st.fx<<" fit: "<<st.fit<<" Mejora?: "<<flag<<" cont: "<<st.cont<<endl;
}
void possible_solution(){
    cout<<"\n---------- Soluciones Candidatas -----------"<<endl;
    bool t = false;
    Sumfit = 0;
    for (size_t i = 0; i < vectorS.size(); i++){
        source st = vectorS[i]; st.prob = 0;
        calcu_solutions(st,i);
        if(vectorS[i].fx < bestS.fx) bestS = vectorS[i];
    }
    cout<<"\n---------- Mejores soluciones -----------"<<endl;
    // get_probability();
    show_solution();
    cout<<"\n---------- Probabilidad de Seleccion -------------"<<endl;
    get_probability();
    
}

num seleccionar_fuente(numf ale){
    numf l=0;
    for (num i = 0; i < vectorS.size(); i++){
        if(l >= ale or  ale<= l + vectorS[i].prob)
            return i;
        l += vectorS[i].prob;
    }
}

void looker_bee(){
    numf ale;
    num it;
    Sumfit = 0;
    cout<<"\n======================================\n"<<"------------ Enviar a Abejas Observadoras -----------"<<endl;
    for (size_t i = 0; i <NS; i++){
        cout<<"\nAbeja observadora "<<i;
        ale = ((numf)rand() * (1-0)) /(numf)RAND_MAX + 0;
        it = seleccionar_fuente(ale);
        cout<<"\t[ Aleatorio: "<<ale<<"\tFuente (i):"<<it<<" ]\n"<<endl;
        source st=vectorS[it]; st.prob=0; st.cont=0;
        calcu_solutions(st,it);
        // cout<<"*-------mostrando:------------\n";
        get_probability();
        cout<<"----------- Solucion Mejorada ---------------\n";
        show_solution();
        bestS = (vectorS[it].fx < bestS.fx)? vectorS[it]: bestS; 
    }
    cout<<"==================================================\n";
    cout<<"------- Enviar a Abejas Exploradoras -------\n"<<endl;
    for (size_t i =0; i< NS; i++){
        explora_bee(vectorS[i]);
        bestS = (vectorS[it].fx < bestS.fx)? vectorS[it]: bestS;
    }
}

int main(){
    srand(time(NULL));
    cout<<"Parametros:"<<endl
        <<"SN = "<< NS<<endl
        <<"D = "<< D<<endl
        <<"LimD = "<< lim_inf<<";" <<lim_sup<<endl
        <<"l = "<<L<<endl
        <<"Iteraciones = "<<iteraciones<<endl<<endl;

    for(size_t it = 0; it <= iteraciones; it++){
        if(vectorS.size()>0){
            cout<<"\n********* Iteracion "<<it<<" *********\n";
            show_solution();
            // cout<<" Nuevas soluciones para abejas empleadas"<<endl;
            possible_solution();
            looker_bee();
            cout<<"mejor: "<<bestS.x1<<" "<<bestS.x2<<" f(x):"<<bestS.fx<<" fit:"<<bestS.fit<<endl;
        }else{
            cout<<"Fuentes de alimento iniciales"<<endl;
            create();
            show_solution();
            cout<<"mejor: "<<bestS.x1<<" "<<bestS.x2<<" f(x):"<<bestS.fx<<" fit:"<<bestS.fit<<endl;
        }    
    }
}