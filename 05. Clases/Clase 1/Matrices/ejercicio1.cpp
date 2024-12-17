/*Nombre: Jesica Valdez

Enunciado:
*/

#include <iostream>
#include <locale>
using namespace std;


//Definicion de funcion
void cargarMat(int mat[][3]);
int encontrarMaximoF (int mat[][3], int numFila);
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
encontrarMaximoF(mat, 2);
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

int encontrarMaximoF (int mat[][3], int numFila){
    int mayor = mat [numFila][0];

    for (int c=1; c<3; c++){
        if(mat[numFila][c] > mayor)
            mayor = mat[numFila][c];
    }
    return mayor;
}

void mostrarResultado (int mat[][3]){
int resultado = encontrarMaximoF(mat, 2)
cout << resultado;
}


