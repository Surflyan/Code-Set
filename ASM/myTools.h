#pragma once

template <typename T>
T * change_length_of_1Darray(T * arr, int oldLength, int newLength)
{
	T * temp = new T[newLength];
	for (int i = 0; i < oldLength; i++)
	{
		temp[i] = arr[i];
		arr[i].~T();
	}
	delete[] arr;
	return temp;
}