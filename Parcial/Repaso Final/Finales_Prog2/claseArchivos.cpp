/*Nombre: Jesica Valdez
*/

#include <iostream>
#include <locale>
#include <cstdlib>
#include <cstring>

using namespace std;

void cargarCadena(char *pal, int tam);

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

class Persona{
protected:
    int DNI;
    Fecha fechaNac;
    char nombre[25];
    char apellido[25];
    char email[25];
    char telefono[20];
    bool estado;
public:
    int getDNI(){return DNI;}
    Fecha getFechaNac(){return fechaNac;}
    const char* getNombre(){return nombre;}
    const char* getApellido(){return apellido;}
    const char* getEmail(){return email;}
    const char* getTelefono(){return telefono;}
    bool getEstado(){return estado;}

    void setDNI(const int d){DNI=d;}
    void setFechaNac(Fecha f){fechaNac = f;}
    void setNombre(const char *n){strcpy(nombre, n);}
    void setApellido(const char *a){strcpy(apellido, a);}
    void setEmail(const char *e){strcpy(email,e);}
    void setTelefono(const char *t){strcpy(telefono, t);}
    void setEstado(bool e){estado=e;}

    void Cargar(int d);
    void Mostrar();
};

/*
Fecha Persona::getFechaNac(){
   return fechaNac;
}
*/

void Persona::Cargar(int d= -1){
    if(d==-1){
        cout<<"DNI: ";
        cin>>DNI;
    }
    else {
        setDNI(d);
    }
    cout<<"Fecha Nacimiento: "<<endl;
    fechaNac.Cargar();
    cout<<"Nombre: ";
    cargarCadena(nombre, 24);
    cout<<"Apellido: ";
    cargarCadena(apellido, 24);
    cout<<"EMAIL: ";
    cargarCadena(email, 24);
    cout<<"Telefono: ";
    cargarCadena(telefono, 19);
    estado=true;
}

void Persona::Mostrar(){
    if(estado==true)
    {
        cout<<"DNI: ";
        cout<<DNI<<endl;
        cout<<"Fecha Nacimiento: "<<endl;
        fechaNac.Mostrar();
        cout<<"Nombre: ";
        cout<<nombre<<endl;
        cout<<"Apellido: ";
        cout<<apellido<<endl;
        cout<<"EMAIL: ";
        cout<<email<<endl;
        cout<<"Telefono: ";
        cout<<telefono<<endl;
    }
}

class Cliente: public Persona{
private:
    char CUIT[12];
    Fecha fechaInicio;
public:
    const char *getCUIT(){return CUIT;}
    Fecha getFechaInicio(){return fechaInicio;}
    void setCUIT(const char *c){strcpy(CUIT, c);}
    void setFechaInicio(Fecha fi){fechaInicio=fi;}

    //Metodos
    void Cargar(int d);
    void Mostrar();
};
void Cliente::Cargar(int d=-1){
    Persona::Cargar(d);
    cout<<"CUIT: ";
    cargarCadena(CUIT, 11);
    cout<<"Fecha de Inicio: "<<endl;
    fechaInicio.Cargar();
}
void Cliente::Mostrar(){
    if(estado==true)
    {
        Persona::Mostrar();
        cout<<"CUIT "<< CUIT<<endl;
        cout<<"Fecha de Inicio"<<endl;
        fechaInicio.Mostrar();
    }
}

bool mostrarArchivoClientes();
int cargarClienteArchivo();
void buscarEnArchivo();

///CLAS ARCHIVO
class ArchivoCliente{
private:
    char nombre[30];
public:
    //constructor
    ArchivoCliente(const char *n)
    {
        strcpy(nombre, n); //LE COPIAMOS EN NOMBRE EL VALOR QUE RECIBIMOS DESPUES DE LA COMA
    }
    const char *getNombre(){return nombre;}
    void setNombre(const char *n){strcpy(nombre, n);}

    //Modulos
    int agregarRegistro();
    int sobreEscribirRegistro(Cliente reg, int pos);
    int bajaLogica();
    int modificarEmail();
    bool listarArcihvo();
    int buscarDNI(int valor);
    Cliente leerRegistro(int pos);
    void mostrarPorFecha(Fecha aux); //listado filtrado
    bool vaciarArchivo();
};

