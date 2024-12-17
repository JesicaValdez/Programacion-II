///Nombre: Jesica Valdez

#include <iostream>
#include <locale>
using namespace std;
#include <cstring>

void cargarCadena(char *pal, int tam);

class Articulo{
    private:
        char codigo[5];
        char descripcion[30];
        float precio;
        int stock;
        bool estado;
    public:
        ///Constructor
        Articulo();
        Articulo(const char *);

        ///Seters
        void *setCodigo(const char *c){
            strcpy(codigo,c);
        }
        void *setDescripcion(const char *d){
            strcpy(descripcion, d);
        }
        void setPrecio(float p){
            precio = p;
        }
        void setStock(int s){
            stock = s;
        }
        void setEstado(bool e){
            estado = e;
        }

        ///Geters
        const char *getCodigo(){
            return codigo;
        }
        const char *getDescripcion(){
            return descripcion;
        }
        float getPrecio(){
            return precio;
        }
        int getStock(){
            return stock;
        }
        bool getEstado(){
            return estado;
        }

        ///Metodos
        void Cargar();
        void Mostrar();
};

///Constructores
Articulo::Articulo(){
    strcpy (codigo, "S/C");
    strcpy (descripcion, "S/D");
    precio = 0;
    stock = 0;
    estado = false;
}

Articulo::Articulo(const char *d){
    strcpy (descripcion, d);
}

///Prototipo
void Articulo::Cargar(){

    cout << "CODIGO         :";
    cargarCadena(codigo, 4);
    cout << "DESCRIPCION    :";
    cargarCadena(descripcion, 29);
    cout << "PRECIO         :";
    cin >> precio;
    cout << "STOCK          :";
    cin >> stock;
    cout << "ESTADO         :";
    cin >> estado;
    cout << endl;


}
void Articulo::Mostrar(){

    cout << "CODIGO         :" << codigo << endl;
    cout << "DESCRIPCION    :" << descripcion << endl;
    cout << "PRECIO         :" << precio << endl;
    cout << "STOCK          :" << stock << endl;
    cout << "ESTADO         :" << estado << endl;
    cout << endl;

}

///Funciones del programa
void PuntoA(Articulo *artcs, int TAM);
void PuntoB(Articulo *artcs, int TAM);
void PuntoC(Articulo *artcs, int TAM);
int posicion(Articulo *artc, int TAM, char cod);
void PuntoD(Articulo *artcs, int TAM);
Articulo PuntoE(Articulo *artcs, int TAM, char cod);
void PuntoEMostrar(Articulo *artcs, int TAM);
int contar(Articulo *artcs, int TAM, int valor);
void PuntoF(Articulo *artcs, int TAM);
void incrementar(Articulo *artcs, int TAM, float porcentaje);
void PuntoG(Articulo *artcs, int TAM);



int main ()
{
 setlocale(LC_ALL, "");

 const int TAM=2;

 ///OBJETO
 Articulo artcs[TAM];

    char opc;

while(true){
    system("cls");
    cout<<"----------MENU------------"<<endl;
    cout<<"a). Cargar un vector de 10 artículos."<<endl;
    cout<<"b). Listar todos los artículos del vector."<<endl;
    cout<<"c). Listar todos los artículos cuyo precio sea mayor a un valor que se ingresa por teclado."<<endl;
    cout<<"d). Devolver la posición del objeto que contiene ese código. De no encontrarlo devolver -1."<<endl;
    cout<<"e). Devolver el objeto completo que contiene el código. De no encontrarlo devolver un valor de -1 en el stock."<<endl;
    cout<<"f). Devolver la cantidad de artículos cuyo stock sea inferior a ese valor recibido."<<endl;
    cout<<"g). Dado un porcentaje de incremento,modificar el precio unitario de todos los objetos."<<endl;
    cout<<"s). SALIR"<<endl;
    cout<<"OPCION: ";
    cin>>opc;
        system("cls");
        switch(opc){
            case 'a':
                    PuntoA(artcs, TAM);
                break;
            case 'b':
                    PuntoB(artcs, TAM);
                break;
            case 'c':
                    PuntoC(artcs, TAM);
                break;
            case 'd':
                    PuntoD(artcs, TAM);
                break;
            case 'e':
                    PuntoEMostrar(artcs, TAM);
                break;
            case 'f':
                   PuntoF(artcs, TAM);
                break;
            case 'g':
                    PuntoG(artcs, TAM);
                break;
            case 's':
                return 0;
        }
        system("pause>null");
}



return 0;
}


///Declaracion Funciones
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

///A
void PuntoA(Articulo *artcs, int TAM){
    for (int i=0; i<TAM; i++){
        artcs[i].Cargar();
    }
}

///B
void PuntoB(Articulo *artcs, int TAM){
    for (int i=0; i<TAM; i++){
        artcs[i].Mostrar();
    }
}

///C
void PuntoC(Articulo *artcs, int TAM){
    int valor;

    cout << "Ingrese un Precio  :$";
    cin >> valor;
    for (int i=0; i<TAM; i++){
        if(artcs[i].getPrecio() > valor){
            artcs[i].Mostrar();
        }
    }
}

///D
int posicion(Articulo *artcs, int TAM, char *cod){

 for (int i=0; i<TAM; i++){
    if(strcmp(artcs[i].getCodigo(), cod)==0){
        return i;
    }
 }
return -1;
}

void PuntoD(Articulo *artcs, int TAM){
    char cod[5];
    cout << "Ingrese codigo     :";
    cargarCadena(cod, 4);
    cout << endl;

    cout << "Posicion   :" << posicion(artcs, TAM, cod);
}

///E
Articulo PuntoE(Articulo *artcs, int TAM, char *cod){

 Articulo objAux;

 for (int i=0; i<TAM; i++){
    if(strcmp(artcs[i].getCodigo(), cod)==0){
        return artcs[i];
    }
 }

objAux.setStock(-1);
return objAux;

}

void PuntoEMostrar(Articulo *artcs, int TAM){
    char cod[5];
    Articulo objAux;

    cout << "Ingrese codigo     :";
    cargarCadena(cod, 4);
    cout << endl;

    objAux = PuntoE(artcs, TAM, cod);
    if(objAux.getStock() == -1){
        objAux.Mostrar();
    }
    else{
        objAux.Mostrar();
    }
}

///F
int contar(Articulo *artcs, int TAM, int valor){

int contador = 0;

 for (int i=0; i<TAM; i++){
    if(artcs[i].getStock() < valor){
         contador++;
    }
 }
return contador;
}

void PuntoF(Articulo *artcs, int TAM){
    int valor;
    cout << "Ingrese valor de STOCK     :";
    cin >> valor;
    cout << endl;

    cout << "Cantidad de Articulos   :" << contar(artcs, TAM, valor);
}

void incrementar(Articulo *artcs, int TAM, float porcentaje){
    int aumentar;

    for (int i=0; i<TAM; i++){
        aumentar = artcs[i].getPrecio();
        aumentar += aumentar * porcentaje / 100;
        artcs[i].setPrecio(aumentar);
    }
}

void PuntoG(Articulo *artcs, int TAM){
    float porcentaje;
    cout << "Ingrese valor de PORCENTAJE     :";
    cin >> porcentaje;
    cout << endl;

    incrementar(artcs, TAM, porcentaje);
}
