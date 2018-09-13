#include "Query.h"

#define RANGO_INICIAL 0
#define RANGO_FINAL 1

using namespace std;

Query::Query()
{

}


Query::~Query()
{
   
}

Query::Query(string line)
{
	string str;
	Array<int> commas;
	Array<int> semicolons;
	
	int i=0;
	int InitPos=0;
	

	//cargo arreglo con las posiciones de las comas
	while((int)line.find(",", InitPos) != -1)
	{
		commas.Append(line.find(",", InitPos));
		InitPos = line.find(",", InitPos) + 1;
	}

	InitPos=0; //reinicio la variable

	//cargo arreglo con las posiciones de los punto y coma
	while((int)line.find(";", InitPos) != -1)
	{
		semicolons.Append(line.find(";", InitPos));
		InitPos = line.find(";", InitPos) + 1;
	}

	if(semicolons.UsedSize() == 0)
	{
		this->SensorsName.Append(line.substr(0, commas[0]));
	}else{
		this->SensorsName = ObtieneNombreSensores(line,semicolons, commas);
	}
	
	this->InitRange = ObtieneParametro(line,RANGO_INICIAL, commas);
	this->FinalRange = ObtieneParametro(line,RANGO_FINAL, commas);
	
		
		
}

int Query::ObtieneParametro(string linea, int instruccion, Array<int>& array) const
{
	int ValorInstruccion=0;

	if(instruccion < array.UsedSize()-1)
	{
	
		istringstream(linea.substr(array[instruccion]+1, array[instruccion+1]-array[instruccion]-1)) >> ValorInstruccion;	
		
	}else{
		istringstream(linea.substr(array[instruccion]+1, linea.length())) >> ValorInstruccion;	
		
	}
	cout<<"ValorInstruccion: "<<ValorInstruccion<<endl;
	return ValorInstruccion;
}

Array<string> Query::ObtieneNombreSensores(string linea, Array<int>& arraySemicolons, Array<int>& arrayCommas) const
{
	Array<string> NombreSensores;
	int InitPos=0;

	for(int i = 0; i<arraySemicolons.UsedSize() ;i++)
	{

		NombreSensores.Append(linea.substr(InitPos, arraySemicolons[i]-InitPos));
		InitPos = arraySemicolons[i]+1;
	}

	NombreSensores.Append(linea.substr(InitPos, arrayCommas[0]-InitPos));

	return NombreSensores;

}

int Query::GetInitRange()
{
	return this->InitRange;
}

int Query::GetFinalRange()
{
	return this->FinalRange;
}

string Query::GetSensorNameAt(int pos)
{
	//validar
	return this-> SensorsName[pos];
}

int Query::GetSensorsNameQuantity()
{
	return this-> SensorsName.UsedSize();
}
