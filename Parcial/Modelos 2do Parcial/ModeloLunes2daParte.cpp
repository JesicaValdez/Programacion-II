# include<iostream>
# include<cstdlib>
# include<cstring>

using namespace std;
///se incluye el punto h necesario
#include "parcial1l.h"

/// a1. Generar un archivo con los equipos que tengan al menos 10 jugadores inscriptos.
///Cada registro debe tener el ID de equipo, el nombre y la categoría.

class Equipos10{
private:
    int IDequipo, IDcategoria;
    char nombre[30];
    bool estado;
public:
    void setEquipo(int e){IDequipo=e;}
    void setNombre(const char *nom){strcpy(nombre, nom);}
    void setCategoria(int cat){IDcategoria=cat;}
    void setEstado(bool e){estado=e;}
    void Mostrar(){
        cout<<"EQUIPO "<<IDequipo<<endl;
        cout<<"NOMBRE "<<nombre<<endl;
        cout<<"CATEGORIA "<<IDcategoria<<endl;
    }

};

class ArchivoEquipos10{
private:
    char nombre[30];
public:
    ArchivoEquipos10(const char *n){
        strcpy(nombre, n);
    }
    Equipos10 leerRegistro(int pos){
        Equipos10 reg;
        reg.setEstado(false);
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
        return tam/sizeof(Equipos10);
    }
    bool grabarRegistro(Equipos10 reg){
        FILE *p;
        p=fopen(nombre, "ab");
        if(p==NULL) return false;
        int escribio=fwrite(&reg, sizeof reg,1, p);
        fclose(p);
        return escribio;
    }
};

int contarJugadores(int equipo){
    ArchivoJugadores archiJ("jugadores.dat");
    Jugador reg;
    int cantReg, cantJug=0;
    cantReg=archiJ.contarRegistros();
    for(int i=0;i<cantReg;i++){
        reg=archiJ.leerRegistro(i);
        if(reg.getIDequipo()==equipo) cantJug++;
    }
    return cantJug;
}

int buscarDeporte(int equipo){
    ArchivoJugadores archiJ("jugadores.dat");
    Jugador reg;
    int cantReg;
    cantReg=archiJ.contarRegistros();
    for(int i=0;i<cantReg;i++){
        reg=archiJ.leerRegistro(i);
        if(reg.getIDequipo()==equipo) return reg.getIDdeporte();
    }
    return -1;
}

int buscarCategoria(int deporte){
    ArchivoDeportes archiD("deportes.dat");
    Deporte reg;
    int cantReg;
    cantReg=archiD.contarRegistros();
    for(int i=0;i<cantReg;i++){
        reg=archiD.leerRegistro(i);
        if(reg.getIDdeporte()==deporte) return reg.getIDcategoria();
    }
    return -1;
}

void puntoA1(){
    Equipos10 aux;
    ArchivoEquipos10 archiE10("equipos10.dat");
    Equipo reg;
    ArchivoEquipos archiE("equipos.dat");
    int cantReg, cantJug, categoria, deporte;
    cantReg=archiE.contarRegistros();
    for(int i=0;i<cantReg;i++){
        reg=archiE.leerRegistro(i);
        cantJug=contarJugadores(reg.getIDequipo());
        if(cantJug>=10){
                deporte=buscarDeporte(reg.getIDequipo());
                categoria=buscarCategoria(deporte);
                aux.setEquipo(reg.getIDequipo());
                aux.setNombre(reg.getNombre());
                aux.setCategoria(categoria);
                archiE10.grabarRegistro(aux);
        }
    }

}

void puntoB1(){
    Equipos10 *v;
    ArchivoEquipos10 archiE10("equipos10.dat");
    int cantReg;
    cantReg=archiE10.contarRegistros();
    if(cantReg==0){
        cout<<"NO HAY REGISTROS EN EL ARCHIVO"<<endl;
        return;
    }
    v=new Equipos10[cantReg];
    if(v==NULL) return;
    for(int i=0;i<cantReg;i++){
            v[i]=archiE10.leerRegistro(i);
    }
    for(int i=0;i<cantReg;i++){
        v[i].Mostrar();
    }
    delete v;
}

int main(){
    puntoA1();
    puntoB1();
	cout<<endl;
	system("pause");
	return 0;
}


///punto c1
///Sobrecargar el operador == para comparar un objeto Jugador con un objeto Deporte. Debe devolver verdadero cuando coinciden los Id de deporte
///en la clase Jugador iría el código

bool operator==(const Deporte &obj){
    if(idDeporte==obj.getIDdeporte()) return true;
    return false;
}

///Punto 2A - Hacer un archivo con los deportes que tengan jugadores de todos los claustros. Los registros del archivo nuevo deben tener el mismo formato que el archivo de deportes.
void Punto2a(){
Deporte reg, regN;
ArchivoDeportes archD("deportes.dat");
ArchivoDeportes archivoN("nuevo.dat");

Jugador regJ;
ArchivoJugadores archJ("jugadores.dat");
int cant  = archJ.contarRegistros();

bool vClaustro[4]={};

    for (int i=0; i<cant; i++){
        reg = archD.leerRegistro(i);
        for (int i=0; i<cant; i++){
            reg = archJ.leerRegistro(i);

            if(regD.getIDdeporte()==regJ.getIDdeporte){
                vClaustro[regJ.getClaustro()-1]=true;
            }

        }
        if(vClaustro[0] && vClaustro[1] && vClaustro[2] && vClaustro[3]){
            regN.getIDdeporte();
            regN.getNombre();
            regN.getIDcategoria();
            regN.getAnioOrigen();
            regN.getEstado();
            archivoN.grabarRegistro(regN);
        }
    }
}

