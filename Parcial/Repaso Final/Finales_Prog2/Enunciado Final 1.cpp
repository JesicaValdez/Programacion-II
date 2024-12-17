/*
Nombre: Jesica Valdez

ENUNCIADO:
1) Desarrollar un programa con un menú para dar el alta, baja lógica y listado del siguiente archivo:
guías.dat:
DNI (int),
nombre y apellido (char[50])
código de nacionalidad (1 a 50)
nivel (1 a 15)
fecha de nacimiento.

2) Agregar un constructor para alguna de las clases del ejercicio 1.
El método debe poner en 0 alguna propiedad de tipo int si no se le envía valor; si se envía un valor debe usar el valor enviado para la propiedad.

2A) Agregar un constructor para la clase que da formato a los registros de archivo con valores por omision que deben usarse en caso que el constructor sea llamado sin valores. Si recibe valores debe usarlos ignorando los que tiene por omision (2 puntos)

3) Listar el archivo del punto 1 usando asignación dinámica de memoria. Se deben copiar los registros en el vector dinámico que tengan una fecha anterior a una fecha que se ingresa por teclado

4) Agregar una sobrecarga para alguna de las clases del programa
*/

#include <iostream>
#include <locale>
#include <cstring>

using namespace std;

void cargarCadena(char *pal, int tam);

