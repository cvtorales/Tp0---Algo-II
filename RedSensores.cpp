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
				cout<<"str_sensor: " <<str_sensor <<endl;
				// number = str_sensor.stod(str_sensor, &sz);
				if(!str_sensor.empty())
				{
					istringstream(str_sensor) >> number;	
					sensores[j].SetElementAt(number);
				}
				
				cout<<"number: "<<number<<endl;
				cout<<"jota: "<<j<<endl;
				
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
	cout<<"El elemento 5 del sensor 0 es: "<<sensores[0].GetElementAt(2)<<endl;
	cout<<"El nombre del sensor 3 es: "<<sensores[3].GetName()<<endl;
}


void RedSensores::LecturaQuerys(istream& iss)
{
	int i = 0;
	string str;


	for(i=0 ; !iss.eof() ; i++)      // Con este ciclo for se recorre cada fila
	{   
		getline(iss, str);
	    Query* q = new Query(str);   // Inicializo una Query por linea
	    this->Querys.Append(*q);     // Agrego un query como ultimo elemento del vector
	}

}

Query RedSensores::ObtieneQuery(int pos)
{
	//validar
	return Querys[pos];
}

void RedSensores::ProcesamientoQuerys(ostream& oss)
{
	int i=0;
	
	for(i = 0; i < Querys.UsedSize() ; i++)
	{
		EjecutoQuery(Querys[i],Querys[i].GetSensorsNameQuantity(), Sensores.UsedSize() ,oss);	//pasar cantidad de sensores y cantidad de nombres de sensores
	}
}


//RECORDAR HACER STATUS_T
void RedSensores::EjecutoQuery(Query q, int cantNombresSensores , int cantidadSensores, ostream& oss)
{
	int i=0, j=0, k=0; 
	int tb = 0;    // Esta variable cuenta la cantidad de coincidencias entre nombres de sensores.

	int InitRange = q.GetInitRange();
	int FinalRange = q.GetFinalRange();
	
	for(i=0; i<cantNombresSensores; i++)    // Por si en el query hay mas de un sensor
	{
		for(j=0; j<cantidadSensores; j++)
		{
			string query_name = q.GetSensorNameAt(i);

			cout << "---------ggg" << query_name << endl;
			cout << ".........!!!!!" << Sensores[j].GetName() << endl;
			
			if( query_name == "-")
			{
				cout << "Emtro al caso en que tiene el guion, es decir consulta por todos"<< endl;
				query_name = Sensores[j].GetName();
			}

			cout << "nombre de queeeeeeeeeeerryy: " << query_name << endl;
			if( query_name == Sensores[j].GetName())   // Se compara por nombre del sensor
			{
				tb++;
				Array<double> datos;
				cout<<"tamaño de Sensores: "<<Sensores[j].GetData().UsedSize()<<endl;
				cout<<"tamaño del arreglo datos:"<<datos.UsedSize()<<endl;

				if (Sensores[j].ValidarRango(InitRange, FinalRange))  // Si esta dentro del rango
				{
					for( k = InitRange; k < FinalRange; k++)
					{
						cout<<"k: "<<k<<endl;
						cout<<"Sensores[j].GetData()[k]: "<<Sensores[j].GetData()[k]<<endl;
						datos += Sensores[j].GetData()[k];
						cout<<"tamaño del arreglo datos:"<<datos.UsedSize()<<endl;
					}

					oss<<datos.Maximo()<<","<<datos.Minimo()<<","<<datos.Promedio()<<endl;
				}
				else{
					oss<<"NO DATA"<<endl;
				}

			}

		}

		cout << "termino con un sensor " <<endl;
		

				if(tb == 0 )
				{
					oss << "UNKNOW ID" << endl;
				}

	}


}

