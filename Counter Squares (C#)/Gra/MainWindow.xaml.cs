using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Timers;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Gra
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        
        GradientSelector gs = new GradientSelector();
        Random random = new Random();
        Player player = new Player();
        GameArea ga;
        Timer timer = new Timer(100);
        TimeSpan ts = new TimeSpan(); 

        private bool gameStarted = false;
        private bool mouseOnButton = false;
        int counter = 0;

        public MainWindow()
        {
            try
            {
                InitializeComponent();
                gs.InitBrushes();
                timer.Elapsed += new ElapsedEventHandler(timer_Elapsed);
            }
            catch (Exception e)
            {
                Console.WriteLine("Błąd w glebi kodu!");
                Close();
            }
        }

        void timer_Elapsed(object sender, ElapsedEventArgs e)
        {
            this.Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, (Action)(() =>
            {            
                if (timeLeftBar.Value > 0)
                {
                    timeLeftBar.Value -= 0.1;
                    counter++;
                    if (counter == 10)
                    {
                        counter = 0;
                        ts = ts.Subtract(new TimeSpan(0, 0, 1));
                        timeLeftLabelValue.Content = ts.ToString(@"mm\:ss");
                    }
                }
                else
                {
                    timer.Stop();
                    GameOver();
                }
            }));
        }

        private void GameOver()
        {
            gameStarted = false;

            gameCanvas.Visibility = Visibility.Hidden;
            timeLeftLabel.Visibility = Visibility.Hidden;
            timeLeftLabelValue.Visibility = Visibility.Hidden;
            topScoreLabel.Visibility = Visibility.Hidden;
            topScoreValue.Visibility = Visibility.Hidden;
            currentScoreLabel.Visibility = Visibility.Hidden;
            currentScoreValue.Visibility = Visibility.Hidden;
            timeLeftBarCanvas.Visibility = Visibility.Hidden;

            for (int j = 0; j < 5; ++j)
                for (int i = 0; i < 7; ++i)
                   ga.AccessSpecifiedField(i, j).GetField().Visibility = Visibility.Hidden;

            player.ResetScore();

            menuCanvas.Visibility = Visibility.Visible;        
        }

        private void ChangeButtonForeground(Button testedButton)
        {
            BrushConverter bc = new BrushConverter();
            if (mouseOnButton)
            {
                if (gs.GetColorName().Equals("RED"))
                    testedButton.Foreground = (Brush)bc.ConvertFrom("#FFFF0000");
                else if (gs.GetColorName().Equals("GREEN"))
                    testedButton.Foreground = (Brush)bc.ConvertFrom("#FF00FF00");
                else if (gs.GetColorName().Equals("BLUE"))
                    testedButton.Foreground = (Brush)bc.ConvertFrom("#FF0000FF");
            }
            else
                testedButton.Foreground = (Brush)bc.ConvertFrom("#FF000000");
        }

        private void ChangeMouseOnButtonState()
        {
            mouseOnButton = !mouseOnButton;
        }

        private void ChangeBackgroundGradient(LinearGradientBrush lgb)
        {
            gameGrid.Background = lgb;
        }

        private void InitGameField()
        {
            ga = new GameArea(random, player);
            for (int j = 0; j < 5; ++j)
                for (int i = 0; i < 7; ++i)
                {
                    ga.AccessSpecifiedField(i, j).SetOnBoard(i, j);
                    gameGrid.Children.Add(ga.AccessSpecifiedField(i, j).GetField());
                }
        }

        private void startButton_MouseEnter(object sender, MouseEventArgs e)
        {
            ChangeMouseOnButtonState();
            ChangeButtonForeground(sender as Button);
        }

        private void startButton_MouseLeave(object sender, MouseEventArgs e)
        {
            ChangeMouseOnButtonState();
            ChangeButtonForeground(sender as Button);
        }

        private void startButton_Click(object sender, RoutedEventArgs e)
        {
            menuCanvas.Visibility = Visibility.Hidden;

            InitGameField();

            gameStarted = true;

            gameCanvas.Visibility = Visibility.Visible;
            timeLeftLabel.Visibility = Visibility.Visible;
            timeLeftLabelValue.Visibility = Visibility.Visible;
            topScoreLabel.Visibility = Visibility.Visible;
            topScoreValue.Visibility = Visibility.Visible;
            currentScoreLabel.Visibility = Visibility.Visible;
            currentScoreValue.Visibility = Visibility.Visible;
            timeLeftBarCanvas.Visibility = Visibility.Visible;

            ts = ts.Add(new TimeSpan(0, 0, 60));
            timeLeftBar.Value = 60;

            timeLeftLabelValue.Content = ts.ToString(@"mm\:ss");
            timer.Start();
        }

        private void optionsButton_MouseEnter(object sender, MouseEventArgs e)
        {
            ChangeMouseOnButtonState();
            ChangeButtonForeground(sender as Button);
        }

        private void optionsButton_MouseLeave(object sender, MouseEventArgs e)
        {
            ChangeMouseOnButtonState();
            ChangeButtonForeground(sender as Button);
        }

        private void optionsButton_Click(object sender, RoutedEventArgs e)
        {
            gs.ChangeGradientColor();
            ChangeBackgroundGradient(gs.SelectGradientToChange());
            ChangeButtonForeground(sender as Button);
        }

        private void exitButton_MouseEnter(object sender, MouseEventArgs e)
        {
            ChangeMouseOnButtonState();
            ChangeButtonForeground(sender as Button);
        }

        private void exitButton_MouseLeave(object sender, MouseEventArgs e)
        {
            ChangeMouseOnButtonState();
            ChangeButtonForeground(sender as Button);
        }

        private void exitButton_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }

        private void gameWindow_MouseMove(object sender, MouseEventArgs e)
        {
            if (gameStarted == true)
            {
                topScoreValue.Content = player.GetTopScore();
                currentScoreValue.Content = player.GetCurrentScore();

                if (ga.CheckNoMoveLeft())
                {
                    ga.ResetGameField();
                    ts = ts.Add(new TimeSpan(0, 0, 15));
                    timeLeftBar.Value += 15;
                }
            }
        }
    }
}
