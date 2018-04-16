/*==============================================================================================================================================================
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Przedmiot: Jezyki assemblerowe - projekt                                                                     //
// Autor: Patryk Gregorczuk                                                                                     //
// Wersja: 1.0                                                                                                  //
// Klasa odpowiedzialna za wszelkie operacje przeprowadzane na danych. Implementuje metody realizoujace wczy-   //
// tywanie, przetwarzanie, zapisywanie segmentow do bufora wyjsciowego i zapisanie do pliku wynikowego.         //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CHANGELOG:

------------------------------------------------------------------------------------------------------------------
Autor: Patryk Gregorczuk
Data: 05.12.2017
Wersja: 0.2
Zmiany:
        - Utworzenie pliku i klasy
        - Implementacja metod:
            a) ProcessData() - glowna metoda klasy odpowiedzialna za wywolywanie pozostalych metod
            b) ReadFile() - wczytuje fragment przetwarzanego pliku do glownego bufora
            c) SplitData() - metoda rozdziela dane z glownego bufora do mniejszych na ktorych beda operowaly watki
            d) Cipher() - metoda szyfrujaca, w obecnej wersji nie dziala 
            e) mergeBuffers() - metoda scala mniejsze bufory spowrotem do glownego bufora
            f) WriteFile() - metoda zapisuje glowny bufor do pliku
            g) MergeSegmentFiles() - metoda scala segmenty powstale poprzez wywolywanie metody WriteFile w jeden
------------------------------------------------------------------------------------------------------------------
Autor: Patryk Gregorczuk
Data: 18.12.2017
Wersja: 0.3
Zmiany:
        - Utworzenie zmiennych pomocnicznych
        - Pomiar czasu dzialania funkcji bibliotecznych
        - Poprawki wczytywania i zapisywania plikow dotyczace stosowanego kodowania
        - Metoda Cipher() zastapiona rozgalezieniem w ktorym nastepuje wielowatkowe wywolanie funkcji bibliotecznej
------------------------------------------------------------------------------------------------------------------
Autor: Patryk Gregorczuk
Data: 09.02.2018
Wersja: 0.8
Zmiany:
        - Zmiana sposobu przydzielania danych dla watkow: Dane sa dzielone tak aby pierwszy znak klucza byl pierwszym znakiem szyfrujacym dla kazdego watku
        - Dodano mechanizm delegata realizujacego odswiezanie paska postepu w glownym oknie programu
        - Oczyszczono kod
------------------------------------------------------------------------------------------------------------------
Autor: Patryk Gregorczuk
Data: 12.02.2018
Wersja: 0.9
Zmiany:
        - Usuniecie offsetu klucza jako argumentu funkcji bibliotecznych
        - Instancja klasy Stopwatch dla funkcji bibliotecznych jest tworzona teraz w metodzie calculateButton_Click klasy okna programu
        - Zoptymalizowano operacje na plikach, sa one teraz tylko jednokrotnie otwierane i zamykane w ciagu trwania calego procesu szyfrowania/deszyfrowania
------------------------------------------------------------------------------------------------------------------
Autor: Patryk Gregorczuk
Data: 12.02.2018
Wersja: 1.0
Zmiany:
        - Dodanie komentarzy
        - Program oddany do oceny
------------------------------------------------------------------------------------------------------------------
==============================================================================================================================================================*/

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Threading;

namespace VigenereCoding
{
    public class VigenereConverter
    {
        // lista buforow, do niej trafiaja podzielone segmenty glownego bufora
        private List<StringBuilder> buffers;

        // zmienna przechowuje nazwe pliku wejsciowego
        private string fileName;

        // zmienna przechowuje sciezke pliku wejsciowego
        private string outputFilePath;

        // zmienna przechowuje nazwe pliku wyjsciowego
        private string outputFileName;

        // zmienna przechowuje nazwe pliku wyjsciowego razem ze sciezka
        private string resultFile;

        // zmienna przechowuje ilosc wybranych przez uzytkownika watkow
        private int threadsCount;

