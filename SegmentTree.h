/*
	Archivo: SegmentTree.h
*/

#ifndef _SEGMENT_TREE_H_INCLUDED_
#define _SEGMENT_TREE_H_INCLUDED_

#include <math.h>
#include "TemplateArray.h"
#include "Data.h"

using namespace std;

class SegmentTree
{
    private:
        Array<Data> Datos;
        int Pot2MasCercana(int cantidadElementos);
    public:
        SegmentTree();
        SegmentTree(const Array<double>& v);
        ~SegmentTree();
        
        
};


#endif