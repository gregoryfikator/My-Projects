using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;

namespace Gra
{
    public class GradientSelector
    {
        private enum GradientColorSet { RED = 0, GREEN = 1, BLUE = 2 };
        private int colorSet = (int)GradientColorSet.RED;
        static private int enumLength = GradientColorSet.GetNames(typeof(GradientColorSet)).Length;

        GradientColorAndOffsetHolder gradientHolder;
        private class GradientColorAndOffsetHolder
        { 
            public string[] GradientHexStringValues = new string[enumLength];
            public string[] GradientOffsetStringValues = { "0,00", "0,15", "0,50", "0,85", "1,00" };

            public GradientColorAndOffsetHolder()
            {
                InitGradientHexTable();
            }

            private void InitGradientHexTable()
            {
                GradientHexStringValues[0] = "#FF7E0000" + "#FE4B0000" + "#FE4D0202" + "#FE4B0000" + "#FF7E0000"; //RED
                GradientHexStringValues[1] = "#FF16A608" + "#FE027A0D" + "#FE044908" + "#FE027A0D" + "#FF16A608"; //GREEN
                GradientHexStringValues[2] = "#FF0808A6" + "#FE021672" + "#FE0C0461" + "#FE021672" + "#FF0808A6"; //BLUE
            }

            public string GetHexStringToCreateSubstrings(int index)
            {                
                try
                {
                    return GradientHexStringValues[index];
                }
                catch (Exception e)
                {
                    Console.WriteLine("Bład w GetHexStringToCreateSubstrings()!");
                    throw e;
                }
            }

            public string GetOffsetString(int index)
            {
                try
                {
                    return GradientOffsetStringValues[index];
                }
                catch(Exception e)
                {
                    Console.WriteLine("Bład w GetOffsetString()!");
                    throw e;
                }
            }
        }

        List<LinearGradientBrush> lgbList = new List<LinearGradientBrush>();
        
        public void InitBrushes()
        {
            try
            {
                gradientHolder = new GradientColorAndOffsetHolder();

                for (int i = 0; i < enumLength; i++)
                {
                    LinearGradientBrush lgb = new LinearGradientBrush();
                    lgb.StartPoint = new Point(0.5, 1);
                    lgb.EndPoint = new Point(0.5, 0);
                    AddGradientStops(lgb, i);
                    lgbList.Add(lgb);
                }
            }
            catch(Exception e)
            {
                Console.WriteLine("Błąd w InitBrushes()!");
                throw e;
            }
        }

        private void AddGradientStops(LinearGradientBrush lgb, int indexFromEnum)
        {
            try
            {
                for (int i = 0, j = 0; i < 5; i++, j += 9)
                    lgb.GradientStops.Add(new GradientStop() {
                        Color = (Color)ColorConverter.ConvertFromString(gradientHolder.GetHexStringToCreateSubstrings(indexFromEnum).Substring(j, 9)),
                        Offset = Double.Parse(gradientHolder.GetOffsetString(i))
                    });

            }
            catch (Exception e)
            {
                Console.WriteLine("Bład w AddGradientStops()!");
                throw e;
            }
}

        public void ChangeGradientColor()
        {
            if (colorSet < enumLength - 1)
                colorSet++;
            else
                colorSet = 0;
        }

        public LinearGradientBrush SelectGradientToChange()
        {
            Console.WriteLine("colorSet value: " + colorSet);
            return lgbList[colorSet];
        }

        public string GetColorName()
        {
            return GradientColorSet.GetNames(typeof(GradientColorSet))[colorSet];
        }
    }
}
