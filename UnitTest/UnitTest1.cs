using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Checkers;

namespace UnitTest
{
    [TestClass]
    public class TestCheckersGame
    {
        [TestMethod]
        public void test_initGame() 
        {
            CheckersGame game = new CheckersGame();
            Assert.IsTrue(game.squares[0].squareType == CheckerType.whiteChecker);
            
        }
        [TestMethod]
        public void test_scoreGame()
        {
            CheckersGame game = new CheckersGame();
            //Start with a blank board
            for (int i = 0; i < 32; i++)
                game.squares[i].squareType = CheckerType.empty;
            game.squares[4].squareType = CheckerType.whiteKing;
            game.squares[0].squareType = CheckerType.whiteChecker;
            game.squares[9].squareType = CheckerType.whiteChecker;
            game.squares[14].squareType = CheckerType.whiteChecker;
            game.squares[10].squareType = CheckerType.redChecker;
            game.squares[29].squareType = CheckerType.redChecker;
            game.squares[17].squareType = CheckerType.redKing;
            game.squares[16].squareType = CheckerType.redKing;
            double score = game.scoreGame(game, false);
            double epsilon = 0.001;
            Assert.IsTrue(epsilon > Math.Abs(score - 0.583333));
        }
        
    }
}
