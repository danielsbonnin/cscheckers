using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Checkers;

namespace UnitTest
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void test_initGame() 
        {
            CheckersGame game = new CheckersGame();
            Assert.IsTrue(game.squares[0].squareType == CheckerType.whiteChecker);
            
        }
    }
}
