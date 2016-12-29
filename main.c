#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#define MINUTE 60
#define FALSE 0



    /********************************************************************
    ****                         FUNCTIONS                          ****
   *******************************************************************/

    void saveGame();
    void loadGame();
    void printArrayToFile();
    void loserCase(int openRow, int openColumn);
    void openCell(int openRow, int openColumn);
    void openAdjacentCells(int openRow, int openColumn);
    void srand(unsigned int seed);
    void loadPlayers();
    void savePlayers();
    int rand(void);


     /*******************************************************************
    ******                  GLOBAL VARIABLES                      ******
   *******************************************************************/


    char gridArray[50][50], finalGrid[50][50];
    int winningCount = 0, playersNum = 0, numberOfMoves = 0, numberOfFlags = 0, numberOfQues = 0;
    clock_t beginningTime;
    long savedTime = 0;
    int rowsNum, columsNum;
    struct player
    {
        char playerName[20];
        int playerScore;
        int playerRank;

    } players[20];



int main()
{

    short int i,j;     //incrementation variables
    int numberOfMines, adjacentMinesCounter = 0, adjacentMinesCounter2 = 0;
    int openRow, openColumn;
    char cellValue, currentPlayerName[20];
    char gameMenu;
    short int flag = 1, isSavedFinished = 0;

    printf("In the given action label:\n\n1. To start the game press S.\n2. To load a previous game press L.\n\
3. To access the players scores menu press P.\n4. Press E to close the game\n\n");

while(gameMenu != 's' && gameMenu != 'S'){

    printf("Action: ");
    scanf(" %c", &gameMenu);

    switch(gameMenu){

    case 76: case 108:              // case of loading the game

        loadGame();
        if(savedTime == 0) {
            printf("\nThere isn't any previous saved game.\n\n");
            break;
        }
        isSavedFinished = 1;
        goto playingTheGame;

    case 80: case 112:

        loadPlayers();
        printf("\n");
        for(i = 0; i < playersNum; ++i) {
            printf("%s | %d | %d\n", players[i].playerName, players[i].playerScore, players[i].playerRank);
        }
        printf("\n");

    break;

    case 69: case 101:      //cases for exiting the game

        exit(0);


    case 83: case 115: //To start the game case for s and S

    break;

    default:

        printf("You have entered an invalid character!\n");

    break;

}

}

    system("cls");

    clock_t secondsPassed;
    int minutesPassed;

   printf("Game Instructions:\n1. You enter the size of the grid.\n2. There is an ACTION label.\nUse the following symbols in the action label\
 for every move you want to make:\n\
\t 'F' for flags(placing of removing).\n\t '?' for a question mark(placing of removing).\n\
\t 'O' to open the cell.\n\t 'S' to save the game.\n\t 'L' to load the game\n\
3. There is a CELL label.\n4. The rows and columns of the game range from 2 to 50.\n\n");


    printf("Enter the number of rows and columns of the game (rows  columns) format: "); // may cause a problem
    scanf("%d  %d", &rowsNum, &columsNum);
    printf("\n");

    if(!(rowsNum <= 50 && columsNum > 0 && columsNum <= 50 && rowsNum > 0)){

        printf("You have entered invalid values for the rows and columns!\n\n");
        exit(0);

    }




    numberOfMines = 1 + (rowsNum * columsNum)/10; // Formula calculates number of mines


        /****         initialization of the grid array (debugging and solved array)       *****/
       /****            initialization of the the game array (displayed array)           *****/

     gridArray[rowsNum][columsNum];
     finalGrid[rowsNum][columsNum];

     for(i  = 0; i < rowsNum; i++) {

       for(j = 0; j < columsNum; j++) {

        gridArray[i][j] = 'X';
        finalGrid[i][j] = 'X';

       }
    }


        /***********************************************************************************

       *** Initializing the mines and evaluating the cells values in the solved array ***

     ********************************************************************************/


        srand(time(NULL));

        for(i  = 0; i < numberOfMines; i++){

            gridArray[rand() % rowsNum][rand() % columsNum] = '*';
        }

        for(i  = 0; i < rowsNum; i++) {
           for(j = 0; j < columsNum; j++) {

                if(gridArray[i][j] != '*'){
            if(i - 1 >= 0 && j - 1 >= 0 && gridArray[i - 1][j - 1] == '*'){
                    adjacentMinesCounter++;
                                                                          }

            if(i - 1 >= 0 && j >= 0 && gridArray[i - 1][j] == '*'){
                    adjacentMinesCounter++;
                                                                  }

            if(i - 1 >= 0 && j + 1 >= 0 && gridArray[i - 1][j + 1] == '*'){
                    adjacentMinesCounter++;
                                                                          }

            if(i >= 0 && j - 1 >= 0 && gridArray[i][j - 1] == '*'){
                    adjacentMinesCounter++;
                                                                  }

            if(i >= 0 && j + 1 >= 0 && gridArray[i][j + 1] == '*'){
                    adjacentMinesCounter++;
                                                                  }

            if(i + 1 >= 0 && j - 1 >= 0 && gridArray[i + 1][j - 1] == '*'){
                    adjacentMinesCounter++;
                                                                          }

            if(i + 1 >= 0 && j >= 0 && gridArray[i + 1][j] == '*'){
                    adjacentMinesCounter++;
                                                                  }

            if(i + 1 >= 0 && j + 1 >= 0 && gridArray[i + 1][j + 1] == '*'){
                    adjacentMinesCounter++;
                                                                          }


                switch(adjacentMinesCounter){

                    case 0: gridArray[i][j] = ' ';  break;
                    case 1: gridArray[i][j] = '1';  break;
                    case 2: gridArray[i][j] = '2';  break;
                    case 3: gridArray[i][j] = '3';  break;
                    case 4: gridArray[i][j] = '4';  break;
                    case 5: gridArray[i][j] = '5';  break;
                    case 6: gridArray[i][j] = '6';  break;
                    case 7: gridArray[i][j] = '7';  break;
                    case 8: gridArray[i][j] = '8';  break;

                                            }}

                adjacentMinesCounter  = 0;

           }


           }

           // Print the current opened grid to a file.

           printArrayToFile();



                /***********************************************************************************
                ***********************************************************************************
               **************  GAME LOOP CONTINUES UNTIL THE PLAYER LOSES OR WINS ***************
              **********************************************************************************
             **********************************************************************************/



    while(winningCount < rowsNum * columsNum - numberOfMines){

        system("cls");

        if(FALSE){

            invalidValue:
            system("cls");
            printf("Error! You have entered an invalid value!\n\n");

        }

        printf("    ");

        for(j = 1; j <= columsNum; j++) printf("%-2d ", j);

        printf("\n\n");

        for(i  = 0; i < rowsNum; i++) {

            printf("%-4d", i + 1);

            for(j = 0; j < columsNum; j++) {

                    printf("%-2c ",gridArray[i][j]);

            }

            printf("\n");

        }

        printf("\n\n");

        printf("    ");

        for(j = 1; j <= columsNum; j++) printf("%-2d ", j);

        printf("\n\n");

        for(i  = 0; i < rowsNum; i++) {

                printf("%-4d", i + 1);

            for(j = 0; j < columsNum; j++) {

                    printf("%-2c ",finalGrid[i][j]);

            }

                printf("\n");
        }

        printf("\n\n");

        if(flag){

                printf("\ntime : 0:0\nnumber of moves : 0\nnumber of Flags : 0\nnumber of question marks : 0\n\n");

        }


        else{
                secondsPassed = clock()/CLOCKS_PER_SEC - beginningTime + savedTime;
                minutesPassed = secondsPassed/MINUTE;
                secondsPassed -= minutesPassed*MINUTE;

                printf("\ntime : %d:%ld\nnumber of moves : %d\nnumber of Flags : %d\nnumber of question marks : %d\n\n", minutesPassed, secondsPassed, numberOfMoves, numberOfFlags, numberOfQues);

        }


        printf("ACTION: ");
        scanf(" %c", &cellValue);
        numberOfMoves++;

        if(flag){

            beginningTime = clock()/CLOCKS_PER_SEC;

        }

        flag = FALSE;



        printf("CELL: ");
        scanf(" %d  %d", &openRow , &openColumn);
        printf("\n\n");

        if(openRow > rowsNum || openRow < 1 || openColumn > columsNum || openColumn < 1){

            numberOfMoves--;
            goto invalidValue;

        }



   switch(cellValue){

        case 83: case 115:               // case of saving the game

            saveGame();

        break;

        case 76: case 108:              // case of loading the game

            playingTheGame:
            beginningTime = clock()/CLOCKS_PER_SEC;

        break;




        case 70: case 102:                          // case for Flags cases for f and F

            if(finalGrid[openRow - 1][openColumn - 1] == 'F') {

                finalGrid[openRow - 1][openColumn - 1] ='X';
                numberOfFlags--;

            }

            else if (finalGrid[openRow - 1][openColumn - 1] == 'X') {

                finalGrid[openRow - 1][openColumn - 1] = 'F';
                numberOfFlags++;

            }

        break;

        case 63:                                // case for question Marks

            if(finalGrid[openRow - 1][openColumn - 1] == '?'){

                finalGrid[openRow - 1][openColumn - 1] ='X';
                numberOfQues--;

            }

            else if (finalGrid[openRow - 1][openColumn - 1] == 'X') {

                finalGrid[openRow - 1][openColumn - 1] = '?';
                numberOfQues++;

            }

        break;

        case 111: case 79:              // case for for opening a cell (111 and 79) are ASCII codes for o and O respectively


                if(gridArray[openRow - 1][openColumn - 1] == '*' && winningCount == 0) goto firstSafeOpenning;

                continuePlaying:

                switch(gridArray[openRow - 1][openColumn - 1]){

                    case 42:                                    // ASCII CODE 42 == '*' character

                        finalGrid[openRow -1][openColumn - 1] = gridArray[openRow - 1][openColumn - 1];
                        loserCase(openRow, openColumn);

                    case 32:                                   // 32 == space character ' ' for empty cells

                        finalGrid[openRow -1][openColumn - 1] = gridArray[openRow - 1][openColumn - 1];
                        openCell(openRow - 1, openColumn - 1);

                    break;


                    default:

                        if(finalGrid[openRow - 1][openColumn - 1] >= '1' && finalGrid[openRow - 1][openColumn - 1] <= '8')
                                openAdjacentCells(openRow - 1, openColumn - 1);

                        finalGrid[openRow -1][openColumn - 1] = gridArray[openRow - 1][openColumn - 1];

                    break;

                }

        break;


        default:

            numberOfMoves--;
            goto invalidValue;

   }

        winningCount = 0;
        numberOfMines = 1 + (rowsNum * columsNum)/10;

        for(i = 0; i < rowsNum; i++){

            for(j = 0; j < columsNum; j++){

                    // 48 through 57 are characters 0 to 9 in ASCII code

                if((finalGrid[i][j] < 57 && finalGrid[i][j] > 48) || finalGrid[i][j] == ' ') winningCount++;

            }

        }

}








                          /***********//************************//***********/
                         /***********//*** WE HAVE A WINNER ***//***********/
                        /***********//************************//***********/

        secondsPassed = clock()/CLOCKS_PER_SEC - beginningTime + savedTime;

        printf("\n\n");

        printf("    ");

        for(j = 1; j <= columsNum; j++) printf("%-2d ", j);

        printf("\n\n");

        for(i  = 0; i < rowsNum; i++) {

                printf("%-4d", i + 1);

            for(j = 0; j < columsNum; j++) {

                    printf("%-2c ",finalGrid[i][j]);

            }

                printf("\n");
        }

        printf("\n\n");

        // Loading the players in a array of structures to add the current player score.

        loadPlayers();

        // Taking the player's name.

        printf("Enter your name : ");
        i = 0;
        while(i == 0) {
            int k = 0;
            j = 0;
            currentPlayerName[0] = '\n';
            scanf("%c", &currentPlayerName[j]);
            while(currentPlayerName[j] != '\n') {
                scanf("%c", &currentPlayerName[j+1]);
                ++j;
                if (currentPlayerName[j] == ':') {
                    k = 1;
                    printf("Enter your name again without this character (:) : ");
                }
                i = 1;
                if(k == 1) i = 0;
            }
        }
        currentPlayerName[j] = '\0';

        // Checking if the player exists in the leader board to add his score,
        // and if not to add his name and his score.

        int currentPlayerIndex = -1, currentPlayerScore = (pow(rowsNum, 4)*pow(columsNum, 4))/(secondsPassed*numberOfMoves), temp = 1;

        for(i = 0; i < playersNum; ++i) {

            j = 0;
            temp = 1;

            while(players[i].playerName[j] != '\0') {

                if (currentPlayerName[j] != players[i].playerName[j]) {
                    temp = 0;
                    break;
                }

                ++j;

            }

            if (temp == 1) {

                currentPlayerIndex = i;
                break;

            }

            else {

                currentPlayerIndex = -1;

            }
        }

        if (currentPlayerIndex == -1) {

            ++playersNum;
            currentPlayerIndex = playersNum-1;
            i = 0;

            while (currentPlayerName[i] != '\0') {

                players[currentPlayerIndex].playerName[i] = currentPlayerName[i];
                ++i;

            }

            players[currentPlayerIndex].playerScore = currentPlayerScore;
            players[currentPlayerIndex].playerRank = playersNum;
        }

        else {

            players[currentPlayerIndex].playerScore += currentPlayerScore;

        }

        // Saving the players and loading them to update their ranks and their order in the array of structures.
        // Then printing the structure.

        savePlayers();
        loadPlayers();

        printf("\n");
        for(i = 0; i < playersNum; ++i) {
            printf("%s | %d | %d\n", players[i].playerName, players[i].playerScore, players[i].playerRank);
        }

        if (isSavedFinished == 1) {         // Checks if the saved game is played to delete it.
            FILE *emptySavedFile;
            emptySavedFile = fopen("tmp/savedGame.txt", "w+");
            fclose(emptySavedFile);
        }


                      /***********           SAFE OPENING         ************/
                     /***********           SAFE OPENING         ************/
                    /***********           SAFE OPENING         ************/

    if(FALSE){

        firstSafeOpenning:

            for(i = openRow - 2; i <= openRow; i++){

                for(j = openColumn - 2; j <= openColumn; j++){

                    if(i < 0 || i >= rowsNum || j < 0 || j >= columsNum) continue;

                    if(gridArray[i][j] != '*'){


                        gridArray[openRow - 1][openColumn - 1] = gridArray[i][j];
                        gridArray[i][j] = '*';



                            goto rearrangingCells;


                    }
                }
            }



         rearrangingCells:

                for(i  = 0; i < rowsNum; i++) {

                   for(j = 0; j < columsNum; j++) {

                    if(gridArray[i][j] != '*'){

                        if(i - 1 >= 0 && j - 1 >= 0 && gridArray[i - 1][j - 1] == '*'){
                                adjacentMinesCounter2++;
                                                                                      }

                        if(i - 1 >= 0 && j >= 0 && gridArray[i - 1][j] == '*'){
                                adjacentMinesCounter2++;
                                                                              }

                        if(i - 1 >= 0 && j + 1 >= 0 && gridArray[i - 1][j + 1] == '*'){
                                adjacentMinesCounter2++;
                                                                                      }

                        if(i >= 0 && j - 1 >= 0 && gridArray[i][j - 1] == '*'){
                                adjacentMinesCounter2++;
                                                                              }

                        if(i >= 0 && j + 1 >= 0 && gridArray[i][j + 1] == '*'){
                                adjacentMinesCounter2++;
                                                                              }

                        if(i + 1 >= 0 && j - 1 >= 0 && gridArray[i + 1][j - 1] == '*'){
                                adjacentMinesCounter2++;
                                                                                      }

                        if(i + 1 >= 0 && j >= 0 && gridArray[i + 1][j] == '*'){
                                adjacentMinesCounter2++;
                                                                              }

                        if(i + 1 >= 0 && j + 1 >= 0 && gridArray[i + 1][j + 1] == '*'){
                                adjacentMinesCounter2++;
                                                                                  }


                        switch(adjacentMinesCounter2){

                            case 0: gridArray[i][j] = ' ';  break;
                            case 1: gridArray[i][j] = '1';  break;
                            case 2: gridArray[i][j] = '2';  break;
                            case 3: gridArray[i][j] = '3';  break;
                            case 4: gridArray[i][j] = '4';  break;
                            case 5: gridArray[i][j] = '5';  break;
                            case 6: gridArray[i][j] = '6';  break;
                            case 7: gridArray[i][j] = '7';  break;
                            case 8: gridArray[i][j] = '8';  break;

                                                    }}

                        adjacentMinesCounter2  = 0;

                   }


                   }


                   goto continuePlaying;

                }



        return 0;


   }


                /*****************************************************************
                ****    DFS function open the boundary around an empty cell  ****
               ****************************************************************/





