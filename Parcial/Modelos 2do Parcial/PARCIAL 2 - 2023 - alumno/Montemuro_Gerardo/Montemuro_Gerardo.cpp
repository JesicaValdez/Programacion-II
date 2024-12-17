#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;
#include "parcial2.h"


class Punto1{

private:
  int codigoRestaurante;
  char nombre[30];
  int cantidadDeVentas;

public:
  void Mostrar();
  int getCodigoRestaurante(){return codigoRestaurante;}
  void setCodigoRestaurante(int cd){codigoRestaurante=cd;}
  const char *getNombre(){return nombre;}
  void setNombre (const char *n){strcpy(nombre,n);}
  int getCantidadDeVentas(){return cantidadDeVentas;}
  void setCantidadDeVentas(int cv){cantidadDeVentas=cv;}
  /*
  //PTO 3
  bool operator >=(int num){
    if(cantidadDeVentas >= num) return true;
    return false;}*/

};

void Punto1::Mostrar(){
  cout<<"CODIGO DE RESTAURANTE :# "<<codigoRestaurante<<endl;
  cout<<"NOMBRE DEL RESTAURANTE:# "<<nombre<<endl;
  cout<<"CANTIDAD DE VENTAS    :# "<<cantidadDeVentas<<endl;

}

class ArchivoPunto1{
  private:
    char nombre[30];

  public:

    ArchivoPunto1(const char *n){
      strcpy(nombre, n);
    }
    ////GUARDAR REGISTRO.
    bool guardar(Punto1 reg) {

      FILE *p = fopen(nombre, "ab");
      if (p == NULL)
      {
        return false;
      }
      bool pudoEscribir = fwrite(&reg, sizeof(Punto1), 1, p);
      fclose(p);
      return pudoEscribir;
    }
    ///MUESTRA ARCHIVO
    bool MostrarArchivo(){
    Punto1 objPto1;

    FILE *p;
    p= fopen(nombre,"rb");
    if(p==NULL){
     cout<<"no abrio el archivo";
     return false;
     }

     while(fread(&objPto1,sizeof(Punto1),1,p)==1){
        objPto1.Mostrar();
      cout<<endl;
      }
      fclose(p);
      return true;
    }


  };

void Punto1Funcion(){

  Punto1 objP;
  ArchivoPunto1 objAP1("archivo1.dat");
  Restaurante objR;
  ArchivoRestaurantes objRA("restaurantes.dat");
  Venta objV;
  ArchivoVentas objVA("ventas.dat");
  int contador;
  int cantidadDeVentas;
  int cantidadDeRestaurantes;

  cantidadDeVentas=objVA.contarRegistros();
  cantidadDeRestaurantes=objRA.contarRegistros();

  //CARGAR ARCHIVO
  for(int i=0; i<cantidadDeRestaurantes;i++){
    objR=objRA.leerRegistro(i);
    contador=0;

    if(objR.getCategoria()==4){

      for(int j=0;j<cantidadDeVentas;j++){

      objV=objVA.leerRegistro(j);
        if(objR.getCodigoRestaurante()==objR.getCodigoRestaurante() && objV.getFechaReserva().getAnio()==2022 && objV.getEstado()==true){
        contador++;
        }
      }
      objP.setCantidadDeVentas(contador);
      objP.setCodigoRestaurante(objR.getCodigoRestaurante());
      objP.setNombre(objR.getNombre());

      objAP1.guardar(objP);
    }

  }

  //LISTAR ARCHIVO
  objAP1.MostrarArchivo();

}

void Punto2Funcion(){

  ArchivoRestaurantes objAR ("restaurantes.dat");
  Restaurante objR;
  int cantidadDeRestaurantes;
  int vecProvincias[24]={0};
  int contadorProvincias=0;

  cantidadDeRestaurantes=objAR.contarRegistros();

  for(int i=0; i<cantidadDeRestaurantes;i++){
    objR=objAR.leerRegistro(i);
    if(objR.getEstado()==true){
    vecProvincias[objR.getProvincia()-1]++;}
  }

  for(int j=0; j<24;j++){
    if(vecProvincias[j]<5 && vecProvincias[j]>0){
      contadorProvincias++;
    }
  }

  cout<<"LA CANTIDAD DE PROVINCIAS QUE TIENEN MENOS DE 5 RESTAURANTES SON: "<<contadorProvincias;

}





int main()
{

  cout<<"PUNTO 1:"<<endl;
  Punto1Funcion();
  cout<<"PUNTO 2:"<<endl;
  Punto2Funcion();

    return 0;
}
