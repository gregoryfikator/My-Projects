using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
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
    class GameArea
    {
        GameField[,] gameField;
        Random random;
        Player player;
        Button selectedButton;
        Brush selectedButtonBrush;

        public class SolidColorBrushComparer : IEqualityComparer<SolidColorBrush>
        {
            public bool Equals(SolidColorBrush x, SolidColorBrush y)
            {
                return x.Color == y.Color &&
                    x.Opacity == y.Opacity;
            }

            public int GetHashCode(SolidColorBrush obj)
            {
                return new { C = obj.Color, O = obj.Opacity }.GetHashCode();
            }
        }

        public GameArea(Random random, Player player)
        {
            this.random = random;
            this.player = player;

            InitGameField();
        }

        private void InitGameField()
        {
            gameField = null;
            gameField = new GameField[7, 5];

            for (int i = 0; i < 7; ++i)
                for (int j = 0; j < 5; ++j)
                {
                    gameField[i, j] = new GameField();
                    gameField[i, j].SetField(random.Next(11).ToString(), random.Next(3));
                    gameField[i, j].GetField().Click += SelectClickedButton;
                }
        }

        public void ResetGameField()
        {
            SetFieldsOnBoard();
        }

        private void SetFieldsOnBoard()
        {
            for (int i = 0; i < 7; ++i)
                for (int j = 0; j < 5; ++j)
                    gameField[i, j].SetField(random.Next(11).ToString(), random.Next(3));
        }

        public GameField AccessSpecifiedField(int i, int j)
        {
            return gameField[i,j];
        }

        public void SelectClickedButton(object sender, RoutedEventArgs e)
        {
            if (selectedButton == null)
            {               
                selectedButton = (Button)sender;
                ChangeButtonForegroundToSelected();
            }
            else if (selectedButton == sender)
            {
                ChangeButtonForegroundToDefault();
                selectedButton = null;                
            }
            else
            {
                if (CompareButtonsValue((Button)sender))
                {
                    Button sended = (Button)sender;

                    if (CompareBrushes(sended))
                        player.AddScore(50 + (5 * int.Parse(selectedButton.Content.ToString())));
                    else
                        player.AddScore(25 + (int.Parse(selectedButton.Content.ToString())));

                    selectedButton.Visibility = Visibility.Hidden;
                    ChangeButtonForegroundToDefault();
                    selectedButton = null;
                  
                    sended.Visibility = Visibility.Hidden;
                    sended = null;
                }
                else
                {
                    ChangeButtonForegroundToDefault();
                    selectedButton = null;                  
                }
            }
        }

        private bool CompareButtonsValue(Button comparedButton)
        {
            return selectedButton.Content.ToString().Equals(comparedButton.Content.ToString());
        }

        private bool CompareBrushes(Button comparedButton)
        {
            return (new SolidColorBrushComparer().Equals((SolidColorBrush)selectedButtonBrush, (SolidColorBrush)comparedButton.Background));
        }

        private bool CompareSelectedBrushWithColor(string color)
        {
            return (new SolidColorBrushComparer().Equals((SolidColorBrush)selectedButton.Background, (SolidColorBrush)(new BrushConverter().ConvertFrom(color))));
        }

        private void ChangeButtonForegroundToDefault()
        {
            selectedButton.Background = selectedButtonBrush;
        }

        private void ChangeButtonForegroundToSelected()
        {
            BrushConverter bc = new BrushConverter();
            selectedButtonBrush = selectedButton.Background.CloneCurrentValue();

            if (CompareSelectedBrushWithColor("#FF800000"))
                selectedButton.Background = (SolidColorBrush)bc.ConvertFrom("#FFFF0000");
            else if (CompareSelectedBrushWithColor("#FF008000"))
                selectedButton.Background = (SolidColorBrush)bc.ConvertFrom("#FF00FF00");
            else if (CompareSelectedBrushWithColor("#FF000080"))
                selectedButton.Background = (SolidColorBrush)bc.ConvertFrom("#FF0000FF");
        }

        public bool CheckNoMoveLeft()
        {
            List<string> valuesLeftOnBoard = new List<string>();
            for (int i = 0; i < 7; ++i)
                for (int j = 0; j < 5; ++j)
                    if (gameField[i, j].GetField().Visibility == Visibility.Visible)
                        valuesLeftOnBoard.Add(gameField[i, j].GetField().Content.ToString());

            List<string> valuesLeftOnBoardCopy = valuesLeftOnBoard.ToList();

            foreach (string valueLeft in valuesLeftOnBoard)
            {
                valuesLeftOnBoardCopy.Remove(valueLeft);
                if (valuesLeftOnBoardCopy.Contains(valueLeft))
                    return false; 
            }
            return true;
        }
    }
}
