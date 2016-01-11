using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Checkers
{
    public class CheckersGame
    {
        public CheckersGame()
        {
            this.squares = new Square[32];
            initSquares(this.squares);
        }

        public CheckersGame(Square[] squares)
        {
            this.squares = squares;
        }
        Boolean jumpRequired = false;
        Boolean multipleJumpInProgress = false;
        Boolean originSelected = false;
        Boolean curPlayerIsWhite = true;
        Square originSquare;
        Square multipleJumper;
        public Square[] squares;
        private void initSquares(Square[] squares)
        {
            for (int i = 0; i < 32; i++)
            {
                squares[i] = new Square();
                squares[i].squareNumber = i;
            }
            squares[0].tl = null;
            squares[0].tr = squares[4];
            squares[0].bl = null;
            squares[0].br = null;
            squares[1].tl = squares[4];
            squares[1].tr = squares[5];
            squares[1].bl = null;
            squares[1].br = null;
            squares[2].tl = squares[5];
            squares[2].tr = squares[6];
            squares[2].bl = null;
            squares[2].br = null;
            squares[3].tl = squares[6];
            squares[3].tr = squares[7];
            squares[3].bl = null;
            squares[3].br = null;
            squares[4].tl = squares[8];
            squares[4].tr = squares[9];
            squares[4].bl = squares[0];
            squares[4].br = squares[1];
            squares[5].tl = squares[9];
            squares[5].tr = squares[10];
            squares[5].bl = squares[1];
            squares[5].br = squares[2];
            squares[6].tl = squares[10];
            squares[6].tr = squares[11];
            squares[6].bl = squares[2];
            squares[6].br = squares[3];
            squares[7].tl = squares[11];
            squares[7].tr = null;
            squares[7].bl = squares[3];
            squares[7].br = null;
            squares[8].tl = null;
            squares[8].tr = squares[12];
            squares[8].bl = null;
            squares[8].br = squares[4];
            squares[9].tl = squares[12];
            squares[9].tr = squares[13];
            squares[9].bl = squares[4];
            squares[9].br = squares[5];
            squares[10].tl = squares[13];
            squares[10].tr = squares[14];
            squares[10].bl = squares[5];
            squares[10].br = squares[6];
            squares[11].tl = squares[14];
            squares[11].tr = squares[15];
            squares[11].bl = squares[6];
            squares[11].br = squares[7];
            squares[12].tl = squares[16];
            squares[12].tr = squares[17];
            squares[12].bl = squares[8];
            squares[12].br = squares[9];
            squares[13].tl = squares[17];
            squares[13].tr = squares[18];
            squares[13].bl = squares[9];
            squares[13].br = squares[10];
            squares[14].tl = squares[18];
            squares[14].tr = squares[19];
            squares[14].bl = squares[10];
            squares[14].br = squares[11];
            squares[15].tl = squares[19];
            squares[15].tr = null;
            squares[15].bl = squares[11];
            squares[15].br = null;
            squares[16].tr = null;
            squares[16].tl = squares[20];
            squares[16].bl = null;
            squares[16].br = squares[12];
            squares[17].tl = squares[20];
            squares[17].tr = squares[21];
            squares[17].bl = squares[12];
            squares[17].br = squares[13];
            squares[18].tl = squares[21];
            squares[18].tr = squares[22];
            squares[18].bl = squares[13];
            squares[18].br = squares[14];
            squares[19].tl = squares[22];
            squares[19].tr = squares[23];
            squares[19].bl = squares[14];
            squares[19].br = squares[15];
            squares[20].tl = squares[24];
            squares[20].tr = squares[25];
            squares[20].bl = squares[16];
            squares[20].br = squares[17];
            squares[21].tl = squares[25];
            squares[21].tr = squares[26];
            squares[21].bl = squares[17];
            squares[21].br = squares[18];
            squares[22].tl = squares[26];
            squares[22].tr = squares[27];
            squares[22].bl = squares[18];
            squares[22].br = squares[19];
            squares[23].tl = squares[27];
            squares[23].tr = null;
            squares[23].bl = squares[19];
            squares[23].br = null;
            squares[24].tl = null;
            squares[24].tr = squares[28];
            squares[24].bl = null;
            squares[24].br = squares[20];
            squares[25].tl = squares[28];
            squares[25].tr = squares[29];
            squares[25].bl = squares[20];
            squares[25].br = squares[21];
            squares[26].tl = squares[29];
            squares[26].tr = squares[30];
            squares[26].bl = squares[21];
            squares[26].br = squares[22];
            squares[27].tl = squares[30];
            squares[27].tr = squares[31];
            squares[27].bl = squares[22];
            squares[27].br = squares[23];
            squares[28].tl = null;
            squares[28].tr = null;
            squares[28].bl = squares[24];
            squares[28].br = squares[25];
            squares[29].tl = null;
            squares[29].tr = null;
            squares[29].bl = squares[25];
            squares[29].br = squares[26];
            squares[30].tl = null;
            squares[30].tr = null;
            squares[30].bl = squares[26];
            squares[30].br = squares[27];
            squares[31].tl = null;
            squares[31].tr = null;
            squares[31].bl = squares[27];
            squares[31].br = null;

            for (int i = 0; i < 32; i++)
            {
                if (i < 12)
                    squares[i].squareType = CheckerType.whiteChecker;
                else if (i >= 20)
                    squares[i].squareType = CheckerType.redChecker;
            }
        }

        public void mouseHandler()
        {
            var mouseState = Microsoft.Xna.Framework.Input.Mouse.GetState();
            var mousePosition = new Point(mouseState.X, mouseState.Y);
            if (mouseState.LeftButton == Microsoft.Xna.Framework.Input.ButtonState.Pressed)
            {
                for (int i = 0; i < 32; i++)
                {
                    if (this.squares[i].location.Contains(mousePosition))
                    {
                        var curChecker = this.squares[i].squareType;
                        if (!originSelected &&
                            curChecker != CheckerType.empty &&
                            //Piece color matches player color
                            (curPlayerIsWhite ^ (curChecker == CheckerType.redChecker || curChecker == CheckerType.redKing)))
                        {
                            if (jumpRequired && canCapture(this, this.squares[i]) == MoveDirs.NONE)
                                continue;
                            this.squares[i].highlighted = true;
                            originSelected = true;
                            originSquare = this.squares[i];
                        }

                        else if (originSelected && i != originSquare.squareNumber)
                        {
                            if (checkMove(this, originSquare, this.squares[i], jumpRequired))
                            {
                                curPlayerIsWhite = !curPlayerIsWhite;
                                jumpRequired = false;
                                for (int j = 0; j < 32; j++)
                                {
                                    if (this.squares[j].squareType != CheckerType.empty &&
                                        (curPlayerIsWhite ^
                                        (this.squares[j].squareType == CheckerType.redChecker ||
                                        this.squares[j].squareType == CheckerType.redKing)))
                                    {
                                        if ((canCapture(this, this.squares[j])) != MoveDirs.NONE)
                                            jumpRequired = true;
                                    }
                                }
                            }
                            originSquare.highlighted = false;
                            originSelected = false;
                        }
                        else { }
                    }
                }
            }
        }
        public void kingMe(CheckersGame game, Square loc)
        {
            if (loc.squareNumber < 4)
            {
                if (loc.squareType == CheckerType.redChecker)
                    loc.squareType = CheckerType.redKing;
                else
                    return;
            }
            else if (loc.squareNumber >= 28)
            {
                if (loc.squareType == CheckerType.whiteChecker)
                    loc.squareType = CheckerType.whiteKing;
                else
                    return;
            }
            else
                return;
        }
        public void move(CheckersGame game, Square origin, Square destination)
        {
            destination.squareType = origin.squareType;
            origin.squareType = CheckerType.empty;
            kingMe(game, destination);
        }

        public void singleCapture(CheckersGame game, Square origin, MoveDirs capDir)
        {

            switch (capDir)
            {
                case MoveDirs.TLEFT:
                    origin.tl.tl.squareType = origin.squareType;
                    origin.tl.squareType = CheckerType.empty;
                    origin.squareType = CheckerType.empty;
                    kingMe(game, origin.tl.tl);
                    break;
                case MoveDirs.TRIGHT:
                    origin.tr.tr.squareType = origin.squareType;
                    origin.tr.squareType = CheckerType.empty;
                    origin.squareType = CheckerType.empty;
                    kingMe(game, origin.tr.tr);
                    break;
                case MoveDirs.BLEFT:
                    origin.bl.bl.squareType = origin.squareType;
                    origin.bl.squareType = CheckerType.empty;
                    origin.squareType = CheckerType.empty;
                    kingMe(game, origin.bl.bl);
                    break;
                case MoveDirs.BRIGHT:
                    origin.br.br.squareType = origin.squareType;
                    origin.br.squareType = CheckerType.empty;
                    origin.squareType = CheckerType.empty;
                    kingMe(game, origin.br.br);
                    break;
                default:
                    break;
            }
        }

        private MoveDirs canCapture(CheckersGame game, Square origin)
        {
            MoveDirs capDirs = MoveDirs.NONE;
            if (origin.tl != null && origin.tl.tl != null && isLegalCapture(game, origin, MoveDirs.TLEFT))
                capDirs = capDirs | MoveDirs.TLEFT;
            if (origin.tr != null && origin.tr.tr != null && isLegalCapture(game, origin, MoveDirs.TRIGHT))
                capDirs = capDirs | MoveDirs.TRIGHT;
            if (origin.bl != null && origin.bl.bl != null && isLegalCapture(game, origin, MoveDirs.BLEFT))
                capDirs = capDirs | MoveDirs.BLEFT;
            if (origin.br != null && origin.br.br != null && isLegalCapture(game, origin, MoveDirs.BRIGHT))
                capDirs = capDirs | MoveDirs.BRIGHT;
            return capDirs;

        }
        private Boolean isLegalMove(CheckersGame game, Square origin, MoveDirs destination)
        {
            var stop = (destination == MoveDirs.TLEFT ? origin.tl :
                        (destination == MoveDirs.TRIGHT ? origin.tr :
                        (destination == MoveDirs.BLEFT ? origin.bl : origin.br)));
            if (stop == null || stop.squareType != CheckerType.empty)
                return false;
            if (origin.squareType == CheckerType.whiteKing ||
                origin.squareType == CheckerType.redKing)
            {
                return true;
            }

            else if (origin.squareType == CheckerType.whiteChecker)
            {
                if (stop == origin.tl || stop == origin.tr)
                    return true;
                else
                    return false;
            }
            else if (origin.squareType == CheckerType.redChecker)
            {
                if (stop == origin.bl || stop == origin.br)
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
        /**
         * @param capDir MoveDirs single direction
         * @return whether proposed capture is legal 
          */
        private Boolean isLegalCapture(CheckersGame game, Square origin, MoveDirs capDir, Square ignore = null)
        {
            Boolean isWhite = (
                (origin.squareType == CheckerType.whiteChecker ||
                 origin.squareType == CheckerType.whiteKing) ?
                 true : false
                 );
            Square toCapture, stop;


            if (capDir == MoveDirs.TLEFT)
            {
                if (origin.squareType == CheckerType.redChecker)
                    return false;
                stop = origin.tl.tl;
                toCapture = origin.tl;

            }
            else if (capDir == MoveDirs.TRIGHT)
            {
                if (origin.squareType == CheckerType.redChecker)
                    return false;
                stop = origin.tr.tr;
                toCapture = origin.tr;
            }
            else if (capDir == MoveDirs.BLEFT)
            {
                if (origin.squareType == CheckerType.whiteChecker)
                    return false;
                stop = origin.bl.bl;
                toCapture = origin.bl;
            }
            else if (capDir == MoveDirs.BRIGHT)
            {
                if (origin.squareType == CheckerType.whiteChecker)
                    return false;
                stop = origin.br.br;
                toCapture = origin.br;
            }
            else
                return false;

            if (toCapture == null || stop == null)
                return false;

            if (toCapture.squareType == CheckerType.empty)
                return false;

            if (stop.squareType != CheckerType.empty && stop != ignore)
                return false;

            if ((toCapture.squareType == CheckerType.redChecker ||
                toCapture.squareType == CheckerType.redKing) ^
                isWhite)
                return false;
            return true;
        }
        public Boolean checkMove(CheckersGame game, Square origin, Square destination, Boolean mustJump = false)
        {
            if (origin.tl != null && destination == origin.tl && !mustJump)
                if (isLegalMove(game, origin, MoveDirs.TLEFT))
                {
                    move(game, origin, destination);
                    return true;
                }
                else
                    return false;

            else if (origin.tr != null && destination == origin.tr && !mustJump)
                if (isLegalMove(game, origin, MoveDirs.TRIGHT))
                {
                    move(game, origin, destination);
                    return true;
                }
                else
                    return false;

            else if (origin.bl != null && destination == origin.bl && !mustJump)
                if (isLegalMove(game, origin, MoveDirs.BLEFT))
                {
                    move(game, origin, destination);
                    return true;
                }
                else
                    return false;

            else if (origin.br != null && destination == origin.br && !mustJump)
            {
                if (isLegalMove(game, origin, MoveDirs.BRIGHT))
                {
                    move(game, origin, destination);
                    return true;
                }
                else
                    return false;
            }

            else if (origin.tl != null && origin.tl.tl != null && destination == origin.tl.tl)
            {
                if (isLegalCapture(game, origin, MoveDirs.TLEFT))
                {
                    singleCapture(game, origin, MoveDirs.TLEFT);
                }
                else
                    return false;
            }
            else if (origin.tr != null && origin.tr.tr != null && destination == origin.tr.tr)
            {
                if (isLegalCapture(game, origin, MoveDirs.TRIGHT))
                {
                    singleCapture(game, origin, MoveDirs.TRIGHT);
                }
                else
                    return false;
            }
            else if (origin.bl != null && origin.bl.bl != null && destination == origin.bl.bl)
            {
                if (isLegalCapture(game, origin, MoveDirs.BLEFT))
                {
                    singleCapture(game, origin, MoveDirs.BLEFT);
                }
                else
                    return false;
            }
            else if (origin.br != null && origin.br.br != null && destination == origin.br.br)

                if (isLegalCapture(game, origin, MoveDirs.BRIGHT))
                {
                    singleCapture(game, origin, MoveDirs.BRIGHT);

                }
                else
                    return false;
            else
                return false;

            //Check for multiple jump
            if (canCapture(game, destination) == MoveDirs.NONE)
            {
                jumpRequired = false;
                multipleJumpInProgress = false;
                return true;
            }
            else
            {
                originSquare = destination;
                jumpRequired = true;
                multipleJumpInProgress = true;
                multipleJumper = destination;
                return false;
            }

        }

        public double scoreGame(CheckersGame game, Boolean isWhite)
        {
            int i, whiteRowNum, redRowNum;
            double whiteScore, redScore, scoreSum, score;

            whiteScore = 0.0;
            redScore = 0.0;

            for (i = 0; i < 32; i++)
            {
                whiteRowNum = i / 4;
                redRowNum = 7 - whiteRowNum;

                //Calculate white portion of score
                if (game.squares[i].squareType == CheckerType.whiteChecker)
                    whiteScore += 1 + (whiteRowNum / 2);
                else if (game.squares[i].squareType == CheckerType.redChecker)
                    redScore += (1 + (redRowNum / 2));
                else if (game.squares[i].squareType == CheckerType.whiteKing)
                    whiteScore += 5;
                else if (game.squares[i].squareType == CheckerType.redKing)
                    redScore += 5;
                else
                    continue;
            }
            scoreSum = whiteScore + redScore;
            if (whiteScore == 0)
                return isWhite ? -1.0 : 1.0;
            else if (redScore == 0)
                return isWhite ? 1.0 : -1.0;
            else if (whiteScore > redScore)
            {
                score = whiteScore / scoreSum;
                if (isWhite)
                    return score;
                else
                    return -score;
            }
            else if (redScore > whiteScore)
            {
                score = redScore / scoreSum;
                if (isWhite)
                    return -score;
                else return score;
            }
            //Scores are equal and non-zero.
            else
                return 0.0;
        }
    }
}
