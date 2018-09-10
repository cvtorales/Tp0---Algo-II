#include <iostream>
#include <string>
 
using namespace std;

// Primero leo la primer linea tomando los strings para los 
// nombres de los sensores

// En un principio, no se sabe la cantidad de filas , por lo tanto 
// se realiza la comparación con eof.

// con sensors_quantity sabemos la cantidad de sensores con las que se van a operar

for(i=0 ; !iss.eof() ; i++)     // con este for recorro cada fila
{          
          getline(iss, str);   // Con esto leemos cada linea y la asignamos a cadena
          initial_pos = 0;
          final_pos = 0;
          j = 0;

          while( j < sensors_quantity ) // con este for recorro cada sensor con la misma fila 
          {
                final_pos = str.find(",", initial_pos);
                str_sensor = str.substr(initial_pos, final_pos);

                initial_pos = final_pos + 1;
                // convertir a str_sensor a double
                j++;
          }

}

// Para leer la primer linea  

void Sensor:: load_data(istream & iss, Array<double>  v_data, Array<Sensor> V_Sensor)
{
  string str;
  int dim;
  int initial_pos = 0, sensors_quantity = 0;

  if(!iss.good())
  {
    cerr << "No se puede abrir la base de datos del sensor." << endl;
  }

  getline(iss, str);   // Lectura de la primer linea: datos  de los nombres y cantidad de sensores

  for( i=0; str[i] != '\n'; i++)
  {
    if(str[i] == ',')
    {
      V_Sensor[sensors_quantity].SetName( str.substr(initial_pos,i) );
            sensors_quantity++;
            initial_pos = i;
        }   
  }


  for(i=0 ; !iss.eof() ; i++)     // con este for recorro cada fila
  {          
          getline(iss, str);   // Con esto leemos cada linea y la asignamos a cadena
          initial_pos = 0;
          final_pos = 0;
          j = 0;

          while( j < sensors_quantity ) // con este for recorro cada sensor con la misma fila 
          {
                final_pos = str.find(",", initial_pos);
                str_sensor = str.substr(initial_pos, final_pos);

                initial_pos = final_pos + 1;
                // convertir a str_sensor a double
                j++;
          }

  }

}


