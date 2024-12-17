///Ejercicio:
///Autor:DEK
///Fecha:
///Comentario:

# include<iostream>
# include<cstdlib>

using namespace std;


int main(){
    Articulo obj;
    Articulo otro(5.4);
    Articulo distinto("zapallo");

    otro.Mostrar();
	cout<<endl;
	system("pause");
	return 0;
}


//Constructor

    Articulo(float precio = 0, const char *cod = "S/C", const char *desc = "S/D",  int stock=0, bool estado=true){
        strcpy(Codigo, cod);
        strcpy(Descripcion, desc);
        Precio = precio;
        Stock = stock;
        Estado = estado;
    }

    Articulo(const char *desc){
        strcpy(Codigo, "D/E");
        strcpy(Descripcion, desc);
        Precio = 15;
        Stock = 2;
        Estado = false;
    }


