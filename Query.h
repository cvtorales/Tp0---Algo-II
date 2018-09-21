#ifndef _QUERY_H_INCLUDED_
#define _QUERY_H_INCLUDED_

#include <iostream>
#include <string>
#include <sstream>
#include "TemplateArray.h"




using namespace std;


class Query
{
    private:
        Array<string> SensorsName;
        int InitRange;
        int FinalRange;
        int ObtieneParametro(string linea, int instruccion, Array<int>& array) const;
        Array<string> ObtieneNombreSensores(string linea, Array<int>& arraySemicolons, int) const;
    public:
        Query();
        Query(string);
        ~Query();
        int GetInitRange();
        int GetFinalRange();
        string GetSensorNameAt(int pos);
        int GetSensorsNameQuantity();
};



#endif