#ifndef Cpplib_h
#define Cpplib_h
#pragma comment (lib, "GdiPlus.lib")
#include <iostream>
#include <windows.h>
#include<gdiplus.h>
#include<gdiplusheaders.h>
#include<mutex>

#if BUILDING_DLL
#	define DLLIMPORT __declspec (dllexport)
#else 
#	define DLLIMPORT __declspec (dllimport)
#endif

extern "C" DLLIMPORT void cppDLL(unsigned char* bmp, unsigned char* Scan0,  int width, int height,int stride, int i);


#endif