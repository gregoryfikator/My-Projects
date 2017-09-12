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
    class GameField
    {
        Button field = new Button();

        public void SetField(string randomNumberValueAsContent, int randomNumberValueAsColor)
        {
            SetButtonProperties(randomNumberValueAsContent);
            RandomizeColorOfButton(randomNumberValueAsColor);
        }

        private void SetButtonProperties(string randomNumberValueAsContent)
        {
            field.FontSize = 24;
            field.Content = randomNumberValueAsContent;
            field.Visibility = Visibility.Visible;
        }

        private void RandomizeColorOfButton(int randomNumberValueAsColor)
        {
            BrushConverter bc = new BrushConverter();

            if (randomNumberValueAsColor == 0)
                field.Background = (Brush)bc.ConvertFrom("#FF800000");
            else if (randomNumberValueAsColor == 1)
                field.Background = (Brush)bc.ConvertFrom("#FF008000");
            else if (randomNumberValueAsColor == 2)
                field.Background = (Brush)bc.ConvertFrom("#FF000080");
        }

        public void SetOnBoard(int i, int j)
        {
            Grid.SetRow(field, j + 2);
            Grid.SetColumn(field, i + 2);
        } 

        public Button GetField()
        {
            return field;
        }




    }
}
