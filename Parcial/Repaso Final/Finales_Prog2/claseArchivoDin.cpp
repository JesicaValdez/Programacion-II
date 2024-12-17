/*Nombre: Jesica Valdez
*/

#include <iostream>
#include <locale>
#include <cstring>

using namespace std;
#include "parcial1.h"

int main ()
{
 setlocale(LC_ALL, "");

 Proyecto *vProy;
 ArchivoProyecto obj("proyectos.dat");

 int tam;
 tam=obj.contarRegistros();
 vProy=new Proyecto[tam];

 if(vProy==NULL){
    cout<<"Error de asignacion de memoria";
    return -1;
 }

 for (int i=0;i<tam; i++){
    vProy[i].Mostrar();
    cout<<endl;
 }

 delete vProy;
 cout<<endl;
 system("pause");
 return 0;
}


