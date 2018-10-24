#include "Data.h"
#include "SegmentTree.h"

#define INIT_RANGE 3
#define FINAL_RANGE 5
#define ARRAY_QUANTITY 5
 

using namespace std;

int main(void)
{
	Array<Data> array_data;
	Array<Data> array_data_new;

	Array<Data> array_d;   // Es un arreglo vacio que se pasa al metodo recursivo.
	int init_range = INIT_RANGE;
	int final_range = FINAL_RANGE;
	int data_quantity = array_data.Pot2MasCercana(ARRAY_QUANTITY) - 1;

	// Se carga el arreglo de datas:
	for(int i=0; i< ARRAY_QUANTITY;i++)
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

	cout << "Parte del segment SegmentTree" << endl;
	// Defincion del SegmentTree:
	SegmentTree ST(array_data);
	ST.Print();

	// Se prueba el metodo para buscar un data en un intervalo.
	Data dato = ST.BuscoDataEnST(2,3);
	dato.PrintData();

    cout << "***** Prueba de metodo recursivo para encontrar intervalo *****" << endl;
	
    // Se valida el rango.
	if(init_range < 0 || init_range > data_quantity || final_range < init_range ||  final_range > data_quantity)
	{
		cout << "El rango es incorrecto." << endl;
		exit(EXIT_FAILURE);
	}

	// Busca el data correspondiente al rango indicado en los dos
	// ultimos argumentos del metodo.
	ST.BuscoIntervaloDeData(array_d, 0, data_quantity, init_range, final_range);
	for(int k=0; k <array_d.UsedSize() ; k++)
		array_d[k].PrintData();

	//ST.ArmaArrayDatos( array_data_new, 0, array_data, 0, last);
	//ST.Print();

    return 0;
}