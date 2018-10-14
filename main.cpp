/*
	Archivo: main.cpp
*/

#include "main.h"


using namespace std;

/******************************* Elementos globales ***********************************/

static option_t options[] = {
								{1, "d", "data", "-", opt_data, OPT_DEFAULT},
								{1, "i", "input", "-", opt_input, OPT_DEFAULT},
								{1, "o", "output", "-", opt_output, OPT_DEFAULT},
								{0, }
							};

static istream *dss = 0;	// Data Stream (clase para manejo de los flujos de entrada)
static istream *iss = 0;	// Input Stream (clase para manejo de los flujos de entrada)
static ostream *oss = 0;	// Output Stream (clase para manejo de los flujos de salida)
static fstream ifs; 
static fstream dfs; 		// Input File Stream (derivada de la clase ifstream que deriva de istream para el manejo de archivos)
static fstream ofs;		// Output File Stream (derivada de la clase ofstream que deriva de ostream para el manejo de archivos

/**************************************************************************************/

int main(int argc, char * const argv[])
{
    cmdline cmdl(options);	// Objeto con parametro tipo option_t (struct) declarado globalmente. Ver l�nea 51 main.cc
	cmdl.parse(argc, argv); // Método de parseo de la clase cmdline.
	
		
	RedSensores rs(*dss);
	
	rs.LecturaQuerys(*iss);

	rs.ProcesamientoQuerys(*oss);
	
	//pruebas desde aca
	Array<double> arreglo;

	for(double i=0; i<5;i++)
	{
		arreglo.Append(i+1);
	}
	
	SegmentTree st(arreglo);
	
	Array<Data> arregloDatasUtiles;
	Data d;

	st.BuscoIntervaloDeData(arregloDatasUtiles, 0, 7, 3, 7);
	d.Distinto(arregloDatasUtiles);

	/*

	for(int i=0; i<st.Datos.UsedSize();i++){
		cout<<"Min: "<<st.Datos[i].Min<<endl;
	}
	cout<<endl;
	for(int i=0; i<st.Datos.UsedSize();i++){
		cout<<"Max: "<<st.Datos[i].Max<<endl;
	}
	cout<<endl;
	for(int i=0; i<st.Datos.UsedSize();i++){
		cout<<"CantidadDatos: "<<st.Datos[i].CantidadDatos<<endl;
	}
	cout<<endl;
	
	for(int i=0; i<st.Datos.UsedSize();i++){
		cout<<"First: "<<st.Datos[i].GetFirst()<<endl;
	}
	cout<<endl;
	for(int i=0; i<st.Datos.UsedSize();i++){
		cout<<"Last: "<<st.Datos[i].GetLast()<<endl;
	}

	cout<<endl;
	*/
	
	for(int i=0; i<arregloDatasUtiles.UsedSize();i++)
	{
		cout<<"Minimo: "<<arregloDatasUtiles[i].GetMin()<<endl;
		cout<<"Maximo: "<<arregloDatasUtiles[i].GetMax()<<endl;
		cout<<"#Datos: "<<arregloDatasUtiles[i].GetCantidadDatos()<<endl;
	}

	//cout<<"Minimo: "<<d.GetMin()<<endl;
	//cout<<"Maximo: "<<d.GetMax()<<endl;
	//cout<<"#Datos: "<<d.GetCantidadDatos()<<endl;
	
	//hasta aca


	
    return 0;
}

static void opt_data(string const &arg)
{
	// Si el nombre del archivos es "-", usaremos la entrada
	// estandar. De lo contrario, abrimos un archivo en modo
	// de lectura.
	//
	if (arg == "-") {
		dss = &cin;		// Establezco la entrada estandar cin como flujo de entrada
	}
	else {
		dfs.open(arg.c_str(), ios::in); // c_str(): Returns a pointer to an array that contains a null-terminated
										// sequence of characters (i.e., a C-string) representing
										// the current value of the string object.
		dss = &dfs;
	}

	// Verificamos que el stream este OK.
	//
	if (!dss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
}

static void opt_input(string const &arg)
{
	// Si el nombre del archivos es "-", usaremos la entrada
	// est�ndar. De lo contrario, abrimos un archivo en modo
	// de lectura.
	//
	if (arg == "-") {
		iss = &cin;		// Establezco la entrada estandar cin como flujo de entrada
	}
	else {
		ifs.open(arg.c_str(), ios::in); // c_str(): Returns a pointer to an array that contains a null-terminated
										// sequence of characters (i.e., a C-string) representing
										// the current value of the string object.
		iss = &ifs;
	}

	// Verificamos que el stream este OK.
	//
	if (!iss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
}

static void opt_output(string const &arg)
{
	// Si el nombre del archivos es "-", usaremos la salida
	// est�ndar. De lo contrario, abrimos un archivo en modo
	// de escritura.
	//
	if (arg == "-") {
		oss = &cout;	// Establezco la salida estandar cout como flujo de salida
	} else {
		ofs.open(arg.c_str(), ios::out);
		oss = &ofs;
	}

	// Verificamos que el stream este OK.
	//
	if (!oss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);		// EXIT: Terminaci�n del programa en su totalidad
	}
}