int ArchivoCliente::agregarRegistro(){
    Cliente reg;
    FILE *pCliente;
    int DNI;

    cout<<"Ingrese DNI: ";
    cin >> DNI;

    if(buscarDNI(DNI)> -1){
        cout<<"El usuario ya se encuentra cargado"<<endl;
        return -1;
    }
    else{
    pCliente=fopen(nombre, "ab");

    if(pCliente==NULL){
        return -1;
    }

    reg.Cargar(DNI); //variable que contiene los datos que queremos llevar al disco
    int valor=fwrite(&reg, sizeof reg, 1, pCliente);
    fclose(pCliente);
    return valor;
    }
}

int ArchivoCliente::bajaLogica(){
//buscar
    char opc;
    int DNI, pos;
    cout<<"Ingrese el DNI del cliente a Borrar :";
    cin>>DNI;
    pos=buscarDNI(DNI);
    if(pos==-1)
    {
        cout<<"No hay clientes con ese DNI"<<endl;
        return -1;
    }
//leer
    Cliente reg;
    reg=leerRegistro(pos);
    cout<<"-------------------------------------"<<endl;
    cout<<"|||||||||Registro Encontrado|||||||||"<<endl;
    cout<<"-------------------------------------"<<endl;
    reg.Mostrar();
    cout<<"Esta sefuro que desea borrar (S/N): ";
    cin>>opc;
       if(opc=='s' || opc=='S')
    {
//cambiar el estado
        reg.setEstado(false);
        cout<<"Datos del Cliente fueron eliminados exitosamente"<<endl;
    }
//sobreescribir el reg
    sobreEscribirRegistro(reg, pos);
    return 1;
}

int ArchivoCliente::sobreEscribirRegistro(Cliente reg, int pos){
    FILE *pCliente;

    pCliente=fopen(nombre, "rb+");
    if(pCliente==NULL)
    {
        return -1;
    }

    fseek(pCliente, pos*sizeof(Cliente), 0 );

    int valor=fwrite(&reg, sizeof reg, 1, pCliente);
    fclose(pCliente);
    return valor;
}

int ArchivoCliente::modificarEmail(){
//buscar
    int DNI, pos, opc;
    char email[25];

    cout<<"Ingrese el DNI del cliente para modificar su email:";
    cin>>DNI;

    pos=buscarDNI(DNI);
    if(pos==-1)
    {
        cout<<"No hay clientes con ese DNI"<<endl;
        return -1;
    }
//leer
cout<<"Esta sefuro que desea modificar (S/N): ";
    cin>>opc;
       if(opc=='s' || opc=='S')
    {
    Cliente reg;
    reg=leerRegistro(pos);
    cout<< "-------------------------------" <<endl;
    cout<< "||||||Registro Encontrado||||||" <<endl;
    cout<< "-------------------------------" <<endl;
    reg.Mostrar();

        cout<<"Ingrese nuevo Email: ";
        cargarCadena(email, 24);
        reg.setEmail(email);
        //sobreescribir el reg
        sobreEscribirRegistro(reg, pos);
        cout<<"Email modificado exitosamente"<<endl;
    }
    return 1;
}

bool ArchivoCliente::listarArcihvo(){
//Abrimos el archivo, chequeamos la apertura, si pudo abrir lo listamos, finalmente cerramos
    Cliente reg;
    FILE *pCliente;
    pCliente=fopen(nombre, "rb");

    if(pCliente==NULL)
    {
        return false;
    }

    while(fread(&reg, sizeof reg, 1, pCliente)==1)
    {
        reg.Mostrar();
        cout<<endl;
    }

    fclose(pCliente);
    return true;
}


int ArchivoCliente::buscarDNI(int valor){
    //abrimos el arvhivo, leo registro individualmente, y preguntamos si el que leyo es igual al que ingresamos por parametro necesito guardar su posicion
    Cliente reg;
    FILE *pCliente;


    pCliente=fopen(nombre, "rb");
    if(pCliente==NULL)
    {
        return -2;
    }

    int pos = 0;
    while(fread(&reg, sizeof reg, 1, pCliente)==1)
    {
        if(reg.getDNI()==valor)
        {
            fclose(pCliente);
            return pos;
        }
        pos++;
    }

    fclose(pCliente);
    return -1; //devolvemos porque no hubieron concidencias
}

