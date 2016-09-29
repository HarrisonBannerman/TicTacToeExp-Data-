//=============================================
//Roosevelt Bannerman
//Expanded Tic-Tac-Toe Program
//Full Error Checking
//=============================================
#include <iostream>
#include <string>
#include "Player.h"
#include "Gameboard.h"

using namespace std;

const int
   MAX_PLAYERS = 7,
   MIN_PLAYERS = 2;

const char PLAYER_PIECES[MAX_PLAYERS] = {'a','b','c','d','e','f','g'};

string
   obtainPlayerName(int),
   obtainBoardSize();
int
   obtainNumberPlayers(),
   calcRows(string),
   calcColumns(string),
   obtainPlayerMove(Player,Gameboard);


void
   displayScores(Player[],int),
   addWins(Player[],int,int),
   addDraws(Player[],int);

char obtainPlayAgain();

int main(){

   const int NUM_PLAYERS = obtainNumberPlayers();

   Player theGroup[NUM_PLAYERS];

   for(int i=0;i<NUM_PLAYERS;i++){
      string temp = obtainPlayerName(i);
      Player newPlayer(temp,PLAYER_PIECES[i],i);
      theGroup[i] = newPlayer;
   }

   string boardSize = obtainBoardSize();

   const int
      NUM_ROWS = calcRows(boardSize),
      NUM_COLUMNS = calcColumns(boardSize);

   Gameboard theBoard(NUM_ROWS,NUM_COLUMNS);

   int
      startingPlayer = 0,
      numberGames = 0;
   char playAgain = '\0';

   do{
      bool
         hasWinner = false,
         hasDraw = false;
      do{
         for(int i=startingPlayer;i<NUM_PLAYERS;i++){
            int temp = obtainPlayerMove(theGroup[i],theBoard);
            theBoard.placePiece(temp,theGroup[i].getPlayerPiece());
            hasWinner = theBoard.checkWin();
            hasDraw = theBoard.checkDraw();
            if(hasWinner == true){
               theBoard.displayBoard();
               addWins(theGroup,NUM_PLAYERS,i);
               startingPlayer = i + 1;
               numberGames++;
               cout << "\n\n\t" << theGroup[i].getFirstName() << " is the winner!";
               cout << "\n\n\tTotal game played = " << numberGames;
               break;
            }
            else if(hasDraw == true){
               addDraws(theGroup,NUM_PLAYERS);
               startingPlayer++;
               numberGames++;
               cout << "\n\n\tThe game has ended in a draw!";
               cout << "\n\n\tTotal game played = " << numberGames;
               break;
            }
         }
      } while(hasWinner == false && hasDraw == false);
      if(startingPlayer == NUM_PLAYERS){
         startingPlayer = 0;
      }
      displayScores(theGroup,NUM_PLAYERS);
      theBoard.clearBoard();
      playAgain = obtainPlayAgain();
   }while(playAgain == 'y');

   cout << "\n\tHave a nice day!" << endl << endl;
}


//=============================================
//Recieves the number of the the current player
//Obtains the full name of the current player
//Returns the name of the current player
//=============================================
string obtainPlayerName(int playerNum){

   string name;
   bool isValid = true;
   int spaceCounter = 0;

   do{
      cout << "\n\tPlease enter the name of player " << (playerNum+1) << ": ";
      getline(cin,name);

      for(unsigned int i=0;i<name.length();i++){
         //Makes sure the name is all letters
         char temp = name[i];
         if(temp > 'z' || (temp < 'A' && temp != ' ') || ('Z' < temp && temp < 'a')|| name.length() < 3 || name[0] == ' '){
            isValid = false;
            cout << "\n\tInvalid Input.";
            break;
         }
         else if(temp == ' '){
            spaceCounter++;
            if(spaceCounter > 1){
               cout << "\n\tInvalid Input.";
               isValid = false;
               spaceCounter = 0;
               break;
            }
         }
         else{
            isValid = true;
         }
      }
      if(isValid == true && spaceCounter != 1){
         cout << "\n\tInvalid Input.";
         isValid = false;
      }
   }while(isValid == false);


   const int BUFFER = 'a' - 'A';
   int startLast;

   for(unsigned int i =0;i<name.length();i++){
      if(name[i] == ' '){
         startLast = i + 1;
      }
      else if(name[i] < 'a'){
         name[i] = name[i] + BUFFER;
      }
   }

   name[0] = name[0] - BUFFER;
   name[startLast] = name[startLast] - BUFFER;

   return name;
}


