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
	double min=array[0].Min, max=array[0].Max;
	


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

void Data::Distinto(Array<Data> &array)
{
	Data d;
	double min=array[0].Min, max=array[0].Max;
	//int first=array[0].First, last=array[0].Last;


	int sum=0;


	for(int i=0; i<array.UsedSize();i++)
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

	this -> Min = min;
	this -> Max = max;
	this -> CantidadDatos = sum;
	
}