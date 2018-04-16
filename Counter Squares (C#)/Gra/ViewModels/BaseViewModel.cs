using System.ComponentModel;

namespace Gra.ViewModels
{
    public class BaseViewModel : INotifyPropertyChanged
    {
        private string colorGradientString;

        public event PropertyChangedEventHandler PropertyChanged;

        public string ColorGradientString
        {
            get
            {
                return colorGradientString;
            }
            set
            {
                colorGradientString = value;
                OnPropertyChanged("ColorGradientString");
            }
        }

        virtual protected void OnPropertyChanged(string propName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propName));
        }
    }
}
