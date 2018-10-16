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
        //Array<Data> Datos;
    public:
        Array<Data> DatosST;
        SegmentTree();
        SegmentTree(const Array<Data>& v);
        ~SegmentTree();
        void ArmaArrayDatos(Array<Data> &st_datos, int pos, Array<Data> &v, int first, int last);
        Data BuscoDataEnST(int first, int last);
        void BuscoIntervaloDeData(Array<Data> &data_array, int first, int last, int init_range, int final_range);
        SegmentTree& operator=(const SegmentTree &st);
};


#endif