Cliente ArchivoCliente::leerRegistro(int posParametro){
    Cliente reg;
    FILE *pCliente;

    pCliente=fopen(nombre, "rb");
    if(pCliente==NULL)
    {
        reg.setDNI(-2);
        return reg;
    }
//Desplazo el puntero hacia donde quiero leer:
    fseek(pCliente, posParametro*sizeof reg, 0);
///fseek(puntero FILE sobre sobre el que se abrio el archivo, cantidad de bytes a desplazarse, desde donde desplazarse)
///desde donde= 0 SEEK_SET el desplazamiento va desde el principio del archivo
///desde donde= 1 SEEK_CUR el desplazamiento va desde donde se encuentra el indicador del puntero FILE
///desde donde= 2 SEEK_END el desplazamiento va desde el FIN del archivo


//ahora leo:
    int leyo= fread(&reg, sizeof reg, 1, pCliente);
    fclose(pCliente);
    if(leyo==0)
    {
        reg.setDNI(-3);
    }
    return reg;
}

/*
///aternativa sin FSEEK()
Cliente ArchivoCliente::leerRegistro(int posParametro){
Cliente reg;
reg.setDNI(-2);//ejemplo para hacer referencia a que si devuelve -2 se cerro porque no se pudo abrir el archivo
FILE *pCliente;
int pos=0;

pCliente=fopen(nombre, "rb");
if(pCliente==NULL){
    return reg;
}
while(fread(&reg, sizeof reg, 1, pCliente)==1){
    if(pos==posParametro){
        fclose(pCliente);
        return reg;
    }
    pos++;
}

fclose(pCliente);
reg.setDNI(-3); // si llego aca y devuelve esto es porque no encontro una coincidencia de posiciones
return reg;

}
*/
void ArchivoCliente::mostrarPorFecha(Fecha aux){
    Cliente reg;
    FILE *pCliente;

    pCliente=fopen(nombre, "rb");
    if(pCliente==NULL)
    {
        return;
    }

    while(fread(&reg, sizeof reg, 1, pCliente)==1)
    {
        if(reg.getFechaInicio().getDia()==aux.getDia())
            if(reg.getFechaInicio().getMes()==aux.getMes())
                if(reg.getFechaInicio().getAnio()==aux.getAnio())
                    reg.Mostrar();
    }
    fclose(pCliente);
}

bool ArchivoCliente::vaciarArchivo(){
    char opc;
    cout<<"Esta accion eliminara los registros existentes."<<endl;
    cout<<"Esta seguro/a de continuar: (S/N)";
    cin>>opc;

    if(opc=='s' || opc=='S')
    {
        FILE *pCliente;

        pCliente=fopen(nombre, "wb");
        if(pCliente==NULL)
        {
            return false;
        }
        fclose(pCliente);
        return true;
    }

    cout<<"El archivo no fue modificado"<<endl;
    return true;

}

int main (){
    setlocale(LC_ALL, "");

    ArchivoCliente aux("cliente.dat");
    //aux.vaciarArchivo();

    int opc;
    while(true){
        system("cls");
        cout<<"Menu Principal"<<endl;
        cout<<"---------------------"<<endl;
        cout<<"1 - Cargar registro de cliente en archivo"<<endl;
        cout<<"2 - Mostrar archivo clientes"<<endl;
        cout<<"3 - Buscar Cliente"<<endl; //debe pedir DNI y mostrar el registro que contiene ese DNI
        cout<<"4 - Mostar PorFecha"<<endl; //recibe una fecha y muestra los registros en los que coincidan la fecha recibida con la fecha de Inicio
        cout<<"5 - Eliminar registro de cliente en el archivo"<<endl;
        cout<<"6 - Modificar registro de email"<<endl;
        cout<<"0 - Salir del Programa"<<endl;
        cout<<"---------------------"<<endl;
        cin>>opc;
        system("cls");

        switch(opc)
        {
        case 1:
            if(aux.agregarRegistro()!=1){
                cout<<"No se pudo agregar el registro"<<endl;
            }
            else{
                cout<<"Registro agregado"<<endl;
            }
            break;
        case 2:
            if(aux.listarArcihvo()==false){
                cout<<"No se pudo abrir el archivo"<< endl;
            }
            break;
        case 3:
        {
            int DNI;
            cout<<"Ingrese el DNI del cliente a buscar: ";
            cin>>DNI;
            int pos = aux.buscarDNI(DNI);
            if(pos== -1)
            {
                cout<< "No existe un cliente con ese DNI"<< endl;
            }
            else
            {
                aux.leerRegistro(pos).Mostrar();
            }
            break;
        }
        case 4:
        {
            Fecha fecha;
            cout<<"Ingrese la fecha (DIA/MES/ANIO): "<<endl;
            fecha.Cargar();
            aux.mostrarPorFecha(fecha);
            break;
        }
        case 5:
            aux.bajaLogica();
            break;
        case 6:
            aux.modificarEmail();
            break;
        case 0:
            return 0;
            break;
        default:
            cout<<"Opcion invalida";
            break;
        }
        cout<<endl;
        system("pause");
    }
    return 0;

}


