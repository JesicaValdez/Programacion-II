///Nombre: Jesica Valdez

#include <iostream>
#include <locale>
#include <cstring>
using namespace std;

#include "parcial1l.h"

///Punto 1 - Generar un archivo con los jugadores que participan de equipos de nivel intermedio. Cada registro del archivo nuevo debe tener el siguiente formato: DNI, nombre, apellido y fecha de inscripción
class jugadorNivelIntermedio{
    private:
        int DNI;
        char nombre[25];
        char apellido[30];
        Fecha fechaInsripcion;
    public:
        void setDni(int dni){
            DNI = dni;
        }
        void setNombre(const char *n){
            strcpy(nombre,n);
        }
        void setApellido(const char *a){
            strcpy(apellido,a);
        }
        Fecha setFechaIncripcion(Fecha f){
            fechaInsripcion = f;
        }
        void Mostrar(){
            cout << "DNI #" << DNI << endl;
            cout << "Nombre " << nombre << endl;
            cout << "Apellido " << apellido << endl;
            cout << "Fecha de Inscripcion :";
            fechaInsripcion.Mostrar();
            cout << endl;
        }
};

class ArchivoJugadorNivelIntermedio{
    private:
       char nombre[30];
    public:
   ArchivoJugadorNivelIntermedio(const char *n){
        strcpy(nombre, n);
    }
    bool escribir(jugadorNivelIntermedio obj){
        FILE *p;
        p=fopen(nombre, "ab");
        if(p==NULL) return false;
        bool escribir = fwrite(&obj, sizeof obj, 1, p);
        fclose(p);
        return true;
    }
    bool listar(){
        jugadorNivelIntermedio reg;
        FILE *p;
        p=fopen(nombre, "rb");
        if(p==NULL) return false;
        while(fread(&reg, sizeof reg, 1, p)){
            reg.Mostrar();
            cout << endl;
        }
        fclose(p);
        return true;
    }
};

void punto1(){
ArchivoJugadorNivelIntermedio archivoA("jugadorIntermedio.dat");
jugadorNivelIntermedio registroR;

ArchivoJugadores archivoJ("jugadores.dat");
Jugador registroJ;

ArchivoEquipos archivoE("equipos.dat");
Equipo registroE;
int cant = archivoE.contarRegistros();

for (int i=0; i<cant; i++){
    registroE = archivoE.leerRegistro(i);
    if(registroE.getNivel() == 2){
        registroR.setDni(registroJ.getDNI());
        registroR.setNombre(registroJ.getNombre());
        registroR.setApellido(registroJ.getApellido());
        registroR.setFechaIncripcion(registroJ.getFechaInscirpcion());
        archivoA.escribir(registroR);
    }
}
    archivoA.listar();

}


int main ()
{
 setlocale(LC_ALL, "");
 punto1();

return 0;
}


