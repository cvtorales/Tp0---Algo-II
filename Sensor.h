/*
	Archivo: Sensor.h
*/

#ifndef _SENSOR_H_INCLUDED_
#define _SENSOR_H_INCLUDED_

#include <iostream>
#include <string>
#include "TemplateArray.h"
#include "SegmentTree.h"

using namespace std;

class Sensor
{
    private:
        string Name;
        Array<double> Datos;
        SegmentTree ST;
        Array<Data> DatosSinProcesar;
    public:
        
        //SegmentTree ST;
        Sensor();
        ~Sensor();
        void SetName(string Name);
        string GetName();
        void SetElementAt(double dato);
        void SetElementoSinProcesar(Data d);
        Array<Data>& GetDatosSinProcesar();
        SegmentTree& GetSegmentTree();
        double GetElementAt(int pos);
        Array<double>& GetData();
        bool ValidarRango(int initRange, int finalRange);
        int GetQuantityOfData();
        void SetSegmentTree(SegmentTree &st);
};

#endif