/*Nombre: Jesica Valdez

Ejercicio:
Enunciado:

*/

#include <iostream>
#include <locale>

using namespace std;

void cargarMatriz(int mat[][3]);
int cantidadNumPos(int mat[][3], int numCol);
void mostraResultado(int mat[][3]);

int main(){
setlocale(LC_ALL, "");

const int FILA=3;
const int COLUM=3;

int mat[FILA][COLUM]={};

cargarMatriz(mat);
cantidadNumPos(mat, 2);
mostraResultado(mat);

cout<<endl;
system("pause");
return 0;
}
void cargarMatriz(int mat[][3]){
    for(int f = 0; f < 3; f++){
        for(int c = 0; c < 3; c++){
            cout<<"columna "<<c<<endl;
            cout<<"Ingrese los numeros: ";
            cin>>mat[f][c];
        }
        cout<<endl;
    }
}
int cantidadNumPos(int mat[][3], int numCol){
    int numPositivos=0;
    for(int f = 0; f < 3; f++){
        if(mat[f][numCol]>0){
            numPositivos++;
        }
    }
    return numPositivos;
}
void mostraResultado(int mat[][3]){
    int resultado=cantidadNumPos(mat, 2);
    cout<<resultado;
}

