using System;
using System.Windows;
using System.Windows.Data;
using System.Windows.Media;

namespace Gra.Utilities
{
    public class LinearGradientConverter : IMultiValueConverter
    {
        public object Convert(object[] values, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            FrameworkElement targetElement = values[0] as FrameworkElement;
            string gradientBrushName = values[1] as string;

            if (gradientBrushName == null)
                return null;

            LinearGradientBrush newStyle = (LinearGradientBrush)targetElement.TryFindResource(gradientBrushName);

            if (newStyle == null)
                newStyle = (LinearGradientBrush)targetElement.TryFindResource("MyDefaultGradientBrushName");

            return newStyle;
        }

        public object[] ConvertBack(object value, Type[] targetTypes, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
