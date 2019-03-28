#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>
#include <list>
#include <tuple>

using namespace std;

/*
    rectangulo (A , 1 ,7 ,3 ,4)
    rectangulo (B , 8 ,14 ,2 ,13)

    semillas: < rectangulo >
*/

typedef tuple<string,float,float,float,float> rectangulo;
typedef vector<rectangulo> rectangulos;
typedef vector<int> Vector;

class RTree
{
public:
    pair<string,int> minX;
    pair<string,int> maxX;
    pair<string,int> minY;
    pair<string,int> maxY;
    Vector XFinales;
    Vector YFinales;
    float DNY,DSY,DTY;
    float DNX,DSX,DTX;
    rectangulos Rectangulos;
    rectangulos Semillas;
    RTree(rectangulos _rect)
    {
        Rectangulos = _rect;
    }
public:
    void ObtenerDN();
    void ObtenerFinales();
    void ImprimirRectangulos();
};

void RTree::ObtenerDN()
{
    string s_minX=get<0>(Rectangulos[0]),s_maxX=get<0>(Rectangulos[0]),s_minY=get<0>(Rectangulos[0]),s_maxY=get<0>(Rectangulos[0]);
    int i_minX = get<1>(Rectangulos[0]);
    int i_minY = get<2>(Rectangulos[0]);
    int i_maxX = XFinales[0];
    int i_maxY = YFinales[0];

    int mayminX= get<1>(Rectangulos[0]);
    int menmaxX= XFinales[0];
    int mayminY= get<2>(Rectangulos[0]);
    int menmaxY= YFinales[0];

    for( unsigned int i=0; i< Rectangulos.size(); i++)
    {
        if(i_minX > get<1>(Rectangulos[i])){
            i_minX = get<1>(Rectangulos[i]);
            s_minX = get<0>(Rectangulos[i]);
        }
        if(i_minY > get<2>(Rectangulos[i])){
            i_minY = get<2>(Rectangulos[i]);
            s_minY = get<0>(Rectangulos[i]);
        }
        if(i_maxX < XFinales[i] ){
            i_maxX = XFinales[i];
            s_maxX = get<0>(Rectangulos[i]);
        }
        if(i_maxY < YFinales[i] ){
            i_maxY = YFinales[i];
            s_maxY = get<0>(Rectangulos[i]);
        }
        if(mayminX < get<1>(Rectangulos[i]) )
        {
            mayminX = get<1>(Rectangulos[i]);
            cout<<"Mayor de menores: "<<mayminX;
        }
        if(menmaxX > XFinales[i])
        {
            menmaxX = XFinales[i];
            cout<<"Menor de los mayores: "<<menmaxX;
        }
        if(mayminY < get<2>(Rectangulos[i]) )
            mayminY = get<2>(Rectangulos[i]);
        if(menmaxY > YFinales[i])
            menmaxY = YFinales[i];
    }

    minX = make_pair(s_minX,i_minX);
    cout<<"Minx: "<<s_minX<<" , "<<i_minX<<endl;
    maxX = make_pair(s_maxX,i_maxX);
    cout<<"Maxx: "<<s_maxX<<" , "<<i_maxX<<endl;
    minY = make_pair(s_minY,i_minY);
    cout<<"MinY: "<<s_minY<<" , "<<i_minY<<endl;
    maxY = make_pair(s_maxY,i_maxY);
    cout<<"MaxY: "<<s_maxY<<" , "<<i_maxY<<endl;

    DTX = i_maxX - i_minX;
    cout<<" DTX: "<<DTX;
    DTY = i_maxY - i_minY;
    cout<<" DTY: "<<DTY;
    DSX = mayminX - menmaxX;
    cout<<" DSX: "<<DSX;
    DSY = mayminY - menmaxY;
    cout<<" DSY: "<<DSY;

    DNX = DSX*1.0 /DTX ;
    cout<< "DNX ="<<DNX;
    DNY = DSY*1.0 /DTY ;
    cout<< "DNY ="<<DNY;

    if(DNX > DNY)
    {
        cout<<"Semillas: \n";
        for(int i=0; i<Rectangulos.size(); i++){
            if( minX.first == get<0>(Rectangulos[i]))
            {
                Semillas.push_back(Rectangulos[i]);
                cout<<"Nombre: "<<get<0>(Rectangulos[i])<<"["<<get<1>(Rectangulos[i])<<" , "<<get<2>(Rectangulos[i])<<" , "<<get<3>(Rectangulos[i])<<" , "<<get<4>(Rectangulos[i]) <<" ]\n";
            }
            if( maxX.first == get<0>(Rectangulos[i]))
            {
                Semillas.push_back(Rectangulos[i]);
                cout<<"Nombre: "<<get<0>(Rectangulos[i])<<"["<<get<1>(Rectangulos[i])<<" , "<<get<2>(Rectangulos[i])<<" , "<<get<3>(Rectangulos[i])<<" , "<<get<4>(Rectangulos[i]) <<" ]\n";
            }
        }
    }
    else
    {
        for(int i=0; i<Rectangulos.size(); i++){
            if( minY.first == get<0>(Rectangulos[i]))
            {
                Semillas.push_back(Rectangulos[i]);
                cout<<"Nombre: "<<get<0>(Rectangulos[i])<<"["<<get<1>(Rectangulos[i])<<" , "<<get<2>(Rectangulos[i])<<" , "<<get<3>(Rectangulos[i])<<" , "<<get<4>(Rectangulos[i]) <<" ]\n";
            }
            if( maxY.first == get<0>(Rectangulos[i]))
            {
                Semillas.push_back(Rectangulos[i]);
                cout<<"Nombre: "<<get<0>(Rectangulos[i])<<"["<<get<1>(Rectangulos[i])<<" , "<<get<2>(Rectangulos[i])<<" , "<<get<3>(Rectangulos[i])<<" , "<<get<4>(Rectangulos[i]) <<" ]\n";
            }
        }
    }

    cout<<"Semillas: "<<endl;
    for(int i=0; i<Semillas.size(); i++)
        cout<<"Nombre: "<<get<0>(Semillas[i])<<"["<<get<1>(Semillas[i])<<" , "<<get<2>(Semillas[i])<<" , "<<get<3>(Semillas[i])<<" , "<<get<4>(Semillas[i]) <<" ]\n";
}

