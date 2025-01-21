using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using dama;
using static System.Net.Mime.MediaTypeNames;

namespace dama
{
    public class Board
    {
        private const int Rows = 8;
        private const int Cols = 8;
        private int AllFiguresC = 24;
        private string[,] board;
        private Figurine[] AllFigurine; 

        public Board()
        {
            this.board = new string[Rows,Cols];
            this.AllFigurine = new Figurine[AllFiguresC];
            EmptyBoard();
            GenAllFigurines();
            SetFigurinesToPlaces();
            PrintBoard();
        }

        private void EmptyBoard()
        {
            for (int i = 0; i < Rows; i++)
            {
                for (int j = 0; j < Cols; j++)
                {
                    board[i, j] = ("   ");
                }
            }
        }

        private void GenAllFigurines()
        {
            AllFigurine[0] = new Figurine(7, 0, Color.White); AllFigurine[1] = new Figurine(7, 2, Color.White); AllFigurine[2] = new Figurine(7, 4, Color.White);
            AllFigurine[3] = new Figurine(7, 6, Color.White); AllFigurine[4] = new Figurine(6, 1, Color.White); AllFigurine[5] = new Figurine(6, 3, Color.White);
            AllFigurine[6] = new Figurine(6, 5, Color.White); AllFigurine[7] = new Figurine(6, 7, Color.White); AllFigurine[8] = new Figurine(5, 0, Color.White);
            AllFigurine[9] = new Figurine(5, 2, Color.White); AllFigurine[10] = new Figurine(5, 4, Color.White); AllFigurine[11] = new Figurine(5, 6, Color.White);
            AllFigurine[12] = new Figurine(0, 1, Color.Black); AllFigurine[13] = new Figurine(0, 3, Color.Black); AllFigurine[14] = new Figurine(0, 5, Color.Black);
            AllFigurine[15] = new Figurine(0, 7, Color.Black); AllFigurine[16] = new Figurine(1, 0, Color.Black); AllFigurine[17] = new Figurine(1, 2, Color.Black); 
            AllFigurine[18] = new Figurine(1, 4, Color.Black); AllFigurine[19] = new Figurine(1, 6, Color.Black); AllFigurine[20] = new Figurine(2, 1, Color.Black); 
            AllFigurine[21] = new Figurine(2, 3, Color.Black); AllFigurine[22] = new Figurine(2, 5, Color.Black); AllFigurine[23] = new Figurine(2, 7, Color.Black);
        }

        public Figurine[] GetAllFigurine()
        {
            return this.AllFigurine;
        }
        
        private void SetFigurinesToPlaces()
        {
            for (int i = 0; i < Rows; i++)
            {
                for (int j = 0; j < Cols; j++)
                {
                    for (int k = 0; k < AllFiguresC; k++)
                    {
                        if (AllFigurine[k].row_coordinate == i && AllFigurine[k].col_coordinate == j && AllFigurine[k].is_Queen == false)
                        {
                            board[i, j] = (" ☻ ");
                            break;
                        }
                        else if (AllFigurine[k].row_coordinate == i && AllFigurine[k].col_coordinate == j && AllFigurine[k].is_Queen == true)
                        {
                            board[i, j] = (" Q ");
                            break;
                        }
                        else
                        {
                            board[i, j] = ("   ");

                        }
                    }
                }
            }
        }
        private void helpfun(int i, int j)
        {
            for (int k = 0; k< AllFiguresC; k++)
            {
                if (AllFigurine[k].row_coordinate == i && AllFigurine[k].col_coordinate == j)
                {
                    if (AllFigurine[k].color == Color.White)
                    {
                        Console.ForegroundColor = ConsoleColor.Yellow;//bila na bile bacha
                    }
                    else
                    {
                        Console.ForegroundColor = ConsoleColor.DarkGray;
                    }
                }
            }
        }