void openCell(int openRow, int openColumn){

    short int k, j;


    for(k = openRow-1; k <= openRow+1; ++k){

        for(j = openColumn-1; j <= openColumn+1; ++j) {

        // ASCII CODE: 48 == 0 , 57 == 9

            if (k == -1 || k == rowsNum || j == -1 || j == columsNum) continue;

            if (gridArray[k][j] > 48 && gridArray[k][j] < 57 && finalGrid[k][j] == 'X' && finalGrid[k][j] != 'd') {

                finalGrid[k][j] = gridArray[k][j];

            }

            else if (gridArray[k][j] == 32 && finalGrid[k][j] != 32) {

                finalGrid[k][j] = 'd';
                gridArray[k][j] = 'd';
                openCell(k, j);

                break;
            }

        }

    }

// ASCII CODE 32 == space character ' '

    finalGrid[openRow][openColumn] = 32;
    gridArray[openRow][openColumn] = 32;

    for(k = openRow-1; k <= openRow+1; ++k){

        for(j= openColumn-1; j <= openColumn+1; ++j) {

            if (k == -1 || k == rowsNum || j == -1 || j == columsNum) continue;

            if (finalGrid[k][j] == 'd' ) openCell(k, j);

        }

    }


}




            /*****************************************************************************************************
            ****  This function open the adjacent cells if of a valued cell(valued from 1 to 8  function)    ****
           ****************************************************************************************************/



    void openAdjacentCells(int openRow, int openColumn){

        short int i, j;

        for(i = openRow - 1; i <= openRow + 1; i++){

                for(j = openColumn - 1; j <= openColumn + 1; j++){

                        if((i == openRow && j == openColumn) || finalGrid[i][j] == 'F') continue;

                        if(i < 0 || i >= rowsNum || j < 0 || j >= columsNum) continue;

                        if(gridArray[i][j] == ' '){
                                openCell(i, j);
                        }

                        if(gridArray[i][j] == '*'){
                                loserCase(i + 1, j + 1);
                        }

                        else finalGrid[i][j] = gridArray[i][j];


                }
        }

}


    /**********            LOSING CASE               ************
    *************************************************************

    ********************** LOSING CASE **************************

    *************************************************************
    ***********            LOSING CASE               ***********/

    void loserCase(int openRow, int openColumn){

    printf("\t\tYou have lost! Good Luck Next Time!\n\n");

    short int i, j;

    gridArray[openRow - 1][openColumn - 1] = '!';

    for(i = openRow - 2; i <= openRow; i ++){

        for(j = openColumn - 2; j <= openColumn; j++){

            if(gridArray[i][j] == '*') gridArray[i][j] = 'M';

            if(finalGrid[i][j] == 'F' && gridArray[i][j] != '*') gridArray[i][j] = '-';

        }

    }

    for(i = 0; (i < openRow - 2 || i > openRow) && i < rowsNum; i++){

        for(j = 0; (j < openColumn - 2 || j > openColumn) && j < columsNum; j++){

            if(finalGrid[i][j] == 'F' && gridArray[i][j] != '*') finalGrid[i][j] = '-';

            else finalGrid[i][j] = gridArray[i][j];

        }
    }



    printf("    ");


    for(j = 1; j <= columsNum; j++) printf("%-2d ", j);

    printf("\n\n");

    for(i  = 0; i < rowsNum; i++) {

            printf("%-4d", i + 1);

        for(j = 0; j < columsNum; j++) {

            printf("%-2c ",gridArray[i][j]);

        }

            printf("\n");

    }


    exit(0);

    }



            /********************************************************************
            ****                      saving the game                       ****
           *******************************************************************/



    void saveGame()
{
        // Creating FILE and opening it for writing.

        FILE *savedGame;
        savedGame = fopen("tmp/savedGame.txt", "w+");

        int i, j;

        // saving to the file the time, the number of moves, the number of flags, the number of question marks,
        // the number of rows, the number of columns, the debugging array and the changed array.

        fprintf(savedGame, "%ldT%dM%dF%d?%dR%dC", clock()/CLOCKS_PER_SEC - beginningTime, numberOfMoves, numberOfFlags, numberOfQues, rowsNum, columsNum);
        for(i = 0; i < rowsNum; ++i) {

            for(j = 0; j < columsNum; ++j) {

                fprintf(savedGame, "%c", gridArray[i][j]);

            }
        }

        for(i = 0; i < rowsNum; ++i) {

            for(j = 0; j < columsNum; ++j) {

                fprintf(savedGame, "%c", finalGrid[i][j]);

            }
        }

        //close the FILE.
        fclose(savedGame);
}



            /********************************************************************
            ****                      loading the game                      ****
           *******************************************************************/




