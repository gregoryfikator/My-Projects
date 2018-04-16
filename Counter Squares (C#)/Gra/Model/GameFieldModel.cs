using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace Gra.Models
{
    public class GameFieldModel
    {
        private Button field = new Button();

        public Button Field { get => field; }

        public void SetField(string randomNumberValueAsContent, int randomNumberValueAsColor)
        {
            SetButtonProperties(randomNumberValueAsContent);
            RandomizeColorOfButton(randomNumberValueAsColor);
        }

        private void SetButtonProperties(string randomNumberValueAsContent)
        {
            Field.FontSize = 24;
            Field.Content = randomNumberValueAsContent;
            Field.Visibility = Visibility.Visible;
        }

        private void RandomizeColorOfButton(int randomNumberValueAsColor)
        {      
            BrushConverter bc = new BrushConverter();

            if (randomNumberValueAsColor == 0)
            {
                Field.Background = (Brush)bc.ConvertFrom("#FF800000");
            }
            else if (randomNumberValueAsColor == 1)
            {
                Field.Background = (Brush)bc.ConvertFrom("#FF008000");
            }
            else if (randomNumberValueAsColor == 2)
            {
                Field.Background = (Brush)bc.ConvertFrom("#FF000080");
            }
        }
    }
}
