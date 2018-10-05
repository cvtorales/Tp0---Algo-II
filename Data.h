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
        double Min;
        int CantidadDatos;
        
    public:
        Data();
        ~Data();
        double GetMax();
        double GetMin();
        int GetCantidadDatos();

        
        
};



#endif