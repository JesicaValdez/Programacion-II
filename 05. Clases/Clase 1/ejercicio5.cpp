/*Nombre: Jesica Valdez
Enunciado:

*/

#include <iostream>
#include <locale>

using namespace std;


void cargarVector(int vec[10]);
bool encontrarNumero(int vec[10], int num);

int main(){
setlocale(LC_ALL, "");

const int TAM=10;
int vec[TAM]={};

cargarVector(vec);
if(encontrarNumero(vec, 13)){
    cout<<"true";
}else{
    cout<<"false";
}


cout<<endl;
system("pause");
return 0;
}

void cargarVector(int vec[10]){
    for(int i = 0; i < 10; i++){
        cout<<"Ingrese los numeros: ";
        cin>>vec[i];
    }
}
bool encontrarNumero(int vec[], int num){
    for(int i = 0; i < 10; i++){
        if(vec[i] == num){
            return true;
        }
    }
    return false;
}
