#include "RedSensores.h"


using namespace std;

RedSensores::RedSensores()
{

}


RedSensores::~RedSensores()
{
   //this-> Sensores.~Array();
}

RedSensores::RedSensores(istream& iss)
{
	string str, str_sensor;
	int i=0, j=0;
	int initial_pos=0, final_pos=0, sensors_quantity=0;
	Array<Sensor> sensores;
	
	Array<double> datos;



	double number;

	getline(iss, str);
	//cout<<"str: "<<str<<endl;
	cout << "Hola" << str[str.length()-1] << endl;


	for(i=0; str[i] != '\0'; i++)
	{	
		if(str[i]==',')
		{
			Sensor s;
			cout<<"initial_pos: "<<initial_pos<<endl;
			cout<<"i: "<<i<<endl;
			cout<<"nombre: "<<str.substr(initial_pos, i - initial_pos)<<endl;

			s.SetName(str.substr(initial_pos, i - initial_pos));
			cout<<"nombre sensor: "<<s.GetName()<<endl;
			sensores.Append(s);
			cout<<"v[0]: "<<sensores[sensors_quantity].GetName()<<endl;
			sensors_quantity++;
			//cout<<"sensors_quantity: "<<sensors_quantity<<endl;
			initial_pos=i+1;
		}		
	}

	Sensor s;
	
	s.SetName(str.substr(initial_pos, i - initial_pos));
	cout<<"nombre sensor: "<<s.GetName()<<endl;
	
	sensores.Append(s);
	cout<<"v[0]: "<<sensores[sensors_quantity].GetName()<<endl;
	sensors_quantity++;
	cout<<"sensors_quantity: "<<sensors_quantity<<endl;


	cout << " " << endl;
	
	for(i=0 ; !iss.eof() ; i++)     // con este for recorro cada fila
	{          
	      getline(iss, str);   // Con esto leemos cada linea y la asignamos a cadena
	      initial_pos = 0;
	      final_pos = 0;
	      j = 0;

	      cout << "*************** Leo una linea ****************"<< endl;
		  //cout<<"str: "<<str<<endl;
	      
	      while( j < sensors_quantity ) // con este for recorro cada sensor con la misma fila 
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

	cout<<"El elemento 1 del sensor 1 es: "<<sensores[1].GetElementAt(3)<<endl;

}

