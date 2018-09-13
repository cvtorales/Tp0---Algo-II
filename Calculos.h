#ifndef _CALCULOS_H_INCLUDED_
#define _CALCULOS_H_INCLUDED_

#include <iostream>
#include "TemplateArray.h"


using namespace std;


class Calculos
{
            
    public:
        double Promedio(Array<double>&) const;
        double Maximo(Array<double>&) const;
        double Minimo(Array<double>&) const;

};



#endif