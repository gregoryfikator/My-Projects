using Gra.ViewModels;
using System.Windows;

namespace Gra.Views
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    { 
        public MainWindow()
        {
            InitializeComponent();
            this.DataContext = new MainWindowViewModel(new MainMenuViewModel());
        }
    }
}
