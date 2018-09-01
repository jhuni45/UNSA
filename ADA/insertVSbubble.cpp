#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>
#include <cstdio>
///Algoritmos de ordenamiento///


using namespace std;

typedef int num;
typedef double real;
typedef vector<num> myvector;

void mostrar(myvector A){
    for (num i =0;i<A.size();i++){
        cout<<A[i]<<"\t";
    }
    cout<<endl;
}

real AUX;
bool flag;
///Algoritmo Bubble Sort (CRECIENTE)
void bubblesort(myvector A){
    //cout<<"Bubble sort"<<endl;
    for (num i=0;i<A.size();i++){
        flag=false;
        for(num j=0;j<A.size()-1-i;j++){
            if (A[j]>A[j+1]){
                AUX=A[j];
                A[j]=A[j+1];
                A[j+1]=AUX;
                flag=true;
            }
        }
        if(flag==false){
        	break;
        }
        //mostrar(A);
        //cout<<endl;
    }
}

///Algoritmo Insert Sort (CRECIENTE)
void insertsort(myvector A){
    //cout<<"Insert Sort"<<endl;
    for (num i=1;i<A.size();i++){
        num val=A[i];
        num j=i-1;
        while(j>=0 && A[j]>val){
            A[j+1]=A[j];
            j--;
        }
    A[j+1]=val;
    //mostrar(A);
    //cout<<endl;
    }
}
void merge(myvector &aVector, int size, int low, int middle, int high){
    cout<<"entre al merge"<<endl;
    int temp[size];
    for(int i = low; i <= high; i++){
        temp[i] = aVector[i];
    }
    int i = low;
    int j = middle+1;
    int k = low;

    while (i <= middle && j <= high){
        if(temp[i] <= temp[j]){
            aVector[k] = temp[i];
            ++i;
        }
        else {
            aVector[k] = temp[j];
            ++j;
        }
        ++k;
    }
    while (i <= middle){
        aVector[k] = temp[i];
        ++k;
        ++i;
    }
}

void mergeSort(myvector &aVector, int size, int low, int high){
    if (low < high){
        int middle = (low + high) / 2;
        mergeSort(aVector, size, low, middle);
        cout<<"middle= "<<middle<<"low= "<<low<<"hish = "<<high<<endl;
        mergeSort(aVector, size, middle+1, high);
        cout<<"middle= "<<middle<<"low= "<<low<<"hish = "<<high<<endl;
        merge(aVector, size, low, middle, high);
    }
    mostrar(aVector);
}


int main (){
	ifstream input;
	ofstream graficar;
    input.open("datos.txt");
    string letra;
    myvector valores;
    int tamano=0;
    clock_t TBubble,TInsert;
    graficar.open("graficar.csv");
    graficar<<"tiempo bubble insert"<<endl;
    while(getline(input,letra)){
    	string aux;
    	for(int i=0;i<letra.length();i++){
    		if (letra[i]==' '){
    			int val=atoi(letra.c_str());
    			valores.push_back(val);
    		}
    		aux+=letra[i];
    	}

    	TBubble=clock();
    	bubblesort(valores);
    	TBubble=clock()-TBubble;

    	TInsert =clock();
    	insertsort(valores);
    	TInsert =clock() - TInsert;
    	graficar<<tamano<<" "<<((float)TBubble)/CLOCKS_PER_SEC<<" "<<((float)TInsert)/CLOCKS_PER_SEC<<endl;
    	tamano++;
    }
    graficar.close();


    return 0;
}
