/*Nombre: Jesica Valdez
*/

#include <iostream>
#include <locale>
#include <cstring>

using namespace std;

/*
A. Generar un archivo con la cant de tareas para cada proyecto
Cada registro debe tener: codProyecto, nombre, cantTareas (agregar ESTADO SIEMPRE)

1-Archivos necesarios:TAREAS Y PROYECTOS
2-Necesito una nueva clase para darle formato al registro, y una clase para generar y manejar el archivo
3-Empiezo por proyectos(codigo y el nombre), y con una funcion averiguo la cant de tareas que coincidan con el codigo de proyecto leido.
Repito por cada proyecto.

B. Generar un archivo con el tiempo trabajado por cada empleado en el mes de mayo.
Cada registro debe tener: numEmpleado. nombre, cant de horas.

1-Archivos necesarios:EMPLEADOS y TAREAS
2-Necesito una nueva clase para darle formato al registro, y una clase para generar y manejar el archivo
3-Empiezo por Empleados y luego sumo la cant de horas de las tareas del mes de mayo correspondientes al empleado que lei

C. Informar para cada uno de los empleados la cant total de tareas realizadas de cada categoria.Informar el nombre del empleado y la cant de tareas

1-Archivos necesarios:EMPLEADOS y TAREAS
2-No necesito una nueva clase
3-Puedo usar un vector que inicializo en 0 con cada empleado, o podria usar una matriz (60x5)

D. Para cada origen, informar la cant de componentes de cada tipo

1-Archivos necesarios: COMPONENTES

E. Dar de baja todos los componentes de origen europeo

F. Listar el archivo del punto A usando asignacion dinamica de memoria.

*/
void cargarCadena(char *pal, int tam);

void cargarCadena(char *pal, int tam)
{
    int i;
    fflush(stdin);
    for (i=0; i<tam; i++)
    {
        pal[i] = cin.get();
        if(pal[i] == '\n')break;
    }
    pal[i]='\0';
    fflush(stdin);
}

class Fecha
{
};
class Proyecto
{
private:
    char codigoProyecto[5];
    char nombre[30];
    int ubicacion;
    char direccion[40];
    float presupuesto;
    int estadoDesarrollo;
    Fecha inicio;
    bool activo;
public:
    void Cargar()
    {
        cargarCadena(codigoProyecto,4);
        cargarCadena(nombre,29);
        cargarCadena(direccion,39);
        cin>>ubicacion;
        cin>>presupuesto;
        cin>>estadoDesarrollo;
        inicio.Cargar();
        activo=true;
    }

    void Mostrar()
    {
        cout<<codigoProyecto<<endl;
        cout<<nombre<<endl;
        cout<<direccion<<endl;
        cout<<ubicacion<<endl;
        cout<<presupuesto<<endl;
        cout<<estadoDesarrollo<<endl;
        inicio.Mostrar();
        if(!activo) cout<<"Esta borrado"<<endl<<endl;
    }

    const char* getCodigoProyecto()
    {
        return codigoProyecto;
    }
    const char* getNombre()
    {
        return nombre;
    }
    const char* getDireccion()
    {
        return direccion;
    }
    int getUbicacion()
    {
        return ubicacion;
    }
    int getEstadoDesarrollo()
    {
        return estadoDesarrollo;
    }
    float getPresupuesto()
    {
        return presupuesto;
    }
    bool getActivo()
    {
        return activo;
    }
    Fecha getFechaInicio()
    {
        return inicio;
    }
    void setUbicacion(int u)
    {
        ubicacion=u;
    }

};
class ArchivoProyecto
{
private:
    char nombre[30];
public:
    ArchivoProyecto(const char *n)
    {
        strcpy(nombre, n);
    }
    Proyecto leerRegistro(int pos)
    {
        Proyecto reg;
        reg.setUbicacion(-1);
        FILE *p;
        p=fopen(nombre, "rb");
        if(p==NULL)
        {
            return reg;
        }
        fseek(p, sizeof(Proyecto)*pos,0);
        fread(&reg, sizeof reg, 1, p),
              fclose(p);
        return reg;
    }
};
class Componente
{
};
class ArchivoComponente
{
};
class Tarea
{
};
class ArchivoTarea
{
};
class Empleado
{
};
class ArchivoEmpleado
{
};
class CpuntoA
{
private:
    char codigoProyecto[5];
    char nombre[30];
    int cantTareas;
    bool activo;
public:
    puntoA()
    {
        cantTareas=0;
    }
    void cargar(Proyecto proy)
    {
        strcpy(this->codProyecto, proy.getCodigoProyecto());
        strcpy(this->nombre, proy.getNombre());
        this->activo = proy.getActivo();
    }
    void sumTarea()
    {
        cantTareas++;
    }
    int guardarRegistro()
    {
        FILE * pFILE;
        pFILE = fopen("puntoA.dar", "ab");
        if(pFILE==NULL)
        {
            return -1;
        }
        int resultado = fwrite(this,  sizeof(*this),1,pFILE);
        fclose(pFILE);
        return resultado;
    }
};
void puntoA()
{
}
class CpuntoB {};

