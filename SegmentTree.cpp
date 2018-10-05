/*
	Archivo: SegmentTree.cpp
*/

#include "SegmentTree.h"

SegmentTree::SegmentTree()
{

}

SegmentTree::SegmentTree(const Array &v)
{
    //creo un arreglo de tamaño 2N-1 siendo N el tamaño del arreglo de datos
    Array<Data> datos(2*v.UsedSize() - 1);

    //Agrego los valores del arreglo de datos original al arreglo de 
    //Data, siendo su maximo y minimo cada valor en sí mismo y la cantidad 
    //de datos es 1
    for(int i=0; i<v.UsedSize(); i++)
    {
        Data d;
        d.SetMax(v[i]);
        d.SetMax(v[i]);
        d.SetCantidadDatos(1);
        
    }

}

SegmentTree::~SegmentTree()
{
   
}
