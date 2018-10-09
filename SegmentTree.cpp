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
	
	Array<Data> datos(tamanoST);


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