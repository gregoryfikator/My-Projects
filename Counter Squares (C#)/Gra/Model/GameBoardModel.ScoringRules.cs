namespace Gra.Models
{
    public partial class GameBoardModel
    {
        private const int scoreBaseWhenColorEquals = 50;
        private const int scoreBaseWhenColorNotEquals = 25;

        private const int scoreMultiplerWhenColorEquals = 5;

        public int ScoreBaseWhenColorEquals
        {
            get
            {
                return scoreBaseWhenColorEquals;
            }
        }

        public int ScoreMultiplerWhenColorEquals
        {
            get
            {
                return scoreMultiplerWhenColorEquals;
            }
        }

        public int ScoreBaseWhenColorNotEquals
        {
            get
            {
                return scoreBaseWhenColorNotEquals;
            }
        }
    }
}
