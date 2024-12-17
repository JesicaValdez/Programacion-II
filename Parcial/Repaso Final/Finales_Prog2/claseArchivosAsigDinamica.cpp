/*Nombre: Jesica Valdez
*/

#include <iostream>
#include <locale>
#include <cstring>

using namespace std;

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

void cargarVector(int *v, int tam)
{
    for (int i=0; i<tam; i++)
    {
        cout<<"Ingrese: #";
        cin>>v[i];
    }
}

void mostrarVector(int *v, int tam)
{
    for (int i=0; i<tam; i++)
    {
        cout<<v[i]<<endl;
    }
}

int contarPares(int *v, int tam)
{
    int i, cant=0;
    for (i=0; i<tam; i++)
    {
        if(v[i]%2==0)cant++;
    }
    return cant;
}
void copiarParesImpares(int *vDestino, int *vOrigen, int tam, int resto)
{
    int i, j=0;
    for(i=0; i<tam; i++)
    {
        if(vOrigen[i]%2==resto)
        {
            vDestino[j++]=vOrigen[i];
        }
    }
}

int main ()
{
    setlocale(LC_ALL, "");

    int *v, *vPares, *vImpares;
    int tam;

    cout<<"Ingrese la cantidad de elementos que necesita para el vector";
    cin>>tam;

//pedimos memoria del mismo tipo de dato
    v=new int [tam];
    if(v==NULL)
    {
        cout<<"Error de asignacion de memoria"<<endl;
        return -1;
    }
//si llego aca nos dieron memoria entonces ejecutamos las tareas:

    cargarVector(v,tam);
    int pares = contarPares(v,tam);
    if(pares>0)
    {
        vPares= new int[pares];
        if(vPares==NULL)
        {
            cout<<"Error de asignacion de memoria"<<endl;
            return -1;
        }
        copiarParesImpares(vPares, v, tam,0);
    }
    else
    {
        cout<<"No hay pares. No se construyo el vector"<<endl;
    }

    int impares = tam-pares;
    if(impares>0)
    {
        vImpares= new int[impares];
        if(vImpares==NULL)
        {
            cout<<"Error de asignacion de memoria"<<endl;
            return -1;
        }
        copiarParesImpares(vImpares, v, tam,1);
    }
    else
    {
        cout<<"No hay impares. No se construyo el vector"<<endl;
    }

    delete v;
    if(pares>0)
    {
        cout<<"Vector de PARES"<<endl;
        mostrarVector(vPares, pares);
        cout<<endl<<endl;
    }
    if(impares>0)
    {
        cout<<"Vector de IMPARES"<<endl;
        mostrarVector(vImpares, impares);
    }

    cout<<endl;
    system("pause");
    delete vPares;
    delete vImpares;

    return 0;
}


