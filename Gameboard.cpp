#include "Gameboard.h"


const char Gameboard::rowLetters[12] = {'A','B','C','D','E','F','G','H','I','J','K','L'};

//Default Constuctor
Gameboard::Gameboard(){
   rows = 0;
   columns = 0;
   spaces = 0;
   moves = 0;

   for(int i=0;i<180;i++){
      squares[i] = ' ';
   }
}

//Creates empty gameboard based on rows and columns
Gameboard::Gameboard(int numRows, int numColumns){
   moves = 0;
   rows = numRows;
   columns = numColumns;
   spaces = rows * columns;

   for(int i=0;i<spaces;i++){
      squares[i] = ' ';
   }

   for(int i=spaces;i<180;i++){
      squares[i] = '\0';
   }
}

//Displays the current gameboard
void Gameboard::displayBoard(){

   cout << "\n\t   ";
   for(int i=0;i<columns;i++){
      cout << " " << (i+1) << "  ";
   }

   displayDashes();

   for(int i=0;i<rows;i++){
      cout << "\n\t" << rowLetters[i] << " ";
      for(int ii=0;ii<columns;ii++){
         int temp = (i * columns) + ii;
         cout << "| " << squares[temp] << " ";
      }
      cout << "| " << rowLetters[i];
      displayDashes();
   }

   cout << "\n\t   ";
   for(int i=0;i<columns;i++){
      cout << " " << (i+1) << "  ";
   }

}

//Displays dashes depending on the number of columns
void Gameboard::displayDashes(){

   cout << "\n\t   ";
   for(int i=0;i<columns;i++){
      cout << "--- ";
   }
}

//Checks if a move is valid
bool Gameboard::validMove(int location){

   if(squares[location] != ' '){
      return false;
   }
   return true;
}

//Places a player's piece at their move location
void Gameboard::placePiece(int location, char piece){
   squares[location] = piece;
}

//Returns the number of columns
int Gameboard::getColumns(){
   return columns;
}

//Checks all win conditions
bool Gameboard::checkWin(){

   const int BUFFER = 'a' - 'A';

   for(int i=0;i<spaces;i++){ //Column checking
      char temp = squares[i];
      char tempTwo = squares[i+columns];
      char tempThree = squares[i+columns+columns];
      if((temp == tempTwo) && (temp == tempThree) && (temp != ' ') && (temp != '\0')){
         squares[i] = squares[i] - BUFFER;
         squares[i + columns] = squares[i + columns] - BUFFER;
         squares[i+columns+columns] = squares[i+columns+columns] - BUFFER;
         return true;
      }
   }

   for(int i=0;i<spaces;i+=columns){ //Row checking
      for(int ii=0;ii<(columns-2);ii++){
         char temp = squares[i+ii];
         char tempTwo = squares[i+ii+1];
         char tempThree = squares[i+ii+2];

         if((temp == tempTwo) && (temp == tempThree) && (temp != ' ') && (temp != '\0')){
            squares[i+ii] = squares[i+ii] - BUFFER;
            squares[i+ii+1] = squares[i+ii+1] - BUFFER;
            squares[i+ii+2] = squares[i+ii+2] - BUFFER;
            return true;
         }
     }
   }

   for(int i=0;i<spaces;i+=columns){ //Left diagonal checking
      for(int ii=0;ii<(columns-2);ii++){
         char temp = squares[i+ii];
         char tempTwo = squares[i+ii+columns+1];
         char tempThree = squares[i+ii+columns+columns+2];

         if((temp == tempTwo) && (temp == tempThree) && (temp != ' ') && (temp != '\0')){
            squares[i+ii] = squares[i+ii] - BUFFER;
            squares[i+ii+columns+1] = squares[i+ii+columns+1] - BUFFER;
            squares[i+ii+columns+columns+2] = squares[i+ii+columns+columns+2] - BUFFER;
            return true;
         }
      }
   }

   for(int i=0;i<spaces;i+=columns){ //Right diagonal checking
      for(int ii=2;ii<columns;ii++){
         char temp = squares[i+ii];
         char tempTwo = squares[i+ii+columns-1];
         char tempThree = squares[i+ii+columns+columns-2];

         if((temp == tempTwo) && (temp == tempThree) && (temp != ' ') && (temp != '\0')){
            squares[i+ii] = squares[i+ii] - BUFFER;
            squares[i+ii+columns-1] = squares[i+ii+columns-1] - BUFFER;
            squares[i+ii+columns+columns-2] = squares[i+ii+columns+columns-2] - BUFFER;
            return true;
         }
      }
   }
   return false;
}

//Checks draw condition
bool Gameboard::checkDraw(){
   moves++;

   if(moves == spaces){
      return true;
   }
   return false;

}

//Clears the gameboard for a new game
void Gameboard::clearBoard(){

   moves = 0;

   for(int i=0;i<spaces;i++){
      squares[i] = ' ';
   }

   for(int i=spaces;i<180;i++){
      squares[i] = '\0';
   }

}
