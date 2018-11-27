/*
	Archivo: Data.cpp
*/

#include "Data.h"

Data::Data()
{
		
}

//Instancia un objeto Data segun si es vacio o no con el valor value en el rango
//unitario first=last=position
Data::Data(double value, int position, bool isEmpty)
{
	if(!isEmpty)
	{
		Min=value;
		Max=value;
		Sumatoria=value;
		CantidadDatos=1;
		First=position;
		Last=position;
	}else{
		Min=INFINITY;
		Max=-INFINITY;
		Sumatoria=0;
		CantidadDatos=0;
		First=position;
		Last=position;
	}
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

double Data::GetSumatoria()
{
	return this->Sumatoria;
}

double Data::GetPromedio()
{
	
	if(CantidadDatos!=0){
		return Sumatoria / CantidadDatos;
	}
	return 0;
}

void Data::SetMax(double max)
{
	this->Max = max;
}

void Data::SetMin(double min)
{
	this->Min = min;
}

void Data::SetSumatoria(const double sum)
{
	
	this->Sumatoria=sum;
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

//toma un arreglo de tipos Data. Lo cicla desde una posicion first a last y carga un 
//data individual en el objeto que llamó al metodo
void Data::ArmoDataDeArreglo(Array<Data> &array, int first, int last)
{

	double min=array[first].Min, max=array[first].Max;
	
	int quantity=0;
	double sum=0;

	for(int i=first; i<=last;i++)
	{

		if(array[i].Min != INFINITY && array[i].Max != -INFINITY)
		{
			quantity++;
			sum += array[i].GetSumatoria();
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
	this -> CantidadDatos = quantity;
	this -> Sumatoria = sum;
	
}

/*
//funcion que recibe un arreglo de tipos Data y devuelve un unico tipo Data con los elementos que tiene dentro
void Data::ArmoDataDeArreglo(Array<Data> &array)
{
	Data d;
	double min=array[0].Min, max=array[0].Max;

	int quantity=0;
	double sum=0;

	for(int i=0; i<array.UsedSize();i++)
	{
		if(array[i].Min != INFINITY && array[i].Max != -INFINITY){
			quantity += array[i].CantidadDatos;
			sum += array[i].Sumatoria;
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
	this -> CantidadDatos = quantity;
	this -> Sumatoria = sum;
	
}*/

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
		this ->Sumatoria = d.Sumatoria;
	}

	return *this;
}

Data& Data::operator+=(const Data &d) {
	//Si la direccion del objeto sobre el cual trabajo no es la misma
	//que la del argumento, ejecuto lo siguiente:
	if(this!=&d) 
	{

	if(d.Min != INFINITY && d.Max != -INFINITY){
		
		this -> CantidadDatos++;	
	}

		this -> First = d.First;
		this -> Last = d.Last;
		
		this -> Min += d.Sumatoria;
		this -> Max += d.Sumatoria;
		this -> Sumatoria += d.Sumatoria;
	}

	return *this;
}

//limpia el data que llama al metodo
void Data::CleanData()
{
	this -> First=0;
	this -> Last=0;
	this -> Sumatoria=0;
	this -> CantidadDatos=0;
	this -> Min=0;
	this -> Max=0;
}

void Data::PrintData()
{
	// Testeo del funcionamiento de los getters:
	cout << "D.GetMin()= " << this -> GetMin() << endl
		 << "D.GetMax()= " << this ->GetMax() << endl
		 << "D.GetSumatoria()= "<< this ->GetSumatoria() << endl
		 << "D.GetCantidadDatos()= " << this ->GetCantidadDatos() << endl
		 << "D.GetFirst()= " << this ->GetFirst() << endl
         << "D.GetLast()= " << this ->GetLast() << endl
         << "D.GetPromedio()= " << this ->GetPromedio() << endl
		 << endl;
}

//funcion que recibe dos elementos de tipo Data y devuelve un unico tipo Data como resultado
Data Data::UnificarDatas(Data d1, Data d2)
{
	Data data_resultado;
	
	data_resultado.Min = d1.Min <= d2.Min ? d1.Min : d2.Min;
	data_resultado.Max = d1.Max >= d2.Max ? d1.Max : d2.Max;
	data_resultado.Sumatoria = d1.Sumatoria + d2.Sumatoria;
	data_resultado.CantidadDatos = d1.CantidadDatos + d2.CantidadDatos;
			

	return data_resultado;
	
}