#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

using namespace std;

class Player
{
   public:
      Player();
      Player(string,char,int);
      string
         getFullName(),
         getFirstName();

      void
         addLoss(),
         addWin(),
         addDraw();
      int
         getWins(),
         getDraws(),
         getLoses();
      char getPlayerPiece();
   protected:
   private:
      int
         player,
         draws,
         wins,
         loses;
      string
         fullName,
         firstName;
      char piece;
};

#endif
