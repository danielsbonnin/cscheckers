using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Checkers
{
    public enum CheckerType { empty = 0, redChecker, whiteChecker, redKing, whiteKing }
    public enum MoveDirs { NONE = 0, TLEFT = 1, TRIGHT = 2, BLEFT = 4, BRIGHT = 8 }
    public class Square
    {
        
        public Square(Rectangle location, CheckerType type) {
            this.location = location;
            this.squareType = type;
            this.highlighted = false;
            this.tl = null;
            this.tr = null;
            this.bl = null;
            this.br = null;
        }

        public Square()
        {
            this.location = new Rectangle();
            this.squareType = 0;
            this.highlighted = false;
            this.tl = null;
            this.tr = null;
            this.bl = null;
            this.br = null;
        }
        public Rectangle location;
        public CheckerType squareType;
        public Boolean highlighted;
        public Square tl;
        public Square tr;
        public Square bl;
        public Square br;
        public int squareNumber;
    }
}
