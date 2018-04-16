/*
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Przedmiot: Jezyki assemblerowe - projekt                                                                     //
// Autor: Patryk Gregorczuk                                                                                     //
// Wersja: 1.0                                                                                                  //
// Klasa sterująca głównym wiodkiem aplikacji. Implementuje obsługę eventów związanych z akcjami użytkownika.   //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CHANGELOG:

------------------------------------------------------------------------------------------------------------------
Autor: Patryk Gregorczuk
Data: 8.11.2017
Wersja: 0.1
Zmiany:
        - Utworzenie pliku. 
        - Implementacja podstawowej obslugi niektorych eventow.
------------------------------------------------------------------------------------------------------------------
Autor: Patryk Gregorczuk
Data: 20.11.2017
Wersja: 0.11
Zmiany:
        - Implementacja metody startProcessingData():
            a) wielowatkowe wczytywanie danych z pliku do buforow.
            b) wielowatkowy zapis danych z buforow do plikow segmentowych.
        - Implementacja metody mergeFiles(), ktora ma laczyc segmenty w jeden plik wynikowy.
------------------------------------------------------------------------------------------------------------------
Autor: Patryk Gregorczuk
Data: 05.12.2017
Wersja: 0.2
Zmiany:
        - Reorganizacja kodu:
            a) usunieto metody startProcessingData() oraz mergeFiles() na rzecz klasy VigenereConverter.
        - Porzadki w kodzie.
------------------------------------------------------------------------------------------------------------------
Autor: Patryk Gregorczuk
Data: 18.12.2017
Wersja: 0.3
Zmiany:
        - Poprawki GUI wraz z pelna implemenacja wszystkich funkcjonalnosci kontrolek
        - Mozliwosc wyboru plikow tylko z rozszerzeniem .txt oraz wyboru katalogu docelowego
        - Mozna juz podac klucz wedlug ktorego ma nastapic przetwarzanie wskazanego pliku tekstowego
        - Wyswietlanie informacji o czasie dzialania procesu przetwarzania oraz funkcji bibliotecznych po zakonczeniu dzialania
------------------------------------------------------------------------------------------------------------------
Autor: Patryk Gregorczuk
Data: 09.02.2018
Wersja: 0.8
Zmiany:
        - Dodano pasek postepu
------------------------------------------------------------------------------------------------------------------
Autor: Patryk Gregorczuk
Data: 12.02.2018
Wersja: 0.9
Zmiany:
        - Poprawki instancji klas Stopwatch i TimeSpan zwiazanymi z odmierzaniem czasu dzialania
        - Dodano ograniczenie dlugosci klucza wynikajace z zastosowanego algorytmu dzielenia buforow
------------------------------------------------------------------------------------------------------------------
Autor: Patryk Gregorczuk
Data: 12.02.2018
Wersja: 1.0
Zmiany:
        - Wystawiono wersje 1.0
------------------------------------------------------------------------------------------------------------------
==============================================================================================================================================================*/


using System;
using System.Diagnostics;
using System.Text.RegularExpressions;
using System.Windows;

