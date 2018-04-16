using System.Windows;

namespace Gra.Utilities
{
    public class ControlExtensions
    {
        public static readonly DependencyProperty IsSelectedProperty =
            DependencyProperty.RegisterAttached("IsSelected", typeof(bool), typeof(ControlExtensions), new PropertyMetadata(default(bool)));

        public static void SetIsSelected(UIElement element, bool value)
        {
            element.SetValue(IsSelectedProperty, value);
        }

        public static bool GetIsSelected(UIElement element)
        {
            return (bool)element.GetValue(IsSelectedProperty);
        }

        public static readonly DependencyProperty IndexProperty =
            DependencyProperty.RegisterAttached("Index", typeof(int), typeof(ControlExtensions), new PropertyMetadata(default(int)));

        public static void SetIndex(UIElement element, int value)
        {
            element.SetValue(IndexProperty, value);
        }

        public static int GetIndex(UIElement element)
        {
            return (int)element.GetValue(IndexProperty);
        }
    }
}