        public void PrintBoard()
        {
            SetFigurinesToPlaces();
            Console.Clear();
            int pom = 0, pom1 = 0;
            Console.Write("\n\n  ");
            Console.BackgroundColor = ConsoleColor.Yellow;
            Console.ForegroundColor = ConsoleColor.Black;
            Console.Write("  0  1  2  3  4  5  6  7 \n");
            Console.ResetColor();
            Console.BackgroundColor = ConsoleColor.Yellow;
            Console.ForegroundColor = ConsoleColor.Black;
            Console.Write(" ");
            Console.Write(pom1);
            Console.Write(" ");
            pom1++;

            for (int i = 0; i < Rows; i++)
            {
                for (int j = 0; j < Cols; j++)
                {
                    if (pom == 0 && j + 1 == Cols)
                    {
                        Console.BackgroundColor = ConsoleColor.White;
                        helpfun(i, j);
                        Console.WriteLine(board[i, j]);
                        Console.ResetColor();
                        Console.BackgroundColor = ConsoleColor.Yellow;
                        Console.ForegroundColor = ConsoleColor.Black;
                        if (i + 1 != Cols)
                        {
                            Console.Write(" ");
                            Console.Write(pom1);
                            Console.Write(" ");
                        }
                        pom1++;
                        pom++;
                    }
                    else if (pom == 0)
                    {
                        Console.BackgroundColor = ConsoleColor.White;
                        for (int k = 0; k < AllFiguresC; k++)
                        {
                            if (AllFigurine[k].row_coordinate == i && AllFigurine[k].col_coordinate == j)
                            {
                                if (AllFigurine[k].color == Color.White)
                                {
                                    Console.ForegroundColor = ConsoleColor.Yellow;
                                }
                                else
                                {
                                    Console.ForegroundColor = ConsoleColor.Black;
                                }
                            }
                        }
                        Console.Write(board[i, j]);
                        pom++;
                    }
                    else if (pom == 1 && j + 1 == Cols)
                    {
                        Console.BackgroundColor = ConsoleColor.Black;
                        helpfun(i, j);  
                        Console.WriteLine(board[i, j] + "   ");
                        Console.ResetColor();
                        Console.BackgroundColor = ConsoleColor.Yellow;
                        Console.ForegroundColor = ConsoleColor.Black;
                        if (i + 1 != Cols)
                        {
                            Console.Write(" ");
                            Console.Write(pom1);
                            Console.Write(" ");
                        }
                        pom1++;
                        pom--;
                    }
                    else
                    {
                        Console.BackgroundColor = ConsoleColor.Black;
                        for (int k = 0; k < AllFiguresC; k++)
                        {
                            if (AllFigurine[k].row_coordinate == i && AllFigurine[k].col_coordinate == j)
                            {
                                if (AllFigurine[k].color == Color.White)
                                {
                                    Console.ForegroundColor = ConsoleColor.Yellow;
                                }
                                else
                                {
                                    Console.ForegroundColor = ConsoleColor.DarkGray;
                                }
                            }
                        }
                        Console.Write(board[i, j]);
                        pom--;
                    }
                }
                if (pom == 0)
                {
                    pom++;
                }
                else
                {
                    pom--;
                }
            }
            Console.ResetColor();
            Console.WriteLine("\n\n");
        }

        private Figurine PickFigurine(int row, int col, Color color)
        {
            for (int k = 0; k < AllFiguresC; k++)
            {
                if (AllFigurine[k].row_coordinate == row && AllFigurine[k].col_coordinate == col && AllFigurine[k].color == color)
                {
                    return AllFigurine[k];
                }
            }
            return null;
        }

