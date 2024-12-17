/*Nombre: Jesica Valdez

Ejercicio:
Enunciado:

*/
#include <iostream>
#include <locale>
using namespace std;


//Definicion de funcion
void cargarMat(int mat[][3]);
int acuComponentes (int mat[][3], int numCol);
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
acuComponentes(mat, 1);
mostrarResultado(mat);

return 0;
}

///Declaracion Funciones
void cargarMat(int mat[][3]){

    for (int f=0; f<3; f++){

        for (int c=0; c<3; c++){
            cout << "COL: " << c << endl;
            cout << "Ingrese los numeros: ";
            cin >> mat[f][c];
        }
        cout << endl;
    }

}

int acuComponentes (int mat[][3], int numCol){
    int acu = 0;

    for (int f=0; f<3; f++){
        acu += mat[f][numCol];
    }
    cout << acu;
}

void mostrarResultado (int mat[][3]){
    int acumulacionTotal = acuComponentes(mat, 1);
        cout << "Acumulacion total: " << acumulacionTotal;
}