int calcularHoras(int *v)
{
    ArchivoTareas archiT("tareas.dat");
    Tarea obj;
    int tam=ArchiT.contarRegistros();

    for (int i=0; i<tam; i++)
    {
        if(obj.getFecha().getMes()==5 && obj.getFecha().getAnio()==2023 && obj.getEstado()==true)
        {
            v[obj.getNumeroEmpleado()-1]+=obj.getTiempo();
        }
    }
}
void puntoB()
{
    ArchivoEmpleado archiE("empleados.dat");
    ArchivoPuntoB archiB("puntob.dat");
    int tiempoEmpleados[60]= {};
    Empleado obj;
    puntoB aux;

    calcularHoras(tiempoEmpleados);

    int cantReg= archiE.contarRegistros();
    for(int i=0; i<cantReg; i++)
    {
        obj=archiE.leerRegistro(i);
        aux.obj; //sobrecargar el = para que copie el codigo y el nombre
        aux.setCantidadHoras(tiempoEmpleados[obj.getNumeroEmpleado()-1]);
        archiB.agregarRegistro(aux);
    }
}

void calcularMostrarTareas(int numeroEmpleado)
{
    ArchivoTarea archiT;
    int vCategorias[5]= {};
    Tarea obj;

    int tamReg=archiT.contarRegistros();
    for (int i=0; i<tamReg; i++)
    {
        obj=archiT.leerRegistro(i);
        if(obj.getEmpleado()==numeroEmpleado && obj.getEstado())
        {
            vCategorias[obj.getCategoria()-1]++;
        }
    }
    mostrarVector(vCategorias,5);
}

void puntoC()
{
    ArchivoEmpleado archiE("empleados.dat");
    Empleado obj;

    int cantReg= archiE.contarRegistros();
    for(int i=0; i<cantReg; i++)
    {
        obj= archiE.leerRegistro(i);
        cout<<"Empleado: "<< obj.getNombre()<<endl;
        calcularMostrarTareas(obj.getNumeroEmpleado());
    }

}

//punto c con matriz
void contarTareas(int m[60][5])
{
    ArchivoTarea archiT;
    Tarea obj;
    int tamReg= archiT.contarRegistros();
    for (int i=0; i<tamReg; i++)
    {
        obj=archiT.leerRegistro(i);
        if(obj.getEstado())
        {
            m[obj.getNumerEmpledo()-1][obj.getCategoria()-]++;
        }
    }
}

void mostrarTareas(int ne, int m[60][5])
{
    for (int i=0; i<5; i++)
    {
        cout<<"Categoria"<<i+1<<endl;
        cout <<"Cantidad" << m[ne-1]<<endl;
    }
}

void puntoCconMatriz()
{
    int mEmpleadosTareas[60][5]= {};
    contarTareas(mEmpleadoTareas);
    ArchivoEmpleado archiE("empleados.dat");
    Empleado obj;
    int cantReg=archiE.contarRegistros();
    for (int i=0; i<cantReg; i++)
    {
        obj.archiE.leerRegistro(i);
        cout<<"Empleado " << obj.getNombre()<<endl;
        mostrarTareas(ne, mEmpleadosTareas);
    };

}
void puntoD()
{
}
void puntoE()
{
}
bool modificarComponentes(Componentes comp, int pos)
{
}
void puntoF()
{
    CpuntoA reg;
    int tam = contarRegistrosPA();
    int* pa = new int [tam];
    /*lectura y mostrar*/

    delete[]pA;
}

int contarRegistrosPA()
{
    FILE *p;
    p=fopen(nombre, "rb");
    if(p==NULL) return -1;
    fseek(p, 0,2);
    int tam = ftell(p);
    fclose(p);
    return tam/sizeof(CpuntoA);
}

int main ()
{
    setlocale(LC_ALL, "");
    puntoA();
    puntoB();
    puntoC();
    puntoD();
    puntoE();

    return 0;
}


