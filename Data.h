/*
	Archivo: Data.h
*/

#ifndef _DATA_H_INCLUDED_
#define _DATA_H_INCLUDED_

using namespace std;

class Data
{
    private:
        double Max;
        //double Min;
        int CantidadDatos;
        
    public:
        double Min;
        Data();
        ~Data();
        double GetMax();
        double GetMin();
        int GetCantidadDatos();
        void SetMax(double max);
        void SetMin(double min);
        void SetCantidadDatos(int cantidadDatos);
        
        
};



#endif