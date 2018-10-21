#include "Data.h"

using namespace std;

int main(void)
{
	
	double value = 3.8994;
	int position = 2;

 // Se comenta dependiento de cual se quiera comprobar. 
	bool Empty = false;
 //	bool Empty = true;

	Array<Data> array_data;
	int first=2;
	int last=4;
	
	Data D(value, position, Empty);

	// Dentro de PrintData se utilizan los Getters:
	D.PrintData();

	// Se carga el arreglo de datas:
	for(int i=0; i<5;i++)
	{
		Data d;
		d.SetMin(i+1); 
		d.SetMax(i+1);
		d.SetSumatoria(i+1);
		d.SetCantidadDatos(1);
		d.SetFirst(i);
		d.SetLast(i);
		array_data.Append(d);
	}

    // Se imprime el arreglo de datas:
	for(int j=0; j < array_data.UsedSize() ; j++)
	{
		array_data[j].PrintData();
	}


	cout << "*********************************" << endl;

	D.ArmoDataDeArreglo(array_data);
	// Caso de impresion para el vector completo:
	cout << "Para el caso del vector completo: " << endl
	     << "D.PrintData(): "<< endl;
	D.PrintData();


	cout << "*********************************" << endl;
	D.ArmoDataDeArreglo(array_data, first, last);
	// Caso de impresion para un rango requerido:
	cout << "Para el caso en que se determine un rango: " << endl
	     << "D.PrintData(): "<< endl;

	D.PrintData();


    return 0;
}