void loadGame(){

    // Creating FILE and opening it for reading.

    FILE *loadSaved;
    loadSaved = fopen("tmp/savedGame.txt", "a+");

    int i, j;

    // Loading the saved characters in the FILE, and saving them to the variables.
    // if the FILE is empty, the compiler skip the loop and close the FILE.

    char tmp = 0;
    tmp = fgetc(loadSaved) - 48;
    if(tmp != -49) {

        rowsNum = 0;
        columsNum = 0;
        numberOfMoves = 0;
        numberOfQues = 0;
        numberOfFlags = 0;
        savedTime = 0;

        while(tmp != 36) {

            savedTime *= 10;
            savedTime += tmp;
            tmp = fgetc(loadSaved) - 48;

        }

        tmp = 0;

        while(tmp != 29) {

            numberOfMoves *= 10;
            numberOfMoves += tmp;
            tmp = fgetc(loadSaved) - 48;

        }

        tmp = 0;

        while(tmp != 22) {

            numberOfFlags *= 10;
            numberOfFlags += tmp;
            tmp = fgetc(loadSaved) - 48;

        }

        tmp = 0;

        while(tmp != 15) {

            numberOfQues *= 10;
            numberOfQues += tmp;
            tmp = fgetc(loadSaved) - 48;

        }

        tmp = 0;

        while(tmp != 34) {

            rowsNum *= 10;
            rowsNum += tmp;
            tmp = fgetc(loadSaved) - 48;

        }

        tmp = 0;

        while(tmp != 19) {

            columsNum *= 10;
            columsNum += tmp;
            tmp = fgetc(loadSaved) - 48;

        }

        for(i = 0; i < rowsNum; ++i) {

            for(j = 0; j < columsNum; ++j) {

                gridArray[i][j] = fgetc(loadSaved);

            }
        }
        for(i = 0; i < rowsNum; ++i) {

            for(j = 0; j < columsNum; ++j) {

                finalGrid[i][j] = fgetc(loadSaved);

            }
        }
    }

    // Close the FILE.

    fclose(loadSaved);

    // Print the loaded grid to a file.

    printArrayToFile();
}



            /********************************************************************
            ****           saving the players in the leader board           ****
           *******************************************************************/


