///Nombre: Jesica Valdez

#include <iostream>
#include <locale>
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
    fflush(stdin); ///vuelve a limpiar el buffer para eliminar los caracteres sobrantes
}

///CLASE FECHA
class Fecha{
    private:
        int dia, mes, anio;
    public:
    //CONSTRUCTOR
    Fecha();
    //SETS
    void setDia(int);
    void setMes(int);
    void setAnio(int);
    //GETS
    int getDia();
    int getMes();
    int getAnio();

    void Cargar();
    void Mostrar();
};
//CONSTRUCTOR
Fecha::Fecha(){
    dia=1;
    mes=1;
    anio=1900;
}
//SETS
void Fecha::setDia(int d){
    if(d>=1 && d<=31){
        dia=d;
    }
}
void Fecha::setMes(int m){
    if(m>=1 && m<=12){
        mes=m;
    }
}
void Fecha::setAnio(int a){
    if(anio>0){
        anio=a;
    }
}
//GETS
int Fecha::getDia(){
    return dia;
}
int Fecha::getMes(){
    return mes;
}
int Fecha::getAnio(){
    return anio;
}

void Fecha::Cargar(){
    int d, m, a;
    bool correcto=false;

    do{
        cout<<"DIA: ";
        cin>>d;
        cout<<"MES: ";
        cin>>m;
        cout<<"ANIO: ";
        cin>>a;

        if (d>=1 && d<=31 && m>=1 && m<=12 && a>0){
        dia = d;
        mes = m;
        anio = a;
        correcto = true;
        }else{
            cout<<"Fecha incorrecta."<<endl;
        }

    } while (!correcto);

}

void Fecha::Mostrar(){
    cout << "FECHA: " <<dia<< "/" <<mes<< "/" <<anio<<endl;
}

class ArchivoFinal;

class Final {
private:
	int legajo;
	char nombre[30];
	char apellido[30];
	int dni;
	Fecha fechaNacimiento;
	float sueldo;
	int carrera;
	bool estado;
public:

        /*
	void setLegajo(int l, ) {

        ArchivoFinal arch;
        while (arch.BuscarLegajo(l) != -1) {
            cout << "Legajo no válido. Ingrese otro legajo: ";
            cin >> l;
        }

        legajo = l;}*/
    void setLegajo(int l, ArchivoFinal &arch);
	void* setNombre(const char* n) { strcpy(nombre, n); }
	void* setApellido(const char* a) { strcpy(apellido, a); }
	void setDni(int d) { dni = d; }
	void setFecha (Fecha f){fechaNacimiento=f;}
	void setSueldo(float s) { sueldo = s; }
	void setCarrera(int c) { carrera = c; }
	void setEstado(bool e) { estado = e; }


	int getLegajo() { return legajo; }
	const char* getNombre() { return nombre; }
	const char* getApellido() { return apellido; }
	int getDni() { return dni; }
	Fecha getFecha(){return fechaNacimiento;}
	float getSueldo() { return sueldo; }
	int getCarrera() { return carrera; }
	bool getEstado() { return estado; }

	void cargar(ArchivoFinal &arch);

	/*
	void cargar() {
	    Final obj;

		cout << "Legajo: ";
        cin >> legajo;
        cout << "Nombre: ";
        cin.ignore();
        cargarCadena(nombre, 30);
        cout << "Apellido: ";
        cargarCadena(apellido, 30);
        cout << "DNI: ";
        cin >> dni;
        cout << "Fecha de Nacimiento: " << endl;
        fechaNacimiento.Cargar();
        cout << "Sueldo: ";
        cin >> sueldo;
        cout << "Carrera: ";
        cin >> carrera;
        estado = true;
	}*/

	void mostrar() {
        if (estado == true) {
            cout << "Legajo: " << legajo << endl;
            cout << "Nombre: " << nombre << endl;
            cout << "Apellido: " << apellido << endl;
            cout << "DNI: " << dni << endl;
            fechaNacimiento.Mostrar();
            cout << "Sueldo: " << sueldo << endl;
            cout << "Carrera: " << carrera << endl;
        }
	}
};

