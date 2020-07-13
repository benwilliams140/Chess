#ifndef ARRAY2D_H
#define ARRAY2D_H

template <class T>
class Array2D
{
public:
	Array2D(int = 0, int = 0);
	~Array2D();

	T* operator[](int);

private:
	T** arr;
	int cols, rows;
};

template <class T>
Array2D<T>::Array2D(int _cols, int _rows) : cols(_cols), rows(_rows)
{
	arr = new T*[cols];
	for (int _i = 0; _i < cols; ++_i)
		arr[_i] = new T[rows];
}

template <class T>
Array2D<T>::~Array2D()
{
	for (int _i = 0; _i < cols; ++_i)
		delete[] arr[_i];
	delete[] arr;
}

template <class T>
T* Array2D<T>::operator[](int _index)
{
	return arr[_index];
}

#endif