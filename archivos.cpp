#include <iostream>
#include <utility>
#include <vector>
#include <random>
#include <cstdlib>
#include <set>
#include <string>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <sstream>
using namespace std;

//cambiar para que solo llegue a 10mil
vector<int> generador(int tam){
    vector<int> resultado;
   
    for(int i=1;i<=tam;i++)
        resultado.push_back(i);

    return resultado;
}

void swap(vector<int>  exm, int pos_a,int pos_b){
    int a = exm.at(pos_a);
    int b = exm.at(pos_b);
    
    exm.at(pos_a)=b;
    exm.at(pos_b)=a;
}

/*La función de desordenar recibe el vector y una 0<=cantidad<=100*/
void desordenar(vector<int>& base, float cant) {
    if (cant < 0 || cant > 100) {
        cout << "Error al desordenar" << endl;
        return;
    }

    int tam = base.size();
    int cambios = trunc(tam * (cant / 100));

    set<pair<int, int>> used_pairs;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, tam - 1);

    while (cambios > 0) {
        int a = dist(gen);
        int b = dist(gen);
        
        if (a != b && used_pairs.find({a, b}) == used_pairs.end() && used_pairs.find({b, a}) == used_pairs.end()) {
            used_pairs.insert({a, b});
            swap(base[a], base[b]);
            cambios--;
        }
    }
}

void mostrar(vector<int> exmp){
	for(int i=0;i<exmp.size();i++)
		cout<<exmp[i]<<" ";
	cout<<endl;
}



void genArchivos(string nombreArchivo,vector<int> distribucion,vector<int> porcentages,int tam){
    if(nombreArchivo.empty() || distribucion.empty() || porcentages.empty())
    {
        cout<<"Error de formato"<<endl;
    }
    else{
        int i,j,k;
        int tamDistribucion=distribucion.size();
        int tamPorcentages=porcentages.size();

        ofstream archivo(nombreArchivo);
        vector<int> gen;
        if(!archivo){
            cout << "Error al abrir el archivo para escritura" << endl;
            return;
        }
        /*En esta parte voy metiendo los datos al archivo el archivo */

        for(i=0;i<tamPorcentages;i++){
            for(j=0;j<distribucion[i];j++){
                gen=generador(tam);
                desordenar(gen,porcentages[i]);
                for(k=0;k<tam;k++){
                    archivo<<gen[k]<<" ";
                }
                archivo<<endl;
            }
        }
        archivo.close();

    }

}

int main(void){
    
    vector<int> distribucion ={200,300,500};
    vector<int> porcentaje ={10,50,100};
    
    //genArchivos("PRUEBA.txt",distribucion,porcentaje,100);
    genArchivos("40K.txt",distribucion,porcentaje,40000);


    

    return 0;
}