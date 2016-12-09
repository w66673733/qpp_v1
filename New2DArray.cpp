#include "TDCBlock.h"


CNew2DArray::CNew2DArray()
{
    //_p_syn = new __int64[2];//CS.syn_num_per_sec
//    m_pp_apdTime = new __int64[2];//CS.apd_channel_num

}

template<class T>
T** CNew2DArray::newArrayM(int row, int col)
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



void CNew2DArray::freeArray(void **arr)
{
    if (arr != NULL)
        free(arr);
}
template<class T>
T** CNew2DArray::newArray(int row)
{
    int size = sizeof(T);

	const int col = 4;
    T *p = (T*)malloc(size * row * col);
	T (*arr)[col] = (T(*)[col])p;


	return (T**)arr;
}

template<class T>
T** CNew2DArray::newArrayN(int row, int col)
{
    T **arr = new T*[row];
    while(row--)
        arr[row] = new T[col];

    return arr;
}