        private void jump(int player)
        {
            Color player_color = new Color();
            Color enemy_color = new Color();
            if (player == 1)
            {
                player_color = Color.White;
                enemy_color = Color.Black;
            }
            else
            {
                player_color = Color.Black;
                enemy_color = Color.White;

            }

            string s1 = ("Enter your figurine ROW: ");
            int a1 = 0;

            readNumber(out a1, s1);
            if (a1 < 0 || a1 > 7)
            {
                Console.WriteLine("Enter correct ROW!");
                jump(player);
                return;
            }

            string s2 = ("Enter your figurine COL: ");
            int a2 = 0;
            readNumber(out a2, s2);
            if (a2 < 0 || a2 > 7)
            {
                Console.WriteLine("Enter correct COL!");
                jump(player);
                return;
            }

            Figurine helpFig = PickFigurine(a1, a2, player_color);

            if (helpFig == null)
            {
                Console.WriteLine("Enter correct Figurine");
                jump(player);
                return;
            }

            string s3 = ("Now enter ROW of place where you want to go: ");
            int z1 = 0;

            readNumber(out z1, s3);
            if (z1 < 0 || z1 > 7)
            {
                Console.WriteLine("Enter correct ROW!");
                jump(player);
                return;
            }

            string s4 = ("Now enter COL of place where you want to go: ");
            int z2 = 0;

            readNumber(out z2, s4);
            if (z2 < 0 || z2 > 7)
            {
                Console.WriteLine("Enter correct COL!");
                jump(player);
                return;
            }
            if(z1 == a1 || z2 == a2)
            {
                Console.WriteLine("Incorrect row or col");
                jump(player);
                return;
            }
            int enf1 = 0;
            int myf1 = 0;
            //correct row queeen
            if (z1 < a1 && z2 < a2 && helpFig.is_Queen == true)
            {
                for(int k = z1 + 1, u = z2 + 1; k < a1 && u < a2; k++, u++)
                {
                    
                    if(PickFigurine(k,u,enemy_color) != null)
                    {
                        enf1++;
                    }
                    if (PickFigurine(k, u, player_color) != null)
                    {
                        myf1++;
                    }
                    
                }
            }else if (z1 < a1 && z2 > a2 && helpFig.is_Queen == true)
            {
                for (int k = z1 + 1, u = z2 - 1; k < a1 && u > a2; k++, u--)
                {
                    if (PickFigurine(k, u, enemy_color) != null)
                    {
                        enf1++;
                    }
                    if (PickFigurine(k, u, player_color) != null)
                    {
                        myf1++;
                    }
                }
            }else if(z1 > a1 && z2 > a2 && helpFig.is_Queen == true)
            {
                for (int k = z1 - 1, u = z2 - 1; k > a1 && u > a2; k--, u--)
                {
                    if (PickFigurine(k, u, enemy_color) != null)
                    {
                        enf1++;
                    }
                    if (PickFigurine(k, u, player_color) != null)
                    {
                        myf1++;
                    }
                }
            } else if(z1 > a1 && z2 < a2 && helpFig.is_Queen == true)
            {
                for (int k = z1 - 1, u = z2 + 1; k > a1 && u < a2; k--, u++)
                {
                    if (PickFigurine(k, u, enemy_color) != null)
                    {
                        enf1++;
                    }
                    if (PickFigurine(k, u, player_color) != null)
                    {
                        myf1++;
                    }
                }
            }
            if(!(((z1 <= a1 -2) || (z1 >= a1 + 2)) && 
                (PickFigurine(z1, z2, Color.White) == null) && 
                (PickFigurine(z1, z2, Color.Black) == null) &&
                (enf1 == 1) && (myf1 == 0)) && 
                helpFig.is_Queen == true)
            {
                Console.WriteLine("Enter correct ROW and COL!");
                jump(player);
                return;
            }

            //correct row
            if (!(z1 == a1 - 2) && helpFig.color == Color.White && helpFig.is_Queen == false)
            {
                Console.WriteLine("Enter correct ROW where you want to go!666");
                jump(player);
                return;
            }

            if (!(z1 == a1 + 2) && helpFig.color == Color.Black && helpFig.is_Queen == false)
            {
                Console.WriteLine("Enter correct ROW where you want to go!69");
                jump(player);
                return;
            }

            if (!((z2 == a2 - 2) &&
                (PickFigurine(z1, z2, player_color) == null) &&
                (PickFigurine(z1, z2, enemy_color) == null) &&
                (PickFigurine(z1 + 1, z2 + 1, enemy_color) != null) &&
                (PickFigurine(z1 + 1, z2 + 1, enemy_color).color == enemy_color)) &&
                helpFig.color == Color.White && z2 < a2 && helpFig.is_Queen == false)
            {
                Console.WriteLine("Enter correct COL where you want to go5!");
                jump(player);
                return; 
            }

            if (!((z2 == a2 + 2) &&
                (PickFigurine(z1, z2, player_color) == null) && 
                (PickFigurine(z1, z2, enemy_color) == null) && 
                (PickFigurine(z1 + 1, z2 - 1, enemy_color) != null) && 
                (PickFigurine(z1 + 1, z2 - 1, enemy_color).color == enemy_color)) &&
                helpFig.color == Color.White && z2 > a2 && helpFig.is_Queen == false)
            {
                Console.WriteLine("Enter correct COL where you want to go6!");
                jump(player);
                return;              
            }
            if (!((z2 == a2 - 2) &&
                (PickFigurine(z1, z2, player_color) == null) &&
                (PickFigurine(z1, z2, enemy_color) == null) &&
                (PickFigurine(z1 - 1, z2 + 1, enemy_color) != null) &&
                (PickFigurine(z1 - 1, z2 + 1, enemy_color).color == enemy_color)) &&
                helpFig.color == Color.Black && z2 < a2 && helpFig.is_Queen == false)
            {
                Console.WriteLine("Enter correct COL where you want to go7!");
                jump(player);
                return;
            }

            if (!((z2 == a2 + 2) &&
                (PickFigurine(z1, z2, player_color) == null) &&
                (PickFigurine(z1, z2, enemy_color) == null) &&
                (PickFigurine(z1 - 1, z2 - 1, enemy_color) != null) &&
                (PickFigurine(z1 - 1, z2 - 1, enemy_color).color == enemy_color)) &&
                helpFig.color == Color.Black && z2 > a2 && helpFig.is_Queen == false)
            {
                Console.WriteLine("Enter correct COL where you want to go8!");
                jump(player);
                return;
            }

            Figurine helpFig1 = PickFigurine(z1, z2, player_color);
            if (helpFig1 != null)
            {
                Console.WriteLine("You can't go on your figurine, go on another place or pick another one figurine");
                jump(player);
                return;
            }

            //correct col 2
            if (z1 == 0 && player == 1)
            {
                helpFig.SetQueen(true);
            }

            if (z1 == 7 && player != 1)
            {
                helpFig.SetQueen(true);
            }

            helpFig.SetRow(z1);
            helpFig.SetCol(z2);

            if(z2 > a2 && player_color == Color.White && helpFig.is_Queen == false)
            {
                DeleteFigure(z1 + 1, z2 - 1);
            } else if(z2 < a2 && player_color == Color.White && helpFig.is_Queen == false)
            {
                DeleteFigure(z1 + 1, z2 + 1);
            }else if(z2 > a2 && player_color == Color.Black && helpFig.is_Queen == false)
            {
                DeleteFigure(z1 - 1, z2 - 1);
            }else if(z2 < a2 && player_color == Color.Black && helpFig.is_Queen == false)
            {
                DeleteFigure(z1 - 1, z2 + 1);
            }
            if (z1 < a1 && z2 < a2 && helpFig.is_Queen == true)
            {
                for (int k = z1 + 1, u = z2 + 1; k < a1 && u < a2; k++, u++)
                {
                    if (PickFigurine(k, u, enemy_color) != null)
                    {
                        DeleteFigure(k, u);
                    }
                }
            }
            else if (z1 < a1 && z2 > a2 && helpFig.is_Queen == true)
            {
                for (int k = z1 + 1, u = z2 - 1; k < a1 && u > a2; k++, u--)
                {
                    if (PickFigurine(k, u, enemy_color) != null)
                    {
                        DeleteFigure(k, u);
                    }
                }
            }
            else if (z1 > a1 && z2 > a2 && helpFig.is_Queen == true)
            {
                for (int k = z1 - 1, u = z2 - 1; k > a1 && u > a2; k--, u--)
                {
                    if (PickFigurine(k, u, enemy_color) != null)
                    {
                        DeleteFigure(k, u);
                    }
                }
            }
            else if (z1 > a1 && z2 < a2 && helpFig.is_Queen == true)
            {
                for (int k = z1 - 1, u = z2 + 1; k > a1 && u < a2; k--, u++)
                {
                    if (PickFigurine(k, u, enemy_color) != null)
                    {
                        DeleteFigure(k, u);
                    }
                }
            }

        }
        
