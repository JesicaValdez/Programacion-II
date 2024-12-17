
#include <iostream>
#include <locale>
#include <cstring>
using namespace std;
#include "parcial2.h"


class PuntoAmaterial{
    private:
        int codMaterial;
        int tipo;
        float importe;
    public:
        void setCodigoMaterial(int cm){codMaterial=cm;}
        void setTipo(int t){tipo=t;}
        void setImporte(float imp){importe=imp;}

        void Mostrar(){
            cout<<"Cod Material: "<<codMaterial<<endl;
            cout<<"Tipo: "<<tipo;
            cout<<"Importe: "<<importe;
        }
};

class ArchivoPuntoAmaterial {
    private:
        char nombre[30];
    public:
        ArchivoPuntoAmaterial(const char *n){strcpy(nombre, n);}

        bool grabar(PuntoAmaterial aux){
            FILE *p;
            p=fopen(nombreArchivo, "ab");
            if(p==NULL)return false;
            bool escribio=fwrite(&aux, sizeof aux, 1, p);
            fclose(p);
            return escribio;
        }

        bool listarArchivo(){
            PuntoAmaterial obj;
            FILE *pFile;

            pFile=fopen(nombreArchivo, "rb");
            if(pFile==NULL){
                cout<<"No se pudo abrir"<<endl;
                return false;
            }
            while(fread(&obj, sizeof (PuntoAmaterial), 1, pFile)){
                obj.Mostrar();
                cout<<endl;
            }
            fclose(pFile);
            return true;
        }
};

///Punto 1. Generar un archivo con el codigo de material, el tipo y el importe total de las compras para ese material, para el año actual. Es decir, por cada material se debe registrar el codigo de material, el tipo y el importe total de las compras de ese material en ese año actual.
void Punto1(){
Compra objCompra;
ArchivoCompras arcCompra("compras.dat");
int cantCompras = arcCompra.contarRegistros();

Material objMaterial;
ArchivoMateriales matArchivo ("materiales.dat");
int cantMateriales = matArchivo.contarRegistros();

PuntoAmaterial objPuntoAmat;
ArchivoPuntoAmaterial matArchivo ("puntoAmaterial.dat");


for(int i=0, i<cantMateriales, i++){
    objMaterial = arcCompra.leerRegistro(i);
        for (int i=0; i<cantCompras; i++){
            objCompra = arcCompra.leerRegistro(i);
                if(objMaterial.getCodigoMaterial() == objCompra.getCodigoMaterial()) && objCompra.fechaCompra().getAnio() == 2024){
                    objPuntoAmat.setCodigoMaterial(objMaterial.getCodigoMaterial());
                    objPuntoAmat.setTipo(objMaterial.getTipo());
                    objPuntoAmat.setImporte(objCompra.getImporte());

                    ArchivoPuntoAmaterial.grabar();

                }

        }

}

ArchivoPuntoAmaterial.listarArchivo();
}

///Punto 2. La cantidad de obras de cada provincia
void Punto3(){
Obra objObra;
ArchivoObras arcObra("obras. dat");
int cantObras = arcObra.contarRegistros();

int vecProvincias[24]={};

for (int i=0; i<cantObras; i++){
    objObra = arcObra.leerRegistro(i);
    vecProvincias[objObra.getProvincia()-1]++;
}

for(int i=0; i<24; i++){
    cout "Provincia: " << i+1 << "Cantidad de Obras: " << vecProvincias[i] << endl;
}

///


int main (){



return 0;
}