bool mostrarArchivoClientes(){
    ArchivoCliente aux("cliente.dat");
    return aux.listarArcihvo();
}

int cargarClienteArchivo(){
    ArchivoCliente aux("cliente.dat");
    return aux.agregarRegistro();
}

/*
void buscarEnArchivo(){
int DNI;
ArchivoCliente obj("cliente.dat");
Cliente reg;

cout<<"Ingrese el DNI del cliente a buscar: ";
cin>>DNI;

int pos=obj.buscarDNI(DNI);
if(pos==-1){
    cout<<"No existe un cliente con ese DNI"<<endl;
    return;
}
//si existe...
reg=obj.leerRegistro(pos);
reg.Mostrar();
}
*/

/*
int cargarClienteArchivo(){
Cliente reg;
FILE *pCliente;

pCliente=fopen("cliente.dat", "ab");
if(pCliente==NULL){
    cout<<"No se pudo crear o abrir el archivo"<<endl;
    return -1;
}
reg.Cargar(); //variable que contiene los datos que queremos llevar al disco

int valor=fwrite(&reg, sizeof reg, 1, pCliente);
fclose(pCliente);
return valor;
}


bool mostrarArchivoClientes(){
Cliente reg;
FILE *pCliente;
pCliente=fopen("cliente.dat", "rb");
if(pCliente==NULL){
    cout<<"No se pudo crear o abrir el archivo"<<endl;
    return false;
}

//de esta manera abrimos 2 archivos (sin forma dinamica de apertura)
/*fread(&reg, sizeof reg, 1, pCliente); // la lectura es de disco al ram. Parametro: Direccion de memoria, cantidad de archivos deseados para abrir, especificacion del nombre de archivo
reg.Mostrar();
cout<<endl;
fread(&reg, sizeof reg, 1, pCliente);

fclose(pCliente);
reg.Mostrar();
*/
/*
//leer de manera dinamica:
while(fread(&reg, sizeof reg, 1, pCliente)==1){
    reg.Mostrar();
    cout<<endl;
}
fclose(pCliente);

return true;
}
*/

/*
void buscarCliente(){
int DNI;

cout<<"Ingrese DNI del cliente que desea buscar: ";
cin>>DNI;

FILE *p;
p=fopen("cliente.dat", "rb");
if(p=NULL){
    cout<<"No se pudo abrir el archivo"<<endl;
    system("pause");
    return;
}
Cliente reg;
bool encontro=false;
/*
ALTERNATIVA:
while(fread(&reg, sizeof reg, 1, p)==1 && encontro==false){
    if(DNI==reg.getDNI()){
        reg.Mostrar();
        encontro=true;
    }
}

  if(encontro==false){
        cout<<"No existe un registro con ese DNI"<<endl;
    }
        fclose(p);
*/
/*
while(fread(&reg, sizeof reg, 1, p)==1){
    if(DNI==reg.getDNI()){
        reg.Mostrar();
        fclose(p);
        return;
    }
}
    if(encontro==false){
        cout<<"No existe un registro con ese DNI"<<endl;
        fclose(p);
    }


}
*/
