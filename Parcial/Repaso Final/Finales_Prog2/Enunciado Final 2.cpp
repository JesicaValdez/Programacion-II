/*
Nombre: Jesica Valdez

ENUNCIADO:
1) Desarrollar un programa con un menú para dar el alta, baja lógica y listado del siguiente archivo:
Partidos.dat

Código de partido (entero)
Código de sede (entero)
Código de equipo 1 (local)
Código de equipo 2 (visitante)
Fecha de realización (Objeto Fecha)
Nombre del árbitro
Estado

2) Agregar un constructor para alguna de las clases del ejercicio 1.
El método debe poner en 0 alguna propiedad de tipo int si no se le envía valor; si se envía un valor debe usar el valor enviado para la propiedad. (2 puntos)

3) Listar el archivo del punto 1 usando asignación dinámica de memoria.
Se deben copiar los registros en el vector dinámico que tengan una fecha anterior a una fecha que se ingresa por teclado (2 puntos)
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

class Partido{
private:
    int codPartido;
    int codSede;
    int codLocal;
    int codVisitante;
    Fecha fechaRealizacion;
    char nombreArbitro[30];
    bool estado;
public:
    void setCodPartido(int cP){codPartido=cP;}
    void setCodSede(int cS){codSede=cS;}
    void setCodLocal(int eL){codLocal=eL;}
    void setCodVisitante(int v){codVisitante=v;}
    void setFechaRealizacion(const Fecha& fecha){fechaRealizacion=fecha;}
    void setNombreArbitro(const char* nombreA){strcpy(nombreArbitro, nombreA);}
    void setEstado(bool est){estado=est;}

    int getCodPartido(){return codPartido;}
    int getCodSede(){return codSede;}
    int getCodLocal(){return codLocal;}
    int getCodVisitante(){return codVisitante;}
    const Fecha& getFechaRealizacion(){return fechaRealizacion;}
    const char* getNombreArbitro(){return nombreArbitro;}
    bool getEstado() const{return estado;}

    void Cargar(int c);
    void Mostrar();

};

void Partido::Cargar(int c=-1){
    if(c==-1){
        cout<<"Ingrese Codigo Partido: ";
        cin>>codPartido;
    }
    else {
        setCodPartido(c);
    }
    cout<<"Ingrese Codigo Sede: ";
    cin>>codSede;
    cout<<"Ingrese Codigo Equipo Local: ";
    cin>>codLocal;
    cout<<"Ingrese Codigo Equipo Visitante: ";
    cin>>codVisitante;
    cout<<"Ingrese Fecha de realizacion: ";
    fechaRealizacion.Cargar();
    cout<<"Ingrese nombre del arbitro: ";
    cargarCadena(nombreArbitro, 29);
    estado=true;

}

void Partido::Mostrar(){
    if(estado){
        cout<<"Codigo Partido: "<<codPartido<<endl;
        cout<<"Codigo Sede: "<<codSede<<endl;
        cout<<"Codigo Equipo Local: "<<codLocal<<endl;
        cout<<"Codigo Equipo Visitante: "<<codVisitante<<endl;
        cout<<"Fecha de realizacion: ";
        fechaRealizacion.Mostrar();
        cout<<"Ingrese nombre del arbitro: "<<nombreArbitro<<endl;
        cout<<endl;
    }
}

class ArchivoPartido{
private:
    char nombre[30];
public:
    //constructor
    ArchivoPartido(const char *n){
        strcpy(nombre, n); //LE COPIAMOS EN NOMBRE EL VALOR QUE RECIBIMOS DESPUES DE LA COMA
    }
    const char* getNombre(){return nombre;}
    void setNombre(const char *n){strcpy(nombre, n);}

    //Modulos ALTA
    int buscarCodPartido(int valor);
    int agregarRegistro();

    //Modulos BAJA
    int sobreEscribirRegistro(Partido reg, int pos);
    Partido leerRegistro(int pos);
    int bajaLogica();

    //Modulos LISTAR
    int contarRegistros();
    bool listarArchivoDinamicamente();


};

int ArchivoPartido::buscarCodPartido(int valor){
    Partido reg;
    FILE *pPartido;

    pPartido=fopen(nombre, "rb");
    if(pPartido==NULL){
        return -2;
    }

    int pos = 0;
    while(fread(&reg, sizeof reg, 1, pPartido)==1){
        if(reg.getCodPartido()==valor){
            fclose(pPartido);
            return pos;
        }
        pos++;
    }
    fclose(pPartido);
    return -1; //devolvemos porque no hubieron concidencias
}
int ArchivoPartido::agregarRegistro(){
    Partido reg;
    FILE *pPartido;

    int codPart;
    cout<<"Ingrese Codigo Partido: ";
    cin >> codPart;

    if(buscarCodPartido(codPart)>-1){
        cout<<"El codigo de partido ya existe."<<endl;
        return -1;
    }
    pPartido=fopen(nombre, "ab");
    if(pPartido==NULL){
        cout << "Error al abrir el archivo." << endl;
        return -1;
    }

    reg.Cargar(codPart); //variable que contiene los datos que queremos llevar al disco
    int valor=fwrite(&reg, sizeof reg, 1, pPartido);
    fclose(pPartido);
    return valor;

}
int ArchivoPartido::sobreEscribirRegistro(Partido reg, int pos){
    FILE *pPartido;

    pPartido=fopen(nombre, "rb+");
    if(pPartido==NULL){
        return -1;
    }

    fseek(pPartido, pos*sizeof(Partido), 0);
    int valor=fwrite(&reg, sizeof reg, 1, pPartido);
    fclose(pPartido);
    return valor;
}
Partido ArchivoPartido::leerRegistro(int pos){
    Partido reg;
    FILE *pPartido;

    pPartido=fopen(nombre, "rb");
    if(pPartido==NULL){
        reg.setCodPartido(-2);
        return reg;
    }

    fseek(pPartido, pos*sizeof reg, 0); //Desplazo el puntero hacia donde quiero leer:
    int leyo= fread(&reg, sizeof reg, 1, pPartido); //ahora leo
    fclose(pPartido);//cierro

    if(leyo==0){
        reg.setCodPartido(-3);
    }
    return reg;
}
int ArchivoPartido::bajaLogica(){
    //buscar
    int codPart, pos;
    cout<<"Ingrese el DNI del cliente a Borrar :";
    cin>>codPart;

    pos=buscarCodPartido(codPart);
    if(pos==-1){
        cout<<"No hay Partidos con ese codigo"<<endl;
        return -1;
    }
//leer
    Partido reg;
    reg=leerRegistro(pos);
    cout << "Registro encontrado:\n";
    reg.Mostrar();

    char opc;
    cout<<"Esta sefuro que desea borrar? (S/N): ";
    cin>>opc;
    if(opc=='s' || opc=='S'){
        //cambiar el estado
        reg.setEstado(false);
        //sobreescribir el reg
        sobreEscribirRegistro(reg, pos);
        cout<<"Datos del Partido fueron eliminados exitosamente"<<endl;
    }
    return 1;
}
int ArchivoPartido::contarRegistros(){
    Partido reg;
    FILE *pPartido;
    pPartido=fopen(nombre, "rb");

    if(pPartido==NULL){
        return false;
    }

    int contador=0;
    while(fread(&reg, sizeof reg, 1, pPartido)==1){
        contador++;
    }

    fclose(pPartido);
    return contador;
}
bool ArchivoPartido::listarArchivoDinamicamente() {
    int tam=contarRegistros();
    if (tam==0){
        cout<<"No hay registros para listar."<<endl;
        return false;
    }

    Partido *vPartido = new Partido[tam];
    if (vPartido==NULL){
        cout << "Error de asignación de memoria." << endl;
        return false;
    }

    FILE *pPartido=fopen(nombre, "rb");
    if(pPartido==NULL){
        delete[] vPartido;
        cout << "Error al abrir el archivo." << endl;
        return false;
    }

    fread(vPartido, sizeof(Partido), tam, pPartido);

    // Solicito fecha para el filtro
    Fecha fechaFiltro;
    cout << "Ingrese una fecha para filtrar los partidos: ";
    fechaFiltro.Cargar();

    cout << "Partidos con fecha anterior a: ";
    fechaFiltro.Mostrar();
    cout << endl;

    bool hayPartidos=false;
    for (int i=0; i<tam; i++) {
        if(vPartido[i].getEstado()){ // Verifico que el partido este activo
            Fecha fechaPartido = vPartido[i].getFechaRealizacion();
            if(fechaPartido.getAnio() < fechaFiltro.getAnio() ||
                (fechaPartido.getAnio() == fechaFiltro.getAnio() && fechaPartido.getMes() < fechaFiltro.getMes()) ||
                (fechaPartido.getAnio() == fechaFiltro.getAnio() && fechaPartido.getMes() == fechaFiltro.getMes() && fechaPartido.getDia() < fechaFiltro.getDia())) {
                vPartido[i].Mostrar();
                cout << endl;
                hayPartidos = true;
            }
        }
    }

    if(!hayPartidos){
        cout<<"No hay partidos activos con fecha anterior a la ingresada."<<endl;
    }

    fclose(pPartido);
    delete[] vPartido;
    return true;
}


int main (){
 setlocale(LC_ALL, "");
 ArchivoPartido aux("partidos.dat");

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


