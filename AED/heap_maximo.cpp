#include <iostream>
#include <vector>

using namespace std;

typedef vector<float> lista;
void probar(lista &, int);
void mostrar(lista lis);
///max heap
void insertar(lista & lis, float valor){
    lis.push_back(valor);
    int pos=lis.size();
    if (lis.size()>2){
        //cout<<"entre al if"<<endl;
        probar(lis, pos-1);
    }

}
void probar(lista &lis, int hijo){
    if (hijo==1)
        return;
    //cout<<"el hijo"<<lis[hijo]<<endl;
    int pos_padre=hijo/2;
    //cout<<"padre "<<lis[pos_padre]<<endl;
    if (lis[hijo] > lis[pos_padre]){
        //cout<<"menor"<<endl;
        mostrar(lis);
        return;
    }
    if (lis[hijo] < lis[pos_padre]){
        //cout<<"mayor"<<endl;
        float aux=lis[hijo];
        lis[hijo]=lis[pos_padre];
        lis[pos_padre]=aux;
        probar(lis,pos_padre);
    }
}
void probar_eliminar(lista &lis, int padre){
    if (padre==lis.size()-1 ||padre==lis.size()-2 )
        return;
    int hijo_izq=padre *2;
    int hijo_der=(padre*2)+1;
    int mayor;
    if (lis[hijo_izq]<lis[hijo_der])
        mayor=hijo_izq;
    else if (lis[hijo_izq]>lis[hijo_der])
        mayor=hijo_der;
    if (lis.size()==3)
        mayor=2;
    if (lis[padre]<lis[mayor]){
        //cout<<"bien el"<<endl;
        return;
    }
    if (lis[padre] > lis[mayor]){
        ///cout<<"mal el"<<endl;
        float aux=lis[padre];
        lis[padre]=lis[mayor];
        lis[mayor]=aux;;
        probar_eliminar(lis,mayor);
    }


}
void eliminar(lista &lis){
	if (lis.size()==1){
		cout<<"el heap esta vacio"<<endl;
	}
    if (lis.size()==2){
        lis.erase(lis.begin()+1);
    }
    else if(lis.size()>2){
        lis[1]=lis[lis.size()-1];
        lis.erase(lis.begin()+lis.size()-1);
        probar_eliminar(lis,1);
    }
}

void mostrar(lista lis){
    for (int i =0; i<lis.size();i++){
        cout<<lis[i]<<" ";
    }
    cout<<endl;
}
void consultar(lista lis){
	if (lis.size()==2){
		cout<<"El dato mayor es: "<<lis[1]<<"\nEl dato menor es :"<<lis[1]<<endl;
	}
	if (lis[1]>lis[2]){
		cout<<"Datos del max-heap\nMayor: "<<lis[1]<<"\nMenor: "<<lis[lis.size()-1]<<endl;
	}
	else 
		cout<<"Datos del min-heap\nMayor: "<<lis[lis.size()-1]<<"\nMenor: "<<lis[1]<<endl;

}
int main(){
    lista A;
    int op,valor;
    A.push_back(0);
    do{
        cout<<"Menu de opciones\n[1] insertar\n[2] mostrar \n[3] Eliminar \n[4] Salir\n"<<endl;
        cin>>op;
        cout<<endl;
        if (op<1 || op>4){
            cout<<"opcion invalida"<<endl;
        }
        else{
            switch(op){
                case 1:
                    cout<<"Ingrese el valor"<<endl;
                    cin>>valor;
                    insertar(A,valor);
                    cout<<endl;
                    break;
                case 2:
                    mostrar(A);
                    cout<<endl;
                    break;
                case 3:
                    eliminar(A);
                    break;
            }
        }
    }while(op!=4);
    return 0;
}
