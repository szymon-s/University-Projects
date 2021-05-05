#include "header.h"






void threadFunction(unsigned char* bmp,unsigned char* Scan0, int stride, int width, int i, int size, int wyborDLL)
{
	
	for (i ; i <size; i++)
	{
		for (int j = 3; j < width*3-3; j+=3)
		{
			if (wyborDLL == 2)
			{
				cppDLL(bmp,Scan0, stride, i, j);
			}
			else
			{
				asmDLL( bmp,Scan0,stride, i, j);
			}
		}
	}
}
