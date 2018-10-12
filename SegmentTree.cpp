/*
	Archivo: SegmentTree.cpp
*/

#include "SegmentTree.h"

SegmentTree::SegmentTree()
{

}

SegmentTree::SegmentTree(const Array<double>& v)
{
	int cantElementos = Pot2MasCercana(v.UsedSize());
	int tamanoST = 2*cantElementos-1;
	
	Array<Data> nuevoArray(cantElementos);
	Array<Data> datos(tamanoST);

	for(int i=0; i<cantElementos;i++ )
	{
		Data d;
		//si la potencia de 2 mas cercana es mas grande que la cantidad original 
		//de elementos en el vector, tengo que rellenarlo con datos vacios
		if(i<v.UsedSize())
		{
			
			d.SetMin(v[i]); 
			d.SetMax(v[i]);
			d.SetCantidadDatos(1);
			
		}else{
			
			d.SetMin(INFINITY); 
			d.SetMax(-INFINITY);
			d.SetCantidadDatos(0);
		}
		nuevoArray.Append(d);
	}

	//armo el arreglo de Datos del SegmentTree
	ArmaArrayDatos(datos, 0, nuevoArray, 0,cantElementos-1);
	
	this->Datos = datos;


}

SegmentTree::~SegmentTree()
{
   
}

//Funcion que devuelve el valor de la potencia de 2 mas cercana
//al valor pasado
int SegmentTree::Pot2MasCercana(int cantidadElementos)
{
	int n;
	int exponente=1;
	n = ceil(log2(cantidadElementos));
	return exponente<<=n;
	
}

//funcion que recibe el arreglo de datos del ST(largo=2*N-1), la posicion del arreglo donde será insertado
// el proximo dato, el arreglo que contiene los datos del arreglo original (largo=N) y las posiciones inicial
//y final donde se ciclará el arreglo
void SegmentTree::ArmaArrayDatos(Array<Data> &st_datos, int pos, Array<Data> &v, int first, int last)
{
	Data d;
	
	//armo un unico Data de un arreglo de tipos Data ciclando a partir de las posiciones
	//inicial y final
	d.ArmoDataDeArreglo(v, first, last);

	//si la ultima posicion es mayor que la primera vuelvo a llamar a la funcion
	//para insertar los datos en la posicion correspondiente
	if(first<last)	
	{
		
		int med = (first+last)/2;

		
		ArmaArrayDatos(st_datos, 2*pos+1,v,first,med);
		ArmaArrayDatos(st_datos, 2*pos+2,v,med+1,last);

	}

	//inserta el tipo Data d en la posicion pos
	st_datos.InsertElementAt(pos,d);

}