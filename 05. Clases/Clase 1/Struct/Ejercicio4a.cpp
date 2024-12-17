/*Nombre: Jesica Valdez

Enunciado:
*/

#include <iostream>
#include <locale>
using namespace std;

int main() {
    setlocale(LC_ALL, "");

    int numero = 10; // Variable entera
    int *ptr; // Declaración de un puntero a entero

    ptr = &numero; // Asignar la dirección de memoria de 'numero' al puntero 'ptr'

    cout << "Valor de 'numero': " << numero << endl;
    cout << "Dirección de memoria de 'numero': " << &numero << endl;
    cout << "Valor apuntado por 'ptr': " << *ptr << endl; // Acceso indirecto al valor de 'numero' a través de 'ptr'
    cout << "Dirección almacenada en 'ptr': " << ptr << endl;

    return 0;
}

