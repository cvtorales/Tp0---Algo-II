#include "Sensor.h"

#define SENSOR_NAME "SensorT"
using namespace std;

int main(void)
{
	Sensor sensor;

	sensor.SetName(SENSOR_NAME);
	cout <<sensor.GetName() << endl;
	double dato= 32;
	sensor.SetElementAt(dato);

	Array<Data> array;
	array = sensor.GetDatosSinProcesar();


    return 0;
}