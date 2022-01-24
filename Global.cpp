#ifndef IO
#define IO
#include <iostream> 
#endif

#ifndef SDL
#define SDL
#include <SDL.h>
#endif

#include <Windows.h>
int score;
int max_score;
long Random(int from, int to)
{
	//srand(rand());
	return from + rand() % (to - from + 1);
}


int LenghtOf(const UINT16* arr, const UINT16 symbol = '\0')
{
	int i = 0;
	for (; arr[i] != symbol;i++);
	return i;
}
//Конкатинирует массив 2 после массива 1. Признак окончания-ноль.
void CatArray(UINT16* arr1, const UINT16* const arr2, const char* divider = "\0", bool debug = 0)
{
	int i = 0;
	int lenght = LenghtOf(arr2);
	for (; arr1[i] != '\0'; i++);
	if (strcmp(divider, "\0"))
	{
		arr1[i] = divider[0];
		i++;
	}

	if (debug)
	{
		for (int t = 0; t < lenght; i++, t++)
		{
			arr1[i] = arr2[t];
			std::cout << "arr1[" << i << "] = " << arr1[i] << std::endl;
		}
		arr1[i] = '\0';
		std::cout << "arr1 = " << arr1 << std::endl;
		system("Pause");

	}
	else
	{
		for (int t = 0; t < lenght; i++, t++)
		{
			arr1[i] = arr2[t];
		}
		arr1[i] = '\0';
	}
}

