#include "Sensor.h"
#include <iostream>
#include <vector>

Sensor::Sensor()
{

}

Sensor::~Sensor()
{

}

void Sensor::SetName(string Name)
{
    this->Name = Name;
}

string Sensor:: GetName()
{
	return this->Name;
}