        // zmienna przechowuje rozmiar segmentow zapisanych w liscie buffers
        int segmentSize;

        // zmienna przechowuje dlugosc klucza szyfrujacego
        int cipherKeyLength;

        // zmienna przechowuje tryb dzialania programu
        private int programMode;

        // zmienna przechowuje podany przez uzytkownika rozmiar bufora glownego
        private int bufferSize;

        // zmienna przechowuje klucz szyfrujacy w postaci tablicy typu char
        private char[] cipherKeyCharArray;

        // zmienna przechowuje referencje do obiektu tworzacego string z kluczem szyfrujacym
        private StringBuilder cipherKey;

        // zmienna przechowuje referencje do obiektu sluzacego do pomiaru czasu dzialania bibliotek
        private Stopwatch libraryStopwatch;

        // zmianna przechowuje referencje do obiektu okna programu
        MainWindow mainWindow;

        // zmienna przechowuja sposob kodowania pliku wejsciowego i wyjsciowego
        Encoding encoding;
        Encoding encodingOutput;

        // zmienna przechowuje informacje o wielkosci korekcji bajtow w zaleznosci od kodowania
        int correction;

        // zmienne przechowuja strumienie wejsciowe i wyjsciowe do obslugi plikow
        StreamReader input;
        StreamWriter output;

        public VigenereConverter(string fileName, string outputFilePath, string outputFileName, int threadsCount, int programMode, int bufferSize, char[] cipherKey, Stopwatch libraryStopwatch, MainWindow mainWindow)
        {
            buffers = new List<StringBuilder>();

            this.fileName = fileName;

            this.outputFilePath = outputFilePath;

            this.outputFileName = outputFileName;

            this.resultFile = outputFilePath + "\\" + outputFileName;

            this.threadsCount = threadsCount;

            this.programMode = programMode;

            this.bufferSize = bufferSize;

            cipherKeyCharArray = cipherKey;

            this.cipherKey = new StringBuilder(new string(cipherKeyCharArray));

            cipherKeyLength = cipherKey.Length;

            this.libraryStopwatch = libraryStopwatch;

            this.mainWindow = mainWindow;


            // w zaleznosci czy aplikacja jest ustawiona na szyfrowanie czy deszyfrowanie wybierane jest inne kodowanie
            if (programMode == 6 || programMode == 7)
            {
                encodingOutput = Encoding.Unicode;
            }
            else
            {
                encodingOutput = Encoding.GetEncoding("Windows-1250");
            }

            output = new StreamWriter(resultFile, true, encodingOutput);

            if (programMode == 6 || programMode == 7)
            {
                encoding = Encoding.GetEncoding("Windows-1250");
                correction = 0;
            }
            else
            {
                encoding = Encoding.Unicode;
                correction = 2;
            }

            input = new StreamReader(fileName, encoding, false, bufferSize);
        }

