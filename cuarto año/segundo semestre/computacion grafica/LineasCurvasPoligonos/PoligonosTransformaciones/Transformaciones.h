#ifndef TRANSFORMACIONES_H
#define TRANSFORMACIONES_H
#include <vector>
#include <math.h>
#include "MousePosition.h"
using namespace std;
const int N=3;
class Transformaciones{
    float matriz_traslacion[N][N];
    float matriz_escalado[N][N];
    float matriz_rotacion[N][N];
    float matriz_coordenadas[N][1];

    float dx=1,dy=0,angulo=0,sx=0,sy=0;
    vector<pair<float,float>> VN;
public:
    Transformaciones(){;}
    void rotacion(vector<pair<float,float>>&,float);
    void desplazamiento(vector<pair<float,float>>&,float,float);
    void scalamiento(vector<pair<float,float>>&,float,float);
    void rellenar_matriz_traslacion();
    void rellenar_matriz_rotacion(pair<float,float>);
    void rellenar_matriz_escalamiento(pair<float,float>);
    void multiplicacion_matriz_traslacion(pair<float,float>);
    void multiplicacion_matriz_rotacion(pair<float,float>);
    void multiplicacion_matriz_escalamiento(pair<float,float>);
};

void Transformaciones::rellenar_matriz_escalamiento(pair<float,float> V){
    matriz_escalado[0][0]=sx;
    matriz_escalado[0][1]=0;
    matriz_escalado[0][2]=V.first*(1-sx);

    matriz_escalado[1][0]=0;
    matriz_escalado[1][1]=sy;
    matriz_escalado[1][2]=V.second*(1-sy);

    matriz_escalado[2][0]=0;
    matriz_escalado[2][1]=0;
    matriz_escalado[2][2]=1;

    matriz_coordenadas[0][0]=1;
    matriz_coordenadas[0][1]=1;
    matriz_coordenadas[0][2]=1;
}

void Transformaciones::rellenar_matriz_rotacion(pair<float,float> P){
    matriz_rotacion[0][0]=cos(angulo);
    matriz_rotacion[0][1]=-sin(angulo);
    matriz_rotacion[0][2]=P.first*(1-cos(angulo))+P.second*sin(angulo);

    matriz_rotacion[1][0]=sin(angulo);
    matriz_rotacion[1][1]=cos(angulo);
    matriz_rotacion[1][2]=P.second*(1-cos(angulo))-P.first*sin(angulo);;

    matriz_rotacion[2][0]=0;
    matriz_rotacion[2][1]=0;
    matriz_rotacion[2][2]=1;

    matriz_coordenadas[0][0]=1;
    matriz_coordenadas[0][1]=1;
    matriz_coordenadas[0][2]=1;
}

void Transformaciones::rellenar_matriz_traslacion(){
    matriz_traslacion[0][0]=1;
    matriz_traslacion[0][1]=0;
    matriz_traslacion[0][2]=dx;

    matriz_traslacion[1][0]=0;
    matriz_traslacion[1][1]=1;
    matriz_traslacion[1][2]=dy;

    matriz_traslacion[2][0]=0;
    matriz_traslacion[2][1]=0;
    matriz_traslacion[2][2]=1;

    matriz_coordenadas[0][0]=1;
    matriz_coordenadas[0][1]=1;
    matriz_coordenadas[0][2]=1;
}

void Transformaciones::multiplicacion_matriz_traslacion(pair<float,float> P){
    matriz_coordenadas[0][0]=P.first;
    matriz_coordenadas[0][1]=P.second;
    float sumador=0;
    float x1=0,y1=0;
    for(int x=0;x<N;x++){
        for(int y=0;y<N;y++)
            sumador+=matriz_traslacion[x][y]*matriz_coordenadas[y][0];
        if(x==0)
            x1=sumador;
        else if (x==1)
            y1=sumador;
        sumador=0;
    }
    VN.push_back(make_pair(x1,y1));
}

void Transformaciones::desplazamiento(vector<pair<float,float>> &V,float dx_,float dy_){
    dx=dx_;
    dy=dy_;
    rellenar_matriz_traslacion();
    for(int x=0;x<V.size();x++)
        multiplicacion_matriz_traslacion(V[x]);
    V.clear();
    V=VN;
    VN.clear();

}

void Transformaciones::multiplicacion_matriz_rotacion(pair<float,float> P){
    matriz_coordenadas[0][0]=P.first;
    matriz_coordenadas[0][1]=P.second;
    float sumador=0;
    float x1=0,y1=0;
    for(int x=0;x<N;x++){
        for(int y=0;y<N;y++)
            sumador+=matriz_rotacion[x][y]*matriz_coordenadas[y][0];
        if(x==0)
            x1=sumador;
        else if (x==1)
            y1=sumador;
        sumador=0;
    }
    VN.push_back(make_pair(x1,y1));
}

void Transformaciones::rotacion(vector<pair<float,float>> &V,float ang){
    angulo=ang;
    rellenar_matriz_rotacion(V[0]);
    for(int x=0;x<V.size();x++)
        multiplicacion_matriz_rotacion(V[x]);
    V.clear();
    V=VN;
    VN.clear();
}

void Transformaciones::multiplicacion_matriz_escalamiento(pair<float,float> P){
    matriz_coordenadas[0][0]=P.first;
    matriz_coordenadas[0][1]=P.second;
    float sumador=0;
    float x1=0,y1=0;
    for(int x=0;x<N;x++){
        for(int y=0;y<N;y++)
            sumador+=matriz_escalado[x][y]*matriz_coordenadas[y][0];
        if(x==0)
            x1=sumador;
        else if (x==1)
            y1=sumador;
        sumador=0;
    }
    VN.push_back(make_pair(x1,y1));
}

void Transformaciones::scalamiento(vector<pair<float,float>> &V,float _sx,float _sy){
    sx=_sx;
    sy=_sy;
    rellenar_matriz_escalamiento(V[0]);

    for(int x=0;x<V.size();x++)
        multiplicacion_matriz_escalamiento(V[x]);
    V.clear();
    V=VN;
    VN.clear();
}
#endif