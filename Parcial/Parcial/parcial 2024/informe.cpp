///Nombre: Jesica Valdez


# include<iostream>
# include<cstdlib>
using namespace std;

#include<iomanip>///Deben incluir la biblioteca <iomanip>

int main(){
    string Sucursal="Beccar";
    int cantVentas=4;
    long precio = 2000000;
    int cantVentas2=16;



    cout << "       Version: Mensual    " << endl << endl;
    cout<<left;
    cout<<"Anio:    2024" << endl;
    cout<<"Mes:     Marzo"<< endl <<endl;
    cout<<setw(14)<<"Sucursal";
    cout<<setw(20)<<"Cantidad de Ventas";
    cout<<setw(12)<<"Recaudacion";
    cout<<endl<<"---------------------------------------------------------"<<endl;
    cout<<setw(20)<<Sucursal;
    cout<<setw(16)<<cantVentas;
    cout<<setw(0)<<"$"<<setw(2)<<precio<<endl;
    cout<<setw(20)<<"San Fernando";
    cout<<setw(16)<<"3";
    cout<<setw(0)<<"$"<<setw(2)<<precio<<endl;
    cout<<setw(20)<<"Tigre";
    cout<<setw(16)<<"2";
    cout<<setw(0)<<"$"<<setw(2)<<precio<<endl;
    cout<<setw(20)<<"Martinez";
    cout<<setw(16)<<"1";
    cout<<setw(0)<<"$"<<setw(2)<<precio<<endl;
	cout<<endl;
	cout<<setw(20)<<"Total";
	cout<<setw(16)<<"10";
	cout<<setw(0)<<"$"<<setw(2)<<8000000<<endl<<endl<<endl<<endl;



	cout << "       Version: Anual    " << endl << endl;
    cout<<left;
    cout<<"Anio:    2024" << endl<<endl<<endl;

    cout<<setw(14)<<"Sucursal";
    cout<<setw(20)<<"Cantidad de Ventas";
    cout<<setw(12)<<"Recaudacion";
    cout<<endl<<"---------------------------------------------------------"<<endl;
    cout<<setw(20)<<Sucursal;
    cout<<setw(16)<<cantVentas2;
    cout<<setw(0)<<"$"<<setw(2)<<precio<<endl;
    cout<<setw(20)<<"San Fernando";
    cout<<setw(16)<<"12";
    cout<<setw(0)<<"$"<<setw(2)<<precio<<endl;
    cout<<setw(20)<<"Tigre";
    cout<<setw(16)<<"10";
    cout<<setw(0)<<"$"<<setw(2)<<precio<<endl;
    cout<<setw(20)<<"Martinez";
    cout<<setw(16)<<"9";
    cout<<setw(0)<<"$"<<setw(2)<<precio<<endl;
	cout<<endl;
	cout<<setw(20)<<"Total";
	cout<<setw(16)<<"47";
	cout<<setw(0)<<"$"<<setw(2)<<8000000<<endl<<endl<<endl<<endl;




    system("pause");

	return 0;
}

