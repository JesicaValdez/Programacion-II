#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

#include "parcial2.h"

class ProveedorSinCompras{
private:
    int numeroProveedor;
    int provincia;
    char nombre[30];
    bool estado;
public:
    void setNumero(int n) {numeroProveedor=n;}
    void setProvincia(int p) {provincia=p;}
    void setNombre(const char *n) {strcpy(nombre, n);}
};

class ArchivoProveedoresSin{
private:
    char nombre[30];
public:
    ArchivoProveedoresSin(const char *n="nuevo.dat"){
        strcpy(nombre, n);
    }

    bool Resetear(){
        FILE *p;
        p=fopen(nombre, "wb");
        if(p==NULL) return false;
        fclose(p);
        return true;
    }

    ProveedorSinCompras leerRegistro(int pos){
        ProveedorSinCompras reg;
        reg.setNumero(-1);
        FILE *p;
        p=fopen(nombre, "rb");
        if(p==NULL) return reg;
        fseek(p, sizeof reg*pos,0);
        fread(&reg, sizeof reg, 1, p);
        fclose(p);
        return reg;
    }

    int contarRegistros(){
        FILE *p;
        p=fopen(nombre, "rb");
        if(p==NULL) return -1;
        fseek(p, 0, 2);
        int tam = ftell(p);
        fclose(p);
        return tam/sizeof(ProveedorSinCompras);
    }

    bool grabarRegistro(ProveedorSinCompras reg){
        FILE *p;
        p=fopen(nombre, "ab");
        if(p==NULL) return false;
        bool escribio = fwrite(&reg, sizeof reg, 1, p);
        fclose(p);
        return escribio;
    }
};

///PUNTO 1 - Generar un archivo con los proveedores a los que se les haya comprado el año actual.
///Por cada proveedor al que no se le hayan hecho compras este año se debe registrar el numero de proveedor, el nombre del proveedor y la provincia del proveedor.
void punto1();
bool contarComprasProveedor(int np, int anio);

///PUNTO 2 - El tipo de material con menos cantidad de materiales(ignorando los tipos sin materiales)
void punto2();
int miniVectorTipos(int vTipos, int tam);

///PUNTO 3 - Generar un vector dinamico con todos los materiales y listar luego los materiales del vector que pertenezcan a un tipo que se ingresa por teclado.
bool punto3();

///PUNTO 5 - Sobrecarga el operador == para la clase Obra de manera tal que sea verdadero cuando el objeto que llama la metodo tenga un valor de superficie igual a un valor de tipo float que se recibe como parametro.
///Nota: dejar le codigo comentado en el cpp que se entrega para evitar problemas de compilacion.
void punto5();


int main(){
    punto1();
    punto2();
    punto3();//El enunciado pide copiar todo el vector y mostrar lo que coincidan con x cosa
    aux(); //a diferencia del anterior: copiar en un vector solo el tipo especifico que se ingresa por teclado; para eso recorro el archivo y pregunto si coincide el tipo que tiene el material con lo que se ingreso por teclado incremento la variable; si consigo entonces ahi pido memoria (chequeo apertura, vuelvo a leer y en caso que coincida voy a escribir el registro en el vector dinamico despues de eso lo muestro.
    cout << endl;
    system("pause");
    return 0;
}

void punto1(){
    Proveedor reg;
    ArchivoProveedores arcP("proveedores.dat");
    ProveedorSinCompras aux;
    ArchivoProveedoresSin arcNuevo;
    ArchivoProveedoresSin.Resetear();

    int cantReg=arcP.contarRegistros();
    bool tuvoCompras;

    for (int i=0; i<cantReg; i++){
        reg=arcP.leerRegistro(i);
        tuvoCompras=contarComprasProveedor(reg.getNumeroProveedor(), 2024);
        if(tuvoCompras==false){
            ///setear el registro del archivo nuevo
            aux.setNumero(reg.getNumeroProveedor());
            aux.setProvincia(reg.getProvincia());
            aux.setNombre(reg.getNombre());

            ///grabar el registro en el archivo
            arcNuevo.grabarRegistro(aux);
        }
    };


}

bool contarComprasProveedor(int np, int anio){
    Compra reg;
    ArchivoCompras arcC("compras.dat");

    //cuento registro
    int cantReg=arcC.contarRegistros();

    //recorro
    for (int i=0; i<cantReg; i++)
    {
        //leemos un registro de compras
        reg=arcC.leerRegistro(i);

        //pregunto
        if(reg.getNumeroproveedor()==np && reg.getFechaCompra().getAnio()== anio){
            return true;
        }

    }
    return false;
}

void punto2(){
    Material reg;
    ArchivoMateriales arcM("materiales.dat");
    int vTipos[6]={};

    //cuento registro
    int cantReg=arcM.contarRegistros();

    //recorro
    for (int i=0; i<cantReg; i++)
    {
        //leemos un registro de compras
        reg=arcM.leerRegistro(i);

        //pregunto
        vTipos[reg.getTipo()-1]++;

    }

    cout << "El tipo de material con menos cantidad es: " << miniVectorTipos(vTipos, 6)+1 << endl;
}

int miniVectorTipos(int vTipos, int tam){
 return 1;
}

bool punto3(){
Material *pMat, reg;
ArchivoMateriales arcM("materiales.dat");

    //cuento registro
    int cantReg=arcM.contarRegistros();

    //generamos el vector dinamico
    pMat= new Material[cantReg];
    if(pMat==NULL) return false;

    //hacemos  la lectura
    for (int i=0; i<cantReg; i++)
    {
        //leemos un registro de compras
        reg=arcM.leerRegistro(i);

        //en la posicion i me copio el registro
        pMat[i]=reg;
    }

    int tipo;
    cout << "Ingrese el tipo para listar: ";
    cin >> tipo;

    for (int i=0; i<cantReg; i++)
    {
        //pregunto
        if(pMat[i].getTipo()==tipo){
            pMat[i].Mostrar();
        }

    }
    delete pMat;
    return true;
}

///copiar en un vector dinamico los materiales pertenecientes
///a un tipo de material que se ingresa por teclado. Listar el vector
void aux(){
Material *pMat, reg;
ArchivoMateriales arcM("materiales.dat");

    //cuento registro
    int cantReg=arcM.contarRegistros();

    int cont=0, tipo, pos=0;
    //primero pido el ingreso del tipo de los materiales que se desea contar
    cout << "Ingrese el tipo para listar: ";
    cin >> tipo;

    for (int i=0; i<cantReg; i++){
        //leemos un registro de compras
        reg=arcM.leerRegistro(i);
        //en la posicion i me copio el registro
        if(reg.getTipo()==tipo){
            cont++;
        }
    }

    //chequeo y luego pido memoria para hacer el vector
    if(cont>0){
        //generamos el vector dinamico
        pMat= new Material[cont];
        if(pMat==NULL) {
            return false;
        }
        //ya validado hacemos nuevamente la lectura
        for (int i=0; i<cantReg; i++){
        //leemos un registro de compras
        reg=arcM.leerRegistro(i);
        //en la posicion i me copio el registro
            if(reg.getTipo()==tipo){
                pMat[pos]=reg;
                pos++;
            }
        }

        for(int i=0; i<pos; i++){
            pMat[i].Mostrar();
        }
    }

    delete pMat;
    return true;


}


void punto5(){

}