        public void move(int player)
        {
            Color player_color = new Color();
            if(player == 1)
            {
                player_color = Color.White;
            }
            else
            {
                player_color = Color.Black;
            }
            
            if(player == 1)
            { 
                if(mustJumpPredWhite() == true)
                {
                    jump(player);
                    return;
                }
            }
            else
            {
                if (mustJumpPredBlack() == true)
                {
                    jump(player);
                    return;
                }
            }

            string s1 = ("Enter your figurine ROW: ");
            int a1 = 0;
            
            readNumber(out a1, s1);
            if(a1 < 0 || a1 > 7)
            {
                Console.WriteLine("Enter correct ROW!");
                move(player);
                return;
            }

            string s2 = ("Enter your figurine COL: ");
            int a2 = 0;
            readNumber(out a2, s2);
            if (a2 < 0 || a2 > 7)
            {
                Console.WriteLine("Enter correct COL!");
                move(player);
                return;
            }

            Figurine helpFig = PickFigurine(a1, a2, player_color);

            if (helpFig == null)
            {
                Console.WriteLine("Enter correct Figurine");
                move(player);
                return;
            }

            string s3 = ("Now enter ROW of place where you want to go: ");
            int z1 = 0;

            readNumber(out z1, s3);
            if (z1 < 0 || z1 > 7)
            {
                Console.WriteLine("Enter correct ROW!");
                move(player);
                return;
            }

            string s4 = ("Now enter COL of place where you want to go: ");
            int z2 = 0;

            readNumber(out z2, s4);
            if (z2 < 0 || z2 > 7)
            {
                Console.WriteLine("Enter correct COL!");
                move(player);
                return;
            }

            if (z1 == a1 || z2 == a2)
            {
                Console.WriteLine("Incorrect row or col");
                move(player);
                return;
            }

            //correct row quee
            int soucetZ = z1 + z2;
            int rozdilZ = z2 - z1;
            int soucetA = a1 + a2;
            int rozdilA = a2 - a1;
            if (!((soucetA == soucetZ) || (rozdilA == rozdilZ)) && helpFig.is_Queen == true)
            {
                Console.WriteLine("Enter correct move!");
                move(player);
                return;
            }

                //correct row
            if (!(z1 == a1 - 1) && helpFig.color == Color.White && helpFig.is_Queen == false)
            {
                Console.WriteLine("Enter correct ROW where you want to go!15");
                move(player);
                return;
            }
            
            if (!(z1 == a1 + 1) && helpFig.color == Color.Black && helpFig.is_Queen == false)
            {
                Console.WriteLine("Enter correct ROW where you want to go!888");
                move(player);
                return;
            }

            //correct col
            if (!((z2 == a2 + 1 || z2 == a2 - 1)) && (helpFig.is_Queen == false))
            {
                Console.WriteLine("Enter correct COL where you want to go1!");
                move(player);
                return;
            }

            Figurine helpFig1 = PickFigurine(z1, z2, player_color);
            if(helpFig1 != null)
            {
                Console.WriteLine("You can't go on your figurine, go on another place or pick another one figurine");
                move(player);
                return;
            }
            //set queen
            if(z1 == 0 && player == 1)
            {
                helpFig.SetQueen(true);
            }

            if (z1 == 7 && player != 1)
            {
                helpFig.SetQueen(true);
            }

            //must jump

            helpFig.SetRow(z1);
            helpFig.SetCol(z2);
        }

