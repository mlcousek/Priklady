using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace dama
{
    public class Figurine
    {
        public Color color;
        public int row_coordinate;
        public int col_coordinate;
        public bool is_Queen;

        public Figurine(int row, int col, Color color) 
        {
            this.row_coordinate = row;
            this.col_coordinate = col;
            this.color = color;
            this.is_Queen = false;
        }

        public int GetRow()
        {
            return this.row_coordinate;
        }

        public void SetRow(int x)
        { 
            this.row_coordinate = x;         
        }
        public void SetCol(int y)
        {
            this.col_coordinate = y;
        }

        public int GetCol()
        {
            return this.col_coordinate;
        }
        public Color GetColor()
        {
            return this.color;
        }
        public void SetColor(Color color)
        {
            this.color = color;
        }
        public bool IsQueen()
        {
            return this.is_Queen;
        }
        public void SetQueen(bool isQueen)
        {
            this.is_Queen = isQueen;
        }
    }

}