void cargarCadena(char *pal, int tam){
    int i;
    fflush(stdin);
    for (i=0; i<tam; i++){
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
    Fecha(int d=0, int m=0, int a=0){
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

class Guia{
private:
    int DNI;
    char nombreApellido[50];
    int vCodNacionalidad[50];
    int vNivel[15];
    Fecha fechaNacimiento;
    bool activo;
public:
    Guia(int dni=0, const char* nombreA="", bool estado=true){
        DNI=dni;
        strcpy(nombreApellido, nombreA);
        fechaNacimiento= Fecha();
        activo=estado;
    }

    void setDNI(int dni){DNI=dni;}
    void setNombreApellido(const char* nombreA){strcpy(nombreApellido, nombreA);}
    void setActivo(bool estado){activo=estado;}
    void setFechaNacimiento(const Fecha& fecha){fechaNacimiento=fecha;}

    int getDNI(){return DNI;}
    const char* getNombreApellido(){return nombreApellido;}
    bool getActivo() const{return activo;}
    const Fecha& getFechaNacimiento(){return fechaNacimiento;}

    void Cargar(int d);
    void Mostrar();

};

void Guia::Cargar(int d=-1){
    if(d==-1){
        cout<<"DNI: ";
        cin>>DNI;
    }
    else {
        setDNI(d);
    }
    cout<<"DNI: ";
    cin>>DNI;
    cout<<"Nombre y Apellido: ";
    cargarCadena(nombreApellido, 49);
    cout << "Ingrese la fecha de nacimiento:" << endl;
    fechaNacimiento.Cargar();
    activo = true;

}

void Guia::Mostrar(){
    if(activo){
        cout<<"DNI: "<<DNI<<endl;
        cout<<"Nombre y Apellido: "<<nombreApellido<<endl;
        cout<<"Fecha de Nacimiento: ";
        fechaNacimiento.Mostrar();
        cout<<endl;
    }
}

class ArchivoGuia{
private:
    char nombre[30];
public:
    //constructor
    ArchivoGuia(const char *n){
        strcpy(nombre, n); //LE COPIAMOS EN NOMBRE EL VALOR QUE RECIBIMOS DESPUES DE LA COMA
    }
    const char* getNombre(){return nombre;}
    void setNombre(const char *n){strcpy(nombre, n);}

    //Modulos ALTA
    int buscarDNI(int valor);
    int agregarRegistro();

    //Modulos BAJA
    int sobreEscribirRegistro(Guia reg, int pos);
    Guia leerRegistro(int pos);
    int bajaLogica();

    //Modulos LISTAR
    int contarRegistros();
    bool listarArchivoDinamicamente();


};

int ArchivoGuia::buscarDNI(int valor){
/*abrimos el arvhivo,
leo registro individualmente,
y preguntamos si el que leyo es igual al que ingresamos por parametro
necesito guardar su posicion
*/
    Guia reg;
    FILE *pGuia;

    pGuia=fopen(nombre, "rb");
    if(pGuia==NULL){
        return -2;
    }

    int pos = 0;
    while(fread(&reg, sizeof reg, 1, pGuia)==1){
        if(reg.getDNI()==valor){
            fclose(pGuia);
            return pos;
        }
        pos++;
    }
    fclose(pGuia);
    return -1; //devolvemos porque no hubieron concidencias
}

int ArchivoGuia::agregarRegistro(){
    Guia reg;
    FILE *pGuia;

    int DNI;
    cout<<"Ingrese DNI: ";
    cin >> DNI;

    if(buscarDNI(DNI)>-1){
        cout<<"El usuario ya se encuentra cargado"<<endl;
        return -1;
    }
    else{
        pGuia=fopen(nombre, "ab");
        if(pGuia==NULL){
            return -1;
    }

    reg.Cargar(DNI); //variable que contiene los datos que queremos llevar al disco
    int valor=fwrite(&reg, sizeof reg, 1, pGuia);
    fclose(pGuia);
    return valor;
    }
}

int ArchivoGuia::sobreEscribirRegistro(Guia reg, int pos){
    FILE *pGuia;

    pGuia=fopen(nombre, "rb+");
    if(pGuia==NULL){
        return -1;
    }

    fseek(pGuia, pos*sizeof(Guia), 0);

    int valor=fwrite(&reg, sizeof reg, 1, pGuia);
    fclose(pGuia);
    return valor;
}

Guia ArchivoGuia::leerRegistro(int posParametro){
    Guia reg;
    FILE *pGuia;

    pGuia=fopen(nombre, "rb");
    if(pGuia==NULL){
        reg.setDNI(-2);
        return reg;
    }
//Desplazo el puntero hacia donde quiero leer:
    fseek(pGuia, posParametro*sizeof reg, 0);
///fseek(puntero FILE sobre sobre el que se abrio el archivo, cantidad de bytes a desplazarse, desde donde desplazarse)
///desde donde= 0 SEEK_SET el desplazamiento va desde el principio del archivo
///desde donde= 1 SEEK_CUR el desplazamiento va desde donde se encuentra el indicador del puntero FILE
///desde donde= 2 SEEK_END el desplazamiento va desde el FIN del archivo

//ahora leo:
    int leyo= fread(&reg, sizeof reg, 1, pGuia);
    fclose(pGuia);
    if(leyo==0){
        reg.setDNI(-3);
    }
    return reg;
}

int ArchivoGuia::bajaLogica(){
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
    Guia reg;
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
        reg.setActivo(false);
        cout<<"Datos del Cliente fueron eliminados exitosamente"<<endl;
    }
//sobreescribir el reg
    sobreEscribirRegistro(reg, pos);
    return 1;
}

int ArchivoGuia::contarRegistros(){
    Guia reg;
    FILE *pGuia;
    pGuia=fopen(nombre, "rb");

    if(pGuia==NULL){
        return false;
    }

    int contador=0;
    while(fread(&reg, sizeof reg, 1, pGuia)==1){
        contador++;
    }

    fclose(pGuia);
    return contador;
}

bool ArchivoGuia::listarArchivoDinamicamente(){
 Guia *vGuia;
 int tam;
 tam = contarRegistros();
 vGuia=new Guia[tam];

 if(vGuia==NULL){
    cout<<"Error de asignacion de memoria";
    return -1;
 }

 FILE *pGuia;
 pGuia = fopen(nombre, "rb");
 if(pGuia==NULL){
    delete[] vGuia;
    return false;
 }

 fread(vGuia, sizeof(Guia), tam, pGuia);
 for (int i=0;i<tam; i++){
    vGuia[i].Mostrar();
    cout<<endl;
 }
 fclose(pGuia);
 delete[] vGuia;
 return true;
}


int main (){
 setlocale(LC_ALL, "");

 ArchivoGuia aux("guias.dat");

  int opc;
    while(true){
        system("cls");
        cout<<"Menu Principal"<<endl;
        cout<<"---------------------"<<endl;
        cout<<"1 - Cargar registro"<<endl;
        cout<<"2 - Baja Logica"<<endl;
        cout<<"3 - Listar Archivo"<<endl;
        cout<<"0 - Salir del Programa"<<endl;
        cout<<"---------------------"<<endl;
        cin>>opc;
        system("cls");

        switch(opc){
        case 1:
            if(aux.agregarRegistro()!=1){
                cout<<"No se pudo agregar el registro"<<endl;
            }
            else{
                cout<<"Registro agregado"<<endl;
            }
            break;
        case 2:
            if(aux.bajaLogica()>0){
                cout<<"Baja logica realizada correctamente."<<endl;
            }
            else{
                cout<< "No se pudo realizar la baja lógica." << endl;
            }
            break;
        case 3:
            if(!aux.listarArchivoDinamicamente()){
                cout<<"Error al listar el archivo o archivo vacío."<< endl;
            }
            break;
        case 0:
            cout << "Saliendo del programa..." << endl;
            return 0;
            break;
        default:
            cout<<"Opcion invalida. Intente nuevamente."<<endl;
            break;
        }
        cout<<endl;
        system("pause");
    }


return 0;
}


