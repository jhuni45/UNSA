#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void mostrar(vector<vector<char>> A){
	for (int i=0;i<A.size();i++){
		for (int j = 0; j < A[0].size(); j++)
		{
			cout<<A[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

int paso_base(vector<vector<char>> &grilla, int fila, int columna)
{
	if ((fila >=grilla.size() || fila <0 && columna>=grilla[0].size() || columna<0) || grilla[fila][columna]=='T'){
		return 0;
	}
	else
	{
		if(grilla[fila][columna]=='A')
		{
			cout<<"holaaa"<<endl;
			grilla[fila][columna]='T';
			mostrar(grilla);
			return 1+paso_base(grilla,fila-1, columna-1)+
			paso_base(grilla,fila-1,columna)+
			paso_base(grilla,fila-1,columna+1 )+
			paso_base(grilla,fila,columna-1 )+
			paso_base(grilla,fila, columna+1 )+
			paso_base(grilla,fila+1, columna-1 )+
			paso_base(grilla,fila+1,columna )+
			paso_base(grilla,fila+1,columna+1 );

		}

	}
	

}

int main()
{
	vector<vector<char>> grilla={{'T','T','T','T','T','T','T','T','T'},
								 {'T','T','A','A','T','T','A','T','T'},
								 {'T','A','A','T','T','T','T','T','T'},
								 {'T','A','A','A','T','A','A','T','T'},
								 {'T','T','T','A','A','A','T','T','T'},
								 {'T','T','T','T','T','T','T','T','T'},
								 {'T','T','T','A','A','T','T','A','T'},
								 {'T','T','A','T','A','T','T','T','T'},
								 {'T','T','T','T','T','T','T','T','T'}};
	mostrar(grilla);
	cout<<paso_base(grilla,6,4);
	cout<<endl;
	//mostrar(grilla);
	return 0;
}