/*
	Archivo: RedSensores.cpp
*/

#include "RedSensores.h"

RedSensores::RedSensores()
{

}

RedSensores::~RedSensores()
{

}

//inicializo una Red de Sensores a partir de pasarle un archivo con los datos separados por comas
RedSensores::RedSensores(istream & dss)
{
	string str, str_value;
	int i=0, j=0, delimiter_pos = 0;
	int initial_pos = 0, final_pos = 0, sensors_quantity = 0;
	double number;
	Array<Sensor> sensores;

	

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
		  int pos=0; //contador que guardará la posicion del arreglo donde se guarde cada dato

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

				//guardo cada valor en una cadena
				str_value = str.substr(initial_pos, final_pos);

				//creo un tipo Data para contener el promedio de cada fila

				Data dAverage;

				if(!str_value.empty())
				{
					data_quantity++;
					istringstream(str_value) >> number;	//convierto el string a double
					sensores[j].SetElementAt(number); //agrego el valor al sensor
					acum_row += number;   // Se acumula la suma de todos los sensores en una fila.

					//creo un objeto tipo Data para contener los valores individuales
					Data d(number, pos, false);
					dAverage += d;
					sensores[j].SetElementoSinProcesar(d);
					
					pos++;

				}else{

					// Si no se encuentra ningun dato, se asigna una constante.
					istringstream(EMPTY_SPACE) >> number;
					sensores[j].SetElementAt(number);

					//creo un objeto tipo Data para contener los valores individuales
					Data d(number, pos, true);
					
					//agrego un data al data promedio de esa fila de sensores
					dAverage += d;
					
					sensores[j].SetElementoSinProcesar(d);

					pos++;

				}

				if(j == (sensors_quantity - 1)) // Cuando termina sumar los valores.
				{
					// Se calcula el promedio de los sensores en una fila 
					// y se agrega a un vector de promedios (Average).  
					if(data_quantity!=0)
						Average.Append(acum_row/data_quantity);  

					if(dAverage.GetCantidadDatos()!=0)
					{
						//divido la suma de datos de cada fila de sensores por la # de datos en la misma
						dAverage.SetSumatoria(dAverage.GetSumatoria()/dAverage.GetCantidadDatos());
						dAverage.SetMin(dAverage.GetMin()/dAverage.GetCantidadDatos());
						dAverage.SetMax(dAverage.GetMax()/dAverage.GetCantidadDatos());

						AverageDataST.Append(dAverage);
						dAverage.CleanData(); //limpio los valores del Data
					}
				}
				
	            initial_pos += final_pos+1;
	            j++;
	      }
	}

	//inicializo el ST del promedio de sensores
	SegmentTree stAverage(AverageDataST);
	AverageST = stAverage;

	for(int i=0; i<sensors_quantity;i++)
	{
		SegmentTree st(sensores[i].GetDatosSinProcesar());
		sensores[i].SetSegmentTree(st);
	}

	Sensores = sensores;

}

//lee archivo de consultas e inicializa objetos Query que se guardan en un arreglo
//propio de la clase
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

//Query RedSensores::GetQuery(int pos)
//{
//	return Querys[pos];
//}

void RedSensores::ProcesamientoQuerys(ostream& oss, int search_method)
{
	int i=0;
	size_t init_process, final_process;
	size_t init_process_st, final_process_st;
	double usual_processing_time, st_processing_time;
	
	switch(search_method){
	//se ejecutan las querys segun el tipo de busqueda que se haya pasado por parametro

		case SEGMENT_TREE_METHOD:

			init_process_st = clock();

			for(i = 0; i < Querys.UsedSize() ; i++)
			{
				EjecutoQueryST(Querys[i],Querys[i].GetSensorsNameQuantity(), Sensores.UsedSize() ,oss);
			}

			final_process_st = clock();
			st_processing_time = (double (final_process_st - init_process_st)/ CLOCKS_PER_SEC); 
			cout << "Tiempo de ejecucion de Búsqueda EjecutoQueryST: "<< 1000 * st_processing_time << " ms" << endl;

			break;

		case USUAL_METHOD:

			init_process = clock();

			for(i = 0; i < Querys.UsedSize() ; i++)
			{
				EjecutoQueryUsual(Querys[i],Querys[i].GetSensorsNameQuantity(), Sensores.UsedSize() ,oss);
			}

			final_process = clock();
			usual_processing_time =  (double (final_process - init_process)/ CLOCKS_PER_SEC); 
			cout << "Tiempo de ejecucion de EjecutoQuery Búsqueda Usual: "<< 1000 * usual_processing_time << " ms" << endl;

			break;


	}

}


