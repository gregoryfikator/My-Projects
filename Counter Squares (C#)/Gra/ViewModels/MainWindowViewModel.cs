using System.ComponentModel;
using System.Windows.Input;

namespace Gra.ViewModels
{
    public class MainWindowViewModel : INotifyPropertyChanged
    {
        private IBaseViewModel currentView;
        private ICommand changeViewCommand;

        public event PropertyChangedEventHandler PropertyChanged;

        public IBaseViewModel CurrentView
        {
            get
            {
                return currentView;
            }
            set
            {
                if (currentView != value)
                {
                    value.RequestViewChange +=
                        (view) =>
                        {
                            ChangeViewCommand.Execute(view);
                        };

                    currentView = value;
                    OnPropertyChanged("CurrentView");
                }
            }
        }

        public ICommand ChangeViewCommand
        {
            get
            {
                if (changeViewCommand == null)
                {
                    changeViewCommand = new RelayCommand(p => CurrentView = p as IBaseViewModel);
                }

                return changeViewCommand;
            }
        }

        virtual protected void OnPropertyChanged(string propName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propName));
        }

        public MainWindowViewModel(IBaseViewModel startViewModel)
        {
            CurrentView = startViewModel;
        }
    }
}
