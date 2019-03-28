#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> matriz;

void mostrar(matriz A){
  for (int i=0;i<A.size();i++){
      for (int j=0;j<A[0].size();j++){
      cout<<A[i][j]<< " ";
    }
    cout<<endl;
  }
  cout<<endl;
}

void

void calculos(matriz &datos){
  int A,B,C;

  for (int i=1;i<datos[0].size();i++){
    datos[0][i]+=datos[0][i-1];
  }
  for (int i=1;i<datos.size();i++){
    datos[i][0]+=datos[i-1][0];
  }
  for (int i =1;i<datos.size();i++){
    for (int j=1;j<datos[0].size();j++){
      A=datos[i-1][j-1];
      B=datos[i][j-1];
      C=datos[i-1][j];
      datos[i][j]=B+C-A+datos[i][j];
    }
  }

}
int main(){
  matriz prueba={{0,-2,-7,0},{9,2,-6,2},{-4,1,-4,1},{-1,8,0,-2}};
  mostrar(prueba);
  cout<<"resolucion\n"<<endl;
  vector<int> p1={0,0};
  vector<int> p2={0,0};

  for (int i=0;i<prueba;i++){
    p1[0]=i;
    for (int j=0;j<prueba[0];j++){
      p1[1]=j;
      for (int )
    }
  }

  return 0;
}
