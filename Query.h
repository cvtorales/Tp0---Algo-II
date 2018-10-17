/*
	Archivo: Query.h
*/

#ifndef _QUERY_H_INCLUDED_
#define _QUERY_H_INCLUDED_

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include "TemplateArray.h"

#define RANGO_INICIAL 0
#define RANGO_FINAL 1
#define MINIMUM_EXPECTED_COMMAS 2
#define USUAL_METHOD 0
#define SEGMENT_TREE_METHOD 1

using namespace std;

class Query
{
    private:
        Array<string> SensorsName;
        int InitRange;
        int FinalRange;
        bool IsBadQuery;
        int ObtieneParametro(string linea, int instruccion, Array<int>& array);
        Array<string> ObtieneNombreSensores(string linea, Array<int>& arraySemicolons, int) const;
	    string RemoveSpaces(string &str);
    public:
        Query();
        Query(string);
        ~Query();
        int GetInitRange();
        int GetFinalRange();
        string GetSensorNameAt(int pos);
        int GetSensorsNameQuantity();
        void SetBadQuery(bool badq);
        bool GetBadQuery();
        
};



#endif
