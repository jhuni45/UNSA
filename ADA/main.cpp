#include <iostream>

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    int tamano=4;//3;
    //cin>>matriz_n;
    int ** matriz_n = new int * [tamano];

    int A[tamano][tamano]={{0,-2,-7,0},{9,2,-6,2},{-4,1,-4,1},{-1,8,0,-2}};//{{3,2,-1},{-4,4,2},{6,-3,2}};
    int respuesta [tamano][tamano];
    int num_maximo=-1;

    cout<<"inicion"<<num_maximo<<endl;
    int array_temp[tamano]={0,0,0};
    int maximo=0;
    int indice_1=-1;
    int indice_2=-1;
    for(int i=0;i<tamano;i++)
    {
        array_temp[0]=A[i][0] ;
        for(int t=1;t<tamano ;t++){
                array_temp[t]=A[i][t]+array_temp[t-1];
        }

        for(int j=0;j<tamano ;j++)
        {
            if(i==0)
                A[i][j]=array_temp[j];
            else
                A[i][j]=A[i-1][j]+array_temp[j];

            if(num_maximo<A[i][j])
            {
                num_maximo=A[i][j];
                indice_1=j;
                cout<<"cuadros  hacia la izquierda "<<num_maximo<<endl;
            }
        }

        //for(int q=1;q<tamano;q++)
        //{ ///los recuadros interiores
        ///los laterales,reviso cada fila
        for(int s=1;s<tamano-1;s++)
        {
            int menos_num=s-1;
            for(int p=1;p<tamano;p++)
            {
                if(menos_num<p && num_maximo<A[i][p]-A[i][menos_num])
                {
                    num_maximo=A[i][p]-A[i][menos_num];
                    indice_1=p;
                    indice_2=menos_num;
                    //cout<<"num_maximo "<<num_maximo<< "numeros "<<A[i][menos_num]<<" "<< A[i][p-menos_num]<<"resultado"<<A[i][p-menos_num]-A[i][menos_num]<<endl;
                    //menos_num++;
                    cout<<"entre cuadros indice "<<indice_1<<endl;
                }
                //if(num_maximo<)
            }
        }

    }
    ///reviso los verticales
    for(int c=1;c<tamano;c++)
    {
        for(int s=1;s<tamano-1;s++)
        {
            int menos_num=s-1;
            for(int f=tamano-1;f>=1;f--){
                if(num_maximo<A[f][c]- A[menos_num][c])
                {
                    num_maximo=A[f][c]-A[menos_num][c];
                }
            }
        }
    }

    cout<<"el numero maximo = "<<num_maximo<<"indice  1 "<<indice_1<<"indice 2 "<<indice_2<<endl;
    for(int i=0;i<tamano;i++)
    {
        for(int j=0;j<tamano;j++)
        {
            cout<<A[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
