/*
	Archivo: Sensor.cpp
*/

#include "Sensor.h"
#include <iostream>

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
	this->Datos.Append(dato);
}

double Sensor::GetElementAt(int pos)
{
	return this-> Datos[pos];
}

void Sensor::SetElementoSinProcesar(Data d)
{
	this->DatosSinProcesar.Append(d);
}

Array<double>& Sensor::GetData()
{
	return this -> Datos;
}

Array<Data>& Sensor::GetDatosSinProcesar()
{
	return this -> DatosSinProcesar;
}

SegmentTree& Sensor::GetSegmentTree()
{
	return this -> ST;
}

//valida que el rango (initRange-finalRange) del sensor sea correcto
bool Sensor::ValidarRango(int initRange, int finalRange)
{
	bool resultado=false;


	if(finalRange>initRange && initRange >= 0 && initRange<Datos.UsedSize())
	{
		resultado = true;
	}
	

	return resultado;

}


int Sensor::GetQuantityOfData()
{
	return this -> Datos.UsedSize();
}

void Sensor::SetSegmentTree(SegmentTree &st)
{
    this->ST = st;
}