/*
	Archivo: SegmentTree.cpp
*/

#include "SegmentTree.h"

SegmentTree::SegmentTree()
{

}

SegmentTree::SegmentTree(const Array<Data>& v)
{
	int cantElementos = v.Pot2MasCercana(v.UsedSize());
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
			d=v[i];
		}else{		
			d.SetMin(INFINITY); 
			d.SetMax(-INFINITY);
			d.SetCantidadDatos(0);
			d.SetSumatoria(0);
			d.SetFirst(i);
			d.SetLast(i);
		}
		nuevoArray.Append(d);
	}
	
	// Armo el arreglo de Datos del SegmentTree:
	ArmaArrayDatos(datos, 0, nuevoArray, 0,cantElementos-1);
	this->DatosST = datos;
}

SegmentTree::~SegmentTree()
{
   
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
		
		ArmaArrayDatos(st_datos, 2*pos+1, v, first, med);
		ArmaArrayDatos(st_datos, 2*pos+2, v, med+1, last);

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


	for(int i=0; i<DatosST.UsedSize();i++)
	{
		//si el rango pasado (first-last) se encuentra en los rangos guardados en el ST
		//devuelve el Data del mismo
		if(DatosST[i].GetFirst()==first && DatosST[i].GetLast()==last)
		{

			return DatosST[i];
			
		}
	}

	return d;
}

//funcion que recibe un arreglo vacio de tipos Data con su posicion inicial, final y el rango buscado. Recursivamente
//va a ir cargando el arreglo con los intervalos completos encontrados que esten dentro del rango
void SegmentTree::BuscoIntervaloDeData(Array<Data> &data_array, int first, int last, int init_range, int final_range)
{

	
	if(first >= init_range && last <= final_range)  // CASO BASE
	{
		//busco en el segment tree el Data correspondiente al intervalo completo
		//encontrado
		data_array += BuscoDataEnST(first, last);
	}

	else{
		int middle = (first+last)/2;

		if(init_range <= middle && final_range > middle) //me voy para izq y der
		{

			BuscoIntervaloDeData(data_array, first, middle, init_range, middle);	//izq
			BuscoIntervaloDeData(data_array, middle+1, last, middle+1, final_range);//der
		}	

		if(init_range <= middle && final_range <= middle)//me voy para la izq
		{

			BuscoIntervaloDeData(data_array, first, middle, init_range, final_range);	//der
		}

		if(init_range > middle && final_range > middle)//me voy para la der
		{

			BuscoIntervaloDeData(data_array, middle + 1 , last, init_range, final_range); //der
		}
	}

}


SegmentTree& SegmentTree::operator=(const SegmentTree &st) 
{
	//Si la direccion del objeto sobre el cual trabajo no es la misma
	//que la del argumento, ejecuto lo siguiente:
	if(this!=&st) 
	{
		this->DatosST = st.DatosST;
	}

	return *this;
}


void SegmentTree::Print()
{
	for(int i=0; i<DatosST.UsedSize();i++)
	{
		cout<<"First: "<<DatosST[i].GetFirst()<<endl;
	//}
	//cout<<endl;
	//for(int i=0; i<DatosST.UsedSize();i++)
	//{
		cout<<"Last: "<<DatosST[i].GetLast()<<endl;
	//}
	//cout<<endl;
	//for(int i=0; i<DatosST.UsedSize();i++)
	//{
		cout<<"Min: "<<DatosST[i].GetMin()<<endl;
	//}
	//cout<<endl;
	//for(int i=0; i<DatosST.UsedSize();i++)
	//{
		cout<<"Max: "<<DatosST[i].GetMax()<<endl;
	//}
	//cout<<endl;
	//for(int i=0; i<DatosST.UsedSize();i++)
	//{
		cout<<"Cantidad de Datos: "<<DatosST[i].GetCantidadDatos()<<endl;
	//}	
	//cout<<endl;
	//for(int i=0; i<DatosST.UsedSize();i++)
	//{
		cout<<"Promedio: "<<DatosST[i].GetPromedio()<<endl;

		cout << endl;
	}	
		
	
}
