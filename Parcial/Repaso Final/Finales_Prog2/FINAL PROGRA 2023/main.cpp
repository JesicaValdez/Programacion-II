#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

class Fecha{

private:
    int dia,mes, anio;
public:
    void Cargar(){
        cout<<"DIA ";cin>>dia;
        cout<<"MES ";cin>>mes;
        cout<<"ANIO ";cin>>anio;
    }
    void Mostrar(){
        cout<<dia<<"/";
        cout<<mes<<"/";
        cout<<anio<<endl;
    }
    int getDia(){return dia;}
    int getMes(){return mes;}
    int getAnio(){return anio;}

    void setDia(int d){dia=d;}
    void setMes(int m){mes=m;}
    void setAnio(int a){anio=a;}

};

class Conductores{

private:
    int DNI;
    char NombreApellido[50];
    int Provincia;
    int Categoria;
    int Especialidad;
    int AnioIngreso;
    bool estado;

public:

    void setDni(int d){DNI=d;}
    void setNombreApellido(const char* n){strcpy(NombreApellido,n);}
    void setProvincia(int p){Provincia=p;}
    void setCategoria (int c){Categoria=c;}
    void setEspecialidad (int esp){Especialidad=esp;}
    void setAnioIngreso (int a){AnioIngreso=a;}
    void setEstado(bool e){estado=e;}

    int getDni(){return DNI;}
    const char* getNombreApellido(){return NombreApellido;}
    int getProvincia(){return Provincia;}
    int getCategoria(){return Categoria;}
    int getEspecialidad(){return Especialidad;}
    int getAnioIngreso(){return AnioIngreso;}
    bool getEstado(){return estado;}
};
class ArchivosConductores{

  private:
  char nombre[30];

  public:

  ArchivosConductores(const char*n){
    strcpy(nombre,n);}

  Conductores leerRegistro(int pos){
    Conductores reg;
    FILE *p;
    p=fopen(nombre, "rb");
    if(p==NULL) return reg;
    fseek(p, sizeof reg*pos,0);
    fread(&reg, sizeof reg,1, p);
    fclose(p);
    return reg;
  }

  int contarRegistros(){

    FILE *p;
    p=fopen(nombre, "rb");
    if(p==NULL) return -1;
    fseek(p, 0,2);
    int tam=ftell(p);
    fclose(p);
    return tam/sizeof(Conductores);
  }
};


class Viajes{

private:
    int DNI;
    Fecha FechaViaje;
    int NumeroDestino;
    int NumeroVehiculo;
    int TipodeViaje;
    int Distancia;
    bool estado;

public:

    void setDni(int d){DNI=d;}
    void setFechaViaje(Fecha f){FechaViaje=f;}
    void setNumeroDestino(int nd){NumeroDestino=nd;}
    void setNumeroVehiculo (int nv){NumeroVehiculo=nv;}
    void setTipoDeViaje (int tv){TipodeViaje=tv;}
    void setDistancia (int d){Distancia=d;}
    void setEstado(bool e){estado=e;}

    int getDni(){return DNI;}
    Fecha getFechaViaje(){return FechaViaje;}
    int getNumeroDestino(){return NumeroDestino;}
    int getNumeroVehiculo(){return NumeroVehiculo;}
    int getTipodeViaje(){return TipodeViaje;}
    int getDistancia(){return Distancia;}
    bool getEstado(){return estado;}
};

class ArchivosViajes{

  private:
  char nombre[30];

  public:

  ArchivosViajes(const char*n){
    strcpy(nombre,n);}

  Viajes leerRegistro(int pos){
    Viajes reg;
    FILE *p;
    p=fopen(nombre, "rb");
    if(p==NULL) return reg;
    fseek(p, sizeof reg*pos,0);
    fread(&reg, sizeof reg,1, p);
    fclose(p);
    return reg;
  }

  int contarRegistros(){

    FILE *p;
    p=fopen(nombre, "rb");
    if(p==NULL) return -1;
    fseek(p, 0,2);
    int tam=ftell(p);
    fclose(p);
    return tam/sizeof(Viajes);
  }
};

class Punto1{

private:
  int DNI;
  char NombreApellido[50];
  int CantidadDeViajes;
  bool estado;


public:

  void setDni(int d){DNI=d;}
  void setNombreApellido (const char* nom){strcpy(NombreApellido,nom);}
  void setCantidadDeViajes(int cant){CantidadDeViajes=cant;}
  void setEstado(bool e){estado=e;}

  int getDni(){return DNI;}
  const char* getNombreApellido(){return NombreApellido;}
  int getCantidadViajes(){return CantidadDeViajes;}
  bool getEstado(){return estado;}

  ///PTO 3 *SOBRECARGA
  bool operator !=(Conductores obj){

  if(obj.getDni()!= DNI)return true;
  return false;
  }

};

class ArchivoPto1{

private:
  char nombre[30];

public:

  ArchivoPto1(const char*n){
    strcpy(nombre,n);}

  bool guardar(Punto1 reg){

    FILE *p=fopen(nombre, "ab");
    if(p==NULL){
      return false;
    }

    bool pudoEscribir= fwrite(&reg,sizeof(Punto1),1,p);
    fclose(p);
    return pudoEscribir;
  }
};

void DesarrolloPto1A(){

    Punto1 objP1;
    ArchivoPto1 objAPT1 ("Archivo1.dat");
    Conductores objCO;
    ArchivosConductores objACO ("conductores.dat");
    Viajes objVI;
    ArchivosViajes objAVI ("viajes.dat");

    int CantidadDeViajes;
    int CantidadDeConductores;

    CantidadDeConductores=objACO.contarRegistros();
    CantidadDeViajes=objAVI.contarRegistros();


    for(int i=0; i<CantidadDeConductores;i++){

      objCO=objACO.leerRegistro(i);
      int cont=0;
      bool cond=false;

      for(int j=0;j<CantidadDeViajes;j++){

        objVI=objAVI.leerRegistro(j);

        if(objCO.getDni()==objVI.getDni() && objVI.getTipodeViaje()==2 && objVI.getEstado()== true){
          cont++;
          cond=true;
        }

      }

      if (cond==true){

        objP1.setDni(objCO.getDni());
        objP1.setNombreApellido(objCO.getNombreApellido());
        objP1.setCantidadDeViajes(cont);
        objP1.setEstado(objCO.getEstado());

        objAPT1.guardar(objP1);
      }

    }

  }

void DesarrolloPto1B(){

  Conductores objCO;
  ArchivosConductores objACO ("conductores.dat");

  int vecCategorias[7]={};

  int CantidadDeConductores;

  CantidadDeConductores=objACO.contarRegistros();


  for(int i=0;i<CantidadDeConductores;i++){

    objCO=objACO.leerRegistro(i);

    if(objCO.getEstado()==true){
      vecCategorias[objCO.getCategoria()-1]++;
    }

  }

  int minimo=vecCategorias[0];
  int categoria=0;

  for(int j=1;j<7;j++){

    if(vecCategorias[j]<minimo){
      minimo=vecCategorias[j];
      categoria=j;
    }
  }


  cout<<"La categoria con menos conductores  es la categoria: "<< categoria+1;

}





int main()
{
    DesarrolloPto1A();
    DesarrolloPto1B();
    return 0;
}
