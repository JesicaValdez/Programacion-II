///Nombre: Jesica Valdez

#include <iostream>
#include <locale>
#include <cstring>
using namespace std;

#include "parcialm1.h"

///Punto A - Generar un archivo con el codigo de obra, la direccion y la provincia de las obras cuyo estado de ejecuccion sea en "ejecucion"
class Ejecucion
{
private:
    char codObra[5];
    char direccion[30];
    int provincia;
public:
    void setCodObra(const char *co)
    {
        strcpy(codObra,co);
    }
    void setDireccion(const char *d)
    {
        strcpy(direccion,d);
    }
    void setProvincia(int p)
    {
        provincia = p;
    }
    void Mostrar()
    {
        cout << "Codigo de Obra #" << codObra << endl;
        cout << "Direccion " << direccion << endl;
        cout << "Provincia " << provincia << endl;
    }
};

class ArchivoEjecucion
{
private:
    char nombre[30];
public:
    ArchivoEjecucion(const char *n)
    {
        strcpy(nombre, n);
    }
    bool escribir(Ejecucion obj)
    {
        FILE *p;
        p=fopen(nombre, "ab");
        if(p==NULL) return false;
        bool escribir = fwrite(&obj, sizeof obj, 1, p);
        fclose(p);
        return true;
    }
    bool listar()
    {
        Ejecucion reg;
        FILE *p;
        p=fopen(nombre, "rb");
        if(p==NULL) return false;
        while(fread(&reg, sizeof reg, 1, p))
        {
            reg.Mostrar();
            cout << endl;
        }
        fclose(p);
        return true;
    }


};

void puntoA()
{
    ArchivoEjecucion archivoE("obrasEjecucion.dat");
    Ejecucion registroE;

    ArchivoObras archivoO("obras.dat");
    Obra registroO;
    int cant = archivoO.contarRegistros();

    for (int i=0; i<cant; i++)
    {
        registroO = archivoO.leerRegistro(i);
        if(registroO.getEstadoEjecucion() == 3)
        {
            registroE.setCodObra(registroO.getCodigoObra());
            registroE.setDireccion(registroO.getDireccion());
            registroE.setProvincia(registroO.getProvincia());
            archivoE.escribir(registroE);
        }
    }
    archivoE.listar();

}


void punto1()
{
    ArchivoMateriales archivoM("materiales.dat");
    Material registroM;
    int cantM = archivoM.contarRegistros();

    ArchivoCompras archivoC("compras.dat");
    Compra registroC;
    int cantC = archivoC.contarRegistros();

    int contador;
    for (int i=0; i<cantM; i++)
    {
        registroM = archivoM.leerRegistro(i);
        contador = 0;

        for (int j=0; j<cantC; j++)
        {
            registroC = archivoC.leerRegistro(j);

            if(registroM.getCodigoMaterial()==registroC.getCodigoMaterial())
            {
                contador++;
            }
        }
        cout << "Codigo #" << registroM.getCodigoMaterial() << " : " << contador << endl;
    }

}
//a2) El nombre del proveedor que mayor importe haya obtenido entre todas las compras que se le realizaron.
void punto2()
{

    ArchivoProveedores archivoP("proveedores.dat");
    Proveedor registroP;

    ArchivoCompras archivoC("compras.dat");
    Compra registroC;
    int cantidad = archivoC.contarRegistros();
//cantidad me devuelve la cantidad de registros de compras en los archivos.


    float importeP[60]= {};

    for (int i=0; i<cantidad; i++)
    {
        registroC = archivoC.leerRegistro(i);
        importeP[registroC.getNumeroproveedor()-1] += registroC.getImporte();
    }

    int mayor = 0;
    int pos = 0;
    for (int i=0; i<60; i++)
    {
        if(importeP[i]>mayor)
        {
            mayor=importeP[i];
            pos=i;
        }
    }

    cout << "Posicion: " << pos << endl;
    registroP = archivoP.leerRegistro(pos+1);
    cout << "Proveedor " << registroP.getNombre() << " realizo mayor importe de todas las compras" << endl;
}

