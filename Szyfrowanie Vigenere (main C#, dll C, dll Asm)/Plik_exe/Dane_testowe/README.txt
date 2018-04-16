W ca³oœci poprawne szyfrowanie zachodzi dla plików wejœciowych kodowanych w ANSI - Windows-1250.
Po zaszyfrowaniu plik zapisany jest przy pomocy kodowania Unicode. Aby móc go ponownie zaszyfrowaæ
musi on zostaæ najpierw odszyfrowany, tak aby otrzymaæ spowrotem plik kodowany jako Windows-1250.

Szyfrowanie plików tekstowych kodowanych w Unicode nie jest obs³ugiwane. 

Mo¿na natomiast szyfrowaæ pliki kodowane w UTF-8. Zaszyfrowany plik nie do koñca jest poprawny ze wzglêdu na
nieregularn¹ liczbê bajtów przypadaj¹cych na ka¿dy znak. W przypadku polskich znaków diakrytycznych s¹ to 2 bajty,
a dla pozosta³ych 1 bajt. Po zaszyfrowaniu pliku o takim kodowaniu bêdzie mo¿na zauwa¿yæ miejsca w których znajdowa³y
siê polskie znaki diakrytyczne - bêd¹ one rozpisane na dwa poœrednie znaki. Jednak po odszyfrowaniu tego pliku
treœæ bêdzie w 100% odpowiada³a pierwotnie szyfrowanemu orygina³owi.