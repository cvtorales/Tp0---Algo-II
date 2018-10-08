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
        Array<double> Data;
        //SegmentTree ST;

    public:
        SegmentTree ST;
        Sensor();
        ~Sensor();
        void SetName(string Name);
        string GetName();
        void SetElementAt(double dato);
        double GetElementAt(int pos);
        Array<double>& GetData();
        bool ValidarRango(int initRange, int finalRange);
        int GetQuantityOfData();
        void SetSegmentTree(SegmentTree &st);
};

#endif