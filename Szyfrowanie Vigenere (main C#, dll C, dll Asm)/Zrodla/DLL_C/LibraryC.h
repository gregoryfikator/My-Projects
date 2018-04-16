/*
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Przedmiot: Jezyki assemblerowe - projekt                                                                     //
// Autor: Patryk Gregorczuk                                                                                     //
// Wersja: 1.0                                                                                                  //
// Biblioteka DLL w jezyku C																				    //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CHANGELOG:

------------------------------------------------------------------------------------------------------------------
Autor: Patryk Gregorczuk
Data: 8.11.2017
Wersja: 0.1
Zmiany:
- Utworzenie pliku.
- Implementacja metody testujacej dzialanie biblioteki w programie glownym.
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
==============================================================================================================================================================*/

#ifdef LIBRARYC_EXPORTS
#define LIBRARYC_API __declspec(dllexport)
#else
#define LIBRARYC_API __declspec(dllimport)
#endif

extern "C" LIBRARYC_API void _stdcall CodingC(wchar_t* wcharArray, int bufferSize, wchar_t* key, int keyLength);
extern "C" LIBRARYC_API void _stdcall DecodingC(wchar_t* wcharArray, int bufferSize, wchar_t* key, int keyLength);