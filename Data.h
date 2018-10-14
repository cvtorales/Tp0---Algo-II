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
        int First;  //posicion inicial del arreglo original con el que se armó el Data
        int Last;
    public:
        double Max;
        double Min;
        int CantidadDatos;
        Data();
        ~Data();
        double GetMax();
        double GetMin();
        int GetFirst();
        int GetLast();
        int GetCantidadDatos();
        void SetMax(double max);
        void SetMin(double min);
        void SetFirst(int first);
        void SetLast(int last);
        void SetCantidadDatos(int cantidadDatos);
        void ArmoDataDeArreglo(Array<Data> &array, int first, int last);
        void Distinto(Array<Data> &array);


        
};



#endif