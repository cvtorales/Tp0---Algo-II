#include "RedSensores.h"
#define DELIMITER ","


using namespace std;

RedSensores::RedSensores()
{

}


RedSensores::~RedSensores()
{
   //this-> Sensores.~Array();
}

RedSensores::RedSensores(istream& dss)
{
	string str, str_sensor;
	int i=0, j=0, delimiter_pos = 0;
	int initial_pos=0, final_pos=0, sensors_quantity=0;
	Array<Sensor> sensores;
	
	Array<double> datos;



	double number;



 // Lectura y procesamiento de la primer linea (que contiene a los nombres de los sensores).
 // Como son elementos separados por un delimitador, se decidio ubicar al delimitador para 
 // obtener los nombres de cada sensor. En particular, para el ultimo nombre, se realizo una 
 // comparacion con '\0' para poder obtenerlo.

	getline(dss, str);

	for(i=0; str[i] != '\0'; i++)
	{	
		if(str[i]==',' || str[i+1] == '\0')  // Para el ultimo nombre se compara con '\0'
		{
			Sensor s;

			if(str[i+1] == '\0')
			{
				delimiter_pos = i+1;   // Caso en que encuentra el ultimo nombre
			}else
			{
				delimiter_pos =i;      // Caso en que encuentra el nombre por medio del delimitador
			}

			cout<<"initial_pos: "<<initial_pos<<endl;
			cout<<"i: "<<delimiter_pos<<endl;
			cout<<"nombre: "<<str.substr(initial_pos, delimiter_pos - initial_pos)<<endl;

			s.SetName(str.substr(initial_pos, delimiter_pos - initial_pos));
	
			cout<<"nombre sensor: "<<s.GetName()<<endl;
			sensores.Append(s);
			cout<<"v[0]: "<<sensores[sensors_quantity].GetName()<<endl;
			sensors_quantity++;
			//cout<<"sensors_quantity: "<<sensors_quantity<<endl;
			initial_pos=i+1;
		}		
	}


// Lectura y procesamiento de los datos correspondientes a cada sensor, tener en cuenta 
// que en cada linea se encuentran las posiciones de las columnas y la fila es constante
// Se carga una fila a medida que se lee una linea.

	for(i=0 ; !dss.eof() ; i++)     // Con este ciclo for se recorre cada fila
	{          
	      getline(dss, str);   // Con esto leemos cada linea y la asignamos a cadena
	      initial_pos = 0;
	      final_pos = 0;
	      j = 0;

	      cout << "*************** Leo una linea ****************"<< endl;

	      while( j < sensors_quantity )  // con este ciclo recorro cada sensor con la misma fila 
	      {
			  	//cout<<"initial_pos: "<<initial_pos<<endl;
	      		if(j != (sensors_quantity - 1))
	      		{	
		            final_pos = str.find(",", initial_pos) - initial_pos;
		        }else
		        {
		         	final_pos = str.length() - initial_pos;
		        }
	            cout<<"final_pos: "<<final_pos<<endl;
				str_sensor = str.substr(initial_pos, final_pos);
				cout<< str_sensor <<endl;
				// number = str_sensor.stod(str_sensor, &sz);
				istringstream(str_sensor) >> number;
				cout<<"jota: "<<j<<endl;
				sensores[j].SetElementAt(number);
				//datos.Append(number);
	            //cout<<"datos["<<j<<"]: "<<datos[j]<<endl;
	            initial_pos += final_pos+1;
				cout<<initial_pos<<endl << endl;
	            // convertir a str_sensor a double
	            //sensores[j].SetData(datos);
	            j++;


	      }
	}

	Sensores = sensores;
	cout<<"El elemento 1 del sensor 1 es: "<<sensores[1].GetElementAt(3)<<endl;

}


void RedSensores::LecturaQuerys(istream& iss)
{
	int i = 0;
	string str;


	for(i=0 ; !iss.eof() ; i++)     // Con este ciclo for se recorre cada fila
	{   
		getline(iss, str);
	    Query* q = new Query(str);   // Inicializo una Query por linea
	    this->Querys.Append(*q);
	}

}

Query RedSensores::ObtieneQuery(int pos)
{
	return Querys[pos];
}

void RedSensores::ProcesamientoQuerys(ostream& oss)
{
	int i=0;
	double promedio=0.0, max=0.0, min=0.0;

	
	for(i = 0; i < Querys.UsedSize() ; i++)
	{
		EjecutoQuery(Querys[i], oss ,promedio, max, min);
	}
}


//RECORDAR HACER STATUS_T
void RedSensores::EjecutoQuery(Query q, ostream& oss , double& promedio, double& max, double& min)
{
	int i = 0, j=0;

	
	for(i=0; i<q.GetSensorsNameQuantity(); i++)
	{
		for(j=0; j<Sensores.UsedSize(); j++)
		{
			
			if(q.GetSensorNameAt(i) == Sensores[j].GetName())
			{

				max = Maximo(Sensores[j].GetData());
				min = Minimo(Sensores[j].GetData());

				oss<<max<<","<<min<<endl;

			}	
		}
		
	}
}

double RedSensores::Maximo(Array<double>& valores) const
{
	int i=0;
	double maximo=0;
	

	for(i=0; i<valores.UsedSize(); i++)
	{
		if(maximo < valores[i])
		{
			maximo = valores[i];
		}
	}

	return maximo;	
}

double RedSensores::Minimo(Array<double>& valores) const
{
	int i=0;
	double minimo = valores[0];
	
	for(i=0; i<valores.UsedSize(); i++)
	{
		if(minimo > valores[i])
		{
			minimo = valores[i];
		}
	}

	return minimo;
}