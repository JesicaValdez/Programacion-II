#include <iostream>
#include <cstring>
using namespace std;

#include "parcial2.h"




////Recursos:
/*
Para eliminar----------------------------------------:
AGREGAR FUNCION EN CLASE ARCHIVO:
bool Sobreescribir(int pos, Vendedor reg) {
    FILE* pFile;

    pFile = fopen(_nombreArchivo, "rb+");
    if (pFile == nullptr) {
        return false;
    }

    fseek(pFile, sizeof(Vendedor) * pos, SEEK_SET);

    bool resultado = fwrite(&reg, sizeof(Vendedor), 1, pFile);

    fclose(pFile);

    return resultado;
}

int BuscarId(int indice) {
    Vendedor reg;
    int pos = 0;
    FILE* pFile;

    pFile = fopen(_nombreArchivo, "rb");
    if (pFile == nullptr) {
        return -1;
    }

    while (fread(&reg, sizeof(Vendedor), 1, pFile)) {
        if (reg.getNroLegajo() == indice) {
            fclose(pFile);
            return pos;
        }
        pos++;
    }

    fclose(pFile);
    return -1;
}

DESPUES--------------------------------------------:

void VendedorManager::EliminarVendedor()
{
    int numLegajo, indice;
    Vendedor vendedor;
    int opcion;


    cout << "Ingrese el numero de Legajo: ";
    cin >> numLegajo;

    necesito una funcion buscar ID en la clase archivo
    indice=_archivo.BuscarId(numLegajo);


    if(indice != -1){
        vendedor=_archivo.leerRegistro(indice);

        cout<< "Desea eliminar este vendedor? (1)Si - (2)No: " << endl;
        cin >> opcion;
        system("cls");

        if(opcion == 1){
            vendedor.setEliminado(true);

            if(_archivo.Sobreescribir(indice, vendedor)){
                cout<<"Se elimino con exito."<<endl;
            }else{
                cout<<"No se pudo eliminar."<<endl;
            }
        }else{
            cout<<"Cancelo el eliminado del vendedor."<<endl;
        }
    }else{
        cout<<"Numero de Legajo inexistente."<< endl;
    }
}


MODIFICAR---------------------------------------------:

void Modificar();
{
    int legajo;
    int opcion;


    cout << "Ingrese legajo a modificar: ";
    cin >> legajo;
    system("cls");

    int indice = _archivo.BuscarId(legajo);

    Vendedor vendedor;
    vendedor = _archivo.leerRegistro(indice);

    if(indice != -1){
        vendedor=_archivo.leerRegistro(indice);

        cout << "¿Desea editar la Fecha de Ingreso? (1)Si - (2)No: " << endl;
        cin >> opcion;
        system("cls");

        if(opcion == 1){
            cout<<end;
            //LLAMADO AL ATRIBUTO DE LA CLASE QUE SE DESEA MODIFICAR
            Fecha f;
            cout << "Ingrese nueva fecha: "<<endl;
            f.Cargar();
            system("cls");
            vendedor.setFechaIngreso(f);
            int newA=vendedor.calcularAntiguedad();
            vendedor.setAntiguedad(newA);

            bool result = _archivo.Sobreescribir(indice, vendedor);

            if (result == true) {
                std::cout<<"Se edito correctamente el vendedor."<<std::endl;
            }

        }else{
            std::cout<<"Cancelo el modificar del vendedor."<<std::endl;
        }
    }else{
        std::cout<<"Numero de Legajo inexistente."<<std::endl;
    }

}




/*


class PuntoA {
private:
    char codigoEmpresa[6];
    char nombre[30];
    float cantToneladas;

public:
    void Mostrar() {
        cout << codigoEmpresa <<"   "<< nombre <<"  "<< cantToneladas;
    }

    void setCodigoEmpresa(const char* codigo) { strcpy(codigoEmpresa, codigo);}
    void setNombre(const char* nomb) { strcpy(nombre, nomb); }
    void setCantToneladas(float cant) { cantToneladas = cant; }
};

class ArchivoPuntoA {
private:
    char nombre[30];

public:
    ArchivoPuntoA() {
        strcpy(nombre, "PuntoA.dat");
    }

    bool escribirRegistro(PuntoA reg) {
        FILE* p;
        p = fopen(nombre, "ab");
        if (p == NULL) return false;
        bool escribio = fwrite(&reg, sizeof reg, 1, p);
        fclose(p);
        return escribio;
    }

    void vaciar(){
        FILE *p = fopen(nombre, "wb");
        if (p == NULL){return ;}
        fclose(p);
    }

    bool listarArchivo() {
        PuntoA reg;
        FILE* p;
        p = fopen(nombre, "rb");
        if (p == NULL) {
            cout << "No se pudo abrir el archivo." << endl;
            return false;
        }
        while (fread(&reg, sizeof reg, 1, p) == 1) {
            reg.Mostrar();
            cout << endl;
        }
        fclose(p);
        return true;
    }

};


bool remplazarReg(Cosecha reg, int pos){
    FILE *p = fopen("Cosecha.dat", "rb+");
    if (p == NULL){return false;}
    fseek(p, pos * sizeof(Cosecha), SEEK_SET);
    bool pudoEscribir = fwrite(&reg, sizeof(Cosecha), 1, p);
    fclose(p);
    return pudoEscribir;
}

void solucionPuntoA();
void solucionPuntoB();
void solucionPuntoC();
void solucionPuntoD();
void solucionPuntoE();

int main(){
    /*ArchivoCosecha obj;
    obj.listarArchivo();
    return 0;*/


    setlocale (LC_ALL, "Spanish");
    cout << "PUNTO A" << endl;
    solucionPuntoA();
    cout << endl;
    cout << "PUNTO B" << endl;
    //solucionPuntoB();
    cout << endl;
    cout << "PUNTO C" << endl;
    solucionPuntoC();
    cout << endl;
    cout << "PUNTO D" << endl;
    //solucionPuntoD();
    ///TENER EN CUENTA ANTES DE DESCOMENTAR EL LLAMADO DE PUNTO D QUE ESTE YA SE RESOLVIO
    ///POR LO TANTO YA MODIFICO EL ARCHIVO ORIGINAL (YA PASO DE TONELADA A KILO), SI LO
    ///VUELVEN A EJECUTAR VA A DIVIDIR KILO / 1000.
    cout << endl;
    cout << "PUNTO E" << endl;
    //solucionPuntoE();
    cout << endl;

    return 0;
}