void savePlayers(){

    // Creating FILE and opening it for writing.

    FILE *SavePlayersFile;
    SavePlayersFile = fopen("tmp/players.txt", "w+");

    int i, j, temp = 0, index;

    // Saving the number of the players into the FILE.

    fprintf(SavePlayersFile, "%dP\n", playersNum);

    // Saving the players into the FILE by order from the highest score to the lowest score and ranking them.

    for(i = 0; i < playersNum; ++i) {

        for(j = 0; j < playersNum; ++j) {

            if(players[j].playerScore >= temp) {
                temp = players[j].playerScore;
                index = j;

            }
        }

        temp = 0;
        fprintf(SavePlayersFile, "%s:%d:%d\n", players[index].playerName, players[index].playerScore, i+1);
        players[index].playerScore = -1;

    }

    // Close the FILE.

    fclose(SavePlayersFile);

}



            /********************************************************************
            ****           loading the players in the leader board          ****
           *******************************************************************/




void loadPlayers(){

    // Creating FILE and opening it for writing.

    FILE *loadSavedPlayers;
    loadSavedPlayers = fopen("tmp/players.txt", "a+");

    char tmp = 0, line[256];
    int i, j;
    playersNum = 0;

    // Loading the number of players.

    while(tmp != 32 && tmp != -49) {

        playersNum *= 10;
        playersNum += tmp;
        tmp = fgetc(loadSavedPlayers) - 48;

    }

    // Loading the players names, scores and ranks. Then, saving this data into a array of structures.

    tmp = fgetc(loadSavedPlayers) - 48;
    tmp = 0;

    for(i = 0; i < playersNum; ++i) {

        fgets(line, 255, (FILE*)loadSavedPlayers);
        j=0;

        while(line[j] != ':') {

            players[i].playerName[j] = line[j];
            ++j;

        }

        players[i].playerName[j] = '\0';
        players[i].playerScore = 0;
        ++j;

        while(line[j] != ':') {

            players[i].playerScore *= 10;
            players[i].playerScore += line[j] - 48;
            ++j;

        }

        players[i].playerRank = 0;
        ++j;

        while(line[j] != '\n') {

            players[i].playerRank *= 10;
            players[i].playerRank += line[j] - 48;
            ++j;

        }
    }

    // Closing the FILE.

    fclose(loadSavedPlayers);

}

void printArrayToFile()
{
    // Creating FILE and opening it for writing.
    FILE *currentGrid;
    currentGrid = fopen("tmp/currentGrid.txt", "w+");

    int i, j;

    // Saving the current opened grid into a the FILE.

    fprintf(currentGrid, "    ");

    for(j = 1; j <= columsNum; j++) fprintf(currentGrid, "%-2d ", j);

        fprintf(currentGrid, "\n\n");

    for(i  = 0; i < rowsNum; i++) {

        fprintf(currentGrid, "%-4d", i + 1);

        for(j = 0; j < columsNum; j++) {

                fprintf(currentGrid, "%-2c ",gridArray[i][j]);

        }

        fprintf(currentGrid, "\n");

    }

    // Close the FILE.
    fclose(currentGrid);
}
