/*
	Archivo: TemplateArray.h
*/

#ifndef _TEMPLATE_ARRAY_INCLUDED_
#define _TEMPLATE_ARRAY_INCLUDED_

#include <iostream>
#include <stdlib.h>
#include <limits>
#include <cmath>

#define DEFAULT_ARRAY_SIZE 20
#define ERROR_ARRAY_CONSTRUCTOR "<Array> constructor: non-positive arguments not allowed."
#define ERROR_ARRAY_INDEX "<Array> operator []: index not allowed."
#define ERROR_ARRAY_SUM "<Array> operator +: Array sizes must match"
#define ERROR_ARRAY_PAD "<Array> pad: PadSize must be greater or equal than UsedSize"

template <class T>
class Array{
private:
	int _AllocSize, _UsedSize;
	T * _Array;

public:
	Array();
	explicit Array(const int N);
	Array(const Array &v);
	~Array();
	int UsedSize() const;
	void Reset();
	void Clear();
	T Maximo() const;
	T Minimo() const;
	T Promedio() const;
	T& operator[](int pos);
	T& operator[](int pos) const;
	Array& operator/=(int divisor);
	Array& operator=(const Array &v);
	Array& operator+=(const T &t);
	void Append(const T &s);
	void InsertElementAt(int pos, T& x);
};

template <class T>
Array<T>::Array() {
	_AllocSize = DEFAULT_ARRAY_SIZE;
	_UsedSize = 0;
	_Array = new T[_AllocSize];
}

template <class T>
Array<T>::Array(const int N) {
	//Si el argumento es invalido, sale del programa.
	if(N<=0) {
		std::cerr<<ERROR_ARRAY_CONSTRUCTOR<<std::endl;
		exit(EXIT_FAILURE);
	}

	_Array = new T[N];
	_AllocSize = N;
	_UsedSize = 0;
}

template <class T>
Array<T>::Array(const Array<T> &v) {

	//El constructor por copia crea un Array del tamano de UsedSize e iguala los elementos
	_AllocSize = _UsedSize = v._UsedSize;
	_Array = new T[_UsedSize];

	for(int i = 0; i<_UsedSize; i++)
		_Array[i] = v._Array[i];
}

template <class T>
Array<T>::~Array() {
	delete [] _Array;
}

template <class T>
int Array<T>::UsedSize() const {
	return _UsedSize;
}

template <class T>
void Array<T>::Reset()  {
	delete [] _Array;
	_AllocSize = DEFAULT_ARRAY_SIZE;
	_UsedSize = 0;
	_Array = new T[_AllocSize];
	return;
}

template <class T>
void Array<T>::Clear()  {
	_UsedSize = 0;
	return;
}

template <class T>
T& Array<T>::operator[](int pos) {

	//Si la posicion ingresada es invalida, sale del programa.
	if(pos < 0 || pos >= _UsedSize) {
		std::cerr<<ERROR_ARRAY_INDEX<<std::endl;
		exit(EXIT_FAILURE);
	}

	return _Array[pos];
}

template <class T>
T& Array<T>::operator[](int pos) const {

	//Si la posicion ingresada es invalida, sale del programa.
	if(pos < 0 || pos >= _UsedSize) {
		std::cerr<<ERROR_ARRAY_INDEX<<std::endl;
		return _Array[0];
	}

	return _Array[pos];
}


template <class T>
Array<T>& Array<T>::operator=(const Array<T> &v) {
	//Si la direccion del objeto sobre el cual trabajo no es la misma
	//que la del argumento, ejecuto lo siguiente:
	if(this!=&v) {
		//Si el _UsedSize del objeto del argumento es menor o igual que el _AllocSize
		//del objeto en el que estoy trabajando, simplemente se igualan los elementos
		//y el _UsedSize.
		if(v._UsedSize <= _AllocSize) {

			for(int i = 0; i < v._UsedSize; i++)
				_Array[i] = v._Array[i];

			_UsedSize=v._UsedSize;
		}
		//Si no alcanza el largo del arreglo de *this, se crea uno nuevo con el largo
		// necesario (_UsedSize del objeto del argumento) y se igualan los elementos.
		else {
			delete[] _Array;
			_Array = new T[v._UsedSize];

			for(int i = 0; i<v._UsedSize; i++)
				_Array[i]=v._Array[i];

			_AllocSize = _UsedSize = v._UsedSize;
		}
	}

	return *this;
}

template <class T>
Array<T>& Array<T>::operator+=(const T &t) {
	this->Append(t);
	return *this;
}

template <class T>
void Array<T>::Append(const T &s) {


	//Si el array no esta lleno, agrega el nuevo elemento.
	if(_UsedSize < _AllocSize) {
		_Array[_UsedSize]=s;
		_UsedSize++;
	}
	else { //Si esta lleno, se debe alargar _Array.
		T *NewArray;
		//Primero, almacena valores en un arreglo auxiliar con el doble de largo.
		int NewSize = _AllocSize*2;
		NewArray = new T[NewSize];
		for(int i = 0; i < _UsedSize; i++) {
			NewArray[i]=_Array[i];
		}
		//Agrega el nuevo elemento al final
		NewArray[_UsedSize]=s;

		//Destruye _Array original y asigna un nuevo _Array con el doble de largo.
		delete[] _Array;
		_Array = NewArray;
		_AllocSize = NewSize;
		_UsedSize++;
	}
}

template <class T>
Array<T>& Array<T>::operator/=(int divisor) {
int i =0;

	if(divisor == 0)
	{
		return *this;
	}

	for(i=0; i<_UsedSize; i++)
	{
		_Array[i] = _Array[i]/divisor;
	}

	return *this;
}

template <class T>
T Array<T>::Maximo() const
{
	int i=0;
	T maximo=_Array[i];
	
	for(i=1; i<_UsedSize; i++)
	{
		if(maximo < _Array[i])
		{
			maximo = _Array[i];
		}
	}

	return maximo;	
}

template <class T>
T Array<T>::Minimo() const
{
	int i=0;
	T minimo = _Array[0];
	
	for(i=1; i<_UsedSize; i++)
	{
		if(minimo > _Array[i])
		{
			minimo = _Array[i];
		}
	}

	return minimo;	
}

template <class T>
T Array<T>::Promedio() const
{
	int i=0;
	T promedio=0;
	
	for(i=0; i<_UsedSize;i++)
	{
		promedio += _Array[i];
	}


	return promedio/_UsedSize;
}

template <class T>
void Array<T>::InsertElementAt(int pos, T &x)
{
	
	if(pos < _AllocSize){
		_Array[pos]= x;
		_UsedSize++;
		
	}
}

#endif