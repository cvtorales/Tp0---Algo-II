#include "Query.h"


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
	int QuantityChars=0;
	string FirstValue, SecondValue;

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

	cout<<"Posicion de semicolons: "<<semicolons[0]<<endl;
/*
	FirstValue = line.substr(commas[0], commas[1]-commas[0]);
	SecondValue= line.substr(commas[0], commas[1]-commas[0]);
*/

		
}