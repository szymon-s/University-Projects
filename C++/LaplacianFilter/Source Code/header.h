#ifndef Header_h
#define Header_h
#pragma comment (lib, "GdiPlus.lib")
#include <windows.h>
#include <iostream>
#include<gdiplus.h>
#include <thread>
#include <string>
#include<gdiplusheaders.h>
#include <chrono>
#include <cstdio>

using namespace Gdiplus;

typedef void (*ptrfunkcjaCPP)(unsigned char* bmp, unsigned char* Scan0, int width, int height, int stride, int i);
typedef void(__fastcall* ptrfunkcjaASM)(unsigned char* bmp, unsigned char* Scan0, int width, int height, int stride, int i);




#endif
