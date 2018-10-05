/*
	Archivo: Data.cpp
*/

#include "Data.h"

Data::Data()
{

}


Data::~Data()
{
   
}

double Data::GetMax()
{
	return this->Max;
}

double Data::GetMin()
{
	return this->Min;
}

int Data::GetCantidadDatos()
{
    return this->CantidadDatos;
}