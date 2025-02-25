/*
	Archivo: Query.cpp
*/

#include "Query.h"

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
	
	int InitPos=0;


	// Cargo arreglo con las posiciones de las comas.
	while((int)line.find(",", InitPos) != -1)
	{
		commas.Append(line.find(",", InitPos));
		InitPos = line.find(",", InitPos) + 1;
	}

	InitPos=0;     // Reinicio la variable.

	// Cargo arreglo con las posiciones de los punto y coma.
	while((int)line.find(";", InitPos) != -1)
	{
		semicolons.Append(line.find(";", InitPos));
		InitPos = line.find(";", InitPos) + 1;
	}

	if(commas.UsedSize()<MINIMUM_EXPECTED_COMMAS)
	{
		this->IsBadQuery=true;
	}else{
			if(semicolons.UsedSize() == 0)
			{
				this->SensorsName.Append(line.substr(0, commas[0]));
			}else{
			this->SensorsName = ObtieneNombreSensores(line,semicolons, commas[0]);
		}

		
		this->InitRange = ObtieneParametro(line,RANGO_INICIAL, commas);
		this->FinalRange = ObtieneParametro(line,RANGO_FINAL, commas);			
	}
	
}

int Query::ObtieneParametro(string linea, int instruccion, Array<int>& array)
{
	int ValorInstruccion=0;
	string str, str_limpio; //str_limpio va a ser un string sin espacios o tabulaciones
	
	bool resultado = false;


	if(instruccion < array.UsedSize()-1)
	{
		
		str = linea.substr(array[instruccion]+1, array[instruccion+1]-array[instruccion]-1);
		
		str_limpio=RemoveSpaces(str);
		
		
		for(size_t i=0; i < str_limpio.length() ; i++)
		{	
			if(!isdigit(str_limpio[i]))
			{
				resultado = true;				
			}
		}    
		IsBadQuery = resultado;
		if(!resultado)
			istringstream(linea.substr(array[instruccion]+1, array[instruccion+1]-array[instruccion]-1)) >> ValorInstruccion;		
		
	}else{

		istringstream(linea.substr(array[instruccion]+1, linea.length())) >> ValorInstruccion;	
		
	}

	return ValorInstruccion;
}

Array<string> Query::ObtieneNombreSensores(string linea, Array<int>& arraySemicolons, int firstCommaPosition) const
{
	Array<string> NombreSensores;
	int InitPos=0;

	for(int i = 0; i<arraySemicolons.UsedSize() ;i++)
	{
		NombreSensores.Append(linea.substr(InitPos, arraySemicolons[i]-InitPos));
		InitPos = arraySemicolons[i]+1;
	}

	NombreSensores.Append(linea.substr(InitPos, firstCommaPosition-InitPos));

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
	if(pos<0 || pos>SensorsName.UsedSize())
	{
		return "Posicion erronea";     // Armar diccionario de errores
	}
	return this-> SensorsName[pos];
}

int Query::GetSensorsNameQuantity()
{
	return this-> SensorsName.UsedSize();
}

void Query::SetBadQuery(bool badq)
{

	this -> IsBadQuery = badq;
}

 bool Query::GetBadQuery()
 {
 	  return this-> IsBadQuery;
 }

string Query::RemoveSpaces(string &str) 
{ 
    
    str.erase(remove(str.begin(), str.end(), ' '), str.end()); 
    return str; 
} 

void Query::PrintQuery()
{
	cout << "Impresion de Query: " << endl;
	cout << "InitRange: " << this -> InitRange  << endl;
    cout << "FinalRange: " << this -> FinalRange << endl;
    cout << "IsBadQuery: " << this -> IsBadQuery << endl;
}
