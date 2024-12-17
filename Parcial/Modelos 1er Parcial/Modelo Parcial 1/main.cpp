#include <iostream>
#include <cstdlib>
#include <cstring>
#include "parcialm1.h"

using namespace std;
///codigo de obra, direccion y provincia de las obras con estado "en ejecucion"

class Pto1
{
private:
    char codigoObra[5];
    char direccion[30];
    int provincia;
    int estadoEjecucion;

public:

    void Mostrar(){
        cout<<codigoObra<<endl;
        cout<<direccion<<endl;
        cout<<provincia<<endl;
        cout<<estadoEjecucion<<endl;
    }

    const char* getCodigoObra(){return codigoObra;}
    const char* getDireccion(){return direccion;}
    int getProvincia(){return provincia;}
    int getEstadoEjecucion(){return estadoEjecucion;}

    void setCodigoObra(const char *co){strcpy(codigoObra, co);}
    void setDireccion(const char *d){strcpy(direccion,d);}
    void setProvincia(int p){provincia=p;}
    void setEstadoEjecucion(int e){estadoEjecucion=e;}

} ;

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
int MostrarArchivo()
{
  Pto1 A;
  FILE *p;
  p=fopen("pto1.dat","rb");
  if(p==NULL){
    return -1;
  }
  while(fread(&A,sizeof(Pto1),1,p)==1){
    A.Mostrar();
    cout<<endl;
    };
  fclose(p);
  return 0;
}
int Pto1funcion(){

    Obra Ob1;
    Pto1 A;
    ArchivoPto1 B("pto1.dat");
    int J;

    FILE *p;
    p=fopen("obras.dat","rb");

    if(p==NULL){
      return -1;
    }

    while(fread(&Ob1,sizeof(Obra),1,p)==1){
      if(Ob1.getEstadoEjecucion()==3){
          A.setCodigoObra(Ob1.getCodigoObra());
          A.setDireccion(Ob1.getDireccion());
          A.setProvincia(Ob1.getProvincia());
          cout<<Ob1.getEstadoEjecucion();
          cout<<endl;

          cout<<A.getCodigoObra();
          cout<<A.getDireccion();
          cout<<A.getProvincia();
          system("pause");
          J=B.CargarArchivo(A);


          if(J==1){cout<<"Registro Guardado";}

      }
    }
    fclose(p);
    return 0;
}





int main()
{
    MostrarArchivo();
    system("pause");
    Pto1funcion();
    MostrarArchivo();

    return 0;
}
