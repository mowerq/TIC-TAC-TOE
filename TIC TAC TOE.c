#include <stdio.h>
#include <stdlib.h>

void welcome(){
  printf("Welcome to my XOX game!!\n");
}

enum whoseTurn{computer, player};
enum situations{playing, win, lose, draw};

enum situations checkTheSituation(char map[], enum whoseTurn who) {
  for (int i = 0; i < 3; i++){
    if (map[i] == map[i+3] && map[i+3] == map[i+6] && map[i+3] != ' ') {
      printf("1\n");
      if (who == player)
        return lose;
      else
        return win;
    }

    if ( (map[3*(i+1)-3] == map[3*(i+1)-2]) && (map[3*(i+1)-2] == map[3*(i+1)-1]) && (map[3*(i+1)-2] != ' ')){
      printf("222\n");
      if (who == player)
        return lose;
      else
        return win;
    }
  }

  if ( ((map[0] == map[4] && map[4] == map[8]) || (map[2] == map[4] && map[4] == map[6])) && map[4] != ' '){
    printf("3\n");
    if (who == player)
      return lose;
    else
      return win;
  }

  for (int i = 0; i < 9; i++){
    if (map[i] == ' ')
      return playing;
  }

  return draw;

}

void drawMap(char map[]){
  printf(" -   -   -\n");
  for (int i=0; i<9; i++){
    printf(" %c%s", map[i], (i+1) % 3 ? " |" : " |\n -   -   - \n");
  }
  printf("\n");
}


int main(int argc, char const *argv[]) {
  int whoIsFirst;
  int chosenNumber;
  int keepPlaying = 1;
  enum situations currentStatus;
  welcome();
  int victory = 0, defeat = 0, draw = 0;
  do {
    char gameMap[] = "         ";
    currentStatus = playing;
    enum whoseTurn who;
    printf("Enter 0 or 1 to play with with X(0) or O(1) : ");
    scanf("%d", &whoIsFirst);
    if (!whoIsFirst)
      who = player;
    else
      who = computer;
    while(!currentStatus){
      drawMap(gameMap);
      if (who == player) {
        printf("Enter a number between 1-9 : ");
        scanf("%d", &chosenNumber);
        if(gameMap[chosenNumber-1] != 'X' && gameMap[chosenNumber-1] != 'O') {
          whoIsFirst ? (gameMap[chosenNumber-1] = 'O') : (gameMap[chosenNumber-1] = 'X');
          printf("You have put an '%c' into %d\n", gameMap[chosenNumber-1], chosenNumber);
        }
        else {
          printf("Please enter a number that haven't been entered!!!\n");
          continue;
        }
        who = computer;
      }
      else{
        int aNumber;
        do {
          aNumber = rand() % 9;
        } while(gameMap[aNumber] != ' ');

        if (whoIsFirst)
          gameMap[aNumber] = 'X';
        else
          gameMap[aNumber] = 'O';
        printf("Computer put an '%c' into %d\n", gameMap[aNumber], aNumber+1);
        who = player;
      }

      currentStatus = checkTheSituation(gameMap, who);
      printf("%d\n", currentStatus);
    }
    drawMap(gameMap);

    if (currentStatus == win){
      printf("You won the game!! Congratulations..\n");
      victory++;
    }
    else if (currentStatus == lose){
      printf("You lost the game!! :(\n");
      defeat++;
    }
    else{
      printf("DRAW !!! \n");
      draw++;
    }

    printf("Total Score : %d victory, %d defeat and %d draw..\n\n", victory, defeat, draw);

    printf("Do you want to play again ? 1 for yes 0 for no : ");
    scanf("%d", &keepPlaying);

  }while(keepPlaying);
  printf("\nTHANKS FOR PLAYING :)))\n");
  return 0;
}
