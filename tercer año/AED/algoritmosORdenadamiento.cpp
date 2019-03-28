#include <iostream>
#include <vector>

///Algoritmos de ordenamiento///


using namespace std;

typedef int num;
typedef double real;
typedef vector<num> myvector;

void mostrar(myvector A){
    for (num i =0;i<A.size();i++){
        cout<<A[i]<<"\t";
    }
    cout<<endl;
}

num AUX;
bool flag;
/// Algoritmo Bubble Sort (CRECIENTE)
void bubblesort(myvector A){
    for (num i=0;i<A.size();i++){
        flag=false;
        for(num j=0;j<A.size()-1-i;j++){
            if (A[j]>A[j+1]){
                AUX=A[j];
                A[j]=A[j+1];
                A[j+1]=AUX;
                flag=true;
            }
        }
        if(flag==false){
            break;
        }
        mostrar(A);
        cout<<endl;
    }

}

/// Algoritmo Bubble Sort 1 Version (CRECIENTE)
void bubble1V(myvector A){
    cout<<"Bubble Sort 1 Version"<<endl;
    for (num i=0;i<A.size()-1;i++){
        real AUX;
        num a=0;
        for (num j=A.size()-1;j>i;j--){
            if (A[j]<A[j-1]){
                AUX=A[j];
                A[j]=A[j-1];
                A[j-1]=AUX;
            }
            a++;
        }
        //cout<<"entre a vece s= <"<<a<<endl;
        mostrar(A);
        cout<<endl;
    }
}

///Algoritmo Bubble Sort 2 Version (CRECIENTE)
void bubble2V(myvector A){
    cout<<"Bubble Sort 2 Version"<<endl;
    bool bandera=true;
    while (bandera){
        real AUX;
        for(num j=0;j<A.size()-1;j++){
            if (A[j]>A[j+1]){
                AUX=A[j];
                A[j]=A[j+1];
                A[j+1]=AUX;
                bandera=false;
            }
        }
        if (bandera==false){
            bandera=true;
        }
        else
            bandera=false;
        mostrar(A);
        cout<<endl;
    }
}

///Algoritmo Insert Sort (CRECIENTE)
void insertsort(myvector A){
    cout<<"Insert Sort"<<endl;
    for (num i=1;i<A.size();i++){
        num val=A[i];
        num j=i-1;
        while(j>=0 && A[j]>val){
            A[j+1]=A[j];
            j--;
        }
    A[j+1]=val;
    mostrar(A);
    cout<<endl;
    }
}

///Algoritmo Selection Sort (CRECIENTE)
void selectionsort(myvector A){
    cout<<"Selection Sort"<<endl;
    for (num i=0;i<A.size()-1;i++){
        num menor=A[i+1];
        num pos=i+1;
        for (num j=i+1;j<A.size();j++){
            if (A[j]<menor){
                menor=A[j];
                pos=j;
            }
        }
        num AUX;
        if (A[pos]<A[i]){
            AUX=A[i];
            A[i]=A[pos];
            A[pos]=AUX;
        }
        cout<<endl;
        mostrar(A);
    }
}

///Algoritmo Merge Sort  (CRECIENTE)
void merge(myvector &aVector, int size, int low, int middle, int high){
    cout<<"entre al merge"<<endl;
    int temp[size];
    for(int i = low; i <= high; i++){
        temp[i] = aVector[i];
    }
    int i = low;
    int j = middle+1;
    int k = low;

    while (i <= middle && j <= high){
        if(temp[i] <= temp[j]){
            aVector[k] = temp[i];
            ++i;
        }
        else {
            aVector[k] = temp[j];
            ++j;
        }
        ++k;
    }
    while (i <= middle){
        aVector[k] = temp[i];
        ++k;
        ++i;
    }
}

void mergeSort(myvector &aVector, int size, int low, int high){
    if (low < high){
        int middle = (low + high) / 2;
        mergeSort(aVector, size, low, middle);
        cout<<"middle= "<<middle<<"low= "<<low<<"hish = "<<high<<endl;
        mergeSort(aVector, size, middle+1, high);
        cout<<"middle= "<<middle<<"low= "<<low<<"hish = "<<high<<endl;
        merge(aVector, size, low, middle, high);
    }
    mostrar(aVector);
}

///Algoritmo QuickSort (CRECIENTE)
void quickSort(myvector &arr, int left, int right) {
      int i = left, j = right;
      int tmp;
      int pivot = arr[(left + right) / 2];
      /* partition */
      while (i <= j) {
            while (arr[i] < pivot)
                  i++;
            while (arr[j] > pivot)
                  j--;
            if (i <= j) {
                  tmp = arr[i];
                  arr[i] = arr[j];
                  arr[j] = tmp;
                  i++;
                  j--;
            }
      }
      /* recursion */
      if (left < j)
            quickSort(arr, left, j);
      if (i < right)
            quickSort(arr, i, right);
    mostrar(arr);
}


int main (){
    myvector A;
    A.push_back(5);
    A.push_back(4);
    A.push_back(3);
    A.push_back(2);
    cout<<"vector original"<<endl;
    mostrar(A);
    //bubblesort(A);
    //insertsort(A);
    mergeSort(A,4,0,3);
    //quickSort(A,0,4);


    return 0;
}