//Punto 2B - Crear un vector dinámico con los equipos de nivel inicial. Listar el vector.
void Punto2b(){
Equipo *din, reg;
ArchivoEquipos archE("equipos.dat");
int cant = archE.contarRegistros();

int cont=0, pos=0;

    for (int i=0; i<cant; i++){
        reg = archE.leerRegistro(i);
        if(reg.getNivel()==1){
            cont++;
        }
    }

    //chequeo y luego pido memoria para hacer el vector
    if(cont>0){
        //generamos el vector dinamico
        din = new Material[cont];
        if(din==NULL) {
            return false;
        }
        //ya validado hacemos nuevamente la lectura
        for (int i=0; i<cant; i++){
        //leemos un registro de compras
        reg = archE.leerRegistro(i);
        //en la posicion i me copio el registro
                if(reg.getNivel()==1) {
                din[pos]=reg;
                pos++;
            }
        }

        for(int i=0; i<pos; i++){
            din[i].Mostrar();
        }
    }

    delete din;
    return true;
}

//Punto 2C - Sobrecargar el operador == para la clase Jugador,
//que reciba un valor entero y lo compare con el
//Id de claustro

bool operator==(int valor){
    if(claustro==valor) return true;
    return false;
}

//Punto 3A - Generar un archivo con los jugadores que hayan pagado más de $10000 de matrícula y que se hayan inscripto este año. Cada registro del archivo debe tener el siguiente formato:
//DNI, nombre, apellido, claustro y nombre del deporte.
class JugadorMatriculado{
private:
    int DNI, claustro, idDeporte;
    char nombre[25], apellido[30];
public:
   void setDNI(int _DNI){DNI = _DNI;}
   void setClaustro(int c){claustro = c;}
   void setIdDeporte(int d){idDeporte = d;}
   void setNombre(const char *n){strcpy(nombre, n);}
   void setApellido(const char *a){strcpy(apellido,a);}

   void Mostrar(){
        cout<<DNI<<endl;
        cout<<nombre<<endl;
        cout<<apellido<<endl;
        cout<<claustro<<endl;
        cout<<idDeporte<<endl;
   }
};

class ArchivoJugadoresMatriculados{
private:
    char nombre[30];
public:
    ArchivoJugadoresMatriculados(const char *n){
        strcpy(nombre, n);
    }
    JugadorMatriculado leerRegistro(int pos){
        JugadorMatriculado reg;
        reg.setEstado(false);
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
        return tam/sizeof(JugadorMatriculado);
    }
    bool grabarRegistro(JugadorMatriculado reg){
        FILE *p;
        p=fopen(nombre, "ab");
        if(p==NULL) return false;
        int escribio=fwrite(&reg, sizeof reg,1, p);
        fclose(p);
        return escribio;
    }
};

const char *buscarNombreDeporte(int deporte){
Deporte reg;
ArchivoDeportes archiD("deportes.dat");
int cant = archiD.contarRegistros();

    for (int i=0; i<cant; i++){
        reg = archiD.leerRegistro(i);
        if(reg.getIdDeporte()==deporte){
            return reg.getNombre();
        }
    }
    return "";
}

void matriculados(){
JugadorMatriculado reg;
ArchivoJugadoresMatriculados archivoJM("matriculados.dat");

Jugador regJ;
ArchivoJugadores archivoJ("jugadores.dat");

int cant = archivoJ.contarRegistros();

    for (int i=0; i<cant; i++){
        regJ = archivoJ.leerRegistro(i);
        if(regJ.getMatricula()==10000 && regJ.getFechaInscirpcion().getAnio()==2024){
            const char *nombreDeporte=buscarNombreDeporte(regJ.getIdDeporte());
            reg.setNombre(nombreDeporte);
            reg.setDNI(regJ.getDNI());
            reg.setApellido(regJ.getApellido());
            reg.setClaustro(regJ.getClaustro());
            reg.setIdDeporte(regJ.getIdDeporte());
        }
    }

}



//Punto 3B - Crear un vector con los jugadores pertenecientes a un equipo cuyo número de equipo se ingresa por teclado. Listar el vector
void EquipoT(){
Jugador *dinamico, reg;
ArchivoJugadores arcJ("jugadores.dat");

    //cuento registro
    int cantReg=arcJ.contarRegistros();

    int cont=0, numEquipo, pos=0;
    //primero pido el ingreso del tipo de los materiales que se desea contar
    cout << "Ingrese el numero de equipo: ";
    cin >> numEquipo;

    for (int i=0; i<cantReg; i++){
        //leemos un registro de compras
        reg=arcJ.leerRegistro(i);
        //en la posicion i me copio el registro
        if(reg.getIdEquipo()==numEquipo){
            cont++;
        }
    }

    //chequeo y luego pido memoria para hacer el vector
    if(cont>0){
        //generamos el vector dinamico
        dinamico= new Jugador[cont];
        if(dinamico==NULL) {
            return;
        }
        //ya validado hacemos nuevamente la lectura
        for (int i=0; i<cantReg; i++){
        //leemos un registro de compras
        reg=arcJ.leerRegistro(i);
        //en la posicion i me copio el registro
            if(reg.getIdEquipo()==numEquipo){
                dinamico[pos]=reg;
                pos++;
            }
        }

        for(int i=0; i<pos; i++){
            dinamico[i].Mostrar();
        }
    }

    delete dinamico;
}


//Punto 3C -Agregar una sobrecarga para el operador > de la clase Jugador
// de manera tal que sea verdadero cuando el año de inscripción sea mayor
//a un valor de año que se recibe cmo parámetro.

bool Fecha::operator>(int anioIngresado){
 if(anio>anioIngresado)return true;
 return false;
 }

