/*Nombre: Jesica Valdez
*/
#include <iostream>
#include <locale>
#include <cstdlib>
#include <string.h>

using namespace std;
///STRUCT
struct Articulo{
char articulo[6];
char descripcion[30];
float precio;
int stock;
};

///DEFINICIONES
void cargarCadena(char palabra, int tamano);
void cargarArticulo(Articulo *vec);
int mostrarPosicion(Articulo *vec, char *art);

int main(){
setlocale(LC_ALL, "");

int opc;
char art[6]={'1','2','3','4','5'};

Articulo vec[5];

do{
    cout<<"1.CARGAR REGISTRO"<<endl;
    cout<<"2.MOSTRAR POSICION"<<endl;
    cout<<"3.Exit"<<endl;
    cout << endl;
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

            cout<<"MOSTRAR POSICION: "<<endl;
            cout << mostrarPosicion(vec, art);
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
int mostrarPosicion(Articulo *vec, char *art){

    for(int i = 0; i < 5; i++){
    if(strcmp(vec[i].articulo,art)==0){
        return i+1;
        }
    }
    return -1;
}
