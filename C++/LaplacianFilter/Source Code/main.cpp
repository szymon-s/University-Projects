#include "header.h"


 ULONG_PTR gdiplusToken;








 int main()
 {

	 HINSTANCE cppDLLhandler = LoadLibrary(L"cpplib.dll");
	 HINSTANCE asmDLLhandler = LoadLibrary(L"asmlib.dll");
	 GdiplusStartupInput gdiplusStartupInput;
	 GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	 if (cppDLLhandler == NULL)
	 {
		 std::cout << "BLAD PODCZAS WCZYTYWANIA cpplib.dll !" << std::endl;
		 return 1;
	 }
	 if (asmDLLhandler == NULL)
	 {
		 std::cout << "BLAD PODCZAS WCZYTYWANIA asmlib.dll !" << std::endl;
		 return 1;
	 }
	 int wybor=1;
	 while (wybor==1)
	 {
	 
		 int wyborDLL = 0;
		 std::cout << "Wybierz ktora biblioteke chcesz uzyc: \n1. Biblioteka ASM\n2. Biblioteka C++\n";
		 std::cin >> wyborDLL;
		 if (wyborDLL < 1 || wyborDLL>2)
		 {
			 std::cout << "Wybrano niepoprawny numer biblioteki!\n";
			 return 4;
		 }
		 std::string filename = "";
		 std::cout << "\nPodaj nazwe pliku wejsciowego wraz z rozszerzeniem (.bmp, .png, .jpg, jpeg., .gif, .tif, .tiff)" << std::endl;
		 std::cin >> filename;
		 std::string filenameOutput = "";
		 std::cout << "\nPodaj nazwe pliku wyjsciowego wraz z rozszerzeniem .bmp" << std::endl;
		 std::cin >> filenameOutput;
		 int threads = 0;
		 std::cout << std::endl << "Podaj liczbe watkow (1-64)" << std::endl;
		 std::cin >> threads;
		 if (threads < 1 || threads > 64)
		 {
			 std::cout << "Podano niepoprawna ilosc watkow!\n";
			 return 5;
		 }
		 std::thread* threadsTable = new std::thread[threads];
		 Bitmap* bitmapa_wynikowa = new Bitmap(std::wstring(filename.begin(), filename.end()).c_str());

		 if (bitmapa_wynikowa->GetHeight() == 0)
		 {
			 std::cout << "Blad podczas wczytywania bitmapy!" << std::endl;
			 return 3;
		 }

		 int height = bitmapa_wynikowa->GetHeight();
		 int width = bitmapa_wynikowa->GetWidth()*3-3;
		 BitmapData bitmapData;
		 bitmapa_wynikowa->LockBits(&Rect(0, 0, bitmapa_wynikowa->GetWidth(), bitmapa_wynikowa->GetHeight()), ImageLockModeWrite, PixelFormat24bppRGB, &bitmapData);
		 int stride = std::abs(bitmapData.Stride);
		 unsigned char* bgrtab = new unsigned char[bitmapData.Height * stride];

		 for (int i = 0; i < bitmapData.Stride * bitmapData.Height; i++)
		 {
			 bgrtab[i] = ((unsigned char*)bitmapData.Scan0)[i];
		 }

		 ptrfunkcjaASM asmDLL = (ptrfunkcjaASM)GetProcAddress(asmDLLhandler, "asmDLL");
		 ptrfunkcjaCPP cppDLL = (ptrfunkcjaCPP)GetProcAddress(cppDLLhandler, "cppDLL");
		 auto start = std::chrono::steady_clock::now();
		 int count = height / threads;
		 int reszta = height % threads;
		 if (wyborDLL == 1)
		 {
			 if (threads != 1)
				 threadsTable[0] = std::thread(asmDLL, bgrtab, (unsigned char*)bitmapData.Scan0, width, count, stride,1);
			 else
				 threadsTable[0] = std::thread(asmDLL, bgrtab, (unsigned char*)bitmapData.Scan0, width, count - 1, stride, 1);

			 for (int i = 1; i < threads - 1; i++)
			 {
				 threadsTable[i] = std::thread(asmDLL, bgrtab, (unsigned char*)bitmapData.Scan0, width, count * i + count, stride, (count * i));
			 }
			 if (threads > 1)
				 threadsTable[threads - 1] = std::thread(asmDLL, bgrtab, (unsigned char*)bitmapData.Scan0, width, count * (threads - 1) + count + reszta - 1, stride, count * (threads - 1));

		 }
		 else
		 {
			 if (threads != 1)
				 threadsTable[0] = std::thread(cppDLL, bgrtab, (unsigned char*)bitmapData.Scan0, width, count, stride, 1);
			 else
				 threadsTable[0] = std::thread(cppDLL, bgrtab, (unsigned char*)bitmapData.Scan0, width, count - 1, stride, 1);

			 for (int i = 1; i < threads - 1; i++)
			 {
				 threadsTable[i] = std::thread(cppDLL, bgrtab, (unsigned char*)bitmapData.Scan0, width, count * i + count, stride, count * i);
			 }
			 if (threads > 1)
				 threadsTable[threads - 1] = std::thread(cppDLL, bgrtab, (unsigned char*)bitmapData.Scan0, width, count * (threads - 1) + count + reszta - 1, stride, count * (threads - 1));
		 }

		 for (int k = 0; k < threads; k++)
		 {
				 threadsTable[k].join();
		 }

		 bitmapa_wynikowa->UnlockBits(&bitmapData);
		 auto end = std::chrono::steady_clock::now();
		 CLSID pngClsid;
		 CLSIDFromString(L"{557cf400-1a04-11d3-9a73-0000f81ef32e}", &pngClsid);
		 bitmapa_wynikowa->Save(std::wstring(filenameOutput.begin(), filenameOutput.end()).c_str(), &pngClsid, NULL);
		 std::chrono::duration<double> elapsed_seconds = end - start;
		 std::cout << "Czas wykonania: " << elapsed_seconds.count() << "sekund.\n"<<std::endl;
		 //delete[] bgrtab;
		 //delete[] threadsTable;
		 //delete bitmapa_wynikowa;
		 std::cout << "Aby kontynuowac nacisnij 1, aby zakonczyc nacisnij dowolny inny klawisz..." << std::endl;
		 std::cin >> wybor;
	 }
	return 0;
 }