        static void readNumber(out int a, string text)
        {
            
            Console.Write(text);
            string inputA = Console.ReadLine();
            try
            {
                a = int.Parse(inputA);
            }
            catch (Exception e)
            {
                readNumber(out a, text);
            }
        }

        private bool mustJumpPredWhite()
        {
            for(int i = 0; i < AllFiguresC; i++)
            {
                if(AllFigurine[i].color == Color.White && AllFigurine[i].is_Queen == false)
                {
                    if (((AllFigurine[i].row_coordinate - 1) > -1) && ((AllFigurine[i].col_coordinate - 1) > -1))
                    {
                        if (PickFigurine(AllFigurine[i].row_coordinate - 1, AllFigurine[i].col_coordinate - 1, Color.Black) != null)
                        {
                            if(((AllFigurine[i].row_coordinate - 2) > -1) && ((AllFigurine[i].col_coordinate - 2) > -1))
                            {
                                if((PickFigurine(AllFigurine[i].row_coordinate - 2, AllFigurine[i].col_coordinate - 2, Color.Black) == null) && (PickFigurine(AllFigurine[i].row_coordinate - 2, AllFigurine[i].col_coordinate - 2, Color.White) == null))
                                {
                                    return true;
                                }
                            }
                        }
                    }
                    if (((AllFigurine[i].row_coordinate - 1) > -1) && ((AllFigurine[i].col_coordinate + 1) < 8))
                    {
                        if (PickFigurine(AllFigurine[i].row_coordinate - 1, AllFigurine[i].col_coordinate + 1, Color.Black) != null)
                        {
                            if (((AllFigurine[i].row_coordinate - 2) > -1) && ((AllFigurine[i].col_coordinate + 2) < 8))
                            {
                                if ((PickFigurine(AllFigurine[i].row_coordinate - 2, AllFigurine[i].col_coordinate + 2, Color.Black) == null) && (PickFigurine(AllFigurine[i].row_coordinate - 2, AllFigurine[i].col_coordinate + 2, Color.White) == null))
                                {
                                    return true;
                                }
                            }
                        }
                    }
                }
                if(mustJumpPredWhiteQueen(i) == true)
                {
                    return true;
                }
            }
            return false;
        }
        private bool mustJumpPredWhiteQueen(int i)
        {
            if (AllFigurine[i].is_Queen == true && AllFigurine[i].color == Color.White)
            {
                for (int r = 1; ((AllFigurine[i].row_coordinate - r) > -1) && ((AllFigurine[i].col_coordinate - r) > -1); r++)
                {
                    if (PickFigurine(AllFigurine[i].row_coordinate - r, AllFigurine[i].col_coordinate - r, Color.Black) != null)
                    {
                        if (((AllFigurine[i].row_coordinate - (r + 1)) > -1) && ((AllFigurine[i].col_coordinate - (r + 1)) > -1))
                        {
                            if ((PickFigurine(AllFigurine[i].row_coordinate - (r + 1), AllFigurine[i].col_coordinate - (r + 1), Color.Black) == null) &&
                                (PickFigurine(AllFigurine[i].row_coordinate - (r + 1), AllFigurine[i].col_coordinate - (r + 1), Color.White) == null))
                            {
                                return true;
                            }
                        }
                    }
                }
            }
            if (AllFigurine[i].is_Queen == true && AllFigurine[i].color == Color.White)
            {
                for (int r = 1; ((AllFigurine[i].row_coordinate - r) > -1) && ((AllFigurine[i].col_coordinate + r) < 8); r++)
                {
                    if (PickFigurine(AllFigurine[i].row_coordinate - r, AllFigurine[i].col_coordinate + r, Color.Black) != null)
                    {
                        if (((AllFigurine[i].row_coordinate - (r + 1)) > -1) && ((AllFigurine[i].col_coordinate + (r + 1)) < 8))
                        {
                            if ((PickFigurine(AllFigurine[i].row_coordinate - (r + 1), AllFigurine[i].col_coordinate + (r + 1), Color.Black) == null) &&
                                (PickFigurine(AllFigurine[i].row_coordinate - (r + 1), AllFigurine[i].col_coordinate + (r + 1), Color.White) == null))
                            {
                                return true;
                            }
                        }
                    }
                }
            }


            if (AllFigurine[i].is_Queen == true && AllFigurine[i].color == Color.White)
            {
                for (int r = 1; ((AllFigurine[i].row_coordinate + r) < 8) && ((AllFigurine[i].col_coordinate + r) < 8); r++)
                {
                    if (PickFigurine(AllFigurine[i].row_coordinate + r, AllFigurine[i].col_coordinate + r, Color.Black) != null)
                    {
                        if (((AllFigurine[i].row_coordinate + (r + 1)) < 8) && ((AllFigurine[i].col_coordinate + (r + 1)) < 8))
                        {
                            if ((PickFigurine(AllFigurine[i].row_coordinate + (r + 1), AllFigurine[i].col_coordinate + (r + 1), Color.Black) == null) &&
                                (PickFigurine(AllFigurine[i].row_coordinate + (r + 1), AllFigurine[i].col_coordinate + (r + 1), Color.White) == null))
                            {
                                return true;
                            }
                        }
                    }
                }
            }
            if (AllFigurine[i].is_Queen == true && AllFigurine[i].color == Color.White)
            {
                for (int r = 1; ((AllFigurine[i].row_coordinate + r) < 8) && ((AllFigurine[i].col_coordinate - r) > -1); r++)
                {
                    if (PickFigurine(AllFigurine[i].row_coordinate + r, AllFigurine[i].col_coordinate - r, Color.Black) != null)
                    {
                        if (((AllFigurine[i].row_coordinate + (r + 1)) < 8) && ((AllFigurine[i].col_coordinate - (r + 1)) > -1))
                        {
                            if ((PickFigurine(AllFigurine[i].row_coordinate + (r + 1), AllFigurine[i].col_coordinate - (r + 1), Color.Black) == null) &&
                                (PickFigurine(AllFigurine[i].row_coordinate + (r + 1), AllFigurine[i].col_coordinate - (r + 1), Color.White) == null))
                            {
                                return true;
                            }
                        }
                    }
                }
            }
            return false;
        }
        private bool mustJumpPredBlackQueen(int i)
        {
            if (AllFigurine[i].is_Queen == true && AllFigurine[i].color == Color.Black)
            {
                for (int r = 1; ((AllFigurine[i].row_coordinate - r) > -1) && ((AllFigurine[i].col_coordinate - r) > -1); r++)
                {
                    if (PickFigurine(AllFigurine[i].row_coordinate - r, AllFigurine[i].col_coordinate - r, Color.White) != null)
                    {
                        if (((AllFigurine[i].row_coordinate - (r + 1)) > -1) && ((AllFigurine[i].col_coordinate - (r + 1)) > -1))
                        {
                            if ((PickFigurine(AllFigurine[i].row_coordinate - (r + 1), AllFigurine[i].col_coordinate - (r + 1), Color.Black) == null) &&
                                (PickFigurine(AllFigurine[i].row_coordinate - (r + 1), AllFigurine[i].col_coordinate - (r + 1), Color.White) == null))
                            {
                                return true;
                            }
                        }
                    }
                }
            }
            if (AllFigurine[i].is_Queen == true && AllFigurine[i].color == Color.Black)
            {
                for (int r = 1; ((AllFigurine[i].row_coordinate - r) > -1) && ((AllFigurine[i].col_coordinate + r) < 8); r++)
                {
                    if (PickFigurine(AllFigurine[i].row_coordinate - r, AllFigurine[i].col_coordinate + r, Color.White) != null)
                    {
                        if (((AllFigurine[i].row_coordinate - (r + 1)) > -1) && ((AllFigurine[i].col_coordinate + (r + 1)) < 8))
                        {
                            if ((PickFigurine(AllFigurine[i].row_coordinate - (r + 1), AllFigurine[i].col_coordinate + (r + 1), Color.Black) == null) &&
                                (PickFigurine(AllFigurine[i].row_coordinate - (r + 1), AllFigurine[i].col_coordinate + (r + 1), Color.White) == null))
                            {
                                return true;
                            }
                        }
                    }
                }
            }


            if (AllFigurine[i].is_Queen == true && AllFigurine[i].color == Color.Black)
            {
                for (int r = 1; ((AllFigurine[i].row_coordinate + r) < 8) && ((AllFigurine[i].col_coordinate + r) < 8); r++)
                {
                    if (PickFigurine(AllFigurine[i].row_coordinate + r, AllFigurine[i].col_coordinate + r, Color.White) != null)
                    {
                        if (((AllFigurine[i].row_coordinate + (r + 1)) < 8) && ((AllFigurine[i].col_coordinate + (r + 1)) < 8))
                        {
                            if ((PickFigurine(AllFigurine[i].row_coordinate + (r + 1), AllFigurine[i].col_coordinate + (r + 1), Color.Black) == null) &&
                                (PickFigurine(AllFigurine[i].row_coordinate + (r + 1), AllFigurine[i].col_coordinate + (r + 1), Color.White) == null))
                            {
                                return true;
                            }
                        }
                    }
                }
            }
            if (AllFigurine[i].is_Queen == true && AllFigurine[i].color == Color.Black)
            {
                for (int r = 1; ((AllFigurine[i].row_coordinate + r) < 8) && ((AllFigurine[i].col_coordinate - r) > -1); r++)
                {
                    if (PickFigurine(AllFigurine[i].row_coordinate + r, AllFigurine[i].col_coordinate - r, Color.White) != null)
                    {
                        if (((AllFigurine[i].row_coordinate + (r + 1)) < 8) && ((AllFigurine[i].col_coordinate - (r + 1)) > -1))
                        {
                            if ((PickFigurine(AllFigurine[i].row_coordinate + (r + 1), AllFigurine[i].col_coordinate - (r + 1), Color.Black) == null) &&
                                (PickFigurine(AllFigurine[i].row_coordinate + (r + 1), AllFigurine[i].col_coordinate - (r + 1), Color.White) == null))
                            {
                                return true;
                            }
                        }
                    }
                }
            }
            return false;
        }

