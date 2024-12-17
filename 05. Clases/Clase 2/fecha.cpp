/*Nombre: Jesica Valdez
*/

#include <iostream>
#include <locale>
using namespace std;


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
    cout << endl;
}

void Fecha::Mostrar(){
    cout << "DIA        :" << dia << endl;
    cout << "MES        :" << mes << endl;
    cout << "ANIO       :" << anio << endl;
    cout << endl;

}


int main ()
{
 setlocale(LC_ALL, "");


return 0;
}