void RTree::ObtenerFinales()
{
    for(unsigned int i=0; i<Rectangulos.size();i++)
    {
        XFinales.push_back(get<1>(Rectangulos[i])+get<3>(Rectangulos[i]));
        YFinales.push_back(get<2>(Rectangulos[i])+get<4>(Rectangulos[i]));
    }
    for(unsigned int i=0; i<XFinales.size(); i++)
    {
        cout<<" x[ "<<i<<"]: "<<XFinales[i]<<endl;
        cout<<" y[ "<<i<<"]: "<<YFinales[i]<<endl;
    }
}

void RTree::ImprimirRectangulos()
{
    for (unsigned int i=0;i<Rectangulos.size();i ++)
    {
        cout<<"Nombre: "<<get<0>(Rectangulos[i])<<"["<<get<1>(Rectangulos[i])<<" , "<<get<2>(Rectangulos[i])<<" , "<<get<3>(Rectangulos[i])<<" , "<<get<4>(Rectangulos[i]) <<" ]\n";
    }
}

int main()
{

    rectangulos temp;
    rectangulo rec;
    rec= make_tuple("A",1,7,3,4);
    temp.push_back(rec);
    rec= make_tuple("B",8,14,12,13);
    temp.push_back(rec);
    rec= make_tuple("C",14,15,7,5);
    temp.push_back(rec);
    rec= make_tuple("D",3,1,5,5);
    temp.push_back(rec);
    rec= make_tuple("E",2,2,6,8);
    temp.push_back(rec);
    rec= make_tuple("F",4,1,6,10);
    temp.push_back(rec);
    rec= make_tuple("D",20,20,20,20);
    temp.push_back(rec);

    RTree rtree(temp);
    rtree.ObtenerFinales();
    rtree.ImprimirRectangulos();
    rtree.ObtenerDN();

/*
    rectangulos temp;
    rectangulo rec;
    rec= make_tuple("A",1,3,4,4);
    temp.push_back(rec);
    rec= make_tuple("B",5,15,5,6);
    temp.push_back(rec);
    rec= make_tuple("C",10,12,2,5);
    temp.push_back(rec);
    rec= make_tuple("D",15,2,6,1);
    temp.push_back(rec);

    RTree rtree(temp);
    rtree.ObtenerFinales();
    rtree.ImprimirRectangulos();
    rtree.ObtenerDN();
    */
}