//=============================================
//Obtains the number of players for the game
//Returns the number of players
//=============================================
int obtainNumberPlayers(){

   string players;
   int numberPlayers;
   bool isValid = true;

   do{
      cout << "\n\tPlease enter the number of players: ";
      getline(cin,players);

      numberPlayers = players[0] - '0';

      if(players.length() > 1 || numberPlayers < MIN_PLAYERS || numberPlayers > MAX_PLAYERS){
         cout << "\n\tInvalid Input.";
         isValid = false;
      }
      else{
         isValid = true;
      }
   }while(isValid == false);

   return numberPlayers;
}


//=============================================
//Obtains the size of the board for the game
//Returns the size of the board
//=============================================
string obtainBoardSize(){

   string boardSize;
   bool isValid = true;

   do{
      cout << "\n\tPlease enter the size of the board. Format(4 x 6): ";
      getline(cin,boardSize);

      for(unsigned int i =0;i<boardSize.length();i++){
         if((boardSize[i] != 'x' && boardSize[i] != ' ') || boardSize.length() < 5 || boardSize[0] == ' ' || boardSize[0] == 'x'){
            if(boardSize[i] < '0' || boardSize[i] > '9'){
               cout << "\n\tInvalid Input.";
               isValid = false;
               break;
            }
            else{
               isValid = true;
            }
         }
      }
      if(isValid == true){
         int rows = calcRows(boardSize);
         int columns = calcColumns(boardSize);

         if(rows > 12 || rows < 3){
            cout << "\n\tInvalid Input. Max(12 x 15). Min(3 x 3).";
            isValid = false;
         }
         else if(columns > 15 || columns < 3){
            cout << "\n\tInvalid Input. Max(12 x 15). Min(3 x 3).";
            isValid = false;
         }
      }
   } while(isValid == false);

   return boardSize;
}


//=============================================
//Recieves the string with the size of the board
//Calculates the number of rows for the board
//Returns the number of rows
//=============================================
int calcRows(string boardSize){

   for(unsigned int i=0;i<boardSize.length();i++){
      if(boardSize[i] == ' '){
         boardSize.erase(i);
      }
   }

   int rows = 0;

   if(boardSize.length()== 2){
      rows += (boardSize[0] - '0') * 10;
      rows += (boardSize[1] - '0');
   }
   else{
      rows += (boardSize[0] - '0');
   }
   return rows;
}


//=============================================
//Recieves the string with the size of the board
//Calculates the number of columns for the board
//Returns the number of columns
//=============================================
int calcColumns(string boardSize){

   int spaceCounter = 0;

   for(unsigned int i=0;i<boardSize.length();i++){
      if(boardSize[i] == ' ' && spaceCounter == 0){
         spaceCounter++;
      }
      else if(boardSize[i] == ' ' && spaceCounter == 1){
         boardSize.erase(0,i+1);
      }
   }

   int columns = 0;

   if(boardSize.length()== 2){
      columns += (boardSize[0] - '0') * 10;
      columns += (boardSize[1] - '0');
   }
   else{
      columns += (boardSize[0] - '0');
   }
   return columns;
}


