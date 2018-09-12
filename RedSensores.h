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
    public:
        RedSensores();
        ~RedSensores();
        RedSensores(istream&);
        void LecturaQuerys(istream& iss);
        Query ObtieneQuery(int pos);
};



#endif