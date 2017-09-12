using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Gra
{
    class Player
    {
        int currentScore;
        int topScore;

        public int GetCurrentScore()
        {
            return currentScore;
        }
        public void AddScore(int addedScore)
        {
            currentScore += addedScore;
            UpdateTopScore();
        }

        public int GetTopScore()
        {
            return topScore;
        }
        private void UpdateTopScore()
        {
            if (currentScore > topScore)
                topScore = currentScore;
        }

        public void ResetScore()
        {
            currentScore = 0;
        }
    }
}
