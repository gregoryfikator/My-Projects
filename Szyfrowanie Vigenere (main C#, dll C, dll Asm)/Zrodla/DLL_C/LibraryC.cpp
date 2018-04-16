/*
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Przedmiot: Jezyki assemblerowe - projekt                                                                    //
// Autor: Patryk Gregorczuk                                                                                    //
// Wersja: 1.0	                                                                                               //
// Biblioteka DLL w jezyku C																				   //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CHANGELOG:

------------------------------------------------------------------------------------------------------------------
Autor: Patryk Gregorczuk
Data: 8.11.2017
Wersja: 0.1
Zmiany:
- Utworzenie pliku.
- Implementacja funkcji testujacej dzialanie biblioteki w programie glownym.
------------------------------------------------------------------------------------------------------------------
Autor: Patryk Gregorczuk
Data: 18.12.2017
Wersja: 0.3
Zmiany:
- Implementacja funkcji szyfrujacej i deszyfrujacej
- Funkcje wykorzystuja zawarty w bibliotece szyfrogram dzieki ktoremu uwzgledniane beda polskie znaki
------------------------------------------------------------------------------------------------------------------
Autor: Patryk Gregorczuk
Data: 09.02.2018
Wersja: 0.8
Zmiany:
- Sprzatanie kodu
------------------------------------------------------------------------------------------------------------------
Autor: Patryk Gregorczuk
Data: 12.02.2018
Wersja: 0.9
Zmiany:
- Optymalizacja funkcji szyfrujacej
- Usuniecie offsetu klucza jako argumentu obydwu funkcji i przypisanie stalego offsetu wynoszacego 0 zgodnie z regula przydzielania danych dla watkow
------------------------------------------------------------------------------------------------------------------
Autor: Patryk Gregorczuk
Data: 12.02.2018
Wersja: 1.0
Zmiany:
- Dodanie komentarzy
------------------------------------------------------------------------------------------------------------------
==============================================================================================================================================================
*/

#include "stdafx.h"
#include "LibraryC.h"

wchar_t baseCryptogram[] =
{
	L'A', L'•', L'B', L'C', L'∆', L'D', L'E', L' ', L'F', L'G',
	L'H', L'I', L'J', L'K', L'L', L'£', L'M', L'N', L'—', L'O',
	L'”', L'P', L'Q', L'R', L'S', L'å', L'T', L'U', L'V', L'W',
	L'X', L'Y', L'Z', L'è', L'Ø', L'a', L'π', L'b', L'c', L'Ê',
	L'd', L'e', L'Í', L'f', L'g', L'h', L'i', L'j', L'k', L'l',
	L'≥', L'm', L'n', L'Ò', L'o', L'Û', L'p', L'q', L'r', L's',
	L'ú', L't', L'u', L'v', L'w', L'x', L'y', L'z', L'ü', L'ø'
};

int cryptogramLength = 70;

void _stdcall CodingC(wchar_t* wcharArray, int bufferSize, wchar_t* key, int keyLength)
{
	int cryptogramKeyIndex;		// zmienna przechowuje indeks litery klucza w tablicy szyfrujacej
	int cryptogramLetterIndex;	// zmienna przechowuje indeks szyfrowanej litery w tablicy szyfrujacej
	bool validLetterOccured;	// zmienna oznajmiajaca czy w biezacej iteracji przetwarzana jest znak ktory znajduje sie w tablicy szyfrujacej

	// petla przechodzaca po wszystkich znakach szyfrowanej tablicy - wcharArray
	for (int i = 0, j = 0; i < bufferSize; ++i, ++j)
	{
		// jezeli indeks klucza jest rowny dlugosci klucza, nalezy go wyzerowac
		if (j == keyLength)
		{
			j = 0;
		}

		// petla wyszukujaca indeks litery klucza w tablicy szyfrujacej
		for (cryptogramKeyIndex = 0; cryptogramKeyIndex < cryptogramLength; ++cryptogramKeyIndex)	
		{
			if (key[j] == baseCryptogram[cryptogramKeyIndex])
			{
				break;
			}
		}

		// dalsze operacje maja sens jezeli litera klucza jest inna niz pierwsza w tablicy - wtedy zaszyfrowana litera bedzie identyczna jak szyfrowana
		if (cryptogramKeyIndex != 0)
		{
			// petla wyszukujaca indeks szyfrowanej litery w tablicy szyfrujacej
			for (cryptogramLetterIndex = 0, validLetterOccured = false; cryptogramLetterIndex < cryptogramLength; ++cryptogramLetterIndex)
			{
				if (wcharArray[i] == baseCryptogram[cryptogramLetterIndex])
				{
					validLetterOccured = true;	// znak znajduje sie w szyfrogramie - moze zostac zakodowany
					break;
				}
			}

			// jezeli przetwarzany jest znak znajdujacy sie w szyfrogramie
			if (validLetterOccured)
			{
				// indeks zaszyfrowanego znaku jest suma indeksow klucza i szyfrowanego znaku
				int encryptedIndex = cryptogramLetterIndex + cryptogramKeyIndex;

				// jezeli wynikowy indeks przekrocza maksymalny indeks w tablicy nalezy go zmniejszyc o dlugosc tablicy
				if (encryptedIndex > (cryptogramLength - 1))
				{
					encryptedIndex -= cryptogramLength;
				}

				// podmiana znaku w tablicy przekazanej do funkcji
				wcharArray[i] = baseCryptogram[encryptedIndex];
			}
		}
	}
}

void _stdcall DecodingC(wchar_t* wcharArray, int bufferSize, wchar_t* key, int keyLength)
{
	int cryptogramKeyIndex;		// zmienna przechowuje indeks litery klucza w tablicy szyfrujacej
	int cryptogramLetterIndex;	// zmienna przechowuje indeks szyfrowanej litery w tablicy szyfrujacej
	bool validLetterOccured;	// zmienna oznajmiajaca czy w biezacej iteracji przetwarzana jest znak ktory znajduje sie w tablicy szyfrujacej

	// petla przechodzaca po wszystkich znakach szyfrowanej tablicy - wcharArray
	for (int i = 0, j = 0; i < bufferSize; ++i, ++j)
	{
		// jezeli indeks klucza jest rowny dlugosci klucza, nalezy go wyzerowac
		if (j == keyLength)
		{
			j = 0;
		}

		// petla wyszukujaca indeks litery klucza w tablicy szyfrujacej
		for (cryptogramKeyIndex = 0; cryptogramKeyIndex < cryptogramLength; ++cryptogramKeyIndex)
		{
			if (key[j] == baseCryptogram[cryptogramKeyIndex])
			{
				break;
			}
		}

		// dalsze operacje maja sens jezeli litera klucza jest inna niz pierwsza w tablicy - wtedy odszyfrowana litera bedzie identyczna jak zaszyfrowana
		if (cryptogramKeyIndex != 0)
		{
			// petla wyszukujaca indeks zaszyfrowanej litery w tablicy szyfrujacej
			for (cryptogramLetterIndex = 0, validLetterOccured = false; cryptogramLetterIndex < cryptogramLength; ++cryptogramLetterIndex)
			{
				if (wcharArray[i] == baseCryptogram[cryptogramLetterIndex])
				{
					validLetterOccured = true;	// znak znajduje sie w szyfrogramie - moze zostac odkodowany
					break;
				}
			}

			// jezeli przetwarzany jest znak znajdujacy sie w szyfrogramie
			if (validLetterOccured)
			{
				// indeks odszyfrowanego znaku jest roznica indeksow szyfrowanego znaku i klucza
				int decryptedIndex = cryptogramLetterIndex - cryptogramKeyIndex;

				// jezeli wynikowy indeks jest mniejszy od 0 to nalezy go zwiekszyc o dlugosc tablicy
				if (decryptedIndex < 0)
				{
					decryptedIndex += cryptogramLength;
				}

				// podmiana znaku w tablicy przekazanej do funkcji
				wcharArray[i] = baseCryptogram[decryptedIndex];
			}
		}
	}
}