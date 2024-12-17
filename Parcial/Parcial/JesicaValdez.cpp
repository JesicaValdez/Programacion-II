/*
Nombre: Jesica Valdez

ENUNCIADO:

*/

#include <iostream>
#include <locale>
#include <cstring>

using namespace std;

void cargarCadena(char *pal, int tam){
    int i;
    fflush(stdin);
    for (i=0; i<tam; i++)
    {
        pal[i] = cin.get();
        if(pal[i] == '\n')break;
    }
    pal[i]='\0';
    fflush(stdin);
}

class Fecha{
private:
    int dia, mes, anio;
public:
    Fecha(int d=0, int m=0, int a=0)
    {
        dia=d;
        mes=m;
        anio=a;
    }
    void Cargar();
    void Mostrar();
    //sets
    void setDia(int x){if(x>0 && x<32) dia=x;}
    void setMes(int x){if(x>0 && x<13) mes=x;}
    void setAnio(int x){anio=x;}
    //gets
    int getDia(){return dia;}
    int getMes(){return mes;}
    int getAnio(){return anio;}
};

void Fecha::Cargar(){
    cout<<"DIA: ";
    cin>>dia;
    cout<<"MES: ";
    cin>>mes;
    cout<<"ANIO: ";
    cin>>anio;
}

void Fecha::Mostrar(){
    cout<<dia<<"/"<<mes<<"/"<<anio<<endl;
}

class Final{
private:
    int _ID;
    int _IDVendedor;
    int _IDArticulo;
    int _IDProveedor;
    float _impuestos;
    float _costoTraslado;
    float _costoTotal;
    Fecha _fecha;
public:
    int getID(){return _ID;}
    int getIDVendedor(){return _IDVendedor;}
    int getIDArticulo(){return _IDArticulo;}
    int getIDProveedor(){return _IDProveedor;}
    float getImpuestos(){return _impuestos;}
    float getCostoTraslado(){return _costoTraslado;}
    float getCostoTotal(){return _costoTotal;}
    Fecha getFecha(){return _fecha;}

    void setID(int id){_ID=id;}
    void setIDVendedor(int idV){_IDVendedor=idV;}
    void setIDArticulo(int idArt){_IDArticulo=idArt;}
    void setProveedor(int idP){_IDProveedor=idP;}
    void setImpuestos(float imp){_impuestos=imp;}
    void setCostoTraslado(float cTraslado){_costoTraslado=cTraslado;}
    void setCostoTotal(float cTotal){_costoTotal=cTotal;}
    void setFecha(Fecha f){_fecha=f;}

    void Cargar(int id=0);
    void Mostrar();

    // Sobrecarga del operador ==
    bool operator==(const Final &otro) const {
        return _ID == otro._ID;
    }

};

void Final::Cargar(int id){
    if(id==0){
        cout<<"Ingrese ID: ";
        cin>>_ID;
    }
    else {
        setID(id);
    }
    cout<<"Ingrese ID Vendedor (1 a 20): ";
    cin>>_IDVendedor;
    cout<<"Ingrese ID Articulo (1 a 70): ";
    cin>>_IDArticulo;
    cout<<"Ingrese ID Proveedor: ";
    cin>>_IDProveedor;
    cout<<"Ingrese impuestos ";
    cin>>_impuestos;
    cout<<"Ingrese costo traslado: ";
    cin>>_costoTraslado;
    cout<<"Ingrese costo Total: ";
    cin>>_costoTotal;
    cout<<"Ingrese Fecha: "<<endl;
    _fecha.Cargar();
}

void Final::Mostrar(){
    cout<<"ID: "<<_ID<<endl;
    cout<<"ID Vendedor (1 a 20): "<<_IDVendedor<<endl;
    cout<<"ID Articulo (1 a 70): "<<_IDArticulo<<endl;
    cout<<"ID Proveedor: "<<_IDProveedor<<endl;
    cout<<"impuestos "<<_impuestos<<endl;
    cout<<"costo traslado: "<<_costoTraslado<<endl;
    cout<<"costo Total: "<<_costoTotal<<endl;
    cout<<"Fecha: "<<endl;
    _fecha.Mostrar();
    cout<<endl;
}

class ArchivoFinal{
    private:
        std::string _nombreArchivo;

