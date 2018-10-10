/*
	Archivo: Data.h
*/

#ifndef _DATA_H_INCLUDED_
#define _DATA_H_INCLUDED_

#include "TemplateArray.h"

using namespace std;

class Data
{
    private:
       /* double Max;
        double Min;
        int CantidadDatos;*/
        
    public:
        double Max;
        double Min;
        int CantidadDatos;
        Data();
        ~Data();
        double GetMax();
        double GetMin();
        int GetCantidadDatos();
        void SetMax(double max);
        void SetMin(double min);
        void SetCantidadDatos(int cantidadDatos);
        void ArmoDataDeArreglo(Array<Data> &array, int first, int last);
        
        
};



#endif