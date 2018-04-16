using System.Collections.Generic;

namespace Gra.Utilities
{
    public static class ColorDictionary
    {
        public static int currentGradientNumber = 1;

        public static Dictionary<int, string> colorDictionary = new Dictionary<int, string>
            {
                { 1, "redGradient" },
                { 2, "greenGradient" },
                { 3, "blueGradient" },
            };
    }
}

