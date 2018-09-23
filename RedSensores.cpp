#include "RedSensores.h"
#define DELIMITER ","
#define EMPTY_SPACE -1


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
/*
			cout<<"initial_pos: "<<initial_pos<<endl;
			cout<<"i: "<<delimiter_pos<<endl;
			cout<<"nombre: "<<str.substr(initial_pos, delimiter_pos - initial_pos)<<endl;
*/
			s.SetName(str.substr(initial_pos, delimiter_pos - initial_pos));
	
			//cout<<"nombre sensor: "<<s.GetName()<<endl;
			sensores.Append(s);
			//cout<<"v[0]: "<<sensores[sensors_quantity].GetName()<<endl;
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

	      //cout << "*************** Leo una linea ****************"<< endl;

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
	            //cout<<"final_pos: "<<final_pos<<endl;
				str_sensor = str.substr(initial_pos, final_pos);
				//cout<<"str_sensor: " <<str_sensor <<endl;
				// number = str_sensor.stod(str_sensor, &sz);
				if(!str_sensor.empty())
				{
					istringstream(str_sensor) >> number;	
					sensores[j].SetElementAt(number);
					sensores[j].SetValidPosition(true);
				}
				else{
					sensores[j].SetElementAt(EMPTY_SPACE);  //cargamos un valor cualquiera que no va
					sensores[j].SetValidPosition(false);	//a ser tenido en cuenta al recorrer el arreglo
				}											//porque se chequea el arreglo de booleanos
				//cout<<"number: "<<number<<endl;
				//cout<<"jota: "<<j<<endl;
				
				//datos.Append(number);
	            //cout<<"datos["<<j<<"]: "<<datos[j]<<endl;
	            initial_pos += final_pos+1;
				//cout<<initial_pos<<endl << endl;
	            // convertir a str_sensor a double
	            //sensores[j].SetData(datos);
	            j++;


	      }
	}

	Sensores = sensores;
	//cout<<"El elemento 4 del sensor 1 es: "<<sensores[0].GetElementAt(4)<<endl;
	//cout<<"El nombre del sensor 4 es: "<<sensores[3].GetName()<<endl;
}


void RedSensores::LecturaQuerys(istream& iss)
{
	int i = 0;
	string str;
	char c;


	for(i=0 ; !iss.eof() ; i++)      // Con este ciclo for se recorre cada fila
	{   
		if(iss>>c)
		{
			iss.putback(c);
			getline(iss, str);
		    Query q(str);   // Inicializo una Query por linea
		    this->Querys.Append(q);     // Agrego un query como ultimo elemento del vector	
		}
		
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
	//for(i = 2; i < 3 ; i++)
	{
		EjecutoQuery(Querys[i],Querys[i].GetSensorsNameQuantity(), Sensores.UsedSize() ,oss);
	}
}



void RedSensores::EjecutoQuery(Query q, int cantNombresSensores , int cantidadSensores, ostream& oss)
{
	Array<double> datos;
	Array<double> salida;
	salida.FillWith(0);
	//Array<int> divisores(0);
	int i=0, j=0, k=0; 
	int tb = 0;    // Esta variable cuenta la cantidad de coincidencias entre nombres de sensores.

	int InitRange = q.GetInitRange();
	int FinalRange = q.GetFinalRange();
	
	for(i=0; i<cantNombresSensores; i++)    // Por si en el query hay mas de un sensor
	{
		for(j=0; j<cantidadSensores; j++)
		{
			string query_name = q.GetSensorNameAt(i);

			
			if( query_name == Sensores[j].GetName() || query_name.empty())   // Se compara por nombre del sensor
			{
				tb++;				
				//cout<<"tamaño de Sensores: "<<Sensores[j].GetData().UsedSize()<<endl;
				//cout<<"tamaño del arreglo datos:"<<datos.UsedSize()<<endl;

				if (Sensores[j].ValidarRango(InitRange, FinalRange))  // Si esta dentro del rango
				{
					//si el FinalRange supera la cantidad de datos del sensor, el FinalRange pasa a ser
					//la cantidad de datos del sensor
					FinalRange = FinalRange>Sensores[j].GetQuantityOfData() ? Sensores[j].GetQuantityOfData() : FinalRange ;
					//Array<int> divisores(Sensores[j].GetQuantityOfData());
					//divisores.FillWith(0);

					for( k = InitRange; k < FinalRange; k++)
					{
						//cargo un nuevo arreglo con las dimensiones del rango solicitado
						if(Sensores[j].GetValidPosition(k)){
							datos += Sensores[j].GetData()[k];
						}
						else{
							datos += 0;
						}
						//divisores[k] += 1;
						
						
						//cout<<"tamaño del arreglo datos:"<<datos.UsedSize()<<endl;
					}
					/*
						for(int m=0; m<datos.UsedSize();m++)
						{
							cout<<"datos["<<m<<"]: "<<datos[m]<<endl;
						}
						cout<<"FIN ARREGLO"<<endl;*/
					

					salida.AddAverageArray(datos);
					datos.Reset();
					for(int m=0; m<salida.UsedSize();m++)
					{
						cout<<"salida["<<m<<"]: "<<salida[m]<<endl;
					}
					cout<<"FIN ARREGLO"<<endl;
					
					salida /= 4;

					//oss<<datos.Promedio()<<","<<datos.Minimo()<<","<<datos.Maximo()<<","<<datos.UsedSize()<<endl;
				}
				/*
				else
				{
					oss<<"NO DATA"<<endl;	
				}
				*/
			}
		}
	}




	
	
	

/*	for(int m=0; m<salida.UsedSize();m++)
		{
			cout<<"salida["<<m<<"]: "<<salida[m]<<endl;
		}
		cout<<"FIN ARREGLO"<<endl;
*/
		if(tb>0)
		{


			oss<<salida.Promedio()<<","<<salida.Minimo()<<","<<salida.Maximo()<<","<<salida.UsedSize()<<endl;
			
		}
		else
		{
			oss<<"NO DATA"<<endl;	
		}


}

