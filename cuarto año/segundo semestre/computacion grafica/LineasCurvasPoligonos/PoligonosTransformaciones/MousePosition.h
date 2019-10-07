#ifndef MOUSEPOSITION_H
#define MOUSEPOSITION_H

#include <vector>
#include "Linea.h"
using namespace std;
Linea L_A;
class MousePosition{
    public:
        vector<pair<float,float>>  pares;
        MousePosition(){;}
        void mostrar_puntos();
};

void MousePosition::mostrar_puntos(){
    int x=0;
    for(x;x<pares.size()-1;x++){
        L_A.dibujar(pares[x].first,pares[x].second,pares[x+1].first,pares[x+1].second);
    }
    L_A.dibujar(pares[x].first,pares[x].second,pares[0].first,pares[0].second);
}
#endif // MOUSEPOSITION_H
