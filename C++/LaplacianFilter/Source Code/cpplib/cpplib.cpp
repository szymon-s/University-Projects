#include "cpplib.h"

void cppDLL(unsigned char* bmp, unsigned char* Scan0, int width, int height, int stride, int i)
{
	for (i; i < height; i++)
	{
		for (int j = 3; j < width ; j += 3)
		{
			for (int k = 0; k < 3; k++)
			{
				short int value = 0;

				value = (short int)Scan0[i * stride + j + k]*4;
				value -= (short int)bmp[i * stride + j - 3 + k];
				value -= (short int)bmp[i * stride + j + 3 + k];
				value -= (short int)bmp[(i - 1) * stride + j + k];
				value -= (short int)bmp[(i + 1) * stride + j + k];
				if (value < 0)
					value = 0;
				else if (value > 255)
					value = 255;
				Scan0[i * stride + j+k] = value;
			}
		}
	}
}