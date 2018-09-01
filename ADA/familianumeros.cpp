#include <iostream>
#include <vector>

using namespace std;

#define FOR(a,b) for (a=0;a<b;a++);
typedef vector<vector<int>> mymatriz;

void mostrar(mymatriz A){
  for (int i=0;i<A.size();i++){
      for (int j=0;j<A[0].size();j++){
      cout<<A[i][j]<< " ";
    }
    cout<<endl;
  }
  cout<<endl;
}

int main(){
  mymatriz matriz={{0,-2,-7,0},{9,2,-6,2},{-4,1,-4,1},{-1,8,0,-2}};
  int n_max=-1;

  vector<int> temp={0,0,0,0};
  int i,j;
  int maximo=0, ind_A=-1, ind_B=-1;
  for (int i=0;i<matriz.size();i++){
    temp[0]= matriz[i][0];
    for (int g=1;g<matriz.size();g++){
      temp[g]=matriz[i][g]+ temp[g-1];
    }
    for (int j=0;j<matriz.size();j++){
      if (i==0){
        matriz[i][j]=temp[j];
      }
      else{
        matriz[i][j]=matriz[i-1][j]+temp[j];
      }
      if (n_max<matriz[i][j]){
        n_max=matriz[i][j];
        ind_A=j;
      }
    }
    for (int s=1;s<matriz.size()-1;s++){
      int aux=s-1;
      for (int p=1;p<matriz.size();p++){
        if (aux<p && n_max<matriz[i][p]-matriz[i][aux]){
          n_max=matriz[i][p]- matriz[i][aux];
          ind_A=p;
          ind_B=aux;
          //cout<<"cuadrados"<<endl;
        }
      }
    }
  }
  //VERTICALES
  for (int k=1;k<matriz.size();k++){
    for (int l=1;l<matriz.size()-1;l++){
      int aux=l-1;
      for (int m=matriz.size()-1;m>=1;m--){
        if (n_max<matriz[m][k]-matriz[aux][k]){
          n_max=matriz[m][k]-matriz[aux][k];
        }
      }
    }
  }
  mostrar(matriz);
  return 0;
}
