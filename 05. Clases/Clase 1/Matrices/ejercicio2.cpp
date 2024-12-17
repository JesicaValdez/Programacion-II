/*Nombre: Jesica Valdez

Ejercicio:
Enunciado:

*/
#include <iostream>
#include <locale>
using namespace std;


//Definicion de funcion
void cargarMat(int mat[][3]);
int encontrarPosMaximoF (int mat[][3], int numFila);
void mostrarResultado (int mat[][3]);

int main ()
{
 setlocale(LC_ALL, "");

  //Constantes
 int const FILA = 3;
 int const COLUMNA= 3;

 //variables
 int mat[FILA][COLUMNA]= {};

cargarMat(mat);
encontrarPosMaximoF(mat, 2);
mostrarResultado(mat);

return 0;
}

///Declaracion Funciones
void cargarMat(int mat[][3]){

    for (int f=0; f<3; f++){
            cout << "fila: "<< f << endl;
        for (int c=0; c<3; c++){
            cout << "Ingrese los numeros: ";
            cin >> mat[f][c];
        }
        cout << endl;
    }

}

int encontrarPosMaximoF (int mat[][3], int numFila){
    int posMax = 0;

    for (int c=1; c<3; c++){
        if(mat[numFila][c] > mat[numFila][posMax]){
            posMax = c;
        }
    }
    return posMax;
}

void mostrarResultado (int mat[][3]){
    int resultado = encontrarPosMaximoF(mat, 2);
        cout<< "posicion  maxima encontrada: "<< resultado+1;
}
