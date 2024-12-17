/*Nombre: Jesica Valdez
Enunciado:
Agregar la opción Venta, al menú del ejercicio 2. En la venta se debe pedir el
código de artículo y la cantidad de unidades a comprar, e informar el importe de la
venta.
Se debe verificar que exista el código, y que la cantidad pedida no exceda el stock
disponible. Con cada venta debe disminuir el stock del artículo vendido.
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
void cargarCadena(char *palabra, int tamano);
bool codigoRepetido(Articulo *vec, int indice);
void cargarArticulo(Articulo *vec);
void mostrarArticulo(Articulo *vec);
void ventas(Articulo *vec);

int main(){
setlocale(LC_ALL, "");

int opc;

Articulo vec[5];

do{
    cout<<"1.CARGAR REGISTRO"<<endl;
    cout<<"2.MOSTRAR REGISTRO"<<endl;
    cout<<"3.VENTAS"<<endl;
    cout<<"-------------------"<<endl;
    cout<<"0.Exit"<<endl;
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
            cout<<"VENTAS"<<endl;
            ventas(vec);
            break;
         case 0:
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

bool codigoRepetido(Articulo *vec, int indice){
    for(int i = 0; i < indice; i++){
        if(strcmp(vec[i].articulo, vec[indice].articulo) == 0){
            return true;
        }
    }
    return false;
}

void cargarArticulo(Articulo *vec){

    for( int i = 0; i < 5; i++){
        cout<<"Igresar codigo: ";
        cargarCadena(vec[i].articulo, 5);


         if(codigoRepetido(vec, i)){
            cout << "El código de artículo ya existe. Por favor ingrese otro código." << endl;
            i--; // Decrementar el índice para permitir que el usuario ingrese el código nuevamente
            continue; // Saltar a la siguiente iteración del bucle
        }

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

void ventas(Articulo *vec){
    char artVenta[6]={};
    int cantArticulos;
    float importe;

    cout<<"Ingrese COD.ART: "<<endl;
    cargarCadena(artVenta, 5);
    cout<<"Cuantas unidades desea comprar: "<<endl;
    cin>>cantArticulos;

    for (int i=1; i<5; i++){
         if(strcmp(vec[i].articulo, artVenta) == 0){
             if(vec[i].stock >= cantArticulos){
                importe=vec[i].precio*cantArticulos;
                }
            }

    }
    cout << "IMPORTE: $"<<importe<<endl;

}

