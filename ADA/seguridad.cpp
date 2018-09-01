#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;


/*map<string,int> c2;
map<string,int> c3;
map<string,int> c4;
map<string,int> c5;*/


string criptosistemas(string A,int x,int i){
  string texto="";
  while(i<A.length()){
    texto+=A[i];
    i+=x;
    //cout<<i<<" "<<endl;
  }
  return texto;
}
vector <int> numeros(string A){
  string aux="A";

}

int main (){
  /*string texto="DANLWITZZGSFSTGWDFVSDODJSDIULDLYLNOJUOMODADXUNRSWOVDOEDLSSMIWMLMRWIXYDKMLVWHNAIGJUOZOKAXNWRAVTQHNPBRWNNBODI-TRWNOEZHSJFSBOCTHNCZFEHRETAAEXND";
  for (int i =0;i<5;i++){
    cout<<criptosistemas(texto,5,i);
    cout<<endl;
  }*/
  map<string,int> c1["A"] = 0;
  cout<<c1.first<<" "<<c1.second<<endl;


}
//DANLWITZZGSFSTGWDFVSDODJSDIULDLYLNOJUOMODADXUNRSWOVDOEDLSSMIWMLMRWIXYDKMLVWHNAIGJUOZOKAXNWRAVTQHNPBRWNNBODIÑTRWNOEZHSJFSBOCTHNCZFEHRETAAEXND



//45 10
//5
