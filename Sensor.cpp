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


	if(finalRange>initRange && initRange >= 0 && initRange<Data.UsedSize())
	{
		resultado = true;
	}
	

	return resultado;

}


int Sensor::GetQuantityOfData()
{
	return this -> Data.UsedSize();
}