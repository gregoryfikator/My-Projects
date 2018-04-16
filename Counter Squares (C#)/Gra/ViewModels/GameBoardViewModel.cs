using Gra.Models;
using Gra.Utilities;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Timers;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Input;
using System.Windows.Media;

namespace Gra.ViewModels
{
    public class GameBoardViewModel : BaseViewModel, IBaseViewModel, INotifyPropertyChanged
    {
        private ObservableCollection<Button> buttons;
        private GameBoardModel gameBoardModel;

        ResourceDictionary resourceDictionary = (ResourceDictionary)Application.LoadComponent(new Uri("Views/Styles.xaml", UriKind.Relative));

        private bool gameStarted = false;
        private bool popupVisibility = false;

        private Random randomizer;

        private string selectedButtonContent = String.Empty;
        private Brush selectedButtonDefaultBrush = null;
        private int selectedButtonIndex = -1;
        private bool wasGameFieldSelected = false;

        Timer timer = new Timer(100);
        private TimeSpan timeSpan;
        private double timeLeft;
        private string timeLeftLabel = String.Empty;
        private int counter = 0;

        private ICommand buttonSelectedCommand;
        private ICommand restartGameCommand;
        private ICommand changeBackgroundStyleCommand;
        private ICommand showRecordListCommand;
        private ICommand quitGameCommand;

        public event RequestViewChange RequestViewChange;
        new public event PropertyChangedEventHandler PropertyChanged;

        public ObservableCollection<Button> Buttons
        {
            get
            {
                return buttons;
            }
            set
            {
                buttons = value;
                OnPropertyChanged("Buttons");
            }
        }

        public bool WasGameFieldSelected
        {
            get
            {
                return wasGameFieldSelected;
            }
            set
            {
                wasGameFieldSelected = value;
            }
        }

        public int CurrentScore
        {
            get
            {
                return PlayerModel.CurrentScore;
            }
            set
            {
                PlayerModel.CurrentScore = value;
                OnPropertyChanged("CurrentScore");
                OnPropertyChanged("TopScore");
            }
        }

        public int TopScore
        {
            get
            {
                return PlayerModel.TopScore;
            }
        }

        public string PlayerName
        {
            get
            {
                return PlayerModel.PlayerName;
            }
            set
            {
                PlayerModel.PlayerName = value;
                OnPropertyChanged("PlayerName");
            }
        }

        public double TimeLeft
        {
            get
            {
                return timeLeft;
            }
            set
            {
                timeLeft = value;
                OnPropertyChanged("TimeLeft");
            }
        }

        public string TimeLeftString
        {
            get
            {
                return timeLeftLabel;
            }
            set
            {
                timeLeftLabel = value;
                OnPropertyChanged("TimeLeftString");
            }
        }

        public bool GameStarted
        {
            get
            {
                return gameStarted;
            }
            set
            {
                gameStarted = value;
                OnPropertyChanged("GameStarted");
            }
        }

        public bool PopupVisibility
        {
            get
            {
                return popupVisibility;
            }
            set
            {
                popupVisibility = value;
                OnPropertyChanged("PopupVisibility");
            }
        }

        public ICommand ButtonSelectedCommand
        {
            get
            {
                return buttonSelectedCommand ??
                    (buttonSelectedCommand = new RelayCommand(p => ButtonSelected(p), null));
            }
        }

        public ICommand RestartGameCommand
        {
            get
            {
                return restartGameCommand ??
                    (restartGameCommand = new RelayCommand(p => RestartGame(), null));
            }
        }

        public ICommand ChangeBackgroundStyleCommand
        {
            get
            {
                return changeBackgroundStyleCommand ??
                    (changeBackgroundStyleCommand = new RelayCommand(p => ChangeBackgroundStyle(), null));
            }
        }

        public ICommand ShowRecordListCommand
        {
            get
            {
                return showRecordListCommand ??
                    (showRecordListCommand = new RelayCommand(p => ShowRecordList(), null));
            }
        }

        public ICommand QuitGameCommand
        {
            get
            {
                return quitGameCommand ??
                    (quitGameCommand = new RelayCommand(p => (p as Window).Close(), null));
            }
        }

        override protected void OnPropertyChanged(string propName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propName));
        }

        public GameBoardViewModel()
        {
            ColorGradientString = ColorDictionary.colorDictionary[ColorDictionary.currentGradientNumber];

            randomizer = new Random();

            InitGame(7, 5);
        }

        public void InitGame(int columnsCount, int rowsCount)
        {
            InitGameBoard(columnsCount, rowsCount);

            PlayerModel.ResetScore();

            InitTimer();

            timer.Start();
            GameStarted = true;
        }

        private void RestartGame()
        {
            PopupVisibility = false;
            selectedButtonContent = String.Empty;
            selectedButtonDefaultBrush = null;
            selectedButtonIndex = -1;

            timeSpan = timeSpan.Add(new TimeSpan(0, 0, 60));
            TimeLeft = 60;

            InitGameBoard(7, 5);

            CurrentScore = 0;
            timer.Start();
            GameStarted = true;
        }

        private void InitGameBoard(int columnsCount, int rowsCount)
        {
            Buttons = new ObservableCollection<Button>();

            gameBoardModel = new GameBoardModel()
            {
                GameField = CreateGameFieldArray(columnsCount, rowsCount)
            };
        }

        private void InitTimer()
        {
            timeSpan = timeSpan.Add(new TimeSpan(0, 0, 60));
            TimeLeft = 60;
            TimeLeftString = timeSpan.ToString(@"mm\:ss");
            timer.Elapsed += HandleTimer;
        }

        private GameFieldModel[,] CreateGameFieldArray(int columnsCount, int rowsCount)
        {
            GameFieldModel[,] gameFieldModelArray = new GameFieldModel[columnsCount, rowsCount];

            for (int y = 0; y < rowsCount; ++y)
            {
                for (int x = 0; x < columnsCount; ++x)
                {
                    gameFieldModelArray[x, y] = new GameFieldModel();
                    gameFieldModelArray[x, y].SetField(randomizer.Next(11).ToString(), randomizer.Next(3));
                    Grid.SetColumn(gameFieldModelArray[x, y].Field, x);
                    Grid.SetRow(gameFieldModelArray[x, y].Field, y);
                    InitializeSpecifiedGameField(gameFieldModelArray[x, y].Field, y * columnsCount + x);

                    Buttons.Add(gameFieldModelArray[x, y].Field);
                }
            }

            return gameFieldModelArray;
        }

        private void InitializeSpecifiedGameField(Button gameFieldButton, int index)
        {
            gameFieldButton.Style = (Style)resourceDictionary["gameFieldButtonStyle"];

            gameFieldButton.SetValue(ControlExtensions.IsSelectedProperty, false);
            gameFieldButton.SetValue(ControlExtensions.IndexProperty, index);

            Binding binding = new Binding("Index")
            {
                RelativeSource = new RelativeSource(RelativeSourceMode.Self)
            };

            gameFieldButton.Command = ButtonSelectedCommand;
            gameFieldButton.CommandParameter = ControlExtensions.GetIndex(gameFieldButton);

            gameFieldButton.Visibility = Visibility.Visible;
        }

        private void HandleTimer(object sender, ElapsedEventArgs e)
        {
            if (TimeLeft > 0)
            {
                TimeLeft -= 0.1;
                counter++;
                if (counter == 10)
                {
                    counter = 0;
                    timeSpan = timeSpan.Subtract(new TimeSpan(0, 0, 1));
                    TimeLeftString = timeSpan.ToString(@"mm\:ss");
                }
            }
            else
            {
                timer.Stop();
                GameStarted = false;
                PopupVisibility = true;
            }
        }

        private void ButtonSelected(object param)
        {
            var buttonIndex = (int)param;

            if (WasGameFieldSelected == false)
            {
                WasGameFieldSelected = true;
                SelectButton(buttonIndex);
            }
            else if (!CompareSelectedWithClickedButtonValue(buttons[buttonIndex].Content.ToString()) || 
                (bool)(buttons[buttonIndex].GetValue(ControlExtensions.IsSelectedProperty)))
            {
                DeselectButton(buttons[selectedButtonIndex]);
                WasGameFieldSelected = false;
            }
            else
            {
                MatchFounded(buttons[buttonIndex]);
                WasGameFieldSelected = false;

                if (CheckNoMoveLeft())
                {
                    InitGameBoard(7, 5);
                    timeSpan = timeSpan.Add(new TimeSpan(0, 0, 15));
                    TimeLeft += 15;

                    if (TimeLeft > 60)
                    {
                        timeSpan = new TimeSpan(0, 0, 60);
                        TimeLeft = 60;
                    }

                    TimeLeftString = timeSpan.ToString(@"mm\:ss");
                }
            }
        }

        private void SelectButton(int buttonIndex)
        {
            selectedButtonIndex = buttonIndex;

            buttons[buttonIndex].SetValue(ControlExtensions.IsSelectedProperty, true);

            selectedButtonContent = buttons[buttonIndex].Content.ToString();
            selectedButtonDefaultBrush = buttons[buttonIndex].Background.CloneCurrentValue();

            ChangeButtonBackgroundToSelected(buttons[buttonIndex]);
        }

        private void DeselectButton(Button button)
        {
            ChangeButtonBackgroundToDefault(button);

            buttons[selectedButtonIndex].SetValue(ControlExtensions.IsSelectedProperty, false);
            selectedButtonContent = String.Empty;
            selectedButtonDefaultBrush = null;
            selectedButtonIndex = -1;
        }

        private void MatchFounded(Button button)
        {
            AddPoints(button);
            HideMatchedButtons(button);
            DeselectButton(button);
        }

        private void AddPoints(Button button)
        {
            if (CompareBrushes(button.Background))
            {
                var ExtraScoreWhenColorEquals = gameBoardModel.ScoreMultiplerWhenColorEquals * int.Parse(button.Content.ToString());
                CurrentScore += (gameBoardModel.ScoreBaseWhenColorEquals + ExtraScoreWhenColorEquals);
            }
            else
            {
                CurrentScore += (gameBoardModel.ScoreBaseWhenColorNotEquals + (int.Parse(button.Content.ToString())));
            }
        }

        private void HideMatchedButtons(Button button)
        {
            button.SetValue(ControlExtensions.IsSelectedProperty, false);
            button.Visibility = Visibility.Hidden;
            buttons[selectedButtonIndex].Visibility = Visibility.Hidden;
        }

        private bool CompareSelectedWithClickedButtonValue(string comparedButtonString)
        {
            return selectedButtonContent.Equals(comparedButtonString);
        }

        private bool CompareBrushes(Brush comparedBrush)
        {
            return (new SolidColorBrushComparer().Equals((SolidColorBrush)selectedButtonDefaultBrush, (SolidColorBrush)comparedBrush));
        }

        private bool CompareSelectedBrushWithColor(string color)
        {
            return (new SolidColorBrushComparer().Equals((SolidColorBrush)selectedButtonDefaultBrush, (SolidColorBrush)(new BrushConverter().ConvertFrom(color))));
        }

        private void ChangeButtonBackgroundToDefault(Button button)
        {
            button.Background = selectedButtonDefaultBrush;
        }

        private void ChangeButtonBackgroundToSelected(Button button)
        {
            selectedButtonDefaultBrush = button.Background.CloneCurrentValue();

            BrushConverter bc = new BrushConverter();

            if (CompareSelectedBrushWithColor("#FF800000"))
            {
                button.Background = (SolidColorBrush)bc.ConvertFrom("#FFFF0000");
            }
            else if (CompareSelectedBrushWithColor("#FF008000"))
            {
                button.Background = (SolidColorBrush)bc.ConvertFrom("#FF00FF00");
            }
            else if (CompareSelectedBrushWithColor("#FF000080"))
            {
                button.Background = (SolidColorBrush)bc.ConvertFrom("#FF0000FF");
            }
        }

        private bool CheckNoMoveLeft()
        {
            List<string> valuesLeftOnBoard = new List<string>();

            for (int x = 0; x < 7; ++x)
            {
                for (int y = 0; y < 5; ++y)
                {
                    if (gameBoardModel.AccessSpecifiedField(x, y).Field.Visibility == Visibility.Visible)
                    {
                        valuesLeftOnBoard.Add(gameBoardModel.AccessSpecifiedField(x, y).Field.Content.ToString());
                    }
                }
            }

            List<string> valuesLeftOnBoardCopy = valuesLeftOnBoard.ToList();

            foreach (string valueLeft in valuesLeftOnBoard)
            {
                valuesLeftOnBoardCopy.Remove(valueLeft);

                if (valuesLeftOnBoardCopy.Contains(valueLeft))
                {
                    return false;
                }
            }

            return true;
        }

        private void ChangeBackgroundStyle()
        {
            ColorDictionary.currentGradientNumber += 1;

            if (ColorDictionary.currentGradientNumber == 4)
            {
                ColorDictionary.currentGradientNumber = 1;
            }

            ColorGradientString = ColorDictionary.colorDictionary[ColorDictionary.currentGradientNumber];
        }

        private void ShowRecordList()
        {

        }
    }
}
