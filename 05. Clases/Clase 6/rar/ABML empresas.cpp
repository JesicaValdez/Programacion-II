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

///CLASES DE MUNICIPIO
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
///FIN DE CLASES DE MUNICIPIO

class Empresa{
    private:
        int numero;
        char nombre[30];
        int cantidadEmpleados;
        ///Fecha fechaCreacion;  ///usar un objeto de una clase (Fecha) como propiedad de otra clase (Empresa) ->COMPOSICION
        int categoria; /// 1 a 80
        int numeroMunicipio;  //1 a 135
        bool estado;///true si el registro está activo; false si está borrado
    public:
        Empresa(){estado=false;}
        void setNumero(int n){numero = n;}
        void setCategoria(int c){categoria = c;}
        void setEstado(bool e){estado = e;}
        void setCantidadEmpleados(int ce){cantidadEmpleados=ce;}
        int getNumero(){return numero;}
        int getCantidadEmpleados(){return cantidadEmpleados;}
        int getNumeroMunicipio(){return numeroMunicipio;}
        int getCategoria(){return categoria;}
        bool getEstado(){return estado;}
        void Cargar();
        void Mostrar();
};

void Empresa::Cargar(){
    cout<<"NUMERO: ";
    cin>>numero;
    if(numero<1){
        return;
    }
    cout<<"NOMBRE: ";
    cargarCadena(nombre,29);
    cout<<"CANTIDAD DE EMPLEADOS: ";
    cin>>cantidadEmpleados;
    cout<<"CATEGORIA: ";
    cin>>categoria;
    cout<<"NUMERO DE MUNICIPIO: ";
    cin>>numeroMunicipio;
    estado=true;
}

Municipio buscarMunicipio(int num);

void Empresa::Mostrar(){
    if(estado==true){
        Municipio obj;
        cout<<"NUMERO: "<<numero<<endl;
        cout<<"NOMBRE: "<<nombre<<endl;
        cout<<"CANTIDAD DE EMPLEADOS: "<<cantidadEmpleados<<endl;
        cout<<"CATEGORIA: "<<categoria<<endl;
        cout<<"NUMERO DE MUNICIPIO: "<<numeroMunicipio<<"\t";
        obj=buscarMunicipio(numeroMunicipio);
        cout<<"NOMBRE DEL MUNICIPIO: "<<obj.getNombre();
    }
}

class ArchivoEmpresas{
    private:
        char nombre[30];
    public:
        ArchivoEmpresas(const char *n="empresas.dat"){strcpy(nombre,n);}
        bool grabarRegistro(Empresa obj);
        Empresa leerRegistro(int pos);
        int buscarRegistro(int num);
        int contarRegistros();
        bool modificarRegistro(Empresa obj, int pos);
        bool listarRegistros();
};


bool ArchivoEmpresas::grabarRegistro(Empresa obj){
    FILE *p;
    p=fopen(nombre, "ab");
    if(p==NULL) return false;
    bool escribio=fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}


bool ArchivoEmpresas::listarRegistros(){
    FILE *p;
    Empresa obj;
    p=fopen(nombre, "rb");
    if(p==NULL) return false;
    while(fread(&obj, sizeof obj, 1, p)==1){
            obj.Mostrar();
            cout<<endl;
    }
    fclose(p);
    return true;
}

