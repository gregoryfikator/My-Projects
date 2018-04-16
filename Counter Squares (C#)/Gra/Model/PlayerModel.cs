namespace Gra.Models
{
    public static class PlayerModel
    {
        private static int currentScore;
        private static int topScore;
        private static string playerName;

        public static int CurrentScore
        {
            get
            {
                return currentScore;
            }
            set
            {
                currentScore = value;

                if (currentScore > topScore)
                {
                    topScore = currentScore;
                }
            }
        }

        public static int TopScore { get => topScore; set => topScore = value; }

        public static string PlayerName { get => playerName; set => playerName = value; }

        public static void ResetScore()
        {
            CurrentScore = 0;
        }
    }
}