void solucionPuntoA(){
    ArchivoEmpresa archEmp;
    Empresa regEmp;
    int cantEmp = archEmp.contarRegistros();

    ArchivoCosecha archCos;
    Cosecha regCos;
    int cantCos = archCos.contarRegistros();

    ArchivoPuntoA archPA;
    PuntoA regPA;
    archPA.vaciar();

    for (int i=0 ; i<cantEmp ; i++ ){
        regEmp = archEmp.leerRegistro(i);
        float acumToneladas = 0;

        for (int j=0 ; j<cantCos ; j++ ){
            regCos = archCos.leerRegistro(j);

            if(strcmp(regEmp.getCodigoEmpresa(),regCos.getCodigoEmpresa()) == 0){
                acumToneladas += regCos.getToneladasCosechadas();
            }
        }

        regPA.setCodigoEmpresa(regEmp.getCodigoEmpresa());
        regPA.setNombre(regEmp.getNombre());
        regPA.setCantToneladas(acumToneladas);
        archPA.escribirRegistro(regPA);
    }

    archPA.listarArchivo();
}


void solucionPuntoB(){
    float toneladasPorMes[12]={};

    ArchivoCosecha archCos;
    Cosecha regCos;
    int cantCos = archCos.contarRegistros();

    for (int i=0 ; i<cantCos ; i++ ){
        regCos = archCos.leerRegistro(i);
        if(regCos.getCodigoCereal() == 10){
            toneladasPorMes[regCos.getFecha().getMes()-1]+= regCos.getToneladasCosechadas();
        }
    }

    float maxToneladas = 0;
    int maxMes;

    for (int i=0 ; i<12 ; i++ ){
        if(toneladasPorMes[i] > maxToneladas){
            maxToneladas = toneladasPorMes[i];
            maxMes = i;
        }
    }
    cout << "El meses con mas ton del cereal tipo 10 es el mes: " << maxMes+1 << endl;
}


void solucionPuntoC(){

    ArchivoEmpresa archEmp;
    Empresa regEmp;
    int cantEmp = archEmp.contarRegistros();

    ArchivoCosecha archCos;
    Cosecha regCos;
    int cantCos = archCos.contarRegistros();

    ///PuntoA vec[cantEmp];
    PuntoA* vec = nullptr;
    vec = new PuntoA[cantEmp]{};
    if(vec == nullptr){return ;}

    ArchivoPuntoA archPA;
    archPA.vaciar();

    for (int i=0 ; i<cantEmp ; i++ ){
        regEmp = archEmp.leerRegistro(i);

        float acumToneladas = 0;

        for (int j=0 ; j<cantCos ; j++ ){
            regCos = archCos.leerRegistro(j);
            if(strcmp(regEmp.getCodigoEmpresa(),regCos.getCodigoEmpresa()) == 0){
                acumToneladas += regCos.getToneladasCosechadas();
            }
        }

        vec[i].setCodigoEmpresa(regEmp.getCodigoEmpresa());
        vec[i].setNombre(regEmp.getNombre());
        vec[i].setCantToneladas(acumToneladas);
        //archPA.escribirRegistro(vec[i]);
    }

    for (int i=0 ; i<cantEmp ; i++ ){
        vec[i].Mostrar();
        cout  << endl;

    }


    delete []vec;

    //archPA.listarArchivo();

}

/*
void solucionPuntoD(){
    ArchivoCosecha archCos;
    Cosecha regCos;
    int cantCos = archCos.contarRegistros();
    cout << endl;

    for (int i=0 ; i<cantCos ; i++ ){
        regCos = archCos.leerRegistro(i);
        float ton = regCos.getToneladasCosechadas();
        regCos.setToneladasCosechadas(ton*1000);
        archCos.remplazarReg(regCos,i);
    }
}
*/

void solucionPuntoE(){
    cout << "Operador sobrecargado en la clase Empresa" << endl;
}