int ArchivoEmpresas::buscarRegistro(int num){
    FILE *p;
    Empresa obj;
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

Empresa ArchivoEmpresas::leerRegistro(int pos){
    FILE *p;
    Empresa obj;
    p=fopen(nombre, "rb");
    obj.setNumero(-5);
    if(p==NULL) return obj;
    fseek(p, pos*sizeof obj,0);///función que permite ubicarse dentro del archivo
    fread(&obj, sizeof obj, 1, p);
    fclose(p);
    return obj;
}

bool ArchivoEmpresas::modificarRegistro(Empresa obj, int pos){
    FILE *p;
    p=fopen(nombre, "rb+"); ///agrega al modo de apertura lo que le falta
    if(p==NULL) return false;
    fseek(p, pos*sizeof obj,0);///función que permite ubicarse dentro del archivo
    bool escribio=fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

int ArchivoEmpresas::contarRegistros(){
    FILE *p;
    p=fopen(nombre, "rb");
    if(p==NULL) return -1;
    fseek(p, 0,2);///función que permite ubicarse dentro del archivo, en este caso lo ubiqué al final EOF
    int tam=ftell(p);///me devuelve la cantidad de bytes que hay desde el principio del archivo a la posición actual del indicador de pFILE.
    fclose(p);
    return tam/sizeof(Empresa);
}

void altaEmpresa(){
    Empresa reg;
    ArchivoEmpresas archiEmp("empresas.dat");
    reg.Cargar();
    archiEmp.grabarRegistro(reg);
}

void listarEmpresas(){
    ArchivoEmpresas archiEmp("empresas.dat");
    archiEmp.listarRegistros();

}

void bajaLogica(){
    Empresa reg;
    ArchivoEmpresas archiEmp("empresas.dat");
    cout<<"INGRESE EL NUMERO DE EMPRESA A BORRAR ";
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

Municipio buscarMunicipio(int num){
    Municipio reg;
    ArchivoMunicipios archiM;
    int pos=archiM.buscarRegistro(num);
    reg=archiM.leerRegistro(pos);
    return reg;
}

///
void municipiosMas5();
void listarPorCategoria();
void modificarCantidadEmpleados();
//

int main(){
    ArchivoEmpresas archiE("empresas.dat");
    while(true){
        int opc;
        system("cls");
        cout<<"MENU PRINCIPAL"<<endl;
        cout<<"--------------"<<endl;
        cout<<"1 - ALTA EMPRESA"<<endl;
        cout<<"2 - BAJA LOGICA EMPRESA"<<endl;
        cout<<"3 - MODIFICAR CANTIDAD DE EMPLEADOS"<<endl;
        cout<<"4 - LISTAR EMPRESAS"<<endl;
        cout<<"5 - BUSCAR EMPRESA POR NUMERO"<<endl;
        cout<<"6 - LISTAR MUNICIPIOS CON MAS DE 5 EMPRESAS"<<endl;
        cout<<"7 - LISTAR EMPRESAS POR CATEGORIA"<<endl;
        cout<<"0 - SALIR"<<endl;
        cout<<"----------------------------------------"<<endl;
        cout<<"INGRESE LA OPCION: ";
        cin>>opc;
        system("cls");
        switch(opc){
            case 1:
                altaEmpresa();
                break;
            case 2:
                cout<<"CANTIDAD DE REGISTROS "<<archiE.contarRegistros()<<endl;
                system("pause");
                bajaLogica();
                break;
            case 3:
                modificarCantidadEmpleados();
                break;
            case 4:
                listarEmpresas();
                break;
            case 5:
//                buscarRegistro();
                break;
            case 6: municipiosMas5();
                    break;
            case 7:
                listarPorCategoria();
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


 ///Calcular e informar la cantidad de municipios sin empresas.

 ///Listar los municipios con más de 5 empresas.
 ///Hay 135 municipios. Averiguar cuántas empresas tiene cada municipio, y mostrar sólo los que tienen más de 5
 void municipiosMas5(){
        int empresasMunicipios[135]={0};
        Empresa reg;
        ArchivoEmpresas archiEmp;
        ///Lectura de cada registro del archivo. Por cada lectura sumo un 1 al municipio que corresponda
        int cantReg=archiEmp.contarRegistros();
        for(int i=0;i<cantReg;i++){
            reg=archiEmp.leerRegistro(i);
            empresasMunicipios[reg.getNumeroMunicipio()-1]++;
        }
        ///Recorrer el vector, y mostrar las posiciones (+1) que tengan más de 5
        cout<<"MUNICIPIOS CON MAS DE 5 EMPRESAS "<<endl;
        for(int i=0;i<135;i++){
            if(empresasMunicipios[i]>5){
                cout<<i+1<<endl;
            }
        }
 }

 ///Listar los registros de las empresas que pertenezcan a una categoría que se ingresa por teclado

void listarPorCategoria(){
        Empresa reg;
        ArchivoEmpresas archiEmp;
        int categoria;

        int cantReg=archiEmp.contarRegistros();
        if(cantReg<=0){
            cout<<"PROBLEMAS CON ARCHIVO O ACHIVO INEXISTENTE"<<endl;
            return;
        }
        ///Lectura de cada registro del archivo. Por cada lectura comparo la categoría en el registro con la que se ingresó
        cout<<"CATEGORIA DE LAS EMPRESAS A LISTAR ";
        cin>>categoria;
        for(int i=0;i<cantReg;i++){
            reg=archiEmp.leerRegistro(i);
            if(reg.getCategoria()==categoria){
                reg.Mostrar();
                cout<<endl;
            }
    }
}


void modificarCantidadEmpleados(){
    Empresa reg;
    ArchivoEmpresas archiEmp("empresas.dat");
    cout<<"INGRESE EL NUMERO DE EMPRESA A MODIFICAR ";
    int num;
    cin>>num;
    int pos=archiEmp.buscarRegistro(num);
    if(pos<0){
        cout<<"NO SE ENCUENTRA EL REGISTRO"<<endl;
        return;
    }
    reg=archiEmp.leerRegistro(pos);
    reg.Mostrar();
    cout<<endl<<endl;
    cout<<"ESTA SEGURO DE MODIFICAR EL REGISTRO ? (S/N) ";
    char respuesta;
    cin>>respuesta;
    if(respuesta=='S' || respuesta =='s'){
        cout<<"INGRESE LA CANTIDAD NUEVA DE EMPLEADOS ";
        int cant;
        cin>>cant;
        reg.setCantidadEmpleados(cant);
        if(archiEmp.modificarRegistro(reg,pos)){
            cout<<"REGISTRO MODIFICADO";
        }
        else{
            cout<<"NO SE PUDO MODIFICAR EL REGISTRO";
        }
        cout<<endl;
    }

}
