#include <iostream>
#include <locale>
#include <cstring>

using namespace std;

#include "parcial2.h"

class PuntoA{
    private:
        int codMaterial;
        int tipo;
        float importe;
    public:
        void setCodMateril(int cm){codMaterial=cm;}
        void setTipo(int t){tipo=t;}
        void setImporte(float i){importe=i;}

        void Mostrar(){
            cout<<"CODIGO MATERIAL: "<<codMaterial<<endl;
            cout<<"TIPO: "<<tipo<<endl;
            cout<<"IMPORTE: "<<importe<<endl;
        }
};

class ArchivoPuntoA{
    private:
        char nombre[30];
    public:
        ArchivoPuntoA(const char *n){strcpy(nombre, n);}

         bool grabar(PuntoA aux){
            FILE *p;
            p=fopen(nombre, "ab");
            if(p==NULL)return false;
            bool escribio=fwrite(&aux, sizeof aux, 1, p);
            fclose(p);
            return escribio;
        }

        bool listarArchivo(){
            PuntoA obj;
            FILE *pFile;

            pFile=fopen(nombre, "rb");
            if(pFile==NULL){
                cout<<"No se pudo abrir"<<endl;
                return false;
            }
            while(fread(&obj, sizeof (PuntoA), 1, pFile)){
                obj.Mostrar();
                cout<<endl;
            }
            fclose(pFile);
            return true;
        }

};

/*
void Punto1(){
    Compra objC;
    ArchivoCompras regC("compras.dat");
    int cantC=regC.contarRegistros();

    Material objM;
    ArchivoMateriales regM("materiales.dat");
    int cantM=regM.contarRegistros();

    PuntoA objA;
    ArchivoPuntoA regA("puntoA.dat");

    for(int i = 0; i < cantM; i++){
        objM=regM.leerRegistro(i);
        float acu=0;

        for(int j = 0; j < cantC; i++){
            objC=regC.leerRegistro(j);
            if(objM.getCodigoMaterial()==objC.getCodigoMaterial() && objC.getFechaCompra().getAnio()==2024){
                acu+=objC.getImporte;
            }
        }
            objA.setTipo(objM.getTipo());
            objA.setImporte(acu);
            objA.setCodMateril(objM.getCodigoMaterial());

            regA.grabar(objA);
    }
    regA.listarArchivo();
}
*/

float impCompra(int mat, int anio){
Compra reg;
ArchivoCompras arcC("compras.dat");

//contar registro
int cant= arcC.contarRegistros();
float acu=0;

    for (int i=0;i<; i++){
        reg=arcC.leerRegistro(i);

        if(reg.getCodigoMaterial()==mat && reg.getFechaCompra().getAnio()==anio){
            acu += reg.getImporte();
        }
    }
return acu;
}

void PuntoAa(){
PuntoA aux;
ArchivoPuntoA arcA("archivoA.dat");

Material regM;
ArchivoMateriales archivoM("materiales.dat");

Compra regC;
ArchivoCompras archC("compras.dat");

int cant= archivoM.contarRegistros();
float imp;

    for (int i=0; i<cant; i++){
        regC= archivoM.leerRegistro(i);
        imp = impCompra(regM.getCodigoMaterial(), 2024);
    }
    aux.setCodMateril(regM.getCodigoMaterial());
    aux.setTipo(regM.getTipo());
    aux.setImporte(imp);
    arcA.grabar(aux);
}

void Punto2(){
    Obra objO;
    ArchivoObras regO("obras.dat");
    int contO=regO.contarRegistros();

    int vProvincia[24]={};

    for(int i = 0; i < contO; i++){
        objO=regO.leerRegistro(i);
        vProvincia[objO.getProvincia()-1]++;
    }

    for(int i = 0; i < 24; i++){
        cout<<"Provincia "<<i+1<<" cantidad de obras: "<<vProvincia[i]<<endl;
    }

}




int main(){
setlocale(LC_ALL, "");





cout<<endl;
system("pause");
return 0;
}
