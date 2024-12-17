/*
Nombre: Jesica Valdez

ENUNCIADO:

*/

#include <iostream>
#include <fstream>
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

class Programador {
private:
    int dni;
    char nombreApellido[50];
    int numeroOficina;
    int categoria; // Entre 1 y 5
    int especialidad; // Entre 1 y 10

public:
    Programador(int d = 0, const char* n = "", int no = 0, int c = 0, int e = 0) {
        dni = d;
        strcpy(nombreApellido, n);
        numeroOficina = no;
        categoria = c;
        especialidad = e;
    }

    void setDni(int d) { dni = d; }
    void setNombreApellido(const char* nombre){strcpy(nombreApellido, nombre); }
    void setNumeroOficina(int oficina) {numeroOficina = oficina;}
    void setCategoria(int cat) {categoria = cat;}
    void setEspecialidad(int esp) {especialidad = esp;}

    int getDni(){return dni;}
    const char* getNombreApellido(){return nombreApellido;}
    int getNumeroOficina(){return numeroOficina;}
    int getCategoria(){return categoria;}
    int getEspecialidad(){return especialidad;}

    void cargar() {
        cout<<"Ingrese DNI: ";
        cin>>dni;
        cout<<"Ingrese nombre y apellido: ";
        cargarCadena(nombreApellido, 49);
        cout<<"Ingrese número de oficina (1 a 30): ";
        cin>>numeroOficina;
        cout<<"Ingrese categoría (1 a 5): ";
        cin>>categoria;
        cout<<"Ingrese especialidad (1 a 10): ";
        cin>>especialidad;
    }

    void mostrar(){
        cout<<"DNI: "<<dni<<endl;
        cout<<"Nombre y Apellido: "<<nombreApellido<<endl;
        cout<<"Número de Oficina: "<<numeroOficina<<endl;
        cout<<"Categoría: "<<categoria<<endl;
        cout<<"Especialidad: "<<especialidad<<endl;
    }

};

class Asignacion {
private:
    int dni;
    int dia, mes, anio;
    int tipoTarea; // Entre 1 y 5
    int numeroProyecto;

public:
    Asignacion(int d = 0, int dd = 0, int mm = 0, int yyyy = 0, int tt = 0, int np = 0) {
        dni = d;
        dia = dd;
        mes = mm;
        anio = yyyy;
        tipoTarea = tt;
        numeroProyecto = np;
    }
    void setDni(int d) { dni = d; }
    void setFecha(int d, int m, int a) { dia = d; mes = m; anio = a; }
    void setTipoTarea(int tarea) { tipoTarea = tarea; }
    void setNumeroProyecto(int proyecto) { numeroProyecto = proyecto; }

    int getDni() const { return dni; }
    int getDia() const { return dia; }
    int getMes() const { return mes; }
    int getAnio() const { return anio; }
    int getTipoTarea() const { return tipoTarea; }
    int getNumeroProyecto() const { return numeroProyecto; }

};

// AsignacionFiltrada para nuevo archivo
class AsignacionFiltrada {
private:
    int dni;
    char nombreApellido[50];
    int cantidadAsignaciones;

public:
    AsignacionFiltrada(int d = 0, const char* n = "", int c = 0) {
        dni = d;
        strcpy(nombreApellido, n);
        cantidadAsignaciones = c;
    }

    void guardar(ofstream& archivo) {
        archivo.write((char*)this, sizeof(AsignacionFiltrada));
    }
};

// Función para generar archivo filtrado
void generarArchivoFiltrado(const char* archivoProgramadores, const char* archivoAsignaciones, const char* archivoFiltrado) {
    ifstream progFile(archivoProgramadores, ios::binary);
    ifstream asigFile(archivoAsignaciones, ios::binary);
    ofstream outFile(archivoFiltrado, ios::binary);

    if (!progFile || !asigFile || !outFile) {
        cerr << "Error al abrir los archivos." << endl;
        return;
    }

    Programador prog;
    Asignacion asig;
    while (progFile.read((char*)&prog, sizeof(Programador))) {
        if (prog.getCategoria() == 5) {
            int contadorAsignaciones = 0;
            asigFile.clear();
            asigFile.seekg(0);

            while (asigFile.read((char*)&asig, sizeof(Asignacion))) {
                if (asig.getDNI() == prog.getDNI() && asig.getAnio() >= 2018) {
                    contadorAsignaciones++;
                }
            }

            if (contadorAsignaciones > 0) {
                AsignacionFiltrada nuevoRegistro(prog.getDNI(), prog.getNombreApellido(), contadorAsignaciones);
                nuevoRegistro.guardar(outFile);
            }
        }
    }

    progFile.close();
    asigFile.close();
    outFile.close();
}

// Función para informar la especialidad con más programadores
void informarEspecialidadConMasProgramadores(const char* archivoProgramadores) {
    ifstream progFile(archivoProgramadores, ios::binary);

    if (!progFile) {
        cerr << "Error al abrir el archivo de programadores." << endl;
        return;
    }

    int contadorEspecialidades[10] = {0};
    Programador prog;

    while (progFile.read((char*)&prog, sizeof(Programador))) {
        contadorEspecialidades[prog.getEspecialidad() - 1]++;
    }

    int maxEspecialidad = 0;
    for (int i = 1; i < 10; i++) {
        if (contadorEspecialidades[i] > contadorEspecialidades[maxEspecialidad]) {
            maxEspecialidad = i;
        }
    }

    cout << "La especialidad con más programadores es: " << (maxEspecialidad + 1) << " con "
         << contadorEspecialidades[maxEspecialidad] << " programadores." << endl;

    progFile.close();
}

// Sobrecarga del operador para comparar con un objeto Fecha
class Fecha {
private:
    int dia, mes, anio;

public:
    Fecha(int d = 1, int m = 1, int y = 2000) : dia(d), mes(m), anio(y) {}

    int getAnio() const { return anio; }
    bool

