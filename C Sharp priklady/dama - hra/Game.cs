using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace dama
{
    internal class Game
    {
        private Board game1;

        public Game()
        {
            this.game1 = new Board();
            int x = 1;

            do
            {
                game1.move(x);
                game1.PrintBoard();
                if (x == 1)
                {
                    x = 2;
                }
                else
                {
                    x = 1;
                }
            } while (game1.end() != true);
        }
    }
}
