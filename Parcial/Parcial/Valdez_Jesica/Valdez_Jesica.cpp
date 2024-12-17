
# include<iostream>
# include<cstdlib>
# include<cstring>

using namespace std;

void cargarCadena(char* pal, int tam) {
    int i;
	
    fflush(stdin);
    for (i = 0; i < tam; i++) {
        pal[i] = cin.get();
		if (pal[i] == '\n') break;
    }
    pal[i] = '\0';
    fflush(stdin);
}

///Pregunta 1: Calcular e informar la cantidad de habitantes por cada nivel de ingresos.
class Paises{
private:
	char codigo[5];
	char nombre[30];
	int codigoContinente;
	int nivelIngreso;
	int cantHabitantes;
	float PBI;
	bool estado;
public:

	void setCodigo(const char *c) {
		strcpy(codigo, c);
	}
	void setNombre(const char *n) {
		strcpy(nombre, n);
	}
	void setCodigoContinente(int _codigoContinente) {
		codigoContinente = _codigoContinente;
	}
	void setNivelIngreso(int _nivelIngreso) {
		nivelIngreso = _nivelIngreso;
	}
	void setCantHabitantes(int _cantHabitantes) {
		cantHabitantes = _cantHabitantes;
	}
	void setPBI(float _PBI) {
		PBI = _PBI;
	}
	void setEstado(bool _estado) {
		estado = _estado;
	}
	char* getCodigo() {
		return codigo;
	}
	char* getNombre() {
		return nombre;
	}
	int getCodigoContinente() {
		return codigoContinente;
	}
	int getNivelIngreso() {
		return nivelIngreso;
	}
	int getCantHabitantes() {
		return cantHabitantes;
	}
	float getPBI() {
		return PBI;
	}
	bool getEstado() {
		return estado;
	}

    void mostrar() {
        cout << "Codigo: " << codigo << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Codigo de Continente: " << codigoContinente << endl;
        cout << "Nivel de Ingreso: " << nivelIngreso << endl;
        cout << "Cantidad de Habitantes: " << cantHabitantes << endl;
        cout << "PBI: " << PBI << endl;
        cout << "Estado: " << estado << endl;
    }

};

class ArchivoPaises{
private:
    char nombre[30];
public:
    ArchivoPaises(const char* n) {
        strcpy(nombre, n);
    }
    Paises leerRegistro(int pos) {
        Paises reg;
        reg.setEstado(false);
        FILE* p;
        p = fopen(nombre, "rb");
        if (p == NULL) return reg;
        fseek(p, sizeof reg * pos, 0);
        fread(&reg, sizeof reg, 1, p);
        fclose(p);
        return reg;
    }
    int contarRegistros() {
        FILE* p;
        p = fopen(nombre, "rb");
        if (p == NULL) return -1;
        fseek(p, 0, 2);
        int tam = ftell(p);
        fclose(p);
        return tam / sizeof(Paises);
    }
    bool grabarRegistro(Paises reg) {
        FILE* p;
        p = fopen(nombre, "ab");
        if (p == NULL) return false;
        int escribio = fwrite(&reg, sizeof reg, 1, p);
        fclose(p);
        return escribio;
    }
};

class Continentes {
private:
	int codigoContinente;
	char nombre[30];
public:
	void setCodigoContinente(int _codigoContinente) {
		codigoContinente = _codigoContinente;
	}
	/// aca hice mal
	/*
	void setNombre(char _nombre[30]) {
		strcpy(nombre, _nombre);
	}
	*/
	//corregido
	void setNombre(const char *n) {
		strcpy(nombre, n);
	}
	int getCodigoContinente() {
		return codigoContinente;
	}
	char* getNombre() {
		return nombre;
	}
	void mostrar() {
		cout << "Codigo de Continente: " << codigoContinente << endl;
		cout << "Nombre: " << nombre << endl;
	}
	/*
	bool operator ==(Continentes c1, Continentes c2) {
		if (c1.getCodigoContinente() < c2.getCodigoContinente()) {
			return true;
		}
		return false;
	 }
	*/

};

