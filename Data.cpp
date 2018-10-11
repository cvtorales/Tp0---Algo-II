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

void Data::ArmoDataDeArreglo(Array<Data> &array, int first, int last)
{
	Data d;
	double min=array[first].Min, max=array[first].Max;


	//for(int j=first; j<last)

	for(int i=first; i<last+1;i++)
	{
		if(array[i].Min<min){
			min=array[i].Min;
		}
		if(last-first+1==8)
		{
		cout<<"array["<<i<<"]: "<<array[i].Max<<endl;
		cout<<"max: "<<max<<endl;
		}
		if(array[i].Max>max){
			max=array[i].Max;
		}
		
	}

	this -> Min = min;
	this -> Max = max;
	this ->CantidadDatos = last-first+1;
	
}