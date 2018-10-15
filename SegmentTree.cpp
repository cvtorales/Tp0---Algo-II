/*
	Archivo: SegmentTree.cpp
*/

#include "SegmentTree.h"

SegmentTree::SegmentTree()
{

}

SegmentTree::SegmentTree(const Array<double>& v)
{
	int cantElementos = Pot2MasCercana(v.UsedSize());
	int tamanoST = 2*cantElementos-1;
	
	Array<Data> nuevoArray(cantElementos);
	Array<Data> datos(tamanoST);

	for(int i=0; i<cantElementos;i++ )
	{
		Data d;
		//si la potencia de 2 mas cercana es mas grande que la cantidad original 
		//de elementos en el vector, tengo que rellenarlo con datos vacios
		if(i<v.UsedSize())
		{
			
			d.SetMin(v[i]); 
			d.SetMax(v[i]);
			d.SetCantidadDatos(1);
			d.SetFirst(i);
			d.SetLast(i);

		}else{
			
			d.SetMin(INFINITY); 
			d.SetMax(-INFINITY);
			d.SetCantidadDatos(0);
			d.SetFirst(i);
			d.SetLast(i);
		}
		nuevoArray.Append(d);
	}

	//armo el arreglo de Datos del SegmentTree
	ArmaArrayDatos(datos, 0, nuevoArray, 0,cantElementos-1);
	
	this->Datos = datos;


}

SegmentTree::~SegmentTree()
{
   
}

//Funcion que devuelve el valor de la potencia de 2 mas cercana
//al valor pasado
int SegmentTree::Pot2MasCercana(int cantidadElementos)
{
	int n;
	int exponente=1;
	n = ceil(log2(cantidadElementos));
	return exponente<<=n;
	
}

//funcion que recibe el arreglo de datos del ST(largo=2*N-1), la posicion del arreglo donde será insertado
// el proximo dato, el arreglo que contiene los datos del arreglo original (largo=N) y las posiciones inicial
//y final donde se ciclará el arreglo
void SegmentTree::ArmaArrayDatos(Array<Data> &st_datos, int pos, Array<Data> &v, int first, int last)
{
	Data d;

	
	//armo un unico Data de un arreglo de tipos Data ciclando a partir de las posiciones
	//inicial y final
	d.ArmoDataDeArreglo(v,first,last);


	//si la ultima posicion es mayor que la primera vuelvo a llamar a la funcion
	//para insertar los datos en la posicion correspondiente
	if(first<last)	
	{
		
		int med = (first+last)/2;

		
		ArmaArrayDatos(st_datos, 2*pos+1,v,first,med);
		ArmaArrayDatos(st_datos, 2*pos+2,v,med+1,last);

	}

	//inserta el tipo Data d en la posicion pos
	st_datos.InsertElementAt(pos,d);

}


//Busco en el ST el Data que tiene como rango inicial la posicion first y como rango final
//la posicion last
Data SegmentTree::BuscoDataEnST(int first, int last)
{
	//Creo un data vacio para devolver en caso que no este en el ST
	Data d;


	for(int i=0; i<Datos.UsedSize();i++)
	{
	
		if(Datos[i].GetFirst()==first && Datos[i].GetLast()==last)
		{
			cout<<"Busco First: "<<first<<endl;
			cout<<"Busco Last: "<<last<<endl;
			cout<<endl;
			cout<<"Minimo encontrado: "<<Datos[i].GetMin()<<endl;
			cout<<"Maximo encontrado: "<<Datos[i].GetMax()<<endl;
			cout<<"#Datos encontrado: "<<Datos[i].GetCantidadDatos()<<endl;
			return Datos[i];
			
		}
	}

	return d;
}

void SegmentTree::BuscoIntervaloDeData(Array<Data> &data_array, int first, int last, int init_range, int final_range)
{

	if(first >= init_range && last <= final_range)  // CASO BASE
	{
	
		data_array += BuscoDataEnST(first, last);
	}

	else{
		int middle = (first+last)/2;

		if(init_range <= middle && final_range > middle) //me voy para izq y der
		{
			cout<<"Izquierda y Derecha"<<endl;
			cout<<"Init: "<<init_range<<endl;
			cout<<"Final: "<<final_range<<endl;
			cout<<"First: "<<first<<endl;
			cout<<"Last: "<<last<<endl;
			cout<<endl;
			BuscoIntervaloDeData(data_array, first, middle, init_range, middle);	//izq
			BuscoIntervaloDeData(data_array, middle+1, last, middle+1, final_range);//der
		}	

		if(init_range <= middle && final_range <= middle)//me voy para la izq
		{
			cout<<"Izquierda"<<endl;
			cout<<"Init: "<<init_range<<endl;
			cout<<"Final: "<<final_range<<endl;
			cout<<"First: "<<first<<endl;
			cout<<"Last: "<<last<<endl;
			cout<<endl;
			BuscoIntervaloDeData(data_array, first, middle, init_range, final_range);	//der
		}

		if(init_range > middle && final_range > middle)//me voy para la der
		{
			cout<<"Derecha"<<endl;
			cout<<"Init: "<<init_range<<endl;
			cout<<"Final: "<<final_range<<endl;
			cout<<"First: "<<first<<endl;
			cout<<"Last: "<<last<<endl;
			cout<<endl;
			BuscoIntervaloDeData(data_array, middle + 1 , last, init_range, final_range); //der
		}
	}

}