    public:
        ArchivoFinal(std::string nombreArchivo);
        bool Guardar(Final final);
        bool Guardar(Final final, int posicion);
        int Buscar(int ID);
        Final Leer(int posicion);
        int CantidadRegistros();
};

ArchivoFinal::ArchivoFinal(std::string nombreArchivo){
    _nombreArchivo = nombreArchivo;
}

bool ArchivoFinal::Guardar(Final final){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "ab");
    if(pArchivo == NULL){
        return false;
    }
    bool ok = fwrite(&final, sizeof(Final), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

bool ArchivoFinal::Guardar(Final final,int posicion){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb+");
    if(pArchivo == NULL){
        return false;
    }
    fseek(pArchivo, sizeof(Final) * posicion, SEEK_SET);
    bool ok = fwrite(&final, sizeof(Final), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

int ArchivoFinal::Buscar(int ID){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return -1;
    }
   Final final;
    int i = 0;
    while(fread(&final, sizeof(final), 1, pArchivo)){
        if(final.getID() == ID){
            fclose(pArchivo);
            return i;
        }
        i++;
    }
    fclose(pArchivo);
    return -1;
}

Final ArchivoFinal::Leer(int posicion){
    Final final;
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return final;
    }

    fseek(pArchivo, sizeof(Final) * posicion, SEEK_SET);
    fread(&final, sizeof(Final), 1, pArchivo);
    fclose(pArchivo);
    return final;
}

int ArchivoFinal::CantidadRegistros(){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return 0;
    }
    fseek(pArchivo, 0, SEEK_END);
    int cantidadRegistros = ftell(pArchivo) / sizeof(Final);
    fclose(pArchivo);
    return cantidadRegistros;
}

void calcularIDVendedorConMasCompras(ArchivoFinal &archivo) {
    int cantidadRegistros=archivo.CantidadRegistros();
    if(cantidadRegistros==0){
        cout << "El archivo está vacío." << endl;
        return;
    }

    const int MAX_VENDEDORES = 20;
    int *contadorCompras=new int[MAX_VENDEDORES]();

    for(int i=0; i<cantidadRegistros; i++) {
        Final registro=archivo.Leer(i);
        int idVendedor=registro.getIDVendedor();
        if (idVendedor>= 1 && idVendedor <= MAX_VENDEDORES) {
            contadorCompras[idVendedor - 1]++;
        }
    }

    int maxCompras = 0;
    int idVendedorMax = -1;
    for (int i = 0; i < MAX_VENDEDORES; i++) {
        if (contadorCompras[i] > maxCompras) {
            maxCompras = contadorCompras[i];
            idVendedorMax = i + 1;
        }
    }

    if (idVendedorMax!= -1) {
        cout<<"El IDVendedor con más compras es: "<<idVendedorMax
             << " con " << maxCompras << " compras."<<endl;
    } else {
        cout<<"No se encontraron compras válidas."<<endl;
    }

    delete[] contadorCompras;
}

void listarRegistrosPorIDArticulo(ArchivoFinal &archivo) {
    int idArticuloBuscado;
    cout << "Ingrese el IDArticulo a buscar: ";
    cin >> idArticuloBuscado;

    int cantidadRegistros=archivo.CantidadRegistros();
    if(cantidadRegistros==0){
        cout<<"El archivo está vacío."<<endl;
        return;
    }

    Final *registrosCoincidentes= new Final[cantidadRegistros];
    int contador=0;

    for(int i=0; i<cantidadRegistros; i++) {
        Final registro=archivo.Leer(i);
        if (registro.getIDArticulo()==idArticuloBuscado) {
            registrosCoincidentes[contador++] = registro;
        }
    }

    if(contador>0){
        cout<<"Registros con IDArticulo "<<idArticuloBuscado << ":" << endl;
        for (int i=0; i<contador; i++) {
            registrosCoincidentes[i].Mostrar();
        }
    } else {
        cout<<"No se encontraron registros con el IDArticulo "<<idArticuloBuscado<<endl;
    }

    delete[] registrosCoincidentes;
}


int main (){
 setlocale(LC_ALL, "");

 ArchivoFinal archivo("finales.dat");

 //Punto A
  calcularIDVendedorConMasCompras(archivo);

  //Punto A
  listarRegistrosPorIDArticulo(archivo);



return 0;
}