class ArchivoContinentes {
private:
	char nombre[30];
public:
	ArchivoContinentes(const char* n) {
		strcpy(nombre, n);
	}
	Continentes leerRegistro(int pos) {
		Continentes reg;
		reg.setCodigoContinente(0);
		FILE* p;
		p = fopen(nombre, "rb");
		if (p == NULL) return reg;
		fseek(p, sizeof reg * pos, 0);
		fread(&reg, sizeof reg, 1, p);
		fclose(p);
		return reg;
	}
	int contarRegistros() {
		FILE* p;
		p = fopen(nombre, "rb");
		if (p == NULL) return -1;
		fseek(p, 0, 2);
		int tam = ftell(p);
		fclose(p);
		return tam / sizeof(Continentes);
	}
	bool grabarRegistro(Continentes reg) {
		FILE* p;
		p = fopen(nombre, "ab");
		if (p == NULL) return false;
		int escribio = fwrite(&reg, sizeof reg, 1, p);
		fclose(p);
		return escribio;
	}

};

///Pregunta 1: Calcular e informar la cantidad de habitantes por cada nivel de ingresos.
void contarHabitantes(int hab) {
	ArchivoPaises archiP("paises.dat");
	Paises reg;
	int cantReg, cantHabitantes = 0;
	cantReg = archiP.contarRegistros();

	int vNivel[5] = {};
	for (int i = 0;i < cantReg;i++) {
		reg = archiP.leerRegistro(i);
		vNivel[reg.getNivelIngreso() - 1] += reg.getCantHabitantes();

	}
	for (int i = 0;i < 5;i++) {
		cout << "Nivel de Ingreso: " << i + 1 << " Cantidad de Habitantes: " << vNivel[i] << endl;
	}
}


///Pregunta 2: Generar un archivo con los continentes que tengan menos de 15 países que integran la OCDE. El formato debe ser el mismo que el del archivo de continentes
void punto2() {
	ArchivoPaises archiP("paises.dat");
	Paises reg;
	int cantReg, cantPaises = 0;
	cantReg = archiP.contarRegistros();

	ArchivoContinentes archiC("continentes.dat");
	Continentes regC;
	int cantRegC;
	cantRegC = archiC.contarRegistros();

	ArchivoContinentes archiC2("continentesMenos15.dat");
	Continentes regC2;
	 
	for (int i = 0;i < cantRegC;i++) {
		regC = archiC.leerRegistro(i);
		cantPaises = 0;

		for (int j = 0;j < cantReg;j++) {
			reg = archiP.leerRegistro(j);
			if (regC.getCodigoContinente() == reg.getCodigoContinente()) {
				cantPaises++;
			}
		}
		if (cantPaises < 15) {
			regC2.setCodigoContinente(regC.getCodigoContinente());
			regC2.setNombre(regC.getNombre());
			archiC2.grabarRegistro(regC2);
		}
		
	}
	
}

///Pregunta 3: Listar el archivo nuevo creado usando asignación dinámica de memoria
void punto3() {
	Continentes* vecContinentes;
	ArchivoContinentes archiC2("continentesMenos15.dat");
	Continentes regC2;
	int cantRegC2;
	cantRegC2 = archiC2.contarRegistros();

	if (cantRegC2 == 0) {
		cout << "No hay registros" << endl;
		return;

	}

	vecContinentes = new Continentes[cantRegC2];
	if (vecContinentes == NULL) {
		return;
	}

	for (int i = 0;i < cantRegC2;i++) {
		regC2 = archiC2.leerRegistro(i);
	}

	for (int i = 0;i < cantRegC2;i++) {
		vecContinentes[i].mostrar();
	}

	delete vecContinentes;

}

///Pregunta 4: Sobrecargar un operador para alguna de las clases de los ejercicios anteriores, que sea de utilidad para la resolución de alguno de esos puntos.
/*
bool operator==(Continentes c1, Continentes c2) {
	if (c1.getCodigoContinente() < c2.getCodigoContinente()) {
		return true;
	}
	return false;
}
*/



    int main() {
		

        cout << endl;
        system("pause");
        return 0;
    }