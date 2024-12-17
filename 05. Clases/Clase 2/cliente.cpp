/*Nombre: Jesica Valdez
*/

#include <iostream>
#include <locale>
using namespace std;
#include <cstring>

void cargarCadena(char *pal, int tam);

class Fecha{
    private:
        int dia;
        int mes;
        int anio;
    public:
        ///Constructor
        Fecha();

        ///Seters
        void setDia(int d){
            dia=d;
        }
        void setMes(int m){
            mes=m;
        }
        void setAnio(int a){
            anio=a;
        }
        ///Geters
        int getDia(){
            return dia;
        }
        int getMes(){
            return mes;
        }
        int getAnio(){
            return anio;
        }

        ///Metodos
        void Cargar();
        void Mostrar();

};

///Constructores
Fecha::Fecha(){
    dia = 0;
    mes = 0;
    anio = 0;
}

///Prototipo
void Fecha::Cargar(){
    cout << "DIA         :";
    cin >> dia;
    cout << "MES    :";
    cin >> mes;
    cout << "ANIO         :";
    cin >> anio;
}

void Fecha::Mostrar(){
    cout << "DIA        :" << dia << endl;
    cout << "MES        :" << mes << endl;
    cout << "ANIO       :" << anio << endl;
}

class Cliente{
    private:
        int DNI;
        Fecha fechaNac;
        char nombre[20];
        char apellido[20];
        char email[30];
        char telefono[10];
    public:
        //constructores
        Cliente();
        Cliente(const char *n);

        //seters
        void setDni(int dni){
            DNI = dni;
        }
        void setFechaNac(Fecha fn){
            fechaNac = fn;
        }
        void *setNombre(const char *n){
            strcpy(nombre, n);
        }
        void *setApellido(const char *a){
            strcpy(apellido, a);
        }
        void *setEmail(const char *e){
            strcpy(email, e);
        }
        void *setTelefono(const char *t){
            strcpy(telefono, t);
        }

        //geters
        int getDni(){
            return DNI;
        }
        const char *getNombre(){
            return nombre;
        }
        Fecha getfechaNac(){
            return fechaNac;
        }
        const char *getApellido(){
            return apellido;
        }
        const char *getEmail(){
            return email;
        }
        const char *getTelefono(){
            return telefono;
        }

        //metodos
        void Cargar();
        void Mostrar();

};

//constructores
Cliente::Cliente(){
        int DNI = 0;
        fechaNac = Fecha();
        strcpy (nombre, "S/N");
        strcpy (apellido, "S/A");
        strcpy (email, "S/E");
        strcpy (telefono, "S/T");
}

Cliente::Cliente(const char *n){
    strcpy (nombre, n);
}

//Prototipos
void Cliente::Cargar(){
    cout << "DNI        : ";
    cin >> DNI;
    cout << "Fecha      : " << endl;
    fechaNac.Cargar();
    cout << "Nombre     : ";
    cargarCadena(nombre, 19);
    cout << "Apellido   : ";
    cargarCadena(apellido, 19);
    cout << "Email      : ";
    cargarCadena(email, 29);
    cout << "Telefono   : ";
    cargarCadena(telefono, 9);
    cout << endl;
}

void Cliente::Mostrar(){
    cout << "DNI        : "<< DNI << endl;
    cout << "Fecha      : "<< endl;
    fechaNac.Mostrar ();
    cout << "Nombre     : "<< nombre << endl;
    cout << "Apellido   : "<< apellido << endl;
    cout << "Email      : "<< email << endl;
    cout << "Telefono   : "<< telefono << endl;
    cout << endl;

}

///Funciones del menu
void PuntoA(Cliente *clientes, int TAM);
void PuntoB(Cliente *clientes, int TAM);
void PuntoCcomparar(Cliente *clientes, int TAM, int d);
void PuntoC(Cliente *clientes, int TAM);
void PuntoD(Cliente *clientes, int TAM);
int posicionD(Cliente *clientes, int TAM, int d);
void PuntoD(Cliente *clientes, int TAM);
Cliente devolverObjetoE(Cliente *clientes, int TAM, int d);
void PuntoE(Cliente *clientes, int TAM);
int devolverCantidad(Cliente *clientes, int TAM, Fecha fechaIngresada);
void PuntoF(Cliente *clientes, int TAM);

