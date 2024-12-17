/*Nombre: Jesica Valdez
*/

#include <iostream>
#include <locale>
#include <cstring>
using namespace std;
#include "parcial2.h"


class SinCompra{
    private:
        int numeroProveedor;
        char nombre[30];
        int provincia;
    public:
        void setNumeroProveedor(int np){numeroProveedor=np;}
        void setNombre(const char *n){strcpy(nombre, n);}
        void setProvincia(int p){provincia=p;}

        void Mostrar(){
            cout<<"Numero de Proveedor: "<<numeroProveedor<<endl;
            cout<<"Nombre: "<<nombre;
            cout<<"Provincia: "<<provincia;
        }
};

class ArchivoSinCompra {
    private:
        char nombreArchivo[30];
    public:
        ArchivoSinCompra(const char *na){strcpy(nombreArchivo, na);}

        bool grabar(SinCompra aux){
            FILE *p;
            p=fopen(nombreArchivo, "ab");
            if(p==NULL)return false;
            bool escribio=fwrite(&aux, sizeof aux, 1, p);
            fclose(p);
            return escribio;
        }

        bool listarArchivo(){
            SinCompra obj;
            FILE *pFile;

            pFile=fopen(nombreArchivo, "rb");
            if(pFile==NULL){
                cout<<"No se pudo abrir"<<endl;
                return false;
            }
            while(fread(&obj, sizeof (SinCompra), 1, pFile)){
                obj.Mostrar();
                cout<<endl;
            }
            fclose(pFile);
            return true;
        }
};

///Punto 1. Generar un archivo con los proveedores a los que no se les haya hecho compras el año actual. Por cada proveedor al que no se le hayan hecho compras
///este año se debe registrar el numero de proveedor, el nombre del proveedor y la provincia del Proveedor
void Punto1(){
Compra objCompra;
ArchivoCompras compraArchivo ("compras.dat");
int cantCompras = compraArchivo.contarRegistro();

Proveedor objProveedor;
ArchivoProveedores proveedorArchivo ("proveedores.dat");
int cantProveedores = proveedorArchivo.contarRegistros();

SinCompra objSinCompra;
ArchivoSinCompra sinCompraArchivo ("sincompra.dat");

for(int i=0, i<cantProveedores, i++){
    objProveedor = proveedorArchivo.leerRegistro(i);
    for(int c=0, c<cantCompras, c++){
        objCompra = compraArchivo.leerRegistro(c);
        if(objProveedor.getNumeroProveedor() == objCompra.getNumeroproveedor() && objCompra.getFechaCompra().getAnio() != 2024){
            objSinCompra.setNumeroProveedor(objProveedor.getNumeroProveedor());
            objSinCompra.setNombre(objProveedor.getNombre());
            objSinCompra.setProvincia(objProveedor.getProvincia());

            ArchivoSinCompra.grabar();
        }
    }
}

ArchivoSinCompra.listarArchivo();
}

///Punto 2. El tipo de material con menos cantidad de materiales ignorando los tipos de materiales
void Punto2(){
Material objMaterial;
ArchivoMateriales materialArchivo("materiales.dat");
int cantMateriales = materialArchivo.contarRegistros();

int vecTipos[6]={};

for(int i=0, i<cantMateriales, i++){
    objMaterial = materialArchivo.leerRegistro(i);
    vecTipos[objMaterial.getTipo()-1]++;
}

int menor = vecTipos[0];
bool menorT=false;
int posMat = 0;

for (int i=0; i<6; i++){
     if(vecTipos(i)>0){
        if(!menorT){
            menor = vecTipos[i];
            posMat = i;
            menorT = true;
        }
        else{
            if(vecTipos(i) < menor){
                menor = vecTipos(i);
                posMat = i;
            }
        }
     }
}

 cout << "El tipo de material con menos cantidad es: " << i+1 << endl;

}

///Punto 3. Generar  un vector dinamico con todos los materiales y
///listar luego los materiales del vector que pertenezcan a un tipo que se ingresa por teclado.
void Punto3(){
Material objMat;
ArchivoMateriales arcMat("materiales. dat");
int cantMat = arcMat.contarRegistros();

Material *vec;
vec = new Material[cantMat];

if(vec == NULL){
    return;
}

int tipo;
cout << "Ingrese tipo de Material: 1: en proyecto; 2: proyecto aprobado en espera;3: en ejecución; 4: terminada; 5: suspendida: ";
cin >> tipo;

for(int i=0, i<cantMat, i++){
    objMat = arcMat.leerRegistro(i);
    if(objMat.getTipo()==tipo){
        vec[i].Mostrar();
    }
}

delete [] vec;

}

///


int main (){



return 0;
}
