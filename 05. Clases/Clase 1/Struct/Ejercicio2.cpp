/*Nombre: Jesica Valdez
Enunciado:
Un comercio vende un total de 50 artículos diferentes. Para cada uno de ellos
almacena la información que se detalló en el ejercicio anterior.
Hacer un programa para cargar y mostrar por pantalla la lista de artículos. El programa
debe tener un menú con funciones.
*/

#include <iostream>
#include <locale>
#include <cstdlib>

using namespace std;
///STRUCT
struct Articulo{
char articulo[6];
char descripcion[30];
float precio;
int stock;
};

///DEFINICIONES
void cargarCadena(char *palabra, int tamano);
void cargarArticulo(Articulo *vec);
void mostrarArticulo(Articulo *vec);

int main(){
setlocale(LC_ALL, "");

int opc;

Articulo vec[5];

do{
    cout<<"1.CARGAR REGISTRO"<<endl;
    cout<<"2.MOSTRAR REGISTRO"<<endl;
    cout<<"3.Exit"<<endl;
    cout<<endl;
    cout<<"Ingrese opcion: ";
    cin>>opc;
    system("cls");

    switch(opc){
    case 1:
            cout<<"CARGAR REGISTROS"<<endl;
            cargarArticulo(vec);
            system("cls");
            break;
        case 2:
            cout<<"MOSTRAR REGISTROS"<<endl;
            mostrarArticulo(vec);
            break;
        case 3:
            cout<<"Saliendo del programa.";
            break;
        default:
            cout<<"Opcion no valida. Por favor ingrese de nuevo."<<endl;
            break;
    }
} while (opc != 3);



cout<<endl;
system("pause");
return 0;
}
///DECLARACIONES
void cargarCadena(char *palabra, int tamano){
    int i=0;
    fflush(stdin);
    for (i=0; i<tamano; i++){
        palabra[i]=cin.get();
        if (palabra[i]=='\n'){
            break;
        }
    }
    palabra[i]='\0';
    fflush(stdin);
}
void cargarArticulo(Articulo *vec){
    for(int i = 0; i < 5; i++){
    cout<<"Igresar codigo: ";
    cargarCadena(vec[i].articulo, 5);
    cout<<"Ingresar descripcion: ";
    cargarCadena(vec[i].descripcion, 29);
    cout<<"Ingresar precio: ";
    cin>>vec[i].precio;
    cout<<"Ingrese el stock: ";
    cin>>vec[i].stock;
    cout<<endl;
    }
}
void mostrarArticulo(Articulo *vec){
    for(int i = 0; i < 5; i++){
    cout<<"Codigo: "<<vec[i].articulo<<endl;
    cout<<"Descripcion: "<<vec[i].descripcion<<endl;
    cout<<"Precio: "<<vec[i].precio<<endl;
    cout<<"Stock: "<<vec[i].stock<<endl;
    }
    cout<<endl;
}
