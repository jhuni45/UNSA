#include <iostream>

using namespace std;

int d[100][100][100];
int n;

void floyd_warshall();


int main (int argc, const char * argv[])
{
    cout<<"Please enter the number of vertices\n";
    cin>>n;
    cout<<"Please enter the adjacency matrix, enter 10000 in case of no path\n";
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin>>d[i][j][0];
        }
    }
    floyd_warshall();
    cout<<"The final matrix is\n";
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cout<<d[i][j][n-1]<<"\t";
        }
        cout<<"\n";
    }
    return 0;
}
void floyd_warshall()
{
    for ( int k=1;k<n;k++)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                d[i][j][k]=d[i][j][k-1];
                for(int m =0;m<n;m++)
                {
                    if(i==m)
                        continue;
                    if(d[i][j][k]>(d[i][m][k-1]+d[m][j][0]))
                    {
                        d[i][j][k]=d[i][m][k-1]+d[m][j][0];
                    }
                }
            }
        }
    }
}