int main ()
{
 setlocale(LC_ALL, "");

 const int TAM = 3;
 Cliente clientes[3];

    char opc;

while(true){
    system("cls");
    cout<<"----------MENU------------"<<endl;
    cout<<"a). Cargar un vector de 10 clientes."<<endl;
    cout<<"b). Listar todos los clientes del vector."<<endl;
    cout<<"c). Listar todos los clientes cuyo DNI sea mayor a un valor que se ingresa por teclado."<<endl;
    cout<<"d). A partir de un valor de DNI recibido como parámetro, devolver la posición del objeto que contiene ese DNI. De no encontrarlo devolver -1."<<endl;
    cout<<"e). Igual a la función del punto anterior, pero debe devolver el objeto completo que contiene el DNI. De no encontrar el código la función debe devolver un objeto Cliente con un valor de -1 en el DNI."<<endl;
    cout<<"f). Dado una fecha que se recibe como parámetro devolver la cantidad de clientes cuyo nacimiento sea anterior a ese valor recibido."<<endl;
    cout << endl;
    cout<<"s). SALIR"<<endl;
    cout <<"---------------------------"<<endl;
    cout<<"OPCION: ";
    cin>>opc;
        system("cls");
        switch(opc){
            case 'a':
                    PuntoA(clientes, TAM);
                break;
            case 'b':
                    PuntoB(clientes, TAM);
                break;
            case 'c':
                    PuntoC(clientes, TAM);
                break;
            case 'd':
                    PuntoD(clientes, TAM);
                break;
            case 'e':
                    PuntoE(clientes, TAM);
                break;
            case 'f':
                   PuntoF(clientes, TAM);
                break;
            case 's':
                return 0;
        }
        system("pause>null");
}



return 0;
}

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

void PuntoA(Cliente *clientes, int TAM){
    for (int i=0; i<TAM; i++){
        clientes[i].Cargar();
    }
}

void PuntoB(Cliente *clientes, int TAM){
    for (int i=0; i<TAM; i++){
        clientes[i].Mostrar();
    }
}

void PuntoCcomparar(Cliente *clientes, int TAM, int d){
    for (int i=0; i<TAM; i++){
        if(clientes[i].getDni() > d){
            clientes[i].Mostrar();
        }
    }
}

void PuntoC(Cliente *clientes, int TAM){
    int dni;
    cout<<"Ingrese DNI  : ";
    cin >> dni;

    PuntoCcomparar(clientes, TAM, dni);
}

int posicionD(Cliente *clientes, int TAM, int d){
    for (int i=0; i<TAM; i++){
        if(clientes[i].getDni() == d){
            return i;
        }
    }
    return -1;
}

void PuntoD(Cliente *clientes, int TAM){
    int dni;
    cout<<"Ingrese DNI  : ";
    cin >> dni;

    posicionD(clientes, TAM, dni);
}

Cliente devolverObjetoE(Cliente *clientes, int TAM, int d){
    Cliente aux;
    for (int i=0; i<TAM; i++){
        if(clientes[i].getDni() == d){
            return clientes[i];
        }
    }
    aux.setDni(-1);
    return aux;
}

void PuntoE(Cliente *clientes, int TAM){
    int dni;
    cout<<"Ingrese DNI  : ";
    cin >> dni;

    devolverObjetoE(clientes, TAM, dni);
}

int devolverCantidad(Cliente *clientes, int TAM, Fecha fechaIngresada){
    int contador = 0;

    for (int i=0; i<TAM; i++){
        if(clientes[i].getfechaNac().getAnio() < fechaIngresada.getAnio()){
            contador ++;
        }
        else{
            if(clientes[i].getfechaNac().getAnio() == fechaIngresada.getAnio() && clientes[i].getfechaNac().getMes() < fechaIngresada.getMes()){
                contador++;
            }
            else{
                if(clientes[i].getfechaNac().getAnio() == fechaIngresada.getAnio() && clientes[i].getfechaNac().getMes() == fechaIngresada.getMes() && clientes[i].getfechaNac().getDia() < fechaIngresada.getDia()){
                contador++;
                }
            }
        }
    }
    return contador;
}

void PuntoF(Cliente *clientes, int TAM){
    Fecha fechaIngreso;

    cout << "Ingrese Fecha  : " << endl;
    fechaIngreso.Cargar();

    devolverCantidad(clientes, TAM, fechaIngreso);

}
