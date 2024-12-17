/*Nombre: Jesica Valdez

Ejercicio:
Enunciado:

*/

#include <iostream>
#include <locale>

using namespace std;

void cargarVector(int vec[], int tam);
int posicionMinimo(int vec[], int tam);
void mostrarPosMinimo(int vec[]);

int main(){
setlocale(LC_ALL, "");

const int TAM=5;
int vec[TAM]={};

cargarVector(vec, TAM);
system("cls");
mostrarPosMinimo(vec);


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
int posicionMinimo(int vec[],int tam){
    int posMin=0;
    for(int i = 1; i < tam; i++){
        if(vec[i]<vec[posMin]){
            posMin=i;
        }
    }
    return posMin;
}
void mostrarPosMinimo(int vec[]){
   int pos=posicionMinimo(vec, 5);
    cout<<"posicion  minima encontrada: "<<pos+1;
}