///a3) Los número de los proveedores a los que no se les compró nada el año pasado.
void punto3 ()
{
    ArchivoCompras archivoC("compras.dat");
    Compra registroC;
    int cant = archivoC.contarRegistros();

    bool proveedores[60]= {};

    for (int i=0; i<cant; i++)
    {
        registroC = archivoC.leerRegistro(i);
        if(registroC.getFechaCompra().getAnio()==2022)
        {
            proveedores[registroC.getNumeroproveedor()-1]=true;
        }
    }

    for (int i=0; i<60; i++)
    {
        if(proveedores[i]==false)
        {
            cout << "Al Proveedor #" << i+1 << ", no se le compro el año pasado" << endl;
        }
    }

}

///a4) El gasto en obra gruesa para cada una de las obras. (analizar bien. Es el punto más complejo porque requiere del uso de 3 archivos)
void punto4()
{
    ArchivoObras archivoO("obras.dat");
    Obra registroO;
    int cantO = archivoO.contarRegistros();

    ArchivoCompras archivoC("compras.dat");
    Compra registroC;
    int cantC = archivoC.contarRegistros();

    ArchivoMateriales archivoM("materiales.dat");
    Material registroM;
    int cantM = archivoM.contarRegistros();

    float gasto;

    for (int i=0; i<cantO; i++)
    {
        registroO = archivoO.leerRegistro(i);
        gasto = 0;
        for (int j=0; j<cantC; j++)
        {
            registroC = archivoC.leerRegistro(j);
            for (int m=0; m<cantM; m++)
            {
                registroM = archivoM.leerRegistro(m);
                if(strcmp(registroO.getCodigoObra(),registroC.getCodigoObra())==0 && registroM.getCodigoMaterial()==registroC.getCodigoMaterial())
                {
                    if(registroM.getTipo()==1)
                    {
                        gasto += registroC.getImporte();
                    }
                }
            }
        }


        cout << "Cod Obra " << registroO.getCodigoObra() << " gasto " << gasto << endl;
    }

}


///a5) La/s provincia/s con más de 22 proveedores
void punto5()
{
    ArchivoProveedores archivoP("proveedores.dat");
    Proveedor registroP;
    int cant = archivoP.contarRegistros();

    int vecProvincias[24]= {};

    for (int i=0; i<cant; i++)
    {
        registroP = archivoP.leerRegistro(i);
        vecProvincias[registroP.getProvincia()-1]++;
    }

    for (int i=0; i<24; i++)
    {
        if(vecProvincias[i]>22)
        {
            cout << "Provincia con mas de 22 proveedores " << i << endl;

        }
    }

}

//a6) Dar de baja lógica a todas las compras del año 2020. (necesitamos: leer, contar, crear funcion de baja logica(que es booleana), similar a funciones como escribir, leer
bool baja(Compra registro, int pos)
{
    FILE *p;
    p = fopen("compras.dat", "rb+");
    if(p==NULL)
    {
        return false;
    }
    fseek(p, sizeof(Compra)*pos,SEEK_SET);
    bool resultado = fwrite(&registro,sizeof(Compra), 1, p);
    fclose(p);
    return resultado;
}

void darDebaja()
{
    ArchivoCompras archivoC("compras.dat");
    Compra registroC;
    int cant = archivoC.contarRegistros();

    for (int i=0; i<cant; i++)
    {
        registroC = archivoC.leerRegistro(i);
        if(registroC.getFechaCompra().getAnio() == 2020)
        {
            registroC.setActivo(false);
            baja(registroC, i);
        }
    }

}



///a7) Modificar el precio de las aberturas en el archivo de materiales. Incrementar un 10% todos los materiales de ese tipo.
void punto7()
{
    ArchivoMateriales archivoM("materiales.dat");
    Material registroM;
    int cant = archivoM.contarRegistros();

    float incremento;

    for (int i=0; i<cant; i++)
    {
        registroM = archivoM.leerRegistro(i);
        if(registroM.getTipo()==3)
        {
            incremento = registroM.getPU()*1.1;
            registroM.setPU(incremento);
        }
    }

}



int main ()
{
    setlocale(LC_ALL, "");

    puntoA();



    return 0;
}
