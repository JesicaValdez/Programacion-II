/*Nombre: Jesica Valdez

Ejercicio:
Enunciado:

*/

#include <iostream>
#include <locale>

using namespace std;


void cargarVector(int vec[], int tam);
int valorMaximo(int vec[], int tam);
void mostrarMaximo(int vec[]);

int main(){
setlocale(LC_ALL, "");

const int TAM=5;
int vec[TAM]={};

cargarVector(vec, TAM);
system("cls");
mostrarMaximo(vec);


cout<<endl;
system("pause");
return 0;
}

void cargarVector(int vec[], int tam){
    for(int i = 0; i < tam; i++){
        cout<<"Ingrese los numeros: ";
        cin>>vec[i];
    }
}
int valorMaximo(int vec[],int tam){
    int maximo=vec[0];
    for(int i = 0; i < tam; i++){
        if(vec[i]>maximo){
            maximo=vec[i];
        }
    }
    return maximo;
}
void mostrarMaximo(int vec[]){
    cout<<"valor maximo encontrado: "<<valorMaximo(vec, 5);
}
