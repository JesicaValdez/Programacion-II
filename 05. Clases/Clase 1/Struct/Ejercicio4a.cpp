/*Nombre: Jesica Valdez

Enunciado:
*/

#include <iostream>
#include <locale>
using namespace std;

int main() {
    setlocale(LC_ALL, "");

    int numero = 10; // Variable entera
    int *ptr; // Declaraci�n de un puntero a entero

    ptr = &numero; // Asignar la direcci�n de memoria de 'numero' al puntero 'ptr'

    cout << "Valor de 'numero': " << numero << endl;
    cout << "Direcci�n de memoria de 'numero': " << &numero << endl;
    cout << "Valor apuntado por 'ptr': " << *ptr << endl; // Acceso indirecto al valor de 'numero' a trav�s de 'ptr'
    cout << "Direcci�n almacenada en 'ptr': " << ptr << endl;

    return 0;
}

