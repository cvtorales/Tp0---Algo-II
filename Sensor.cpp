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

void Sensor::SetElementAt(double dato)
{
	this->Data.Append(dato);
}

double Sensor::GetElementAt(int pos)
{
	//validar
	return this-> Data[pos];
}

Array<double>& Sensor::GetData()
{
	return this -> Data;
}

bool Sensor::ValidarRango(int initRange, int finalRange)
{
	bool resultado=false;

	if (initRange >= 0 && finalRange<Data.UsedSize())
	{
		resultado = true;
	}

	return resultado;

}
