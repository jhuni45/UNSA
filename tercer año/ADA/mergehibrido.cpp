///tarea merge hibrido (insertsort) VS merge normal
///Chavez Cruz Jhunior
///Analisis y Diseño de Algoritmos
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <fstream>
#include <cstdio>

using namespace std;

vector<int> merge(vector<int> &left, vector<int>& right){
	vector<int> result;
	while(left.size()>0 && right.size()>0){
		if(left[0]<=right[0]){
			result.push_back(left[0]);
			left.erase(left.begin()+0);
		}
		else{
			result.push_back(right[0]);
			right.erase(right.begin()+0);
		}
	}
	while (left.size()>0){
		result.push_back(left[0]);
		left.erase(left.begin()+0);
	}
	while (right.size()>0){
		result.push_back(right[0]);
		right.erase(right.begin()+0);
	}
	return result;
}
vector<int> merge_sort(vector<int>&  m){
	if (m.size() <=1){
		return m;
	}
	vector<int> left;
	vector<int> right;
	for (int i=0;i<m.size();i++){
		if (i<(m.size()/2)){
			left.push_back(m[i]);
		}		
		else{
			right.push_back(m[i]);
		}
	}
	right=merge_sort(right);
	left=merge_sort(left);
	
	vector<int>aux=merge(left,right);
	return aux;
}

void intercala(vector<int> &A,int p,int q, int r){
	vector<int> B=A;
	int i,j;
	for (i=p;i<=q;i++){
		B[i]=A[i];
	}
	for (j=q+1;j<=r;j++){
		B[r+q+1-j]=A[j];
	}
	i=p;
	j=r;
	for(int k=p;k<=r;k++){
		if (B[i]<=B[j]){
			A[k]=B[i];
			i+=1;
		}
		else{
			A[k]=B[j];
			j-=1;
		}
	}
}

void Rintercala (vector<int> &A,int p,int q,int r){
	if (p<r){
		Rintercala(A,p,(p+q)/2,q);
		Rintercala(A,q+1,(r+q+1)/2,r);
		intercala(A,p,q,r);
	}
}

void insertsort(vector<int>& A){
    for (int i=1;i<A.size();i++){
        int val=A[i];
        int j=i-1;
        while(j>=0 && A[j]>val){
            A[j+1]=A[j];
            j--;
        }
    A[j+1]=val;
    }
}

void merge_hibrido(vector<int>&A,int p, int q,int r){
	if ((r-p)<=128){
		insertsort(A);
	}
	else{
		merge_hibrido(A,p,(p+q)/2,q);
		merge_hibrido(A,q+1,(r+q+1)/2,r);
		intercala(A,p,q,r);
	}
}

int main(){
	ifstream input;
	ofstream graficar;
    input.open("datos.txt");
    string letra;
    int tamano=0,X=0;
	vector<int> valores;
	clock_t TMerge,THibrido;
	graficar.open("hibridoVSmerge.csv");
    graficar<<"tiempo merge hibrido(insert)"<<endl;
    
    while(getline(input,letra)){
    	string aux;
    	for(int i=0;i<letra.length();i++){
    		if (letra[i]==' '){
    			int val=atoi(letra.c_str());
    			valores.push_back(val);
    		}
    		aux+=letra[i];
    	}

    	TMerge=clock();
    	merge_sort(valores);
    	TMerge=clock()-TMerge;

    	THibrido =clock();
    	merge_hibrido(valores,0,(valores.size()-1)/2,valores.size()-1);
    	THibrido =clock() - THibrido;
    	graficar<<tamano<<" "<<((float)TMerge)/CLOCKS_PER_SEC<<" "<<((float)THibrido)/CLOCKS_PER_SEC<<endl;
    	tamano++;
    	X++;
    	if(tamano==1)
    		X--;
    }
    graficar.close();
	return 0;
}
