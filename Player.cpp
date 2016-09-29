#include "Player.h"

//Default Constuctor
Player::Player(){
   piece = '\0';
   wins = 0;
   loses = 0;
   player =0;
   draws = 0;
}

//Creates a new played with their name, piece, and player number
Player::Player(string playerName, char playerPiece, int playerNumber){
   fullName = playerName;
   piece = playerPiece;
   wins = 0;
   draws = 0;
   loses = 0;
   player = playerNumber;

   for(unsigned int i=0;i<playerName.length();i++){
   //Calculates the first name
      if(playerName[i] == ' '){
         playerName.erase(i);
         firstName = playerName;
         break;
         }
      }
}

//Returns the players full name
string Player::getFullName(){
   return fullName;
}

//Returns the player's first name
string Player::getFirstName(){
   return firstName;
}

//Returns the player's game piece
char Player::getPlayerPiece(){
   return piece;
}

//Adds a win to the player
void Player::addWin(){
   wins++;
}

//Adds a draw to the player
void Player::addDraw(){
   draws++;
}

//Adds a loss to the player
void Player::addLoss(){
   loses++;
}

//Returns the player's wins
int Player::getWins(){
   return wins;
}

//Returns the player's draws
int Player::getDraws(){
   return draws;
}

//Returns the player's loses
int Player::getLoses(){
   return loses;
}

