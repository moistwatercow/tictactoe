#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define ansi_red   "\x1b[1;33m"
#define ansi_reset "\x1b[1;0m"

void printgame(char strarr[], char user, int turn);
char* promptinput(char user);
int placemarker(char* oldboard, char user, char* pos);
int checkforwin(char* board, char user);

int main() {
  printf(
    "\nTerminal Tic Tac Toe\n"
    "Created by moistwatercow\n"
    "(github.com/moistwatercow)\n"
  );

  //default board with everything blank
  char arr[] = {
    ' ', ' ', ' ',
    ' ', ' ', ' ',
    ' ', ' ', ' ',
  };


  int i;
  //loop for the maximum amount of turns possible (9)
  for (i = 0; i < 9; i++){
    char user;         

    //alternate whos turn it is, starting with X
    if (i % 2 == 0) user = 'X';
    else user = 'O';

    printgame(arr, user, i + 1);
  
    //prompt for input
    while (1){
      //place marker
      int marker = placemarker(arr, user, promptinput(user));

      //take care of errors
      if      (marker == 1) printf("[?] -> Please try again (Position already taken)\n");
      else if (marker == 2) printf("[?] -> Please try again (Input malformed)\n");

      //if marker was successfully placed
      else break; 
    }

    //if player won
    if (checkforwin(arr, user) == 1){
      printf("[!] -> Player '%c' won\n", user);
      break;
    }
  }

  printf("[!] -> Cats game; No one won\n");
  return 0;
}

//takes a char array[9] and translates it to a more human readable format
void printgame(char strarr[9], char user, int turn) {
  char* strboard = 
                   "\n%c's Turn [%i/9]\n"
                   ansi_red "    [A] [B] [C]\n" ansi_reset    
                   ansi_red "[1]" ansi_reset " [%c] [%c] [%c]\n"
                   ansi_red "[2]" ansi_reset " [%c] [%c] [%c]\n"
                   ansi_red "[3]" ansi_reset " [%c] [%c] [%c]\n\n";


  printf(strboard, user, turn, strarr[0], strarr[1], strarr[2], strarr[3], strarr[4], strarr[5], strarr[6], strarr[7], strarr[8]);
}

//prompts the user for the coordinates of their move 
//format of "NL" with N being the number and L being the letter
//ex: 1a
char* promptinput(char user){
  static char pos[2];

  printf("[%c] -> ", user);
  scanf("%s", &pos); 

  return pos;
}

//updates the board by placing a marker on the specified spot
int placemarker(char* oldboard, char user, char pos[2]){
  int boardpos;
  //TODO: concenate this massive if statement to something cooler
  if      (strcmp(pos, "1a") == 0) boardpos = 0;
  else if (strcmp(pos, "1b") == 0) boardpos = 1;
  else if (strcmp(pos, "1c") == 0) boardpos = 2;

  else if (strcmp(pos, "2a") == 0) boardpos = 3;
  else if (strcmp(pos, "2b") == 0) boardpos = 4;
  else if (strcmp(pos, "2c") == 0) boardpos = 5;

  else if (strcmp(pos, "3a") == 0) boardpos = 6;
  else if (strcmp(pos, "3b") == 0) boardpos = 7;
  else if (strcmp(pos, "3c") == 0) boardpos = 8;

  else return 2; //error: malformed input
  
  //check if a marker has already been placed in the provided boardpos
  if (oldboard[boardpos] == ' '){  
    oldboard[boardpos] = tolower(user);
    return 0; //success: success
  }
  return 1; //error: the position is already taken 
}

int checkforwin(char* board, char user){
  int bpos[9];
  int i;

  for (i = 0; i < 9; i++) {    
    bpos[i] = (board[i] == tolower(user));
  }

  //set the possible combinations
  int combinations[8][3] = {
    //horizontal 
    {0, 1, 2}, //top
    {3, 4, 5}, //middle 
    {6, 7, 8}, //bottom
    
    //vertical
    {0, 3, 6}, //left
    {1, 4, 7}, //middle
    {2, 5, 8}, //right
    
    //diagonal
    {0, 4, 8}, //top left to bottom right
    {6, 4, 2}, //bottom left to top right
  };

  //check for matching combinations
  for (i = 0; i < 8; i++){
    #define COM combinations[i] 
    if (bpos[COM[0]] + bpos[COM[1]] + bpos[COM[2]] == 3) return 1; //if a combination matches
  } 

  return 0;
}



