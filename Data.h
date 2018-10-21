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
    
        double Max;
        double Min;
        int CantidadDatos;
        double Sumatoria;
        int First;  //posicion inicial del arreglo original con el que se armó el Data
        int Last;

    public:
        Data();
        Data(double value, int position, bool isEmpty);
        ~Data();
        double GetMax();
        double GetMin();
        double GetSumatoria();
        int GetFirst();
        int GetLast();
        int GetCantidadDatos();
        double GetPromedio();
        void SetMax(double max);
        void SetMin(double min);
        void SetSumatoria(const double sum);
        void SetFirst(int first);
        void SetLast(int last);
        void SetCantidadDatos(int cantidadDatos);
        void ArmoDataDeArreglo(Array<Data> &array, int first, int last);
        void ArmoDataDeArreglo(Array<Data> &array);
        //void UnicoDataDeArreglo(Array<Data> &array);
        Data& operator=(const Data &d);
        Data& operator+=(const Data &d);
        void CleanData();
        void PrintData();

        
};



#endif