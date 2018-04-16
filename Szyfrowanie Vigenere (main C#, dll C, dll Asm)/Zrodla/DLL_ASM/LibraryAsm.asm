;/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
;// Przedmiot: Jezyki assemblerowe - projekt                                                                    //
;// Autor: Patryk Gregorczuk                                                                                    //
;// Wersja: 1.0                                                                                                 //
;// Biblioteka DLL w Asemblerze																					//
;/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
;
;CHANGELOG:
;
;------------------------------------------------------------------------------------------------------------------
;Autor: Patryk Gregorczuk
;Data: 8.11.2017
;Wersja: 0.1
;Zmiany:
;- Utworzenie pliku.
;- Implementacja funkcji testujacej dzialanie biblioteki w programie glownym.
;------------------------------------------------------------------------------------------------------------------
;Autor: Patryk Gregorczuk
;Data: 18.12.2017
;Wersja: 0.3
;Zmiany:
;- Zdefiniowanie funkcji
;------------------------------------------------------------------------------------------------------------------
;Autor: Patryk Gregorczuk
;Data: 09.02.2018
;Wersja: 0.8
;Zmiany:
;- Implementacja szyfrowania oraz deszyfrowania, bez uzycia rejestrow MMX
;------------------------------------------------------------------------------------------------------------------
;Autor: Patryk Gregorczuk
;Data: 12.02.2018
;Wersja: 0.9
;Zmiany:
;- Usuniecie offsetu klucza jako argumentu obydwu funkcji i przypisanie stalego offsetu wynoszacego 0 zgodnie z regula przydzielania danych dla watkow
;- Implementacja wykorzystania rejestrow MMX
;------------------------------------------------------------------------------------------------------------------
;Autor: Patryk Gregorczuk
;Data: 12.02.2018
;Wersja: 1.0
;Zmiany:
;- Dodano poczatkowe chowanie rejestrow na stosie
;- Program oddany do oceny
;------------------------------------------------------------------------------------------------------------------
;==============================================================================================================================================================

.code

_DATA SEGMENT

; deklaracja tablicy przechowujacej wszystkie mozliwe do zaszyfrowania litery
cipherTable:
dw 0041h, 0104h, 0042h, 0043h, 0106h, 0044h, 0045h, 0118h, 0046h, 0047h
dw 0048h, 0049h, 004Ah, 004Bh, 004Ch, 0141h, 004Dh, 004Eh, 0143h, 004Fh
dw 00D3h, 0050h, 0051h, 0052h, 0053h, 015Ah, 0054h, 0055h, 0056h, 0057h
dw 0058h, 0059h, 005Ah, 0179h, 017Bh, 0061h, 0105h, 0062h, 0063h, 0107h
dw 0064h, 0065h, 0119h, 0066h, 0067h, 0068h, 0069h, 006Ah, 006Bh, 006Ch
dw 0142h, 006Dh, 006Eh, 0144h, 006Fh, 00F3h, 0070h, 0071h, 0072h, 0073h
dw 015Bh, 0074h, 0075h, 0076h, 0077h, 0078h, 0079h, 007Ah, 017Ah, 017Ch

; deklaracja dlugosci powyzszej tablicy
cipherTableLength db 70

_DATA ENDS

; Opis dalszego wykorzystania rejestrow w procedurach:
; RDI - rejestr przechowujacy indeks tablicy wejsciowej 'i'
; RBX - rejestr przechowuje adres pierwszego elementu tablicy wejsciowej
; RSI - rejestr przechowuje adres pierwszego elementu tablicy cipherTable
; R10/MM0 - rejestr przechowuje indeks litery z tablicy cipherKey ktora po wykonaniu szyfrowania/deszyfrowania nalezy wpisac w miejsce szyfrowanej/deszyfrowanej litery
; R13 - rejestr przechowuje zmienna 'j' analogicznie do biblioteki w jezyku C
; R14/MM1 - rejestr przechowuje indeks odpowiadajacej litery klucza z tablicy cipherTable
; R15/MM2 - rejestr przechowuje indeks odpowiadajacej szyfrowanej/deszyfrowanej litery z tablicy cipherTable

; private extern static void CodingAsm(StringBuilder segment, int bufferSize, StringBuilder key, int keyLength);
; Returns void as procedure only modifies passed data array.
; rcx = segment, rdx = bufferSize, r8 = key, r9 = keyLength

CodingAsm PROC export data:QWORD, dataSize:DWORD, key:QWORD, keyLength:DWORD

		PUSH RBX							; schowanie na stosie zawartosci rejestrow
		PUSH RSI							; jw
		PUSH R10							; jw
		PUSH R13							; jw
		PUSH R14							; jw
		PUSH R15							; jw
		XOR RDI, RDI						; wyzerowanie rejestru RDI przechowujacego indeks tablicy data
		MOV RBX, RCX						; przesuniecie adresu tablicy data do rejestru bazowego RBX
		XOR RAX, RAX						; wyzerowanie rejestru RAX
		XOR R13, R13						; wyzerowanie rejestru dla zmiennej 'j'
		LEA RSI, cipherTable				; zaladowanie do rejestru RSI efektywnego adresu poczatku tablicy cipherTable
MAINLOOP:
		CMP RDI, RDX						; sprawdz czy to nie koniec bufora 
		JE ENDPROCEDURE						; jezeli indeks bufora 'i' z rejestru RDI jest rowny dlugosci bufora z RDX, to skocz do ENDPROCEDURE
		CMP R13, R9							; inaczej sprawdz czy nie nalezy zresetowac indeksu klucza 'j'
		JNE CONTINUE						; jesli indeks klucza 'j' z rejestru R13 jest rozny od dlugosci klucza z R9, to skocz do CONTINUE
		XOR R13, R13						; inaczej wyzeruj indeks klucza 'j' z rejestru R13
CONTINUE:
		XOR R14, R14						; wyzerowanie rejestru R14 przechowujacego indeks litery z tablicy szyfrujacej
SEARCH_KEYINDEX_LOOP:						; petla wyszukujaca indeks tablicy cipherKey dla ktorego litera jest taka sama jak aktualna litera z klucza
		MOV AX, WORD PTR [RSI + 2 * R14]	; zaladuj do rejestru AX litere z tablicy cipherTable spod indeksu R14
		CMP [R8 + 2 * R13], AX				; porownaj litere z klucza z litera z tablicy cipherTable
		JE CONTINUE2						; jezeli sa takie same, to skocz do CONTINUE2
		INC R14								; inaczej zwieksz indeks tablicy cipherTable
		JMP SEARCH_KEYINDEX_LOOP			; kontynuuj szukanie indeksu klucza w tablicy cipherTable
CONTINUE2:					
		CMP R14, 0							; sprawdz czy indeks litery z tablicy szyfrujacej nie jest 0 - wowczas nie trzeba szyfrowac znaku
		JE NEXT_ITERATION					; jesli sa takie same wykonaj skok do NEXT_ITERATION bez szyfrowania znaku
		XOR R15, R15						; inaczej zacznij szukanie indeksu szyfrowanej litery w tablicy cipherKey - rejestr R15
SEARCH_LETTERINDEX_LOOP:
		CMP R15b, cipherTableLength			; sprawdz czy nie koniec tablicy szyfrujacej
		JE NEXT_ITERATION					; jesli tak, oznacza to, ze znak nie moze zostac zaszyfrowany - wykonaj skok do NEXT_ITERATION
		MOV AX, WORD PTR [RSI + 2 * R15]	; inaczej zaladuj do rejestru AX litere z tablicy cipherTable spod indeksu R15
		CMP [RBX + 2 * RDI], AX				; porownaj szyfrowana litere z litera z tablicy cipherTable
		JE ENCRYPT_LETTER					; jesli indeks zostal znaleziony litera moze zostac zaszyfrowana - wykonaj skok do ENCRYPT_LETTER
		INC R15								; inaczej zwieksz indeks R15
		JMP SEARCH_LETTERINDEX_LOOP			; kontynuuj szukanie indeksu szyfrowanej litery w tablicy cipherTable
NEXT_ITERATION:								; przygotowanie nastepnej iteracji petli MAINLOOP
		INC RDI								; inkrementuj 'i'
		INC R13								; inkrementuj 'j'
		JMP MAINLOOP						; kontynuuj glowna petle
ENCRYPT_LETTER:
		PXOR MM0, MM0						; wyzeruj rejestr MM0 - bedzie on przechowywal indeks spod ktorego nalezy odczytac zaszyfrowany znak 
		MOVD MM1, R14						; zaladuj do rejestru MM1 indeks litery klucza z R14
		MOVD MM2, R15						; zaladuj do rejestru MM2 indeks odpowiadajacej szyfrowanej litery z R15
		PADDW MM0, MM1						; indeks zaszyfrowanego znaku oblicza sie dodajac do siebie indeks klucza w tablicy(MM1) oraz indeks szyfrowanej litery w tablicy(MM2)
		PADDW MM0, MM2						; jw
		MOVD R10, MM0						; zaladuj indeks wynikowej litery do R10
		XOR RAX, RAX						; wyzerowanie rejestru RAX przez wpisaniem dlugosci tablicy cipherTable do AL
		MOV AL, cipherTableLength			; wpisanie dlugosci tablicy cipherTable do AL
		DEC RAX								; zmniejszenie dlugosci tablicy o 1 w celu porownania w postaci ostatniego indeksu tejze tablicy
		CMP R10, RAX						; porownaj najwiekszy mozliwy indeks tablicy z indeksem zaszyfrowanego znaku
		JLE CONTINUE_ENCRYPTION				; jesli indeks miesci sie w rozmiarach tablicy cipherTable kontynuuj szyfrowanie
		INC RAX								; jesli nie, inkrementuj spowrotem z postaci ostatniego indeksu do rozmiaru tablicy
		MOVD MM3, RAX						; zaladuj rozmiar tablicy do rejestru MM3 w celu wykonania korekty wynikowego indeksu
		PSUBW MM0, MM3						; i odejmij od indeksu zaszyfrowanego znaku
CONTINUE_ENCRYPTION:
		MOVD R10, MM0						; zaladuj indeks wynikowej litery do R10
		MOV AX, WORD PTR [RSI + 2 * R10]	; zaladuj do rejestru AX litere z tablicy cipherTable
		MOV [RBX + 2 * RDI], AX				; przypisz ja jako zaszyfrowana litere pod odpowiedni indeks bufora wejsciowego
		JMP NEXT_ITERATION					; skok do przygotowania kolejnej iteracji petli glownej
ENDPROCEDURE:
		POP R15								; zdjecie ze stosu zawartosci rejestrow
		POP R14								; jw
		POP R13								; jw
		POP R10								; jw
		POP RSI								; jw
		POP RBX								; jw
		RET									; powrot z procedury
CodingAsm ENDP

; private extern static void DecodingAsm(StringBuilder segment, int bufferSize, StringBuilder key, int keyLength);
; Returns void as procedure only modifies passed data array.
; rcx = segment, rdx = bufferSize, r8 = key, r9 = keyLength

DecodingAsm PROC export dataSize:DWORD, data:QWORD, key:QWORD, keyLength:DWORD

		PUSH RBX							; schowanie na stosie zawartosci rejestrow
		PUSH RSI							; jw
		PUSH R10							; jw
		PUSH R13							; jw
		PUSH R14							; jw
		PUSH R15							; jw
		XOR RDI, RDI								; wyzerowanie rejestru RDI przechowujacego indeks tablicy data
		MOV RBX, RCX								; przesuniecie adresu tablicy data do rejestru bazowego RBX
		XOR RAX, RAX								; wyzerowanie rejestru RA
		XOR R13, R13								; wyzerowanie rejestru dla zmiennej 'j'
		LEA RSI, cipherTable						; zaladowanie do rejestru RSI efektywnego adresu poczatku tablicy cipherTable
MAINLOOP:
		CMP RDI, RDX						; sprawdz czy to nie koniec bufora 
		JE ENDPROCEDURE						; jezeli indeks bufora 'i' z rejestru RDI jest rowny dlugosci bufora z RDX, to skocz do ENDPROCEDURE
		CMP R13, R9							; inaczej sprawdz czy nie nalezy zresetowac indeksu klucza 'j'
		JNE CONTINUE						; jesli indeks klucza 'j' z rejestru R13 jest rozny od dlugosci klucza z R9, to skocz do CONTINUE
		XOR R13, R13						; inaczej wyzeruj indeks klucza 'j' z rejestru R13
CONTINUE:
		XOR R14, R14						; wyzerowanie rejestru R14 przechowujacego indeks litery z tablicy szyfrujacej
SEARCH_KEYINDEX_LOOP:						; petla wyszukujaca indeks tablicy cipherKey dla ktorego litera jest taka sama jak aktualna litera z klucza
		MOV AX, WORD PTR [RSI + 2 * R14]	; zaladuj do rejestru AX litere z tablicy cipherTable spod indeksu R14
		CMP [R8 + 2 * R13], AX				; porownaj litere z klucza z litera z tablicy cipherTable
		JE CONTINUE2						; jezeli sa takie same, to skocz do CONTINUE2
		INC R14								; inaczej zwieksz indeks tablicy cipherTable
		JMP SEARCH_KEYINDEX_LOOP			; kontynuuj szukanie indeksu klucza w tablicy cipherTable
CONTINUE2:					
		CMP R14, 0							; sprawdz czy indeks litery z tablicy szyfrujacej nie jest 0 - oznacza to ze litera nie byla szyfrowana
		JE NEXT_ITERATION					; jesli sa takie same wykonaj skok do NEXT_ITERATION bez deszyfrowania litery
		XOR R15, R15						; inaczej zacznij szukanie indeksu szyfrowanej litery w tablicy cipherKey - rejestr R15
SEARCH_LETTERINDEX_LOOP:
		CMP R15b, cipherTableLength			; sprawdz czy nie koniec tablicy szyfrujacej
		JE NEXT_ITERATION					; jesli tak, oznacza to, ze znak nie zostal zaszyfrowany - wykonaj skok do NEXT_ITERATION
		MOV AX, WORD PTR [RSI + 2 * R15]	; inaczej zaladuj do rejestru AX litere z tablicy cipherTable spod indeksu R15
		CMP [RBX + 2 * RDI], AX				; porownaj odszyfrowywana litere z litera z tablicy cipherTable
		JE DECRYPT_LETTER					; jesli indeks zostal znaleziony litera moze zostac odszyfrowana - wykonaj skok do DECRYPT_LETTER
		INC R15								; inaczej zwieksz indeks R15
		JMP SEARCH_LETTERINDEX_LOOP			; kontynuuj szukanie indeksu deszyfrowywanej litery w tablicy cipherTable
NEXT_ITERATION:								; przygotowanie nastepnej iteracji petli MAINLOOP
		INC RDI								; inkrementuj 'i'
		INC R13								; inkrementuj 'j'
		JMP MAINLOOP						; kontynuuj glowna petle
DECRYPT_LETTER:
		PXOR MM0, MM0						; wyzeruj rejestr MM0 - bedzie on przechowywal indeks spod ktorego nalezy odczytac odszyfrowany znak 
		MOVD MM1, R14						; zaladuj do rejestru MM1 indeks litery klucza z R14
		MOVD MM2, R15						; zaladuj do rejestru MM2 indeks odpowiadajacej deszyfrowywanej litery z R15
		PADDW MM0, MM2						; indeks odszyfrowanego znaku oblicza sie odejmujac od indeksu deszyfrowywanej litery w tablicy(MM2) indeks klucza w tablicy(MM1)
		PSUBW MM0, MM1						; jw
		MOVD R10, MM0						; zaladuj indeks wynikowej litery do R10
		CMP R10b, 0							; sprawdz czy indeks odszyfrowanego znaku po odejmowaniu nie jest ujemny
		JGE CONTINUE_DECRYPTION				; jesli indeks nie jest ujemny kontynuuj deszyfrowanie
		XOR RAX, RAX						; inaczej wyzeruj rejestr RAX przez wpisaniem dlugosci tablicy cipherTable do AL
		MOV AL, cipherTableLength			; wpisanie dlugosci tablicy cipherTable do AL	
		MOVD MM3, RAX						; zaladuj rozmiar tablicy do rejestru MM3 w celu wykonania korekty wynikowego indeksu
		PADDW MM0, MM3						; i odejmij od indeksu zaszyfrowanego znaku
CONTINUE_DECRYPTION:
		MOVD R10, MM0						; zaladuj indeks wynikowej litery do R10
		MOV AX, WORD PTR [RSI + 2 * R10]	; zaladuj do rejestru AX litere z tablicy cipherTable
		MOV [RBX + 2 * RDI], AX				; przypisz ja jako zaszyfrowana litere pod odpowiedni indeks bufora wejsciowego
		JMP NEXT_ITERATION					; skok do przygotowania kolejnej iteracji petli glownej
ENDPROCEDURE:
		POP R15								; zdjecie ze stosu zawartosci rejestrow
		POP R14								; jw
		POP R13								; jw
		POP R10								; jw
		POP RSI								; jw
		POP RBX								; jw
		RET									; powrot z procedury
DecodingAsm ENDP

END