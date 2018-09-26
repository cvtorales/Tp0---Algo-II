#include "RedSensores.h"

RedSensores::RedSensores()
{

}

RedSensores::~RedSensores()
{

}

RedSensores::RedSensores(istream & dss)
{
	string str, str_sensor;
	int i=0, j=0, delimiter_pos = 0;
	int initial_pos = 0, final_pos = 0, sensors_quantity = 0;
	double number;
	Array<Sensor> sensores;
	Array<double> datos;

 // Lectura y procesamiento de la primer linea (que contiene a los nombres de los sensores).
 // Como son elementos separados por un delimitador, se decidio ubicar al delimitador para 
 // obtener los nombres de cada sensor. En particular, para el ultimo nombre, se realizo una 
 // comparacion con '\0' para poder obtenerlo.

	getline(dss, str);                       // Lectura de la primer linea.

	for(i=0; str[i] != '\0'; i++)
	{	
		if(str[i]==',' || str[i+1] == '\0')  // Para el ultimo nombre se compara con '\0'.
		{
			Sensor s;

			if(str[i+1] == '\0')
			{
				delimiter_pos = i+1;   // Caso en que encuentra el ultimo nombre.
			}else
			{	
				delimiter_pos =i;      // Caso en que encuentra el nombre por medio del delimitador.
			}

			s.SetName(str.substr(initial_pos, delimiter_pos - initial_pos));

			sensores.Append(s);        // Se agrega el nombre del sensor al vector de sensores. 

			sensors_quantity++;

			initial_pos=i+1;
		}		
	}

// Lectura y procesamiento de los datos correspondientes a cada sensor, tener en cuenta 
// que en cada linea se encuentran las posiciones de las columnas y la fila es constante.
// Se carga una fila para cada sensor a medida que se lee una linea.

	for(i=0 ; !dss.eof() ; i++)     // Se recorre cada fila.
	{          
	      getline(dss, str);        // Se lee cada linea y se asigna a la cadena str.
	      initial_pos = 0;
	      final_pos = 0;
	      j = 0;
	      double acum_row = 0;
	      int data_quantity = 0;

	      while( j < sensors_quantity )  
	      {

	      // Se buscan las posiciones del final de cada subcadena.	
	      		if(j != (sensors_quantity - 1))  
	      		{	
		            final_pos = str.find(",", initial_pos) - initial_pos;
		        }else
		        {
		         	final_pos = str.length() - initial_pos;  // Ultima posicion (no encuentra la coma).
		        }

				str_sensor = str.substr(initial_pos, final_pos);

				if(!str_sensor.empty())
				{
					data_quantity++;
					istringstream(str_sensor) >> number;	
					sensores[j].SetElementAt(number);
					acum_row = acum_row + number;   // Se acumula la suma de todos los sensores en una fila.

					if(j == (sensors_quantity - 1)) // Cuando termina sumar los valores.
					{
						// Se calcula el promedio de los sensores en una fila 
						// y se agrega a un vector de promedios (Average).  

						Average.Append(acum_row/data_quantity);  
					}

				}else{

					// Si no se encuentra ningun dato, se asigna una constante.
					istringstream(EMPTY_SPACE) >> number;
					sensores[j].SetElementAt(number);
				}
				
	            initial_pos += final_pos+1;
	            j++;
	      }
	}

	Sensores = sensores;

	for(int m=0; m<Average.UsedSize();m++)
	{
		cout<<"Average["<<m<<"]"<<Average[m]<<endl;
	}
}


void RedSensores::LecturaQuerys(istream & iss)
{
	int i = 0;
	string str;
	char c;

	for(i=0 ; !iss.eof() ; i++)      // Se recorre cada fila.
	{   
		if(iss>>c)
		{
			iss.putback(c);
			getline(iss, str);
		    Query q(str);           // Inicializo una Query por linea.
		    this->Querys.Append(q); // Agrego un query como ultimo elemento del vector.	
		}	
	}	
}

