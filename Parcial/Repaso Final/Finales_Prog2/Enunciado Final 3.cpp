/*
Nombre: Jesica Valdez

ENUNCIADO:
1) Desarrollar un programa con un menú para dar el alta, baja lógica y listado del siguiente archivo:

Equipos.dat

Código de equipo (entero)
Nombre de equipo (char[30])
Provincia a la que pertenece (1 a 24)
Director técnico (char[30])
División (‘A’,’B’,’C’) (categoría)
Estado

2) Agregar un constructor para la clase que da formato a los registros del archivo con valores por omisión que deben usarse en caso que el constructor sea llamado sin valores.
Si recibe valores debe usarlos ignorando los que tiene por omisión (2 puntos)

3) Agregar una sobrecarga para alguna de las clases del programa (2 puntos)

*/

#include <iostream>
#include <locale>
#include <cstring>

using namespace std;

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
class Equipo{
private:
    int codEquipo;
    char nombreEquipo[30];
    int provincia;
    char directorTec[30];
    char division;
    bool estado;
public:
    // Constructor con valores por omisión
    Equipo(int cE = -1, const char* nE = "", int prov = 0, const char* dT = "Sin DT", char div = 'A', bool est = true) {
        codEquipo = cE;
        strcpy(nombreEquipo, nE);
        strcpy(directorTec, dT);
        division = div;
        estado = est;
    }
    void setCodEquipo(int cE){codEquipo=cE;}
    void setNombreEquipo(const char *nE){strcpy(nombreEquipo, nE);}
    void setDirectorTec(const char *dT){strcpy(directorTec, dT);}
    void setDivision(const char d){division=d;}
    void setEstado(bool est){estado=est;}

    int getCodEquipo(){return codEquipo;}
    const char* getNombreEquipo(){return nombreEquipo;}
    const char* getDirectorTec(){return directorTec;}
    const char getDivision(){return division;}
    bool getEstado(){return estado;}

    void Cargar(int c);
    void Mostrar();

    // Sobrecarga del operador ==
    bool operator==(const Equipo &otro) const {
        return codEquipo == otro.codEquipo;
    }
};

void Equipo::Cargar(int c=-1){
    if(c==-1){
        cout<<"Ingrese Codigo de Equipo: ";
        cin>>codEquipo;
    }
    else{
        setCodEquipo(c);
    }
    cout<<"Ingrese nombre de Equipo: ";
    cargarCadena(nombreEquipo,29);
    cout<<"Ingrese provincia (1 a 24): ";
    cin>>provincia;
    cout<<"Ingrese nombre del Director Tecnico: ";
    cargarCadena(directorTec, 30);
    cout << "Ingrese división ('A', 'B', 'C'): ";
    cin>>division;
    estado=true;
}

void Equipo::Mostrar(){
    if(estado){
        cout<<"Codigo de Equipo: "<<codEquipo<<endl;
        cout<<"Nombre de Equipo: "<<nombreEquipo<<endl;
        cout<<"Provincia: "<<provincia<<endl;
        cout<<"Director Tecnico: "<<directorTec<<endl;
        cout<<"División: "<<division<< endl;
    }
}

class ArchivoEquipo{
private:
    char nombre[30];
public:
    ArchivoEquipo(const char *n){
        strcpy(nombre, n);
    }

    int buscarCodEquipo(int valor);
    int agregarRegistro();
    int sobreEscribirRegistro(Equipo reg, int pos);
    Equipo leerRegistro(int pos);
    int bajaLogica();
    bool listarArchivo();
};

int ArchivoEquipo::buscarCodEquipo(int valor){
Equipo reg;
FILE *pEquipo;

pEquipo=fopen(nombre, "rb");

if(pEquipo==NULL){
    return -1;
}

int pos=0;
while(fread(&reg, sizeof reg, 1, pEquipo)==1){
    if(reg.getCodEquipo()==valor){
        fclose(pEquipo);
        return pos;
    }
    pos++;
}
fclose(pEquipo);
return -1;
}
int ArchivoEquipo::agregarRegistro(){
Equipo reg;
FILE *pEquipo;
int codEquipo;

    cout<<"Ingrese Codigo Partido: ";
    cin >> codEquipo;

    if(buscarCodEquipo(codEquipo)>-1){
        cout<<"El codigo de equipo ya existe."<<endl;
        return -1;
    }

pEquipo = fopen(nombre, "ab");
if(pEquipo==NULL){
    return -2;
}

reg.Cargar(codEquipo);
fwrite(&reg, sizeof reg, 1, pEquipo);
fclose(pEquipo);
cout << "Registro agregado exitosamente." << endl;
}
int ArchivoEquipo::sobreEscribirRegistro(Equipo reg, int pos){
FILE *pEquipo;

pEquipo=fopen(nombre, "rb+");
if(pEquipo==NULL){
    return -1;
}

fseek(pEquipo, pos*sizeof(Equipo), 0);
    int valor=fwrite(&reg, sizeof reg, 1, pEquipo);
    fclose(pEquipo);
    return valor;

}
Equipo ArchivoEquipo::leerRegistro(int pos){
Equipo reg;
FILE *pEquipo;

pEquipo=fopen(nombre, "rb");
if(pEquipo==NULL){
    return -1;
}

fseek(pEquipo, pos*sizeof reg, 0); //Desplazo el puntero hacia donde quiero leer:
    int leyo= fread(&reg, sizeof reg, 1, pEquipo); //ahora leo
    fclose(pEquipo);//cierro

    if(leyo==0){
        reg.setCodEquipo(-3);
    }
    return reg;
}
int ArchivoEquipo::bajaLogica(){
//buscar
    int codE, pos;
    cout<<"Ingrese el codigo del equipo para Borrar: ";
    cin>>codE;

    pos=buscarCodEquipo(codE);
    if(pos==-1){
        cout<<"No existe un Equipo con ese codigo"<<endl;
        return -1;
    }
//leer
    Equipo reg;
    reg=leerRegistro(pos);
    cout << "Registro encontrado:\n";
    reg.Mostrar();

    char opc;
    cout<<"Esta seguro que desea borrar? (S/N): ";
    cin>>opc;
    if(opc=='s' || opc=='S'){
        //cambiar el estado
        reg.setEstado(false);
        //sobreescribir el reg
        sobreEscribirRegistro(reg, pos);
        cout<<"Equipo eliminado exitosamente"<<endl;
    }
    return 1;
}

bool ArchivoEquipo::listarArchivo(){
Equipo reg;
FILE *pEquipo;

pEquipo=fopen(nombre, "rb");

if(pEquipo==NULL){
    cout << "No se pudo abrir el archivo o está vacío." << endl;
    return false;
}

while(fread(&reg, sizeof reg, 1, pEquipo)==1) {
    if (reg.getEstado()){
        reg.Mostrar();
        cout << endl;
    }
}
fclose(pEquipo);
return true;
}

int main (){
 setlocale(LC_ALL, "");

 ArchivoEquipo aux("equipos.dat");
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
            if(aux.bajaLogica()>0){
                cout<<"Baja logica realizada correctamente."<<endl;
            }
            else{
                cout<< "No se pudo realizar la baja lógica." << endl;
            }
            break;
        case 3:
        if(!aux.listarArchivo()){
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


