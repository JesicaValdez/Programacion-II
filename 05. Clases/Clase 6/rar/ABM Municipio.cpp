#include <iostream>
#include <cstring>

using namespace std;

void cargarCadena(char *pal, int tam){
    int i;
    fflush (stdin); ///limpia el buffer de entrada para que la carga se haga sin caracteres que hayan quedado sin usar
    for(i=0; i<tam;i++){
        pal[i]=cin.get();
        if(pal[i]=='\n')break;
    }
    pal[i]='\0';
    fflush(stdin); ///vuelve a limpiar el buffer para eliminar los caracteres sobrantes
}

class Municipio{
    private:
        int numero; ///1 a135
        char nombre[30];
        int cantidadHabitantes;
        int seccion; /// 1 a 6
        bool estado;///true si el registro está activo; false si está borrado
    public:
        Municipio(){estado=false;}
        void setNumero(int n){numero = n;}
        void setSeccion(int c){seccion = c;}
        void setEstado(bool e){estado = e;}
        int getNumero(){return numero;}
        int getCantidadHabitantes(){return cantidadHabitantes;}
        int getSeccion(){return seccion;}
        const char *getNombre(){return nombre;}
        bool getEstado(){return estado;}
        void Cargar();
        void Mostrar();
};

void Municipio::Cargar(){
    cout<<"NUMERO: ";
    cin>>numero;
    if(numero<1){
        return;
    }
    cout<<"NOMBRE: ";
    cargarCadena(nombre,29);
    cout<<"CANTIDAD DE HABITANTES: ";
    cin>>cantidadHabitantes;
    cout<<"SECCION: ";
    cin>>seccion;
    estado=true;
}

void Municipio::Mostrar(){
    if(estado==true){
        cout<<"NUMERO: "<<numero<<endl;
        cout<<"NOMBRE: "<<nombre<<endl;
        cout<<"CANTIDAD DE HABITANTES: "<<cantidadHabitantes<<endl;
        cout<<"SECCION: "<<seccion<<endl;
    }
}

class ArchivoMunicipios{
    private:
        char nombre[30];
    public:
        ArchivoMunicipios(const char *n="Municipios.dat"){strcpy(nombre,n);}
        bool grabarRegistro(Municipio obj);
        Municipio leerRegistro(int pos);
        int buscarRegistro(int num);
        int contarRegistros();
        bool modificarRegistro(Municipio obj, int pos);
        bool listarRegistros();
};


bool ArchivoMunicipios::grabarRegistro(Municipio obj){
    FILE *p;
    p=fopen(nombre, "ab");
    if(p==NULL) return false;
    bool escribio=fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}


bool ArchivoMunicipios::listarRegistros(){
    FILE *p;
    Municipio obj;
    p=fopen(nombre, "rb");
    if(p==NULL) return false;
    while(fread(&obj, sizeof obj, 1, p)==1){
            obj.Mostrar();
            cout<<endl;
    }
    fclose(p);
    return true;
}

int ArchivoMunicipios::buscarRegistro(int num){
    FILE *p;
    Municipio obj;
    p=fopen(nombre, "rb");
    int pos=0;
    if(p==NULL) return -1;
    while(fread(&obj, sizeof obj, 1, p)==1){
                if(obj.getNumero()==num){
                    fclose(p);
                    return pos;
                }
                pos++;
    }
    fclose(p);
    return -2;
}

Municipio ArchivoMunicipios::leerRegistro(int pos){
    FILE *p;
    Municipio obj;
    p=fopen(nombre, "rb");
    obj.setNumero(-5);
    if(p==NULL) return obj;
    fseek(p, pos*sizeof obj,0);///función que permite ubicarse dentro del archivo
    fread(&obj, sizeof obj, 1, p);
    fclose(p);
    return obj;
}

bool ArchivoMunicipios::modificarRegistro(Municipio obj, int pos){
    FILE *p;
    p=fopen(nombre, "rb+"); ///agrega al modo de apertura lo que le falta
    if(p==NULL) return false;
    fseek(p, pos*sizeof obj,0);///función que permite ubicarse dentro del archivo
    bool escribio=fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

int ArchivoMunicipios::contarRegistros(){
    FILE *p;
    p=fopen(nombre, "rb");
    if(p==NULL) return -1;
    fseek(p, 0,2);///función que permite ubicarse dentro del archivo, en este caso lo ubiqué al final EOF
    int tam=ftell(p);///me devuelve la cantidad de bytes que hay desde el principio del archivo a la posición actual del indicador de pFILE.
    fclose(p);
    return tam/sizeof(Municipio);
}

void altaMunicipio(){
    Municipio reg;
    ArchivoMunicipios archiEmp("Municipios.dat");
    reg.Cargar();
    archiEmp.grabarRegistro(reg);
}

void listarMunicipios(){
    ArchivoMunicipios archiEmp("Municipios.dat");
    archiEmp.listarRegistros();

}

void bajaLogicaMunicipio(){
    Municipio reg;
    ArchivoMunicipios archiEmp("Municipios.dat");
    cout<<"INGRESE EL NUMERO DE Municipio A BORRAR ";
    int num;
    cin>>num;
    int pos=archiEmp.buscarRegistro(num);
    if(pos<0){
        cout<<"NO SE ENCUENTRA EL REGISTRO"<<endl;
        return;
    }
    reg=archiEmp.leerRegistro(pos);
    reg.Mostrar();
    cout<<"ESTA SEGURO DE ELIMINAR EL REGISTRO ? (S/N) ";
    char respuesta;
    cin>>respuesta;
    if(respuesta=='S' || respuesta =='s'){
        reg.setEstado(false);
        if(archiEmp.modificarRegistro(reg,pos)){
            cout<<"REGISTRO ELIMINADO";
        }
        else{
            cout<<"NO SE PUDO ELIMINAR EL REGISTRO";
        }
        cout<<endl;
    }

}

int main(){
    ArchivoMunicipios archiE("Municipios.dat");
    while(true){
        int opc;
        system("cls");
        cout<<"MENU PRINCIPAL"<<endl;
        cout<<"--------------"<<endl;
        cout<<"1 - ALTA MUNICIPIO"<<endl;
        cout<<"2 - BAJA LOGICA MUNICIPIO"<<endl;
        cout<<"3 - MODIFICAR SECCION MUNICIPIO"<<endl;
        cout<<"4 - LISTAR MUNICIPIOS"<<endl;
        cout<<"5 - BUSCAR MUNICIPIO POR NUMERO"<<endl;
        cout<<"0 - SALIR"<<endl;
        cout<<"----------------------------------------"<<endl;
        cout<<"INGRESE LA OPCION: ";
        cin>>opc;
        system("cls");
        switch(opc){
            case 1:
                altaMunicipio();
                break;
            case 2:
                cout<<"CANTIDAD DE REGISTROS "<<archiE.contarRegistros()<<endl;
                system("pause");
                bajaLogicaMunicipio();
                break;
            case 3:

                break;
            case 4:
                listarMunicipios();
                break;
            case 5:
//                buscarRegistro();
                break;
            case 0:
                return 0;
            default:
                cout<<"LA OPCION INGRESADA NO ES CORRECTA"<<endl;
                system("pause");
                break;
        }
        system("pause");
    }
    return 0;
}


