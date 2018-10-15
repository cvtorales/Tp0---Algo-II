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

int Data::GetFirst()
{
	return this->First;
}

int Data::GetLast()
{
	return this->Last;
}

int Data::GetCantidadDatos()
{
    return this->CantidadDatos;
}

void Data::SetMax(double max)
{
	this->Max = max;
}

void Data::SetMin(double min)
{
	this->Min = min;
}

void Data::SetCantidadDatos(int cantidadDatos)
{
    this->CantidadDatos = cantidadDatos;
}

void Data::SetFirst(int first)
{
	this->First = first;
}

void Data::SetLast(int last)
{
	this->Last = last;
}


void Data::ArmoDataDeArreglo(Array<Data> &array, int first, int last)
{
	Data d;
	double min=array[first].Min, max=array[first].Max;
	
	int sum=0;

	for(int i=first; i<=last;i++)
	{
		if(array[i].Min!= INFINITY || array[i].Max!= -INFINITY){
			sum++;
		}
		if(array[i].Min<min){
			min=array[i].Min;
		}

		if(array[i].Max>max){
			max=array[i].Max;
		}

	}

	this -> First = first;
	this -> Last = last;
	this -> Min = min;
	this -> Max = max;
	this -> CantidadDatos = sum;
	
}

//funcion que recibe un arreglo de tipos Data y devuelve un unico tipo Data con los elementos que tiene dentro
void Data::ArmoDataDeArreglo(Array<Data> &array)
{
	Data d;
	double min=array[0].Min, max=array[0].Max;
	/*double min= INFINITY;
	double max = -INFINITY;*/

	int sum=0;

	for(int i=0; i<array.UsedSize();i++)
	{
		if(array[i].Min!= INFINITY || array[i].Max!= -INFINITY){
			sum += array[i].CantidadDatos;
		}
		if(array[i].Min<min){
			min=array[i].Min;
		}

		if(array[i].Max>max){
			max=array[i].Max;
		}

	}

	this -> Min = min;
	this -> Max = max;
	this -> CantidadDatos = sum;
	
}

Data& Data::operator=(const Data &d) {
	//Si la direccion del objeto sobre el cual trabajo no es la misma
	//que la del argumento, ejecuto lo siguiente:
	if(this!=&d) 
	{
		this -> First = d.First;
		this -> Last = d.Last;
		this -> Min = d.Min;
		this -> Max = d.Max;
		this -> CantidadDatos = d.CantidadDatos;
	}

	return *this;
}