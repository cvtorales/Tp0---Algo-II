#ifndef _RED_SENSORES_H_INCLUDED_
#define _RED_SENSORES_H_INCLUDED_

#include <iostream>
#include <string>
#include "TemplateArray.h"
#include "Sensor.h"


using namespace std;


class RedSensores
{
    private:
        string Name;
        Array<Sensor> Sensores;
    public:
        RedSensores();
        ~RedSensores();
     //   RedSensores(istream& iss);
};



#endif