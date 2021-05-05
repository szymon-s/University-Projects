.data
maska qword 0707070207010700h						;maska potrzebna do przestawienia bit�ww rejestrze mmx

.code

asmDLL		proc 

			push rbx								;zapisanie potrzebnych rejestr�w
			push rbp
			sub rsp,10h								;przygotowanie miejsca na stosie
			mov rbp,rsp
			mov r10, rdx							;relokacja parametru funkcji
			mov esi,3								;przygotowanie indeksu j

forROWS:	cmp dword ptr[rbp+50h], r9d				;sprawdzanie czy i jest mniejsze od zadanej wysoko�ci
			jae DONE								;je�li nie jest, to p�tla si� ko�czy i przechodzimy do etykiety DONE

forCOLUMNS:	cmp esi, r8d							;sprawdzanie czy j jest mniejsze od zadanej szeroko�ci
			jae endCOLUMNS							;je�li nie jest, to przechodzimy do etykiety endCOLUMNS

			mov eax,dword ptr[rbp+50h]				;wczytywanie piksela s�siaduj�cego od do�u: �adujemy warto�� i do rejestru eax
			inc eax									;inkrementujemy
			imul dword ptr[rbp+48h]					;mno�ymy razy warto�� stride
			add eax,esi								;dodajemy j
			mov ebx, dword ptr[rcx+rax]				;�adujemy warto�� RGB piksela do rejestru ebx
			movq mm3,rbx							;�adujemy warto�� do rejestru mmx
			pshufb mm3, maska						;przestawiamy dane w rejestrze mmx tak aby warto�ci RGB by�y oddzielone dwoma zerami

			mov eax,dword ptr[rbp+50h]				;wczytywanie piksela s�siaduj�cego od g�ry: �adujemy warto�ci i do rejestru eax
			dec eax									;dekrementujemy
			imul dword ptr[rbp+48h]					;mno�ymy razy wartos� stride
			add eax,esi								;dodajemy j
			mov ebx, dword ptr[rcx+rax]				;�adujemy warto�� RGB piksela do rejestru ebx
			movq mm4,rbx							;�adujemy warto�� do rejestru mmx
			pshufb mm4, maska						;przestawiamy dane w rejestrze mmx
				
			mov eax,dword ptr[rbp+50h]				;obliczenie warto�ci indeksu dla obliczanego piksela oraz pikseli s�siaduj�cych z nim po bokach
			imul dword ptr[rbp+48h]					;pobran� do rejestru eax warto�� i mno�ymy razy warto�� stride
			add eax,esi								;dodajemy j

			mov ebx, dword ptr[rcx+rax]				;przenosimy do rejestru ebx warto�ci piksela dla kt�rego obliczana jest warto��
			movq mm0,rbx							;�adujemy warto�ci do rejestru mmx
			pshufb mm0, maska						;przestawiamy dane w rejestrze mmx
			psllw mm0,2								;mno�ymy warto�ci razy cztery

			mov ebx, dword ptr[rcx+rax-3]			;przenosimy do rejestru ebx warto�ci piksela s�siaduj�cego po lewo
			movq mm1,rbx							;�adujemy warto�ci do rejestru mmx
			pshufb mm1, maska						;przestawiamy dane w rejestrze mmx

			mov ebx, dword ptr[rcx+rax+3]			;przenosimy do rejestru ebx warto�ci piksela s�siaduj�cego po prawo
			movq mm2,rbx							;�adujemy warto�ci do rejestru mmx
			pshufb mm2, maska						;przestawiamy dane w rejestrze mmx

			psubusw mm0, mm1						;odejmujemy od obliczanego piksela piksel s�siaduj�cy po lewo
			psubusw mm0, mm2						;odejmujemy od obliczanego piksela piksel s�siaduj�cy po prawo
			psubusw mm0, mm3						;odejmujemy od obliczanego piksela piksel s�siaduj�cy od do�u	
			psubusw mm0, mm4						;odejmujemy od obliczanego piksela piksel s�siaduj�cy od g�ry

			movq mmword ptr [rbp], mm0				;wynik odejmowania zapisujemy na stosie

			mov dl, byte ptr[rbp]					;przenosimy now� warto�� R do rejestru dl
			mov [r10+rax ], dl						;wstawiamy now� warto�� do tablicy wynikowej
			mov dl, byte ptr[rbp+2]					;przenosimy now� warto�� G do rejestru dl
			mov [r10+rax+1], dl						;wstawiamy now� warto�� do tablicy wynikowej
			mov dl, byte ptr[rbp+4]					;przenosimy now� warto�� B do rejestru dl
			mov [r10+rax+2], dl						;wstawiamy now� warto�� do tablicy wynikowej

			add esi,3								;zwi�kszamy indeks j o 3
			jmp forCOLUMNS							;przechodzimy do kolejnej iteracji p�tli wewn�trznej

endCOLUMNS:	inc dword ptr[rbp+50h]					;inkrementujemy indeks i
			xor esi, esi							;zerujemy indeks j
			jmp forROWS								;przechodzimy do kolejnej iteracji p�tli zewn�trznej

DONE:		mov rsp, rbp							;przywracamy wska�nik stosu
			add rsp, 10h
			pop rbp									;�ci�gamy ze stosu rejestry zachowane na pocz�tku funkcji
			pop rbx
			ret										

asmDLL		endp
end