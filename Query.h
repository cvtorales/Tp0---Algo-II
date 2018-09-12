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
    public:
        Query();
        Query(string);
        ~Query();
};



#endif