namespace VigenereCoding
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private int selectedLibrary = 0;
        private int selectedMode = 0;
        private int threadsCount = 1;

        private string inputFileName;
        private string outputFilePath;
        private string outputFileName;

        private VigenereConverter vigenereConverter;
        private Stopwatch mainStopwatch;
        private Stopwatch libraryStopwatch;

        private void calculateButton_Click(object sender, RoutedEventArgs e)
        {
            var fileName = inputFileTextBox.Text;
 
            if (fileName.CompareTo("") != 0)
            {
                if (checkCipherKeyCorectness(cipherKeyTextBox.Text))
                {
                    if (selectedLibrary == 0)
                        MessageBox.Show("You have to select library first!", "Error!", MessageBoxButton.OK);
                    else if (selectedMode == 0)
                        MessageBox.Show("You have to select coding or decoding mode!", "Error!", MessageBoxButton.OK);
                    else
                    {
                        string bufferSizeString = bufferSizeComboBox.SelectedValue.ToString();

                        libraryStopwatch = new Stopwatch();

                        vigenereConverter = new VigenereConverter(
                            inputFileTextBox.Text,
                            outputFilePath,
                            outputFileName,
                            threadsCount,
                            selectedLibrary + selectedMode,
                            int.Parse(bufferSizeString), 
                            cipherKeyTextBox.Text.ToCharArray(), 
                            libraryStopwatch,
                            this);

                        mainStopwatch = new Stopwatch();
                        mainStopwatch.Start();
                        vigenereConverter.ProcessData();
                        mainStopwatch.Stop();

                        TimeSpan t = TimeSpan.FromMilliseconds(mainStopwatch.ElapsedMilliseconds);
                        string mainStopWatchResult = string.Format("{0:D2}h {1:D2}m {2:D2}s {3:D3}ms",
                                                t.Hours,
                                                t.Minutes,
                                                t.Seconds,
                                                t.Milliseconds);

                        TimeSpan t2 = TimeSpan.FromMilliseconds(libraryStopwatch.ElapsedMilliseconds);
                        string libraryStopWatchResult = string.Format("{0:D2}h {1:D2}m {2:D2}s {3:D3}ms",
                                                t2.Hours,
                                                t2.Minutes,
                                                t2.Seconds,
                                                t2.Milliseconds);

                        MessageBox.Show("Total time elapsed: " + mainStopWatchResult + "\n"
                            + "DLL usage time: " + libraryStopWatchResult, "Finished!", MessageBoxButton.OK);
                    }
                }
                else
                    MessageBox.Show("Cipher key is empty/too long (max. 16 characters) or contains unsupported symbols!", "Error!", MessageBoxButton.OK);

            }
            else
                MessageBox.Show("You have to select file first!", "Error!", MessageBoxButton.OK);
        }

        private void inputFileButton_Click(object sender, RoutedEventArgs e)
        {
            // Create OpenFileDialog 
            Microsoft.Win32.OpenFileDialog fileDialog = new Microsoft.Win32.OpenFileDialog();

            fileDialog.Filter = "Pliki tekstowe (*.txt)|*.txt";
            // Display OpenFileDialog by calling ShowDialog method 
            bool? result = fileDialog.ShowDialog();
            
            // Get the selected file name and display in a TextBox 
            if (result == true)
            {
                // Open document 
                string inputFilePath = fileDialog.FileName;
                inputFileTextBox.Text = inputFilePath;
                inputFileName = inputFilePath.Substring(inputFilePath.LastIndexOf('\\') + 1);  
                outputFileName = inputFileName.Substring(0, inputFileName.Length - 4) + "_res" + ".txt";

                if (outputFileTextBox.Text.Length == 0)
                {  
                    outputFilePath = inputFilePath.Substring(0, inputFilePath.LastIndexOf('\\'));
                }
                outputFileTextBox.Text = outputFilePath + '\\' + outputFileName;
            }
        }

        private void outputFileButton_Click(object sender, RoutedEventArgs e)
        {
            using (var dialog = new System.Windows.Forms.FolderBrowserDialog())
            {
                System.Windows.Forms.DialogResult result = dialog.ShowDialog();

                if (result == System.Windows.Forms.DialogResult.OK)
                {
                    outputFilePath = dialog.SelectedPath;
                    if (inputFileTextBox.Text.Length > 0)
                        outputFileTextBox.Text = outputFilePath + '\\' + outputFileName;
                    else
                        MessageBox.Show("You have to select input file first!", "Error!", MessageBoxButton.OK);

                }
            }          
        }

        private void CLibraryRadioButton_Checked(object sender, RoutedEventArgs e)
        {
            selectedLibrary = 1;
        }

        private void AsmLibraryRadioButton_Checked(object sender, RoutedEventArgs e)
        {
            selectedLibrary = 2;
        }

        private void threadsCountSlider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            threadsCount = (int)e.NewValue;
            threadsCountTextBox.Text = threadsCount.ToString();
        }

        private void codingModeRadioButton_Checked(object sender, RoutedEventArgs e)
        {
            selectedMode = 5;
        }

        private void decodingModeRadioButton_Checked(object sender, RoutedEventArgs e)
        {
            selectedMode = 10;
        }

        private bool checkCipherKeyCorectness(string cipherKey)
        {
            return Regex.IsMatch(cipherKey, "^[A-Za-ząĄćĆęĘłŁńŃóÓśŚźŹżŻ]+$") && cipherKey.Length <= 16;
        }
    }
}
