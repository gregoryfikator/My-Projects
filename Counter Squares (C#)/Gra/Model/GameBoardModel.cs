namespace Gra.Models
{
    public partial class GameBoardModel
    {
        private GameFieldModel[,] gameField;

        public GameFieldModel[,] GameField { get => gameField; set => gameField = value; }

        public GameBoardModel()
        {

        }

        public GameFieldModel AccessSpecifiedField(int i, int j)
        {
            return GameField[i, j];
        }
    }
}
