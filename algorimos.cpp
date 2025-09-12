#include <iostream>
#include <utility>
#include <vector>
#include <random>
#include <cstdlib>
#include <set>
#include <ctime>
#include <string>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <sstream>
using namespace std;
#define maxThreads 8
/*Aqui van los algoritmos de ordenamiento*/

//algoritmo original
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped;
  
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        // If no two elements were swapped, then break
        if (!swapped)
            break;
    }
}
/*El código fue obtenido de
https://www.geeksforgeeks.org/bubble-sort-algorithm/
*/

void oddEvenSerial(vector<int>& arr){
    int n = arr.size();
    for(int phase = 0; phase <n;phase ++ ){
        if(phase%2==0){
            for (int i = 1; i < n; i++)
            {
                if(arr[i-1]>arr[i]) swap(arr[i - 1], arr[i]);
            }
            
        }
        else{
            for (int i = 0; i < n-1; i++)
            {
                if(arr[i]>arr[i+1]) swap(arr[i], arr[i+1]);
            }
        }
    }
}

void oddEvenOmp1(vector<int>& arr){
    int n = arr.size();
    for(int phase = 0; phase <n;phase ++ ){
        if(phase%2==0){
            #pragma omp parallel for num_threads(maxThreads) default(none) shared(arr,n) private(i)
            for (int i = 1; i < n; i++)
            {
                if(arr[i-1]>arr[i]) swap(arr[i - 1], arr[i]);
            }
            
        }
        else{
            #pragma omp parallel for num_threads(maxThreads) default(none) shared(arr,n) private(i)
            for (int i = 0; i < n-1; i++)
            {
                if(arr[i]>arr[i+1]) swap(arr[i], arr[i+1]);
            }
        }
    }
}

void oddEvenOmp2(vector<int>& arr){
    int n= arr.size();
    #pragma omp parallel num_threads(maxThreads) default(none) shared (arr,n) private(i)
    {
        for(int phase = 0; phase <n;phase ++ ){
            if(phase%2==0){
                #pragma omp parallel for num_threads(maxThreads) default(none) shared(arr,n) private(i)
                for (int i = 1; i < n; i++)
                {
                    if(arr[i-1]>arr[i]) swap(arr[i - 1], arr[i]);
                }
                
            }
            else{
                #pragma omp parallel for num_threads(maxThreads) default(none) shared(arr,n) private(i)
                for (int i = 0; i < n-1; i++)
                {
                    if(arr[i]>arr[i+1]) swap(arr[i], arr[i+1]);
                }
            }
        }
    }
}


void mostrar(vector<int> exmp){
	for(int i=0;i<exmp.size();i++)
		cout<<exmp[i]<<" ";
	cout<<endl;
}


//funcion que ejecuta los algoritmos
void ejecutar(string archivoEntrada,string archivoSalida){
    ifstream entrada(archivoEntrada);
    if(!entrada){
        cout<<"Error al abrir el archivo de entrada"<<endl;
        return;
    }
    ofstream salida(archivoSalida);
    if(!salida){
        cout<<"Error al abrir el archivo de salida"<<endl;
        return;
    }
    string linea;
    vector<int> leido;
    int elemento;
    //double inicio,fin;
    while(getline(entrada,linea)){
        leido.clear();
        istringstream iss(linea);
        
        //lee una línea y la almacena en el vector
        while (iss>>elemento){
            leido.push_back(elemento);
        }

        //en esta parte se comentan y descomentan los algoritmos segun sea el caso

        auto inicio=chrono::high_resolution_clock::now();
        bubbleSort(leido);
        auto fin=chrono::high_resolution_clock::now();
        chrono::duration<double> duracion = fin-inicio;

        //se escribe la duracion en el archivo de salida
        salida << duracion.count() <<endl;
    }
    entrada.close();
    salida.close();
}


int main(void){  

    ejecutar("100.txt","bubble100.txt");
    //ejecutar("50k.txt","bubble50k.txt");
    

    return 0;
}