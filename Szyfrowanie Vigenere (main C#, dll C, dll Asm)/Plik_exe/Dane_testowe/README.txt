W ca�o�ci poprawne szyfrowanie zachodzi dla plik�w wej�ciowych kodowanych w ANSI - Windows-1250.
Po zaszyfrowaniu plik zapisany jest przy pomocy kodowania Unicode. Aby m�c go ponownie zaszyfrowa�
musi on zosta� najpierw odszyfrowany, tak aby otrzyma� spowrotem plik kodowany jako Windows-1250.

Szyfrowanie plik�w tekstowych kodowanych w Unicode nie jest obs�ugiwane. 

Mo�na natomiast szyfrowa� pliki kodowane w UTF-8. Zaszyfrowany plik nie do ko�ca jest poprawny ze wzgl�du na
nieregularn� liczb� bajt�w przypadaj�cych na ka�dy znak. W przypadku polskich znak�w diakrytycznych s� to 2 bajty,
a dla pozosta�ych 1 bajt. Po zaszyfrowaniu pliku o takim kodowaniu b�dzie mo�na zauwa�y� miejsca w kt�rych znajdowa�y
si� polskie znaki diakrytyczne - b�d� one rozpisane na dwa po�rednie znaki. Jednak po odszyfrowaniu tego pliku
tre�� b�dzie w 100% odpowiada�a pierwotnie szyfrowanemu orygina�owi.