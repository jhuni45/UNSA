#include<bits/stdc++.h>

using namespace std;

#define RATIO 0.05
#define DETECTORS 1000

typedef float value;

typedef vector<vector<value>> matrix;

value PetalLength_min= 1.0;
value PetalLength_max= 6.9;
value PetalWidth_min = 0.1;
value PetalWidth_max = 2.5;

matrix training ={
	{4.7, 1.4},
	{4.5, 1.5},
	{4.9, 1.5},
	{4.0, 1.3},
	{4.5, 1.3},
	{4.7, 1.6},
	{3.3, 1.0},
	{3.9, 1.4},
	{3.5, 1.0},
	{4.2, 1.5},
	{4.0, 1.0},
	{4.7, 1.4},
	{3.6, 1.3},
	{4.4, 1.4},
	{4.5, 1.5},
	{4.1, 1.0},
	{4.5, 1.5},
	{3.9, 1.1},
	{4.8, 1.8},
	{4.0, 1.3},
	{4.9, 1.5},
	{4.7, 1.2},
	{4.3, 1.3},
	{4.4, 1.4},
	{5.0, 1.7},
	{3.5, 1.0},
	{3.8, 1.1},
	{3.7, 1.0},
	{3.9, 1.2},
	{5.1, 1.6},
	{4.5, 1.5},
	{4.7, 1.5},
	{4.4, 1.3},
	{4.1, 1.3},
	{4.0, 1.3},
	{4.4, 1.2},
	{4.6, 1.4},
	{4.0, 1.2},
	{3.3, 1.0},
	{4.2, 1.3},
	{4.2, 1.2},
	{4.2, 1.3},
	{4.3, 1.3},
	{3.0, 1.1},
	{4.1, 1.3},
	{6.0, 2.5},
	{5.1, 1.9},
	{5.9, 2.1},
	{5.6, 1.8},
	{5.8, 2.2},
	{6.6, 2.1},
	{4.5, 1.7},
	{6.3, 1.8},
	{5.8, 1.8},
	{6.1, 2.5},
	{5.1, 2.0},
	{5.3, 1.9},
	{5.5, 2.1},
	{5.0, 2.0},
	{5.1, 2.4},
	{5.3, 2.3},
	{6.7, 2.2},
	{4.9, 2.0},
	{6.7, 2.0},
	{4.9, 1.8},
	{5.7, 2.1},
	{6.0, 1.8},
	{4.9, 1.8},
	{5.6, 2.1},
	{5.8, 1.6},
	{6.1, 1.9},
	{6.4, 2.0},
	{5.6, 2.2},
	{5.1, 1.5},
	{5.6, 1.4},
	{6.1, 2.3},
	{5.6, 2.4},
	{5.5, 1.8},
	{4.8, 1.8},
	{5.4, 2.1},
	{5.6, 2.4},
	{5.1, 2.3},
	{5.1, 1.9},
	{5.9, 2.3},
	{5.7, 2.5},
	{5.2, 2.3},
	{5.0, 1.9},
	{5.2, 2.0},
	{5.4, 2.3},
	{5.1, 1.8}};

matrix test ={
	{4.6, 1.5},
	{4.6, 1.3},
	{4.8, 1.4},
	{4.5, 1.5},
	{4.5, 1.6},
	{5.5, 1.8},
	{6.9, 2.3},
	{5.0, 1.5},
	{5.7, 2.3},
	{4.8, 1.8}};

matrix detectors_list;

void show_matrx(matrix a){
	for (int i=0;i<a.size();i++){
		for (int j=0;j< a[0].size();j++){
			cout<<a[i][j]<< " ";
		}		
		cout<<endl;
	}
	cout<<endl;
}

bool euclidiana(vector<value> temp){
	value eucli_temp=0;
	for (int i=0;i<training.size();i++){
		eucli_temp=sqrt( pow(training[i][0] - temp[0],2) + pow( training[i][1] - temp[1] ,2) );
		if (eucli_temp<RATIO){
			return false;
		}
	}
	return true;
}


void normalizar(){
	for (int i=0;i<training.size();i++){
		training[i][0]=(training[i][0]- PetalLength_min)/(PetalLength_max - PetalLength_min);
		training[i][1]=(training[i][1]- PetalWidth_min)/(PetalWidth_max - PetalWidth_min);
	}
}

vector<value> create_vector(){
	vector<value> temp;

	float val1 = ((float)rand() * (1-0)) /(float)RAND_MAX + 0;
	//cout<<"value1  "<<val1<<endl;
	float val2 = ((float)rand() * (1-0)) /(float)RAND_MAX + 0;
	//cout<<"value2  "<<val2<<endl;
	temp.push_back(val1);
	temp.push_back(val2);
	return temp;
}

void to_test(){
	for (int i=0;i<test.size();i++){
		test[i][0]=(test[i][0]- PetalLength_min)/(PetalLength_max - PetalLength_min);
		test[i][1]=(test[i][1]- PetalWidth_min)/(PetalWidth_max - PetalWidth_min);
	}

	matrix positive, negative;
	value eucli_temp=0;
	
	for (int i = 0;i< test.size();i++){
		int contp=0, contn=0;
		for (int j=0;j<detectors_list.size();j++){
			eucli_temp=sqrt( pow(detectors_list[j][0] - test[i][0],2) + pow( detectors_list[j][1] - test[i][1] ,2) );
			if (eucli_temp>RATIO && contp==0){
				contp++;
				positive.push_back(test[i]);
			}
			else if (eucli_temp<RATIO && contn==0){
				contn++;
				negative.push_back(test[i]);
			}
		}
	}
	cout<<"*** Positivos ***"<<endl;
	show_matrx(positive);
	cout<<"\n*** Negativos ***"<<endl;
	show_matrx(negative);

}

void run(){
	vector<value> temp;
	normalizar();
	cout<<"***** self *****"<<endl;
	show_matrx(training);
	do{
		temp=create_vector();
		if (euclidiana(temp)){
			detectors_list.push_back(temp);
		}
	}while (detectors_list.size()<DETECTORS);
	cout<<"\n*** detectores***"<<endl;
	show_matrx(detectors_list);

	to_test();
}



int main(){
	srand(time(NULL));
	cout<<"*** Parámetros ***"<<endl
		<<"Base de Datos: Iris"<<endl
		<<"Dos Clases: Iris-versicolor (Propia o normal) e Iris-virginica (No-propia o anormal)"<<endl
		<<"Dos Atributos: Largo del Petalo (PetalLength) y Ancho del Petalo(PetalWidth)"<<endl
		<<"R: " <<RATIO<<endl
		<<"Cantidad de Detectores: "<<DETECTORS<<endl
		<<"Minimo Largo del Petalo: "<<PetalLength_min<<endl
		<<"Maximo Largo del Petalo: "<<PetalLength_max<<endl
		<<"Minimo Ancho del Petalo: "<<PetalWidth_max<<endl
		<<"Maximo Ancho del Sépalo: "<<PetalWidth_min<<endl;
	run();

	return 0;
}