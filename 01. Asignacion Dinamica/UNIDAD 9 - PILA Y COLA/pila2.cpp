//Ejercicio:
//Autor:
//Fecha:
//Comentario



#include <iostream>

using namespace std;



class Articulo
	{
	private:
		char codart[5];
		char desc[30];
		float pu;
		int stock;
		int activo;
	public:

		Articulo(char *, char *, float, int);
		Articulo(float, int);
		Articulo(int, float);
		void Cargar();
		void Mostrar();
		char * getCodart(){return codart;};
		char * getDesc(){return desc;};
		float getPu(){return pu;};
		int getStock(){return stock;};
		int getActivo(){return activo;};
		void setCodart(char *c){strcpy(codart,c);};
		void setDesc(char *d){strcpy(desc,d);};
		void setPu(float p){pu=p;};
		void SetStock(int s){stock+=s;};
		void setActivo(int s){activo=s;};
		void Grabar_en_disco(void);
		int Leer_de_disco(int);
		void Modificar_en_disco(int);
		friend ostream & operator <<(ostream &, Articulo &);
		friend istream & operator >>(istream &, Articulo &);
		};
//****************
//desarrollo de los metodos
Articulo::Articulo(char *c="nada", char *d="nada", float p=0.0, int s=0)
  {
    strcpy(codart,c);
    strcpy(desc,d);
    pu=p;
    stock=s;
    }

Articulo::Articulo(float p, int s=0)
  {
    pu=p;
    stock=s;
    }

Articulo::Articulo(int s, float p=0.0)
  {
    stock=s;
    pu=p;
    }

void Articulo::Cargar()
	{
	int encontro=-1;
	cout<<"Ingrese el codigo: ";
	cin>>codart;
	//encontro=buscar_art(codart);
	if(encontro==-1)
	{
    cout<<"Ingrese la descripcion:  ";
    cin>>desc;
    cout<<"Ingrese el precio:  ";
    cin>>pu;
    cout<<"Ingrese el sotck:  ";
    cin>>stock;
    activo=1;
	}
	else
	{
	  cout<<"Ya existe ese c�digo";
	  cout<<"Presione una tecla para continuar";
	  system("pause>null");

	  }
	}

void Articulo::Mostrar()
	{
	cout<<"Codigo: ";
	cout<<codart<<endl;
	cout<<"Descripcion: ";
	cout<<desc<<endl;
	cout<<"Precio: ";
	cout<<pu<<endl;
	cout<<"Stock: ";
	cout<<stock<<endl;
	}

void Articulo::Grabar_en_disco(void)
	{
	FILE *p;
	p=fopen("articulo.dat","ab");
	if(p==NULL){cout<<"Error de archivo";exit(1);}
	fwrite(this,sizeof *this,1,p);
	fclose(p);
	}

int Articulo::Leer_de_disco(int pos)
	{
	int x;
	FILE *p;
	p=fopen("articulo.dat","rb");
	if(p==NULL)
		{
		cout<<"No existe el archivo";
		cout<<"Presione una tecla para continuar";
    system("pause<null");
		return 0;
		}
	fseek(p,pos*sizeof *this,0);
	x=fread(this,sizeof *this,1,p);
	fclose(p);
	return x;
	}

void Articulo::Modificar_en_disco(int pos)
	{
	FILE *p;
	p=fopen("articulo.dat","rb+");
	if(p==NULL){cout<<"Error de archivo";exit(1);}
	fseek(p,pos*sizeof *this,0);
	fwrite(this,sizeof *this,1,p);
	fclose(p);
	}

//FUNCIONES AMIGAS
ostream & operator <<(ostream &salida, Articulo &obj)
{
  cout<<"Codigo: ";
	salida<<obj.codart<<endl;
	cout<<"Descripcion: ";
	salida<<obj.desc<<endl;
	cout<<"Precio: ";
	salida<<obj.pu<<endl;
	cout<<"Stock: ";
	salida<<obj.stock<<endl;
  return salida;
  }

istream & operator >>(istream &entrada, Articulo &obj)
{
  cout<<"Ingrese el codigo: ";
	entrada>>obj.codart;
	cout<<"Ingrese la descripcion: ";
	entrada>>obj.desc;
	cout<<"Ingrese el precio: ";
	entrada>>obj.pu;
	cout<<"Ingrese el Stock: ";
	entrada>>obj.stock;
	cout<<endl;
  return entrada;
  }

typedef Articulo tipo;// la Pila est� pensada para poder ser utilizada como pila de cualquier
                      //tipo de datos. Basta definir con un typedef el tipo de datos del cual tipo va a ser el alias.
class Pila
	{
	private:
    tipo *p;
		int tope, tam;
	public:
		Pila (int);
		void Agregar(tipo);
		tipo Sacar( );
		void Mostrar( );
		~Pila( );
	};

Pila::Pila (int cant=1)
	{
	tam=cant;
	tope=0;
	p=new tipo[tam];
	if (p==NULL) exit(1);
	}

void Pila::Agregar(tipo aux)
	{
	if(tope==tam)
		cout<<"Pila llena";
	else
		{
		p[tope]=aux;
		tope++;
		}
	}

tipo Pila::Sacar( )
	{
	tipo x;
	if(tope== 0)
		{
		cout<<"Pila vac�a";
		return x;
		}
	else
		{
tope--;
return p[tope];
	}
	}

void Pila::Mostrar( )
	{
	for(int i=tope-1;i>=0;i--)
		cout<<p[i];
	}

Pila::~Pila( ) {delete p;};

int main( )
	{
	Pila a(2);
	int i;
	tipo info,x;
	for(i=0;i<2;i++)
		{
    cin>>info;
    a.Agregar(info);
}
	for(i=0;i<2;i++)
		{
		x=a.Sacar();
		cout<<"Elemento que se saca: "<<i+1<<endl;
		cout<<"Valor: "<<x<<endl;

		system("pause");
		}
	return 0 ;
	}

