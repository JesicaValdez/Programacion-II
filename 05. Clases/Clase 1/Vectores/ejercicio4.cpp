/*Nombre: Jesica Valdez

Ejercicio:
Enunciado:

*/

#include <iostream>
#include <locale>

using namespace std;


void cargarVector(int vec[], int tam);
int posicionMaximo(int vec[], int tam);
void mostrarPosMaximo(int vec[]);

int main(){
setlocale(LC_ALL, "");

const int TAM=5;
int vec[TAM]={};

cargarVector(vec, TAM);
system("cls");
mostrarPosMaximo(vec);


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
int posicionMaximo(int vec[],int tam){
    int posMax=0;

    for(int i = 1; i < tam; i++){
        if(vec[i] > vec[posMax]){
            posMax=i;
        }
    }
    return posMax;
}
void mostrarPosMaximo(int vec[]){
   int pos=posicionMaximo(vec, 5);
    cout<<"posicion  maxima encontrada: "<<pos+1;
}
