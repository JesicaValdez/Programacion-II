#include<iostream>
#include<cstring>

using namespace std;

#include "parcialm1.h"

class Punto1{
    private:
        char codigoObra[5];
        char direccion[30];
        int provincia;
    public:
        const char* getCodigoObra(){return codigoObra;}
        const char* getDireccion(){return direccion;}
        int getProvincia(){return provincia;}

        void setCodigoObra(const char *co){strcpy(codigoObra, co);}
        void setDireccion(const char *d){strcpy(direccion,d);}
        void setProvincia(int p){provincia=p;}
};

class ArchivoPunto1{
    private:
        char nombre[30];
    public:
        ArchivoPunto1(const char *n){
            strcpy(nombre, n);
        }
        bool escribirRegistro(Punto1 reg){
            FILE *p;
            p=fopen(nombre, "ab");
            if(p==NULL) return false;
            bool escribio = fwrite(&reg, sizeof reg, 1, p);
            fclose(p);
            return escribio;
        }
};

int main(){
    ArchivoObras obj("obras.dat");
    Obra reg;
    Punto1 aux;
    ArchivoPunto1 arc("Punto1.dat");
    int cantReg = obj.contarRegistros();
    for(int i=0; i<cantReg; i++){
        reg = obj.leerRegistro(i);
        if(reg.getEstadoEjecucion()==3){
            aux.setCodigoObra(reg.getCodigoObra());
            aux.setDireccion(reg.getDireccion());
            aux.setProvincia(reg.getProvincia());
            arc.escribirRegistro(aux);
        }
    }
    return 0;
}