class ArchivoFinal{
private:
	char nombre[30];
public:
	arcF(const char *n= "final.dat"){
		strcpy(nombre, n);
	}
	Final leerRegistro(int pos){
		Final reg;
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
			return tam/sizeof(Final);
		}
			bool grabarRegistro(Final reg){
				FILE *p;
				p=fopen(nombre, "ab");
				if(p==NULL) return false;
				bool escribio=fwrite(&reg, sizeof reg,1, p);
				fclose(p);
				return escribio;
			}

        int BuscarLegajo(int legajo) {
		Final reg;
		ArchivoFinal arch;
		int cantidad = arch.contarRegistros();

		for (int i = 0; i < cantidad; i++)
		{
			reg = arch.leerRegistro(i);
			if (reg.getLegajo() == legajo) {
				return i;
			}
		}
		return -1;
	}

	bool sobreEscribirRegistro(Final reg, int pos) {
		FILE* p;
		p = fopen(nombre, "rb+");
		if (p == NULL) return false;
		fseek(p, sizeof reg * pos, 0);
		fwrite(&reg, sizeof reg, 1, p);
		fclose(p);
		return true;
	}

};

void Final::setLegajo(int l, ArchivoFinal &arch) {
    while (arch.BuscarLegajo(l) != -1) {
        cout << "Legajo no válido. Ingrese otro legajo: ";
        cin >> l;
    }
    legajo = l;
}

void Final::cargar(ArchivoFinal &arch) {
    cout << "Legajo: ";
    cin >> legajo;
    setLegajo(legajo, arch);
    cout << "Nombre: ";
    cin.ignore();
    cargarCadena(nombre, 30);
    cout << "Apellido: ";
    cargarCadena(apellido, 30);
    cout << "DNI: ";
    cin >> dni;
    cout << "Fecha de Nacimiento: " << endl;
    fechaNacimiento.Cargar();
    cout << "Sueldo: ";
    cin >> sueldo;
    cout << "Carrera: ";
    cin >> carrera;
    estado = true;
}

/*
Hacer un menú con opciones para dar alta de registros y dar de baja un registro.
Al dar el alta se debe validad que no se repita el legajo.
*/

void altaRegistro()
{
	Final reg;
	ArchivoFinal arch;

	reg.cargar(arch);
	arch.grabarRegistro(reg);
}

void bajaRegistro()
{
    int numLegajo, indice;
    Final reg;
    ArchivoFinal arcF;
    int opcion;


    cout << "Ingrese el numero de Legajo: ";
    cin >> numLegajo;

    indice=arcF.BuscarLegajo(numLegajo);

    if(indice != -1){
        reg=arcF.leerRegistro(indice);

        cout<< "Desea eliminar este Legajo? (1)Si - (2)No: " << endl;
        cin >> opcion;
        system("cls");

        if(opcion == 1){
            reg.setEstado(false);

            if(arcF.sobreEscribirRegistro(reg, indice)){
                cout<<"Se elimino con exito."<<endl;
            }else{
                cout<<"No se pudo eliminar."<<endl;
            }
        }else{
            cout<<"Cancelo el eliminado del Legajo."<<endl;
        }
    }else{
        cout<<"Numero de Legajo inexistente."<< endl;
    }
}

int menu() {
	int opc;

	while(true){
    system("cls");
	cout << "1. Alta de registro."<<endl;
	cout << "2. Baja de Registro."<<endl;
	cout <<"0. SALIR"<<endl;
	cout << "OPCION: ";
	cin >> opc;
	system("cls");

        switch (opc)
        {
            case 1:
                altaRegistro();
                system("pause");
                break;
            case 2:
                bajaRegistro();
                system("pause");
                break;
            case 0:
                exit(10);
            default:
                break;
        }
	}
}

int main()
{
    setlocale(LC_ALL, "");


    menu();

    cout<<endl;
    system("pause");
    return 0;
}

