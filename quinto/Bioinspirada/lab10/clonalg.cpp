#include <iostream>
#include <bitset>
#include <vector>
#include <functional>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

#define NUM_OF_BITS 16

typedef double TypeVal;
typedef function<TypeVal(vector<TypeVal>)> FunFit;

TypeVal funFit(vector<TypeVal> valores){
	return  pow(valores[0],2) + pow(valores[1], 2);
}


class Leucocito{
	public:
		Leucocito(){}
		Leucocito(TypeVal mutationFactor, int cantidadClones, FunFit funFit);
		Leucocito(Leucocito *);
		vector<bitset<NUM_OF_BITS>> valores;
		vector<Leucocito> clones;
		void setFitness();
		void setAfinidad(TypeVal maxFit, TypeVal minFit);
		void setClones();
		void mutacion();
		void print();
		void printClones();
		TypeVal fitness;
		TypeVal afinidad;
		TypeVal mutationFactor;
		int cantidadClones;
		TypeVal mutationRate;
		FunFit funFit;
};

Leucocito::Leucocito(Leucocito * nuevo){
	this->valores = nuevo->valores;
	this->fitness = nuevo->fitness;
	this->afinidad = nuevo->afinidad;
	this->mutationFactor = nuevo->mutationFactor;
	this->cantidadClones = nuevo->cantidadClones;
	this->mutationRate = nuevo->mutationRate;
	this->funFit = nuevo->funFit;
}

Leucocito::Leucocito(TypeVal mutationFactor, int cantidadClones, FunFit funFit){
	this->mutationFactor = mutationFactor;
	this->cantidadClones = cantidadClones;
	this->funFit = funFit;
	string binary = "";
	int numRandom = 0;
	for(int i = 0; i < 2; i++){
		binary.clear();

		for(int j = 0; j < NUM_OF_BITS; j++){
			numRandom = rand() % 2;
			if(numRandom == 1) binary.push_back('1');
			else binary.push_back('0');
		}
		valores.push_back(bitset<NUM_OF_BITS>(binary));
	}

}

void Leucocito::print(){
	cout<<"x=[";
	TypeVal temp = 0;
	for(int i = 0; i < valores.size(); i++){
		temp = -5 + (TypeVal) ((10) / (TypeVal) (pow(2,NUM_OF_BITS)) * valores[i].to_ulong());
		cout<<" "<<temp<<",";
	}
	cout<<"], f = "<<fitness<<", a = "<<afinidad<<endl;
}

void Leucocito::printClones(){
	for(auto clon : clones){
		cout<<clon.valores[0].to_string()<<clon.valores[1].to_string()<<endl;
	}
}

void Leucocito::setFitness(){
	vector<TypeVal> vals;
	for(auto bs : valores){
		vals.push_back(bs.to_ulong());
	}
	for(int i = 0; i < vals.size(); i++){
		vals[i] = -5 + (TypeVal) ((10) / (TypeVal) (pow(2,NUM_OF_BITS)) * vals[i]);
	}
	fitness = funFit(vals);
}

void Leucocito::setAfinidad(TypeVal maxFit, TypeVal minFit){
	if(maxFit == minFit) afinidad  = 0;
	else afinidad = 1.0 - (fitness / (maxFit - minFit));
}

void Leucocito::setClones(){
	mutationRate = exp(mutationFactor * afinidad);
	clones.clear();
	for(int i = 0; i < cantidadClones; i++){
		clones.push_back(Leucocito(this));
		clones.back().mutacion();
		clones.back().setFitness();
	}
}

void Leucocito::mutacion(){
	float random = 0;
	string binary = "";
	for(int i = 0; i < valores.size(); i++){
		binary = valores[i].to_string();
		for(int j = 0; j < binary.size(); j++){
			random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			if(random >= mutationRate){
				if(binary[j] == '1') binary[j] = '0';
				else binary[j] = '1';
			}
		}
		valores[i] = bitset<NUM_OF_BITS>(binary);
	}
}


class Clonalg{
	public:
		Clonalg(){}
		void run(int iteraciones, int tamPobl, int numRandoms, TypeVal mutationFactor,
					 TypeVal cloneRate, FunFit funFit);
		vector<Leucocito> poblacion;
};


void Clonalg::run(int iteraciones, int tamPobl, int numRandoms, TypeVal mutationFactor,
					 TypeVal cloneRate, FunFit funFit){
	int cantidadClones = tamPobl * cloneRate;
	for(int i = 0; i < tamPobl; i++){
		poblacion.push_back(Leucocito(mutationFactor, cantidadClones, funFit));
	}

	TypeVal maxFit = -1;
	TypeVal minFit = -1;
	vector<Leucocito> nuevaPobl;

	for(int i = 0; i < iteraciones; i++){
		cout<<"Iteracion "<<i + 1<<endl;
		maxFit = -1;
		minFit = -1;
		for(auto iter = poblacion.begin(); iter != poblacion.end(); ++iter){
			iter->setFitness();
			if(maxFit == -1 or maxFit < iter->fitness) maxFit = iter->fitness;
			if(minFit == -1 or minFit > iter->fitness) minFit = iter->fitness;
		}

		for(auto iter = poblacion.begin(); iter != poblacion.end(); ++iter){
			iter->setAfinidad(maxFit, minFit);
			iter->setClones();
			nuevaPobl.push_back((*iter));
			nuevaPobl.insert(nuevaPobl.end(), iter->clones.begin(), iter->clones.end());
			iter->print();
			cout<<"MutationRate = "<<iter->mutationRate<<endl;
			iter->printClones();
		}

		cout<<endl;
		cout<<"Aleatorios"<<endl;

		for(int j = 0; j < numRandoms; j++){
			nuevaPobl.push_back(Leucocito(mutationFactor, cantidadClones, funFit));
			nuevaPobl.back().setFitness();
			nuevaPobl.back().print();
		}
		sort(nuevaPobl.begin(), nuevaPobl.end(), [] (Leucocito a, Leucocito b){
			return a.fitness < b.fitness;
		});
		nuevaPobl.erase(nuevaPobl.begin() + tamPobl, nuevaPobl.end());
		poblacion = nuevaPobl;

		cout<<"Nueva Poblacion"<<endl;

		for(auto iter = poblacion.begin(); iter != poblacion.end(); ++iter){
			iter->print();
		}
	}
}


int main(){
	srand(time(NULL));
	Clonalg cl;
	int iteraciones = 1000;
	int tamPobl = 4;
	int numRandoms = 2;
	TypeVal mutationFactor = -2.5;
	TypeVal cloneRate = 0.5;
	cl.run(iteraciones, tamPobl, numRandoms, mutationFactor, cloneRate, funFit);
}