.data
maska qword 0707070207010700h						;maska potrzebna do przestawienia bitóww rejestrze mmx

.code

asmDLL		proc 

			push rbx								;zapisanie potrzebnych rejestrów
			push rbp
			sub rsp,10h								;przygotowanie miejsca na stosie
			mov rbp,rsp
			mov r10, rdx							;relokacja parametru funkcji
			mov esi,3								;przygotowanie indeksu j

forROWS:	cmp dword ptr[rbp+50h], r9d				;sprawdzanie czy i jest mniejsze od zadanej wysokoœci
			jae DONE								;jeœli nie jest, to pêtla siê koñczy i przechodzimy do etykiety DONE

forCOLUMNS:	cmp esi, r8d							;sprawdzanie czy j jest mniejsze od zadanej szerokoœci
			jae endCOLUMNS							;jeœli nie jest, to przechodzimy do etykiety endCOLUMNS

			mov eax,dword ptr[rbp+50h]				;wczytywanie piksela s¹siaduj¹cego od do³u: ³adujemy wartoœæ i do rejestru eax
			inc eax									;inkrementujemy
			imul dword ptr[rbp+48h]					;mno¿ymy razy wartoœæ stride
			add eax,esi								;dodajemy j
			mov ebx, dword ptr[rcx+rax]				;³adujemy wartoœæ RGB piksela do rejestru ebx
			movq mm3,rbx							;³adujemy wartoœæ do rejestru mmx
			pshufb mm3, maska						;przestawiamy dane w rejestrze mmx tak aby wartoœci RGB by³y oddzielone dwoma zerami

			mov eax,dword ptr[rbp+50h]				;wczytywanie piksela s¹siaduj¹cego od góry: ³adujemy wartoœci i do rejestru eax
			dec eax									;dekrementujemy
			imul dword ptr[rbp+48h]					;mno¿ymy razy wartosæ stride
			add eax,esi								;dodajemy j
			mov ebx, dword ptr[rcx+rax]				;³adujemy wartoœæ RGB piksela do rejestru ebx
			movq mm4,rbx							;³adujemy wartoœæ do rejestru mmx
			pshufb mm4, maska						;przestawiamy dane w rejestrze mmx
				
			mov eax,dword ptr[rbp+50h]				;obliczenie wartoœci indeksu dla obliczanego piksela oraz pikseli s¹siaduj¹cych z nim po bokach
			imul dword ptr[rbp+48h]					;pobran¹ do rejestru eax wartoœæ i mno¿ymy razy wartoœæ stride
			add eax,esi								;dodajemy j

			mov ebx, dword ptr[rcx+rax]				;przenosimy do rejestru ebx wartoœci piksela dla którego obliczana jest wartoœæ
			movq mm0,rbx							;³adujemy wartoœci do rejestru mmx
			pshufb mm0, maska						;przestawiamy dane w rejestrze mmx
			psllw mm0,2								;mno¿ymy wartoœci razy cztery

			mov ebx, dword ptr[rcx+rax-3]			;przenosimy do rejestru ebx wartoœci piksela s¹siaduj¹cego po lewo
			movq mm1,rbx							;³adujemy wartoœci do rejestru mmx
			pshufb mm1, maska						;przestawiamy dane w rejestrze mmx

			mov ebx, dword ptr[rcx+rax+3]			;przenosimy do rejestru ebx wartoœci piksela s¹siaduj¹cego po prawo
			movq mm2,rbx							;³adujemy wartoœci do rejestru mmx
			pshufb mm2, maska						;przestawiamy dane w rejestrze mmx

			psubusw mm0, mm1						;odejmujemy od obliczanego piksela piksel s¹siaduj¹cy po lewo
			psubusw mm0, mm2						;odejmujemy od obliczanego piksela piksel s¹siaduj¹cy po prawo
			psubusw mm0, mm3						;odejmujemy od obliczanego piksela piksel s¹siaduj¹cy od do³u	
			psubusw mm0, mm4						;odejmujemy od obliczanego piksela piksel s¹siaduj¹cy od góry

			movq mmword ptr [rbp], mm0				;wynik odejmowania zapisujemy na stosie

			mov dl, byte ptr[rbp]					;przenosimy now¹ wartoœæ R do rejestru dl
			mov [r10+rax ], dl						;wstawiamy now¹ wartoœæ do tablicy wynikowej
			mov dl, byte ptr[rbp+2]					;przenosimy now¹ wartoœæ G do rejestru dl
			mov [r10+rax+1], dl						;wstawiamy now¹ wartoœæ do tablicy wynikowej
			mov dl, byte ptr[rbp+4]					;przenosimy now¹ wartoœæ B do rejestru dl
			mov [r10+rax+2], dl						;wstawiamy now¹ wartoœæ do tablicy wynikowej

			add esi,3								;zwiêkszamy indeks j o 3
			jmp forCOLUMNS							;przechodzimy do kolejnej iteracji pêtli wewnêtrznej

endCOLUMNS:	inc dword ptr[rbp+50h]					;inkrementujemy indeks i
			xor esi, esi							;zerujemy indeks j
			jmp forROWS								;przechodzimy do kolejnej iteracji pêtli zewnêtrznej

DONE:		mov rsp, rbp							;przywracamy wskaŸnik stosu
			add rsp, 10h
			pop rbp									;œci¹gamy ze stosu rejestry zachowane na pocz¹tku funkcji
			pop rbx
			ret										

asmDLL		endp
end