        [DllImport("LibraryC.dll", EntryPoint = "CodingC", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
        private extern static void CodingC(StringBuilder segment, int bufferSize, StringBuilder key, int keyLength);

        [DllImport("LibraryC.dll", EntryPoint = "DecodingC", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
        private extern static void DecodingC(StringBuilder segment, int bufferSize, StringBuilder key, int keyLength);

        [DllImport("LibraryAsm.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
        private extern static void CodingAsm(StringBuilder segment, int bufferSize, StringBuilder key, int keyLength);

        [DllImport("LibraryAsm.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
        private extern static void DecodingAsm(StringBuilder segment, int bufferSize, StringBuilder key, int keyLength);

        private delegate void Updater(int UI);

        // metoda przeprowadza aktualizacje paska postepu
        public void UpdateData(int percentProgressValue)
        {
            if (percentProgressValue > 100)
                percentProgressValue = 100;
            mainWindow.progressBarLabel.Content = percentProgressValue.ToString() + "%";
            mainWindow.progressBar.Value = percentProgressValue;
        }

        [MethodImplAttribute(MethodImplOptions.NoOptimization)]
        public void ProcessData()
        {
            // zmienna przechowuje obiekt w ktorym znajduje sie bufor wyjsciowy w postaci stringa
            StringBuilder fileData;

            // zmienna wskazuje czy glowna petla przetwarzajaca powinna sie juz zakonczyc po obecnej iteracji
            bool isFinished = false;

            // zmienna oznacza przesuniecie w pliku od jakiego nalezy zaczac wczytywanie
            long offset = 0;

            // ponizej zestaw zmiennych uzywanych do wyliczania przesuniecia paska postepu w GUI
            long processedSegments = 0;

            long totalSegmentsCount = (long)Math.Ceiling((double)(new FileInfo(fileName).Length / bufferSize));

            if (programMode == 11 || programMode == 12)
            {
                totalSegmentsCount = ((totalSegmentsCount / 2));
            }

            if (totalSegmentsCount == 0)
            {
                totalSegmentsCount = 1;
            }

            double percentProgressValue = 100 * processedSegments / totalSegmentsCount;

            Updater uiUpdater = new Updater(UpdateData);

            while (!isFinished)
            {
                // utworzenie bufora wejsciowego
                char[] data = new char[bufferSize];

                // odczyt pliku
                ReadFile(ref data, ref offset, ref isFinished);

                // zmienna oznaczajaca liczbe znakow nieprzydzielonych do zadnego z buforow
                int unAssignedChars = 0;

                // podzial bufora wejsciowego na mniejsze i umieszczenie ich w liscie
                List<StringBuilder> buffers = SplitData(data, ref segmentSize, ref unAssignedChars);

                // korekcja offsetu aby czytac plik od wlasciwego miejsca w przypadku gdy jakies znaki nie zostaly przydzielone do buforow
                if (programMode == 6 || programMode == 7) // Windows-1250 - 1 znak = 1 bajt
                {
                    offset -= unAssignedChars;
                }
                else // Unicode - 1 znak = 2 bajty
                {
                    offset -= unAssignedChars;
                    offset -= unAssignedChars;
                }

                libraryStopwatch.Start();   // uruchomienie odmierzania czasu

                // W zaleznosci od wybranego trybu wybierane jest odpowiednie rozgalezienie, w ktorym uruchamiania jest funkcja biblioteczna
                // dla wybranej liczby watkow za pomoca metody ForEach
                if (programMode == 6)
                {
                    Parallel.ForEach(buffers, new ParallelOptions { MaxDegreeOfParallelism = threadsCount }, buffer =>
                    {
                        CodingC(buffer, segmentSize, new StringBuilder(new string(cipherKeyCharArray)), cipherKeyLength);
                    });
                }
                else if (programMode == 11)
                {
                    Parallel.ForEach(buffers, new ParallelOptions { MaxDegreeOfParallelism = threadsCount }, buffer =>
                    {
                        DecodingC(buffer, segmentSize, new StringBuilder(new string(cipherKeyCharArray)), cipherKeyLength);
                    });
                }
                else if (programMode == 7)
                {
                    Parallel.ForEach(buffers, new ParallelOptions { MaxDegreeOfParallelism = threadsCount }, buffer =>
                    {
                        CodingAsm(buffer, segmentSize, new StringBuilder(new string(cipherKeyCharArray)), cipherKeyLength);
                    });
                }
                else if (programMode == 12)
                {
                    Parallel.ForEach(buffers, new ParallelOptions { MaxDegreeOfParallelism = threadsCount }, buffer =>
                    {
                        DecodingAsm(buffer, segmentSize, new StringBuilder(new string(cipherKeyCharArray)), cipherKeyLength);
                    });
                }

                libraryStopwatch.Stop();    // zatrzymanie timera

                fileData = mergeBuffers(buffers, bufferSize - unAssignedChars, segmentSize);    // scalenie buforow do bufora wyjsciowego

                WriteFile(fileData.ToString().ToCharArray());   // zapisanie do pliku zawartosci bufora wyjsciowego

                processedSegments++;    // zwiekszenie ilosci przetworzonych segmentow

                percentProgressValue = 100 * processedSegments / totalSegmentsCount;    // obliczenie procentowego stanu przetworzenia pliku

                Dispatcher.CurrentDispatcher.Invoke(DispatcherPriority.Render, uiUpdater, (int)percentProgressValue);   // wywolanie odswiezenia progressbara w GUI
            }

            // zamkniecie strumieni
            input.Close();
            output.Close();
        }

        // metoda odczytuje dane z pliku i zapisuje je do bufora wejsciowego
        private int ReadFile(ref char[] data, ref long offset, ref bool isFinished)
        {
            input.BaseStream.Seek(offset + correction, SeekOrigin.Begin);

            int charsCount = input.ReadBlock(data, 0, bufferSize);

            offset += charsCount;

            if (encoding == Encoding.Unicode)
            {
                offset += charsCount;
            }

            if (charsCount < bufferSize)
            {
                char[] shortenedData = new char[charsCount];

                Array.Copy(data, shortenedData, charsCount);

                isFinished = true;
            }

            return charsCount;
        }

        // metoda realizuje podzial bufora wejsciowego na mniejsze bufory, ktorych przetworzeniem zajma sie watki
        private List<StringBuilder> SplitData(char[] data, ref int segmentSize, ref int divisionOutlet)
        {
            List<StringBuilder> dataSegments = new List<StringBuilder>();

            divisionOutlet = 0;

            // ilosc segmentow rowna jest ilosci watkow
            int segmentsCount = threadsCount;
            
            // podzial odbywa sie tak aby pierwszy znak w segmencie zawsze byl szyfrowany przez pierwsza litere klucza 
            if (data.Length >= (threadsCount * cipherKeyLength))
            {
                divisionOutlet = data.Length % (cipherKeyLength * threadsCount);

                int charsLeftToProcess = data.Length - divisionOutlet;

                int segmentLength = charsLeftToProcess / segmentsCount;

                int dataCopyStartIndex = 0;

                for (int i = 0; i < segmentsCount; ++i)
                {
                    char[] newSegment = new char[segmentLength];

                    Array.Copy(data, dataCopyStartIndex, newSegment, 0, segmentLength);

                    dataCopyStartIndex += segmentLength;

                    StringBuilder readyNewSegment = new StringBuilder(new string(newSegment));

                    dataSegments.Add(readyNewSegment);
                }

                segmentSize = segmentLength;
            }
            else // gdy zostalo juz tak malo liter do przetworzenia ze jest ich mniej niz wynosi dlugosc klucza wtedy calosc trafia do jednego segmentu
            {
                char[] lastSmallerSegment = new char[data.Length];

                segmentSize = lastSmallerSegment.Length;

                Array.Copy(data, lastSmallerSegment, data.Length);

                StringBuilder readyLastSmallerSegment = new StringBuilder(new String(lastSmallerSegment));

                dataSegments.Add(readyLastSmallerSegment);
            }

            return dataSegments;
        }

        // metoda scala bufory do jednego wyjsciowego po przetworzeniu ich przez watki
        private StringBuilder mergeBuffers(List<StringBuilder> buffers, int length, int segmentLength)
        {
            char[] result = new char[length];

            for (int i = 0, stamp = 0; i < buffers.Count; ++i)
            {
                Array.Copy(buffers[i].ToString().ToCharArray(), 0, result, stamp, buffers[i].Length);

                stamp += buffers[i].Length;
            }

            if (result[result.Length - 1] == '\0')
            {
                string resultWithTerminators = new string(result);
                string resultWithoutTerminators = resultWithTerminators.TrimEnd('\0');
                result = resultWithoutTerminators.ToCharArray();
            }

            return new StringBuilder(new string(result));
        }

        // metoda zapisuje do pliku bufor wyjsciowy w postaci przekazanej tablicy typu char
        private void WriteFile(char[] data)
        {
            output.Write(data);
        }
    }
}