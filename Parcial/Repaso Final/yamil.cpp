#include <iostream>
using namespace std;

//Encabezados
void mostrarMenu();
void cargarDatos(bool mSucursalxLibros[4][7]);
void punto1(bool mSucursalxLibros[4][7]);
void punto2();
void punto3();
void punto4();

int main ()
{
    int opcion;
    //punto 1
    bool mSucursalxLibros[4][7]={};
    do
    {
        mostrarMenu();
        cin >> opcion;

        switch(opcion)
        {
        case 0:
            //cargar datos
            cargarDatos(mSucursalxLibros);
            break;
        case 1:
            //punto A
            punto1(mSucursalxLibros);
            break;
        case 2:
            //punto B
            punto2();
            break;
        case 3:
            //punto C
            punto3();
            break;
        case 4:
            //punto C
            punto4();
            break;
        case 9:
            //salir
            break;
        default:
            cout << "OPCION INCORRECTA" << endl;
            system("pause");
            system("cls");
            break;
        }
    }
    while(opcion!=9);










return 0;

}


//Declaracion de Funciones

void mostrarMenu(){
    cout << "Menu" << endl;
    cout << "----" << endl;
    cout << "0.- CARGAR DATOS" << endl;
    cout << "1. Punto 1" << endl;
    cout << "2. Punto 2" << endl;
    cout << "3. Punto 3" << endl;
    cout << "3. Punto 4" << endl;
    cout << "9. SALIR" << endl;
    cout << endl << "SELECCIONE UNA OPCION: ";
}

void cargarDatos(bool mSucursalxLibros[4][7]){
    system("cls");
    cout << "CARGAR DATOS" << endl << endl << endl;

    int idVenta, idAutor, idGenero, precio, paginas, idSucursal;
    //float precio;

    cout << "Ingrese # de ID de Venta: ";
    cin >> idVenta;

    while (idVenta !=0) {
        cout << "ID de Autor: ";
        cin >> idAutor;
        cout << "ID de Genero Literario: ";
        cin >> idGenero;
        cout << "Precio: ";
        cin >> precio;
        cout << "Páginas del libro: ";
        cin >> paginas;
        cout << "ID de Sucursal: ";
        cin >> idSucursal;


        if (idGenero >= 1 && idGenero <= 7) {
            mSucursalxLibros[idSucursal - 1][idGenero - 1] = true;
        }






        cout << "ID de Venta: ";
        cin >> idVenta;
        system("pause");
        system("cls");
    }
}

void punto1(bool mSucursalxLibros[4][7]){
    system("cls");
    cout << "Punto 1" << endl;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 7; j++){
            if(mSucursalxLibros[i][j] && (j+1 !=3) && (j+1!=7)){
                cout<<"id sucursal: "<< i + 1000 << endl;
            }
        }
    }
    system("pause");
    system("cls");
}


void punto2(){
    system("cls");
    cout << "Punto 2" << endl;
    system("pause");
    system("cls");
}

void punto3(){
    system("cls");
    cout << "Punto 3" << endl;


    //encabezado
    void punto3()

    //main
      int cantidadVentas=0;
    punto3(, cantidadVentas);

    //declaracion
    void punto3(, int cantidadVentas){
        const string nombresGenero[] = {"Accion", "Aventura", "Romance", "Misterio", "Fantasia", "Ciencia Ficcion", "Horror"};

        int contadorVentas[7]={};
        int acuPrecios[7]={};
        float promedio[7]={};

        for (int i=0; i<cantidadVentas; i++){
            int idGenero = (ventas + i);
            contadorVentas[idGenero-1]++;
            acuPrecios[idGenero-1] += (ventas + i);
        }

        for (int i=0; i<7; i++){
            if(contadorVentas[i]>0){
                promedio[i]= float(acuPrecios[i])/contadorVentas[i];
            }
        }
        cout << "Promedio de precio de venta por genero : " << endl;
        for (int i=0; i<7; i++)
        cout << "Genero Literario: " << i + 1<< ", Promedio de precio: "<< promedio[i]<< endl;








    system("pause");
    system("cls");
    */
}

void punto4(){
    system("cls");
    cout << "Punto 4" << endl;
    system("pause");
    system("cls");
}
