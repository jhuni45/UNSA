#include <iostream>
#include <vector>

using namespace std;

int lastOccurenceFunction(string pattern,vector<int>& L){
	for (int i=0;i<256;i++){
		L[i]=pattern.size();
	}
	for(int i=0;i<pattern.size()-1;i++){
		L[pattern[i]]=pattern.size()-i-1;
	}
}

int boyer_moore(string text, string pattern){
	vector<int> L(256);
	lastOccurenceFunction(pattern,L);
	int m=pattern.size();
	int i=m-1;
	int j=m-1;
	do{
		if (text[i]==pattern[j]){
			if (j==0)
				return i;
			else{
				i-=1;
				j-=1;
			}		}
		else{
			int l=L[text[i]];
			i=i+m-min(j,1+l);
			j=m-1;	
		}

	}while(i>(text.size()-1));
	
	return -1;
}

int main (){
	string text="hola como estas";
	string pattern="estas";
	int result=boyer_moore(text,pattern);
	if (result==-1)
		cout<<"No matching"<<endl;
	else{
		cout<<"Encontrado en la posicion: "<<result+1<<endl;
		cout<<"Posicion final: "<<(result+pattern.size())<<endl;
	}
	
	return 0;
}