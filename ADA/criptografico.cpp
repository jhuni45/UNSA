#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    //string criptografico="XNNEVGKGUGNEJEITSNQITIUCIDPIJXAGSIZVVMBVZQOSLXUUZNÑTJBTVZBMYVWMKKUAVRLMKBQZQMGKZIPKHVXALIRKVDTXGLEVWVMKMKTVVVEIMLUKUMXKGUGDIEXMCIEXLZOWTWYLVZFPUWOKPGRIKIÑZWCTKCIIZIDJSVIPVTRLITPRNEJXALMQIYEVPRLBHIUBIEBQZOTLPHBBÑMKNMDIPZZZZMEMEZIKBUNMEOMJRBRTÑDIEXAMUNLMKNIDCLDPHIZLIZOIHTZRWÑOIEXZCIOGENXXVLUYEPKCVAQZWTIUUMQIICTZTOUQSUXIMLUK";
    string criptografico="DANLWITZZGSFSTGWDFVSDODJSDIQLDLYLNOJUOMODADXUNRSWOVDOEDLSSMIWMLMRWIXYDKMLVWHNAIGJUOZOKAXNWRAVTQHNPBRWNNBODIÑTRWNOEZHSJFSBOCTHNCZFEHRETAAEXND";
    int cada_cuanto=5;//8;
    int j=0;
    vector<string> matriz_cn;
    cout<<"tamano del texto "<<criptografico.size()<<endl<<endl;
    while(j<5)
    {
        int i=j;
        string cn="";
        for(;i<criptografico.size();)
        {
            cn=cn+criptografico[i];
            i+=cada_cuanto;

        }
        matriz_cn.push_back(cn);
        cout<<"c"<<j+1<<" = "<<cn<<endl;
        cout<<endl;
        j++;
    }

    ///comparacion con ABCDEFGHIJKLMNOPQRSTUVWXYZ
    string abcdario="ABCDEFGHIJKLMNÑOPQRSTUVWXYZ";
    vector<vector<int>> resultado;
    for(int k=0;k<matriz_cn.size();k++)
    {
        vector<int> answer_ck;
        for(int p=0;p<abcdario.size();p++)
        {
            int count1=0;
            for(int ck=0;ck<matriz_cn[k].size();ck++)
            {
                if(abcdario[p]==matriz_cn[k][ck])
                {
                  count1++;
                }
            }
            answer_ck.push_back(count1);
        }
        resultado.push_back(answer_ck);
    }
    cout<<"   ";
    for(int caracter=0;caracter<abcdario.size();caracter++)
    {
        cout<<abcdario[caracter]<<"    ";
    }
    cout<<endl;

    for(int crptgm=0;crptgm<resultado.size();crptgm++)
    {
        cout<<"c"<<crptgm+1<<" ";
        for(int caracter=0;caracter<resultado[crptgm].size();caracter++)
        {
            cout<<resultado[crptgm][caracter]<<"    ";
        }
        cout<<endl;
    }

    cout << "Hello world!" << endl;
    return 0;
}
