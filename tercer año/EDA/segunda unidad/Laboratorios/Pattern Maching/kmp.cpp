#include <iostream>
#include <vector>

using namespace std;

void failureFunction(string pattern, vector<int> &F){
	F[0]=0;
	int m=pattern.size();
	int i=1, j=0;
	while(i<m){
		if(pattern[i]==pattern[j]){
			F[i]=j+1;
			i+=1;
			j+=1;
		}
		else if (j>0){
			j=F[j-1];
		}
		else{
			F[i]=0;
			i+=1;
		}
	}
}

int kmpFunction(string text, string pattern){
	vector<int> F(pattern.size());
	failureFunction(pattern,F);
	int i=0,j=0;
	int n=text.size();
	int m=pattern.size();
	while(i<n){
		if(text[i]==pattern[j]){
			if (j==m-1)
				return i-j;
			else{
				i+=1;
				j+=1;
			}
		}
		else{
			if(j>0)
				j=F[j-1];
			else
				i+=1;
		}
	}
	return -1;

}

int main(){
	string text="hola como estas";
	string pattern="estas";
	int result=kmpFunction(text,pattern);
	if (result==-1)
		cout<<"No matching"<<endl;
	else{
		cout<<"Encontrado en la posicion: "<<result+1<<endl;
		cout<<"Posicion final: "<<(result+pattern.size())<<endl;
	}
	return 0;
}
