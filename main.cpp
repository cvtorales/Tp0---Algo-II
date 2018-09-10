#include "main.h"


using namespace std;


/**************** Elementos globales ******************/

static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{0, },
};

static istream *iss = 0;	// Input Stream (clase para manejo de los flujos de entrada)
static ostream *oss = 0;	// Output Stream (clase para manejo de los flujos de salida)
static fstream ifs; 		// Input File Stream (derivada de la clase ifstream que deriva de istream para el manejo de archivos)
static fstream ofs;		// Output File Stream (derivada de la clase ofstream que deriva de ostream para el manejo de archivos)

static void
opt_input(string const &arg)
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

static void
opt_output(string const &arg)
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

int main(int argc, char * const argv[])
{
    cmdline cmdl(options);	// Objeto con parametro tipo option_t (struct) declarado globalmente. Ver l�nea 51 main.cc
	cmdl.parse(argc, argv); // Método de parseo de la clase cmdline
	string str, str_sensor;
	int i=0,j=0;
	int initial_pos=0, final_pos=0, sensors_quantity=0;
	Array<Sensor> sensores;
	Sensor s;
	Array<double> datos;
	size_t sz;

	getline(*iss, str);
	//cout<<"str: "<<str<<endl;
	for(i=0; str[i] != '\n'; i++){
		if(str[i]==','){
			cout<<"initial_pos: "<<initial_pos<<endl;
			cout<<"i: "<<i<<endl;
			cout<<"nombre: "<<str.substr(initial_pos, i - initial_pos)<<endl;
			s.SetName(str.substr(initial_pos, i - initial_pos));
			cout<<"nombre sensor: "<<s.GetName()<<endl;
			sensores.Append(s);
			sensors_quantity++;
			//cout<<"sensors_quantity: "<<sensors_quantity<<endl;
			initial_pos=i+1;
		}
		
	}
	cout<<"nombre: "<<str.substr(initial_pos, str.length())<<endl;
	sensors_quantity++;
	cout<<"sensors_quantity: "<<sensors_quantity<<endl;
	cout<<"v[0]: "<<sensores[0].GetName()<<endl;
for(i=0 ; !iss->eof() ; i++)     // con este for recorro cada fila
{          
          getline(*iss, str);   // Con esto leemos cada linea y la asignamos a cadena
          initial_pos = 0;
          final_pos = 0;
          
		  //cout<<"str: "<<str<<endl;
          while( j < sensors_quantity ) // con este for recorro cada sensor con la misma fila 
          {
			  	//cout<<"initial_pos: "<<initial_pos<<endl;
                final_pos = str.find(",", initial_pos) - initial_pos;
                //cout<<"final_pos: "<<final_pos<<endl;
				str_sensor = str.substr(initial_pos, final_pos);
				datos.Append(stod (str_sensor,&sz));
                cout<<"datos["<<j<<"]: "<<datos[j]<<endl;
                initial_pos += final_pos+1;
				//cout<<str_sensor<<endl;
                // convertir a str_sensor a double
                j++;
          }

}




    return 0;
}

