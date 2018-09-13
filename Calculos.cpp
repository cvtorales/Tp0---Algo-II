#include "Calculos.h"

using namespace std;

double Calculos::Promedio(Array<double>& valores) const
{
	int i = 0;

	for(i=0; i<valores.UsedSize(); i++)
	{

	}
}

double Calculos::Maximo(Array<double>& valores) const
{
	int i=0;
	double maximo=0;
	
	for(i=0; i<valores.UsedSize(); i++)
	{
		if(maximo > valores[i])
		{
			maximo = valores[i];
		}
	}

	return maximo;	
}

double Calculos::Minimo(Array<double>& valores) const
{
	int i=0;
	double minimo=0;
	
	for(i=0; i<valores.UsedSize(); i++)
	{
		if(minimo < valores[i])
		{
			minimo = valores[i];
		}
	}

	return minimo;
}