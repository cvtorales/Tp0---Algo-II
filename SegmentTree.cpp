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

	
	ArmaArrayDatos(datos, 0, nuevoArray, 0,cantElementos-1);
	
	this->Datos = datos;


	/*
	//inserto datos del arreglo desde la posicion tamanoST-cantElementos
	//hasta el final del segment tree
	for(int i=tamanoST - cantElementos; i<tamanoST;i++ )
	{
		int indice = i - cantElementos + 1;
		Data d;
		//si la potencia de 2 mas cercana es mas grande que la cantidad original 
		//de elementos en el vector, tengo que rellenarlo con datos vacios
		if(indice<v.UsedSize())
		{
			d.SetMin(v[indice]); 
			d.SetMax(v[indice]);
			d.SetCantidadDatos(1);
			
		}else{
			
			d.SetMin(-INFINITY); 
			d.SetMax(INFINITY);
			d.SetCantidadDatos(0);
		}
		datos.Append(d);
	}
	*/
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

void SegmentTree::ArmaArrayDatos(Array<Data> &st_datos, int pos, Array<Data> &v, int first, int last)
{
	Data d;
	d.ArmoDataDeArreglo(v, first, last);

	if(first<last)
	{
		
		int med = (first+last)/2;

		
		ArmaArrayDatos(st_datos, 2*pos+1,v,first,med);
		ArmaArrayDatos(st_datos, 2*pos+2,v,med+1,last);

	}

	
	st_datos.InsertElementAt(pos,d);

}