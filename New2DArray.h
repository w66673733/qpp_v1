#ifndef _NEW2DARRAY_H_
#define _NEW2DARRAY_H_
#include "Constants.h"
template<class T>
class CNew2DArray
{
    public:

		T** newArrayM(int row, int col);

		T** newArrayM(int row);

		void freeArray(void **arr);

		T** newArrayN(int row, int col);

		void deleteArray(T **arr);
    public:

};

template<class T>
T** CNew2DArray<T>::newArrayM(int row, int col)
{
    int size = sizeof(T); 
    int pointSize = sizeof(T*);


    T **arr = (T**)malloc(pointSize*row + size * row * col);

	if (arr != NULL)
	{
		memset(arr, 0, pointSize*row + size*row*col);
		T* head = (T*)((int)arr + pointSize*row);
		while(row--)
			arr[row] = (T*)(int(head) + row*col*size);
	}

	return (T**)arr;
}


template<class T>
T** CNew2DArray<T>::newArrayM(int row)
{
    int size = sizeof(T);

	const int col = 4;
    T *p = (T*)malloc(size * row * col);
	T (*arr)[col] = (T(*)[col])p;


	return (T**)arr;
}

template<class T>
void CNew2DArray<T>::freeArray(void **arr)
{
    if (arr != NULL)
        free(arr);
}

template<class T>
T** CNew2DArray<T>::newArrayN(int row, int col)
{
    T **arr = new T*[row];
    while(row--)
        arr[row] = new T[col];

    return arr;
}

template<class T>
void CNew2DArray<T>::deleteArray(T **arr)
{
    int len = (int)*(arr -4);
	int size = sizeof(T);
	len /= size;
    for(int i = 0; i < len; i++)
    {
        delete [] arr[i];
    }
    delete[] arr;
}
#endif