Query RedSensores::ObtieneQuery(int pos)
{
	return Querys[pos];
}

void RedSensores::ProcesamientoQuerys(ostream& oss)
{
	int i=0;
	
	for(i = 0; i < Querys.UsedSize() ; i++)
	{
		EjecutoQuery(Querys[i],Querys[i].GetSensorsNameQuantity(), Sensores.UsedSize() ,oss);
	}
}



void RedSensores::EjecutoQuery(Query q, int cantNombresSensores , int cantidadSensores, ostream& oss)
{
	Array<double> datos;
	Array<double> datos_average;
	int i=0, j=0, k=0; 
	int average_quantity;
	int name_quentity = 0;
	int InitRange = q.GetInitRange();
	int FinalRange = q.GetFinalRange();
	
	for(i=0; i<cantNombresSensores; i++)               // Por si en el query hay mas de un sensor.
	{
		for(j=0; j<cantidadSensores; j++)
		{
			string query_name = q.GetSensorNameAt(i);
			
			if( query_name == Sensores[j].GetName())   // Se compara por nombre del sensor.
			{
				if (Sensores[j].ValidarRango(InitRange, FinalRange))  // Si esta dentro del rango.
				{
					// Si el FinalRange supera la cantidad de datos del sensor, el FinalRange pasa a ser
					// la cantidad de datos del sensor.
					FinalRange = FinalRange>Sensores[j].GetQuantityOfData() ? Sensores[j].GetQuantityOfData() : FinalRange ;

					if(q.GetBadQuery() == true)   // Si la consulta esta mal ingresada.
					{
						oss<<"BUT QUERY"<<endl;
						
					}else{                        // Si se ingresa bien la consulta, se procesan los datos. 

						for( k = InitRange; k < FinalRange; k++)
						{
							// Se carga en el vector datos los valores validos de la consulta.
							if(Sensores[j].GetData()[k] != EMPTY_SPACE_INDICATOR)
								datos += Sensores[j].GetData()[k];
						}

						oss<<datos.Promedio()
						<<","<<datos.Minimo()
						<<","<<datos.Maximo()
						<<","<<datos.UsedSize()<<endl;
					}
				}else
				{
						oss<<"NO DATA"<<endl;	
				}
				
			}

  // En lo que sigue se tiene el cuenta el procesamiento de la consulta en 
  // caso de que no se ingrese el nombre del sensor que se quiere consultar.
  // Se procesan los datos consultando por todos los sensores en el rango indicado.

			if(query_name.empty() && j == 0 )
			{
				average_quantity = GetQuantityOfAverage();

				if (ValidarRangoAverage(InitRange, FinalRange))  // Si esta dentro del rango.
				{
					// Si el FinalRange supera la cantidad de datos del sensor, el FinalRange pasa a ser
					// la cantidad de datos del sensor.

					FinalRange = FinalRange> average_quantity ? average_quantity : FinalRange;
					for( k = InitRange; k < FinalRange; k++)
					{	
						datos_average += Average[k];
					}

					oss<< datos_average.Promedio()
					<<","<<datos_average.Minimo()
					<<","<<datos_average.Maximo()
					<<","<<datos_average.UsedSize()<<endl;
					
				}else
				{
						oss<<"NO DATA"<<endl;	
				}
			}

			for(int l = 0; l < cantidadSensores; l++)
			{
				if(query_name == Sensores[l].GetName() || query_name.empty())
					name_quentity++;

				if((l+1) == cantidadSensores)
					if(name_quentity == 0 && j==0)
						oss << "UNKNOW ID" << endl;

			}
		}
	}
}

bool RedSensores::ValidarRangoAverage(int initRange, int finalRange)
{
	bool resultado=false;


	if(finalRange>initRange && initRange >= 0 && initRange< Average.UsedSize())
	{
		resultado = true;
	}
	

	return resultado;

}

int RedSensores::GetQuantityOfAverage()
{
	return this -> Average.UsedSize();
}