//Ejecuta la Query a partir del metodo de busqueda usual
void RedSensores::EjecutoQueryUsual(Query q, int cantNombresSensores , int cantidadSensores, ostream& oss)
{
	Array<double> datos;
	Array<double> datos_average;
	int i=0, j=0, k=0; 
	int average_quantity;
	int name_quentity = 0;
	int InitRange = q.GetInitRange();
	int FinalRange = q.GetFinalRange();
	
	if(q.GetBadQuery() == true)   // Si la consulta esta mal ingresada.
	{
		oss<<"BAD QUERY"<<endl;
	}else{ // Si se ingresa bien la consulta, se procesan los datos. 

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

                      // Si se ingresa bien la consulta, se procesan los datos. 

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
						
					}else
					{
							oss<<"BAD QUERY"<<endl;	
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
}

//Ejecuta la Query a partir del metodo de busqueda que emplea un Segment Tree
void RedSensores::EjecutoQueryST(Query q, int cantNombresSensores , int cantidadSensores, ostream& oss)
{
	Array<double> datos;
	Array<double> datos_average;
	int i=0, j=0; 
	int average_quantity;
	int name_quantity = 0;
	int InitRange = q.GetInitRange();
	int FinalRange = q.GetFinalRange();
	
	if(q.GetBadQuery() == true)   // Si la consulta esta mal ingresada.
	{
		oss<<"BAD QUERY"<<endl;
	}else{ // Si se ingresa bien la consulta, se procesan los datos. 

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

                      // Si se ingresa bien la consulta, se procesan los datos. 

						//sera necesario un arreglo de tipos Data que contendra los intervalos completos
						//que en la busqueda se vayan capturando y un tipo Data que contendra el resultado
						//final de toda la busqueda
						Array<Data> arregloDatasUtiles;
						Data d;
						
						//se selecciona la cantidad de elementos que tendra el Segment Tree como la potencia de 2
						//mas cercana al tamaño de datos del sensor
						int cantidadElementosST = arregloDatasUtiles.Pot2MasCercana(FinalRange) - 1;

						//usando el ST del sensor se buscan todos los intervalos completos capturados y se agregan al
						//arreglo arregloDatasUtiles
						Sensores[j].GetSegmentTree().BuscoIntervaloDeData(arregloDatasUtiles, 0, cantidadElementosST, InitRange, FinalRange-1);

						//a partir de todos los tipos Data de arregloDatasUtiles se inicializa un único tipo Data con 
						//los resultados
						d.ArmoDataDeArreglo(arregloDatasUtiles);

							oss<<d.GetPromedio()
							<<","<<d.GetMin()
							<<","<<d.GetMax()
							<<","<<d.GetCantidadDatos()
							<<endl;

							
						
					}else
					{
							oss<<"BAD QUERY"<<endl;	
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

						//La metodologia es parecida a la de un sensor en particular pero se usa el Segment Tree
						//promedio capturado en la lectura de sensores
						Array<Data> arregloDatasUtiles;
						Data d;
						
						int cantidadElementosST = arregloDatasUtiles.Pot2MasCercana(FinalRange) - 1;
						AverageST.BuscoIntervaloDeData(arregloDatasUtiles, 0, cantidadElementosST, InitRange, FinalRange-1);
						d.ArmoDataDeArreglo(arregloDatasUtiles);

							
							oss<<d.GetPromedio()
							<<","<<d.GetMin()
							<<","<<d.GetMax()
							<<","<<d.GetCantidadDatos()
							<<endl;
						
					}else
					{
							oss<<"NO DATA"<<endl;	
					}
				}

				//si no se encuentra el nombre del sensor, se devuelve UNKNOW ID
				for(int l = 0; l < cantidadSensores; l++)
				{
					if(query_name == Sensores[l].GetName() || query_name.empty())
						name_quantity++;

					if((l+1) == cantidadSensores)
						if(name_quantity == 0 && j==0)
							oss << "UNKNOW ID" << endl;
				}
			}
		}
	}
}

//valida que el rango (initRange-finalRange) del sensor creado a partir de los promedios de todos
//los sensores sea correcto
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


int RedSensores::GetQuantitySensores()
{
	return this -> Sensores.UsedSize();
}

Array<Sensor> RedSensores::GetSensores()
{
	return this -> Sensores;
}