        private bool mustJumpPredBlack()
        {
            for (int i = 0; i < AllFiguresC; i++)
            {
                if (AllFigurine[i].color == Color.Black)
                {
                    if (((AllFigurine[i].row_coordinate + 1) < 8) && ((AllFigurine[i].col_coordinate - 1) > -1))
                    {
                        if (PickFigurine(AllFigurine[i].row_coordinate + 1, AllFigurine[i].col_coordinate - 1, Color.White) != null)
                        {
                            if (((AllFigurine[i].row_coordinate + 2) < 8) && ((AllFigurine[i].col_coordinate - 2) > -1))
                            {
                                if ((PickFigurine(AllFigurine[i].row_coordinate + 2, AllFigurine[i].col_coordinate - 2, Color.Black) == null) && (PickFigurine(AllFigurine[i].row_coordinate + 2, AllFigurine[i].col_coordinate - 2, Color.White) == null))
                                {
                                    return true;
                                }
                            }
                        }
                    }
                    if (((AllFigurine[i].row_coordinate + 1) < 8) && ((AllFigurine[i].col_coordinate + 1) < 8))
                    {
                        if (PickFigurine(AllFigurine[i].row_coordinate + 1, AllFigurine[i].col_coordinate + 1, Color.White) != null)
                        {
                            if (((AllFigurine[i].row_coordinate + 2) < 8) && ((AllFigurine[i].col_coordinate + 2) < 8))
                            {
                                if ((PickFigurine(AllFigurine[i].row_coordinate + 2, AllFigurine[i].col_coordinate + 2, Color.Black) == null) && (PickFigurine(AllFigurine[i].row_coordinate + 2, AllFigurine[i].col_coordinate + 2, Color.White) == null))
                                {
                                    return true;
                                }
                            }
                        }
                    }
                }
                if (mustJumpPredBlackQueen(i) == true)
                {
                    return true;
                }
            }
            return false;
        }

        private void DeleteFigure(int row, int col)
        {
            for (int i = 0; i < AllFiguresC; i++)
            {
                if (AllFigurine[i].row_coordinate == row && AllFigurine[i].col_coordinate == col)
                {
                    for(int j = i; j < AllFiguresC - 1; j++)
                    {
                        AllFigurine[j] = AllFigurine[j + 1];
                    }
                    AllFiguresC--;
                    break;
                }
            }
        }

        public bool end()
        {
            int black = 0, white = 0;
            for(int i = 0; i < AllFiguresC; i++)
            {
                if (AllFigurine[i].color == Color.White)
                {
                    white++;
                } else
                {
                    black++;
                }
            }

            if(black == 0)
            {
                Console.WriteLine("Yellow won");
                return true;
            }
            if(white == 0)
            {
                Console.WriteLine("Grey won");
                return true;
            }
            return false;
        }

    }
}
