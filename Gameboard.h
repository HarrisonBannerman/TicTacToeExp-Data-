#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <iostream>
#include <string>

using namespace std;


class Gameboard
{
   static const char rowLetters[12];
   //12 is the Max # of Players

   public:
      Gameboard();
      Gameboard(int,int);
      void
         displayBoard(),
         displayDashes(),
         placePiece(int,char),
         clearBoard();
      bool
         validMove(int),
         checkWin(),
         checkDraw();
      int getColumns();
   protected:
   private:
      int
         moves,
         spaces,
         rows,
         columns;
      char squares[180];
      //180(12*15) is the max numbers of squares


};

#endif
