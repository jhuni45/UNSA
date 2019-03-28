#include <iostream>

using namespace std;

int  patternMatching(string text, string patter){
	int n=text.size();
	int m=patter.size();
	for (int i=0;i<n-m;i++){
		int j=0;
		while (j<m && text[i+j]==patter[j]){
			j+=1;
			if (j==m)
				return i;
			//else
			//	break;
		}
	}
	return -1;
}
int main()
{
	string text="hola como estas";
	string patter="la";

	int result=patternMatching(text,patter);
	if (result==-1)
		cout<<"No matching"<<endl;
	else{
		cout<<"Encontrado en la posicion: "<<result+1<<endl;
		cout<<"Posicion final: "<<(result+patter.size())<<endl;
	}



}