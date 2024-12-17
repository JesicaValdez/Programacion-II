/*Nombre: Jesica Valdez
*/
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
    fflush(stdin); ///vuelve a limpiar el buffer para eliminar los caracteres sobrantes
}

//CLASE
class Prestamo{
private:
    int numBanco;
    int mes;
    int tipoPrestamo;
    float importe;
    //plazo
public:
    void setNumBanco(int nb){numBanco = nb;}
    void setMes (int m) {mes = m;}
    void setTipoPrestamo (int tp) {tipoPrestamo = tp;}
    void setImporte (float im) {importe = im;}

    int getNumBanco(){return numBanco;}
    int getMes(){return mes;}
    int getTipoPrestamo(){return tipoPrestamo;}
    float getImporte(){return importe;}
};

//CLASE Archivo
class ArchivoPrestamo{
private:
	char nombre[30];
public:
	ArchivoPrestamo(const char *n="prestamo.dat"){
		strcpy(nombre, n);
	}

	Prestamo leerRegistro(int pos){
		Prestamo reg;
		//reg.setEstado(false);
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
			return tam/sizeof(Prestamo);
		}
			bool grabarRegistro(Prestamo reg){
				FILE *p;
				p=fopen(nombre, "ab");
				if(p==NULL) return false;
				bool escribio=fwrite(&reg, sizeof reg,1, p);
				fclose(p);
				return escribio;
			}
};


//CARGAR REGISTRO
void CargarRegistro(){
	ArchivoPrestamo archiP;
	Prestamo obj;

	int nBancoC;
    int mesC;
    int tipoPrestamoC;
    float importeC;
    //plazo

	cout << "Num Banco: ";
	obj.setNumBanco(nBancoC);

	cout << "Mes: ";
	obj.setMes(mesC);

	cout << "Tipo Prestamo: ";
	obj.setTipoPrestamo(tipoPrestamoC);

	cout << "Importe: ";
	obj.setImporte(importeC);

	if(archiP.grabarRegistro(obj)){
		cout << "El registro se guardo con exito." << endl;
	}else
	{
		cout << "Hubo un error al guardar el registro." << endl;
	}
}

//Cantidad de bancos con mas de 3 prestamos otorgados
void PuntoA(){
    ArchivoPrestamo archiP;
    Prestamo obj;
    //devuelve cantidad total de registro
    int cantidad = archiP.contarRegistros();
    int vecMayor3[5];

    for(int i=0; i<cantidad; i++){
        obj = archiP.leerRegistro(i);
        //devuelve cantidad total de registro DIFERENCIADO POR BANCO
        vecMayor3[obj.getNumBanco()-1]++;
    }
    //verificamos cual banco cumplio la cantidad esperada
    int contarBcos=0;
    for(int i=0; i<5; i++){
        if(vecMayor3[i]>3){
            contarBcos++;
        }
    }

    cout << "Cantidad de Bcos que realizaron mas de 3 prestamos: " << contarBcos << endl;
}

//por cada tipo de prestamo el importe total otorgado
void PuntoB(){
    ArchivoPrestamo archiP;
    Prestamo obj;
    int cantidad = archiP.contarRegistros();
    int tiposPrestamos[10];

    //el for va hasta la cantidad disponible SIEMPRE
     for(int i=0; i<cantidad; i++){
        obj = archiP.leerRegistro(i);
        //devuelve el total acumulado de importe por cada Tipo de PRESTAMO
        tiposPrestamos[obj.getTipoPrestamo()-1] += obj.getImporte();
    }
    //leemos el valor acumulado en el vector
    for(int i=0; i<10; i++){
        cout << "El importe acumulado para el tipo #" << i << ": " << tiposPrestamos[i] << endl;
    }

}

void menu() {
	int opc;
	while(true){
    system("cls");
	cout << "1. Cargar registro."<<endl;
	cout << "2. Punto A"<<endl;
	cout << "3. Punto B"<<endl;

	cout <<"0. SALIR"<<endl;
	cout << "OPCION: ";
	cin >> opc;
	system("cls");
	switch (opc)
	{
		case 1:
			CargarRegistro();
			system("pause");
			break;
		case 2:
            PuntoA();
			system("pause");
			break;
        case 3:
            PuntoB();
			system("pause");
			break;
        case 0:
            exit(10);
	default:
		break;
	}
	}
}

int main ()
{
setlocale(LC_ALL, "");


menu();


cout<<endl;
system("pause");
return 0;
}


