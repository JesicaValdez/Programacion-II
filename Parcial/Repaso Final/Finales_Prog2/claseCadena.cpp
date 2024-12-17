/*Nombre: Jesica Valdez
*/

#include <iostream>
#include <locale>
#include <cstring>

using namespace std;

class Cadena{
private:
    char *p;
    int tam;
public:
    Cadena(const char* palabra="default"){
        tam=strlen(palabra)+1;
        p=new char[tam];
        if(p==NULL){
            cout<<"Error de asignacion de Memoria";
            exit(1);
        }

        strcpy(p, palabra);
        p[tam-1]='\0';
    }
    void Mostrar(){
        cout<<p<<endl;
    }
    void setP(const char *palabra){
        delete p;
        tam= strlen(palabra)+1; //strlen: devuelve la cantidad de caracteres de la cadena
        p=new char[tam];
        if(p==NULL){
            cout<<"Error de asignacion de Memoria";
            exit(1);
        }

        strcpy (p, palabra);
        p[tam-1]='\0';

    }
    int largoCadena(){return strlen(p);}//alternativa: {return tam-1;}
    void Concatenar(const char *otraPalabra){
        char *bak;
        bak= new char [tam];
        if(bak==NULL) return;
        strcpy(bak,p);

        delete p; //libero memoria

        tam+= strlen(otraPalabra);
        p=new char[tam];
        if(p==NULL) return;

        strcpy(p, bak);
        strcat(p, otraPalabra); //a p le agregamos lo que teniamos en otraPalabra. strcat: agrega a la cadena de la izquierda lo que tiene la cadena de la derecha

        delete bak;
    }
    bool operator==(const Cadena &obj){ //cuando encontramos un &nombre en el momento de la declaracion significa que tenemos una referencia, es decir, el alias de una variable
        if(strcmp(p,obj.p)==0)return true;
            return false;
    }
    ~Cadena(){
        delete p;
    }

};

void cambiarValor(int &y){
    y=14;
}
int main ()
{
 setlocale(LC_ALL, "");

 cout<<"Funcion cambiarValor:"<<endl;
 int x=10;
 cambiarValor(x);
 cout<<"x "<<x<<endl;

 cout<<"Funcion sobreCarga:"<<endl;
 Cadena obj("hola a todos"), aux("hola a todos");
 if(obj==aux){
    cout<<"Son Iguales"<<endl;
 }
 else{
    cout<<"Son Distintos"<<endl;
 }
 obj.Mostrar();
 cout<<"Cantidad de caracteres de la cadena: "<<obj.largoCadena()<<endl;
 obj.Concatenar(" los/las estudiantes");
 obj.Mostrar();
 cout<<"Cantidad de caracteres de la cadena: "<<obj.largoCadena()<<endl;
 cout<<endl;
 obj.setP("setP funcionando");
 obj.Mostrar();
 cout<<"Cantidad de caracteres de la cadena: "<<obj.largoCadena()<<endl;
 cout<<endl;
 system("pause");
 return 0;
}


