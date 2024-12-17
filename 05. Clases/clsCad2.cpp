///Ejercicio:
///Autor:DEK
///Fecha:
///Comentario:

# include<iostream>
# include<cstdlib>
# include<cstring>

using namespace std;

///la clase Cadena tiene que servir para manejar cadenas de caracteres.
///El vector de char que contenga la cadena de caracteres debe ajustar su tamaño a lo estrictamente necesario.


class Cadena{
private:
    char *cad;
    int tam;
public:
    Cadena(const char *valorIni){
        tam=strlen(valorIni)+1;
        cad=new char[tam];
        if(cad==NULL)exit(1);
        strcpy(cad,valorIni);
        cad[tam-1]='\0';
    }
    void Mostrar(){
        cout<<cad<<endl;
    }
    ~Cadena(){
        delete []cad;
    }
    int getTam(){return tam;}
    char getCaracter(int pos){
        ///ver que habría que hacer para validar esta
        return cad[pos];
    }
    void aMayuscula(int cuantas=2){
        int i;
        if(cuantas==1){
                if(cad[0]!= 32) cad[0]-=32;
        }
        else{
            for(i=0;i<tam-1;i++){
                if(cad[i] != 32)cad[i]-=32;
            }
        }
    }
    bool operator ==(const Cadena &obj){
       if(strcmp(cad, obj.cad)==0) return true;
       return false;
    }
    bool operator ==(unsigned int caracteres){
       if(strlen(cad)==caracteres) return true;
       return false;
    }
    void operator=(Cadena obj){
        ///cad->quiero asignar lo que contiene obj.cad

        delete cad;
        tam=obj.tam;
        cad=new char[tam];
        if(cad==NULL) exit(1);
        strcpy(cad, obj.cad);
        cad[tam-1]='\0';
    }

    void operator = (const char * caracteres){
        delete cad;
        int tam = strlen(caracteres)+1;
        cad = new char[tam];
        if(cad == NULL) exit(1);
        strcpy(cad, caracteres);
        cad[tam-1] = '\0';
    }

    bool operator>(Cadena obj){
        int tamLocal = strlen(cad);
        int tamExternal = obj.tam;
        int tamFinal;

        if(tamLocal > tamExternal){
            tamFinal = tamExternal;
        }
        else{
            tamFinal = tamLocal;
        }

        for(int i=0; i<tamFinal; i++){
            if(strcmp(cad[i],obj.cad[i])!=0{
                if(cad[i]>obj.cad[i]){
                    return true;
                }
            }
        }
        return false;
    }

};


///Sobrecargar el operador = para que se asigne de manera directa un vector de caracteres a un objeto cadena
///Sobrecargar el operador > para comparar 2 objetos Cadena. Debe devolver true si el objeto que llama contiene
/// una cadena "mayor" a la del objeto que se recibe como parámetro (orden lexicográfico: posición en el diccionario; más grande
/// es el que está más cerca del final del diccionario)


void main(){

    //Cadena palabra("Hola");//, otra("Chau");
    //palabra=otra;
    //otra="Hallo!";
    //char caracteres[30];
    //cin.getline(caracteres, 30);
    //if(palabra>caracteres){
    //    cout << endl << "PALABRA ES MAYOR";
    //    system("pause");
    //}
    //palabra = caracteres;
    //palabra.Mostrar();
    //palabra.Mostrar();
    //if(palabra==otra){
    /////if(palabra.operator==(otra)){
    //    cout<<"SON IGUALES";
    //}
    //else{
    //    cout<<"SON DISTINTAS";
    //}
    //cout<<endl<<endl;
    //if(palabra==4){///comparar con un número para saber si la cantidad de caracteres es igual a ese número
    //    cout<<"EL OBJETO TIENE 4 CARACTERES";
    //}
    //else{
    //    cout<<"EL OBJETO NO TIENE 4 CARACTERES";
    //}
	//cout<<endl<<endl;


	//system("pause");
	return 0;
}
