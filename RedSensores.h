#ifndef _RED_SENSORES_H_INCLUDED_
#define _RED_SENSORES_H_INCLUDED_

#include <iostream>
#include <string>
#include <sstream>
#include "TemplateArray.h"
#include "Sensor.h"
#include "Query.h"



using namespace std;


class RedSensores
{
    private:
        string Name;
        Array<Sensor> Sensores;
        Array<Query> Querys;
        Array<double> Average;
    public:
        RedSensores();
        ~RedSensores();
        RedSensores(istream&);
        void LecturaQuerys(istream&);
        Query ObtieneQuery(int);
        void ProcesamientoQuerys(ostream&);
        void EjecutoQuery(Query,int,int,ostream&);
        double Maximo(Array<double>& valores) const;
		double Minimo(Array<double>& valores) const;
        bool ValidarRangoAverage(int initRange, int finalRange);
        int GetQuantityOfAverage();

};



#endif