using Gra.Utilities;
using System.ComponentModel;
using System.Windows;
using System.Windows.Input;

namespace Gra.ViewModels
{
    public class MainMenuViewModel : BaseViewModel, IBaseViewModel, INotifyPropertyChanged
    {
        private ICommand startGameCommand;
        private ICommand changeBackgroundStyleCommand;
        private ICommand quitGameCommand;

        public event RequestViewChange RequestViewChange;
        new public event PropertyChangedEventHandler PropertyChanged;

        public ICommand StartGameCommand
        {
            get
            {
                return startGameCommand ??
                    (startGameCommand = new RelayCommand(p => RequestViewChange(new GameBoardViewModel()), null));
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

        public MainMenuViewModel()
        {
            ColorGradientString = ColorDictionary.colorDictionary[ColorDictionary.currentGradientNumber];
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
    }
}
