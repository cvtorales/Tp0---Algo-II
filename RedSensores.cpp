#include "RedSensores.h"


using namespace std;

RedSensores::RedSensores()
{

}


RedSensores::~RedSensores()
{
    
}

RedSensores::RedSensores(istream& iss)
{
    string str, str_sensor;
	int i,j;
	int initial_pos=0, final_pos=0, sensors_quantity=0;
	Array<double> datos;
    Array<Sensor> sensores;
	Sensor s;
    size_t sz;

	getline(iss, str);
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
    for(i=0 ; !iss.eof() ; i++)     // con este for recorro cada fila
    {          
            getline(iss, str);   // Con esto leemos cada linea y la asignamos a cadena
            initial_pos = 0;
            final_pos = 0;
            j = 0;
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
}

