/*
	Archivo: RedSensores.h
*/

#ifndef _RED_SENSORES_H_INCLUDED_
#define _RED_SENSORES_H_INCLUDED_

#include <iostream>
#include <string>
#include <sstream>
#include "TemplateArray.h"
#include "Sensor.h"
#include "Query.h"

#define DELIMITER ","
#define EMPTY_SPACE "-1"
#define EMPTY_SPACE_INDICATOR -1

using namespace std;


class RedSensores
{
    private:
    
        string Name;
        Array<Sensor> Sensores;
        Array<Query> Querys;
        Array<double> Average;   // Arreglo de promedios de las filas de todos los sensores.
        Array<Data> AverageDataST;
        SegmentTree AverageST;

    public:
            
        RedSensores();
        ~RedSensores();
        RedSensores(istream&);
        void LecturaQuerys(istream&);
        int GetQuantitySensores();
        Array<Sensor> GetSensores();
     //   Query GetQuery(int);
        void ProcesamientoQuerys(ostream&, int search_method);
        void EjecutoQueryUsual(Query,int,int,ostream&);
        void EjecutoQueryST(Query q, int cantNombresSensores , int cantidadSensores, ostream& oss);
        double Maximo(Array<double>& valores) const;
		double Minimo(Array<double>& valores) const;
        bool ValidarRangoAverage(int initRange, int finalRange);
        int GetQuantityOfAverage();

};



#endif