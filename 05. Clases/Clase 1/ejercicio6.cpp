/*Nombre: Jesica Valdez

Enunciado:

*/

#include <iostream>
#include <locale>

using namespace std;

void cargarVector(int vec[10]);
int encontrarNumero(int vec[10], int num);
void mostrarResultado(int vec[10]);

int main(){
setlocale(LC_ALL, "");

const int TAM=10;
int vec[TAM]={};

cargarVector(vec);
encontrarNumero(vec, 13);
mostrarResultado(vec);

cout<<endl;
system("pause");
return 0;
}

void cargarVector(int vec[10]){
    for(int i = 0; i < 10; i++){
        cout<<"Ingrese los numeros: ";
        cin>>vec[i];
    }
}
int encontrarNumero(int vec[], int num){
    int posNum=0;
    for(int i = 0; i < 10; i++){
        if(vec[i] == num){
        posNum = i+1;
        return posNum;
        }
    }
    return -1;

}
void mostrarResultado(int vec[]){
int resultado=encontrarNumero(vec, 13);
cout << resultado;
}