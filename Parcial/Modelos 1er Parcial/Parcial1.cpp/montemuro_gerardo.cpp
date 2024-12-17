#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

#include "parcial1.h"

class Pto1
{
private:
  int codigo;
  char nombre[15];
  Fecha fechaultimacompra;
public:
  int getCodigo(){return codigo;}
  const char* getNombre(){return nombre;}
  Fecha getFechaUltimaCompra(){return fechaultimacompra;}

  void setNombre(const char *n){strcpy(nombre,n);}
  void setCodigo(int c){codigo=c;}
  void setFechaUltimaCompra(Fecha f){fechaultimacompra=f;}

};

class ArchivoPto1
{
private:
  char nombre[30];
public:
    ArchivoPto1(const char *n){
        strcpy(nombre, n);
    }
   int CargarArchivo(Pto1 n);
};

int ArchivoPto1::CargarArchivo(Pto1 n){
    int valor;
    FILE *p;
    p=fopen(nombre,"ab");
    if(p==NULL){
      return -1;
    }
    valor=fwrite(&n,sizeof(Pto1),1,p);
    fclose(p);
    return valor;
  }

int Pto1Funcion(){

  ArchivoPto1 B("pto1.dat");
  Componente C;
  Pto1 A;
  int J;

  FILE *p;
  p=fopen("componentes.dat","rb");
  if (p==NULL){
    return -1;
  }

  while(fread(&C,sizeof(Componente),1,p)==1){
    if((C.getFecha().getAnio()>2022)&&(C.getTipo()>2)){
      A.setCodigo(C.getCodigo());
      A.setNombre(C.getNombre());
      A.setFechaUltimaCompra(C.getFecha());

      system("pause");
      J=B.CargarArchivo(A);

      if(J==1){cout<<"Registro Guardado";}

    }
  }
    fclose(p);
    return 0;
}

void Pto2(){

    int v[6]={};
    Proyecto reg;
    ArchivoProyecto obj("proyectos.dat");
    int cantReg = obj.contarRegistros();
    for(int i=0; i<cantReg; i++){
        reg = obj.leerRegistro(i);
        v[reg.getEstadoDesarrollo()-1]++;
    }

    int pos=-1;
    for(int i=0; i<6; i++){
        if(v[i]!=0 && pos==-1){
            pos=i;
        }else if(v[i]!=0 && v[i]>v[pos]){
            pos=i;
        }
    }
    while(pos+1==reg.getEstadoDesarrollo()){
        cout<<"EL ESTADO DE PROYECTO QUE MS PROYECTOS TENGA: "<<
        reg.getEstadoDesarrollo()<<endl;}
    }



int main()
  {
     int opcion;

    do{
        cout<<"PARCIAL 1 DE PROGRAMACION"<<endl;
        cout<<"=========================="<<endl;
        cout<<"OPCION 1 : PTO 1 - CREAR ARCHIVO NUEVO"<<endl;
        cout<<"OPCION 2 : PTO 2 - EL ESTADO DE PROYECTO QUE MS PROYECTOS TENGA"<<endl;
        cout<<"OPCION 3 : PTO 3"<<endl;
        cout<<"OPCION 4 : PTO 4"<<endl;
        cout<<"OPCION 0 : SALIR"<<endl;
        cout<<"=========================="<<endl;
        cout<<"SELECCIONA UNA OPCION: ";
        cin >>opcion;
        cout<<endl;
        switch(opcion){

            case 1:
              Pto1Funcion();
              break;
              Pto2();
            case 2:
              break;

            case 3:
              break;

            case 4:
              break;

            case 0:
              break;

        }

    }while(opcion!=0);
    return 0;
}