//=============================================
//Recieves the current player
//Obtains the string of their move
//Returns the integer location for their move
//=============================================
int obtainPlayerMove(Player currentPlayer, Gameboard theBoard){

   string playerMove;
   bool isValid = true;
   int location = 0;
   theBoard.displayBoard();
   cout << endl;

   do{
      cout << "\n\t" << currentPlayer.getFirstName()<< " please choose a location for '" << currentPlayer.getPlayerPiece() << "': ";
      getline(cin,playerMove);

      if(playerMove.length() == 2){
         if(playerMove[0]>'Z' || playerMove[0] < '1' || (playerMove[0] > '9' && playerMove[0] < 'A') ||
            playerMove[1]>'Z' || playerMove[1] < '1' || (playerMove[1] > '9' && playerMove[1] < 'A')){
            isValid = false;
            cout << "\n\tInvalid Input.";
            continue;
         }
         int leftVal = playerMove[0] - '@' - 1;
         int rightVal = playerMove[1] - '0' - 1;
         location = (theBoard.getColumns() * leftVal) + rightVal;
         isValid = theBoard.validMove(location);
      }
      else if(playerMove.length() == 3){
         if(playerMove[0]>'Z' || playerMove[0] < '1' || (playerMove[0] > '9' && playerMove[0] < 'A') ||
            playerMove[1]>'Z' || playerMove[1] < '1' || (playerMove[1] > '9' && playerMove[1] < 'A') ||
            playerMove[2]>'Z' || playerMove[2] < '1' || (playerMove[2] > '9' && playerMove[2] < 'A')){
            isValid = false;
            cout << "\n\tInvalid Input.";
            continue;
         }
         int leftVal = playerMove[0] - '@' - 1;
         int rightVal = ((playerMove[1] - '0') * 10) + (playerMove[2] - '0') - 1;
         location = (theBoard.getColumns() * leftVal) + rightVal;
         isValid = theBoard.validMove(location);
      }
      else{
         isValid = false;
      }

      if(isValid == false){
         cout << "\n\tInvalid Input.";
      }


   } while(isValid == false);

   return location;
}

//=============================================
//Recieves the information for all players
//Displays the wins, loses, and draws for all players
//=============================================
void displayScores(Player theGroup[], int numberPlayers){

   cout << endl;

   int LONGEST_NAME_LENGTH = 0;

   for(int i=0;i<numberPlayers;i++){
      int temp = theGroup[i].getFullName().length();
      if(temp > LONGEST_NAME_LENGTH){
         LONGEST_NAME_LENGTH = temp;
      }
   }


   string spacing(LONGEST_NAME_LENGTH,' ');
   string dashes = "\n\t" + spacing + "  ------ ------ ------";
   cout << "\n\t"<< spacing <<"    WIN   LOSS   DRAW";

   for(int i=0;i<numberPlayers;i++){
      int temp = theGroup[i].getFullName().length();
      temp = LONGEST_NAME_LENGTH - temp + 1;
      string addSpacing(temp,' ');
      cout << dashes;
      cout << "\n\t" << theGroup[i].getFullName() << addSpacing << "|   " << theGroup[i].getWins() << "  |   " << theGroup[i].getLoses() << "  |   " << theGroup[i].getDraws() << "  |";
      cout << dashes;
   }

}

//=============================================
//Recieves the information for all players
//Adds a draw to every player
//=============================================
void addDraws(Player theGroup[],int numberPlayers){

   for(int i=0;i<numberPlayers;i++){
      theGroup[i].addDraw();
   }
}

//=============================================
//Recieves the information for all players
//Adds a win to the winner and loses to other players
//=============================================
void addWins(Player theGroup[],int numberPlayers, int winner){

   for(int i=0;i<numberPlayers;i++){
      if(i == winner){
         theGroup[i].addWin();
      }
      else{
         theGroup[i].addLoss();
      }
   }
}

//=============================================
//Obtains whether they want to play again
//Returns the char for yes or no
//=============================================
char obtainPlayAgain(){

   string playAgain;
   bool isValid = true;

   cout << endl;

   do{
      cout << "\n\tWould you like to play again('y'/'n'): ";
      getline(cin,playAgain);
      if(playAgain.length() > 1 || (playAgain[0] != 'y' && playAgain[0] != 'n')){
         cout << "\n\tInvalid Input.";
         isValid = false;
      }
      else{
         isValid = true;
      }
   } while(isValid == false);

   return playAgain[0];
}


