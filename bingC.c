#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

// ilaw ilaw
#define COLOR_RESET "\033[0m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define GREEN "\033[32m"

const char *colorCycle[] = {
    RED, YELLOW, BLUE, GREEN};
const int colorCycleLength = sizeof(colorCycle) / sizeof(colorCycle[0]);

#define TEXT "LET'S PLAY BINGO!!!"
#define TEXT_2 "[Press enter to continue...]"
// ilaw ilaw

void clearScreen() // USE THIS SHIT
{
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
}

void press_any_key()
{
    while (getchar() != '\n')
        ;
}

#define row_bingo 5
#define column_bingo 5
#define max_players 10     // max num of players
#define max_cards 10       // max num of cards per player
#define max_bingo_chips 75 // numbers 1-75 for Bingo
#define max_patterns 500
#define maxP_index 25
#define max_matchedIndex 25

struct Player
{
    int num_cards;
    int cards[max_cards][row_bingo][column_bingo];
};

int drawnChips[max_bingo_chips] = {0}; // 0 means not drawn
int numDrawn = 0;                      // keep track of how many chips have been drawn
int forCheck;

int *patternPtr[max_patterns];
int patternLengthTotal[max_patterns];
// int patternHolder[2][max_patterns][];
// int patternCount = 0;

int game_running = 1;          // game continues until set to 0
int winnerPlayer[max_players]; // variable to store player index of the winner
int winners = 0;

void promptNumberOfPlayer(struct Player *players, int *num_players);
void startGame(struct Player *players, int num_players);

// check if a number exists on a Bingo card
int numberExists(int number, int card[row_bingo][column_bingo]);
// generate a Bingo card with unique numbers
void generateCard(int card[row_bingo][column_bingo]);
// generate all cards for a player
void generatePlayerCards(struct Player *player);
// save card data to a file
void saveCardToFile(int card[row_bingo][column_bingo], int playerIndex, int cardIndex);
// save player information to files
void savePlayerInfo(struct Player *players, int num_players);
// draw unique Bingo chips
void drawBingoChip(int drawnChips[], int *numDrawn);
// display drawn chips
void displayDrawnChips(int drawnChips[], int numDrawn);
// display all player's cards
void displayPlayerCards(struct Player *players, int num_players, int num);
// update the cards based on drawn chips
void updatePlayerCards(struct Player *players, int num_players);
// reads pattern file and stores to 2d array
void readPatternFile();
// loops on each pattern array
bool isPatternMatch(int *matchedIndexFile, int matchedIndexCount, int *pattern, int patternLength);
// loops on every pattern
bool checkBingoWinner(int *matchedIndexFile, int matchedIndexCount);
// checks winner
bool checkWinner(int playerIndex, int cardIndex);

// NEW ADDITION
int Main_Menu();
int gamestart();
// int list_patterns();
// int parameter_list();
// type
void Lengthto();
int FileRetrieve = 1;
int matchpattern;
void userInt();
void help();
// NEW ADDITION

// EEEEEERRRRRRIIIIIICCCCKKKK ---------------------------------------------------------------------------------------------------------

// VARIABLE ERICK 1
int patternHolder[2][max_patterns][maxP_index];
int patternLength[2][max_patterns];
int patternTrack[2];
// int *patternPtr[max_patterns]; //Equivalent to PatternStorage
// int *patternLengthTotal[max_patterns]; //Equivalent to PatternLengthTotal
int patternCount = 0; // Total count of patterns
int Editable[25];
int pLength = 0;
int save = 0;

int dispP;
// int FileRetrieve = 1;

char classic[] = "bingoPatterns.txt";
char custom[] = "bingoPCustom.txt";
// VARIABLE ERICK 1

// VARIABLE ERICK 2
int parameter_index[max_patterns];
int paramcount = 0;
int param_save = 1;
int *param_IndexPtr;
int param_num;
// VARIABLE ERICK 2

// FUNCTIONS-PATTERN LIST ERICK 1
int Edit_Pattern(int choice, int pnum);
int list_patterns();
int displayPattern(int choice, int mode, int pnum, int function);
int pattern_retrieval(int patternGroup, char *mode);
int generateRandomPattern(int m);
int saveList();
void Delete_Pattern(int choice, int pnum);
void Transfer(int choice, int pnum);
// FUNCTIONS-PATTERN LIST ERICK 1

// FUNCTION ERICK 2
void parameter_retrieve();
int parameter_list(int con);
int parameter_edit(int con);
void parameter_save();
// FUNCTION ERICK 2

// EEEEEERRRRRRIIIIIICCCCKKKK-----------------------------------------------------------------------------------------------------------

//BOARDDDD

void retrLead();
void leaderboard();
void Ultimate();
void compareW(int w);
void InputName(int w);
void storeW();

int prevwin = 0;
int iteration = 1;
int change = 0;
int UltimateWinner;
int rank;

struct winner
{
  char name[40];
  double pointw;
};

#define win struct winner
#define bound printf("---------------------------\n")

win leader[5];
win currentW;

//leader

int main()
{
    // readPatternFile();
    if (FileRetrieve)
    {
        userInt();
        press_any_key();
        clearScreen();

        pattern_retrieval(0, classic);
        dispP = pattern_retrieval(1, custom);
        parameter_retrieve();
        retrLead();
        FileRetrieve = 0;
        srand(time(0)); // seed random number with current time
    }

    Main_Menu();

    return 0;
}

int Main_Menu()
{

    clearScreen();
    int ch;

    //  Lengthto();

    printf("B I N G O   G A M E");
    printf("\n[1] Play\n[2] Pattern List\n[3] Game Parameters\n[4] LeaderBoards\n[5] Help\n[6] Exit\n");
    printf("\n\n ->|  ");
    scanf("%i", &ch);

    switch (ch)
    {
    case 1:
        gamestart();
        break;
    case 2:
        list_patterns();
        break;
    case 3:
        parameter_list(0);
        break;
    case 4:
         leaderboard();
         return Main_Menu();
         break;
    case 5:
        help();
        break;
    case 6:
        clearScreen();
        break;
    default:
        printf("\n\nInvalid input!");
        return main();
        break;
    }
    return 0;
}
// ane
void userInt()
{
    for (int i = 0; i < colorCycleLength; i++)
    {
        clearScreen();
        printf("\t\t\t\t\t\t\t%s%s%s\n", colorCycle[i], TEXT, COLOR_RESET);
        fflush(stdout);
        usleep(500000);
    }
    printf("\t\t\t\t\t\t   %s%s%s\n", GREEN, TEXT_2, COLOR_RESET);
}

// void Lengthto()
// {
//   int r;
//   for(int t = 0; t < patternCount; t++)
//   {

//     for(int r = 0; r < 2; r++)
//     {
//       for(int y = 0; y < patternTrack[r]; y++)
//       {
//         patternLengthTotal[t] = patternLength[r][y];
//       }
//     }
//   }
// }

int gamestart()
{
    struct Player players[max_players]; // Declatation
    int num_players;

    clearScreen();

    promptNumberOfPlayer(players, &num_players);

    if (num_players > 0)
    {
        startGame(players, num_players);
        winners = 0;
        numDrawn = 0;
        memset(drawnChips, 0, sizeof(drawnChips));
        iteration = 1;
        game_running = 1;
    }
    printf("Press Enter to Return to Menu...");
    press_any_key();
    Main_Menu();
    return 0;
}

void promptNumberOfPlayer(struct Player *players, int *num_players)
{
    printf("How many players will play the game? ");
    scanf("%i", num_players);

    if (*num_players <= 0 || *num_players > max_players)
    {
        printf("Invalid number of players. Maximum players allowed: %i\n", max_players);
        *num_players = 0; // no players, so it will not continue
        return;
    }

    // loop to prompt each player for the number of cards they want
    for (int playerIndex = 0; playerIndex < *num_players; playerIndex++)
    {
        printf("\nPlayer %i, how many cards do you want? ", playerIndex + 1);
        scanf("%i", &players[playerIndex].num_cards);

        if (players[playerIndex].num_cards <= 0 || players[playerIndex].num_cards > max_cards)
        {
            printf("Invalid number of cards. Maximum allowed: %i\n", max_cards);
            *num_players = 0; // cancel game
            return;
        }

        // generate each cards
        generatePlayerCards(&players[playerIndex]);
    }

    // save all player information to file
    savePlayerInfo(players, *num_players);
}

void startGame(struct Player *players, int num_players)
{
    clearScreen();

    printf("Bingo cards generated! \n");
    printf("Press ENTER to continue.");

    getchar();
    press_any_key();

    clearScreen();

    displayPlayerCards(players, num_players, 1); // num is set to 1

    printf("\nPress ENTER to start.");
    press_any_key();

    while (game_running)
    {
        if (numDrawn >= max_bingo_chips)
        {
            printf("All chips have been drawn. Ending game.\n");
            break;
        }

        clearScreen();
        drawBingoChip(drawnChips, &numDrawn);

        displayDrawnChips(drawnChips, numDrawn);

        updatePlayerCards(players, num_players);

        displayPlayerCards(players, num_players, 0); // num is set to 0

        if (winners > 0)
        {
            game_running = 0;
            Ultimate();
        }

        if (game_running)
        {
            printf("Press ENTER to draw the next chip.");
            press_any_key();
        }
    }
}

void drawBingoChip(int drawnChips[], int *numDrawn)
{
    int newChip;
    int unique = 0;

    while (!unique)
    {
        newChip = (rand() % 75) + 1;

        unique = 1;
        for (int i = 0; i < *numDrawn; i++)
        {
            if (drawnChips[i] == newChip)
            {
                unique = 0;
                break;
            }
        }
    }

    drawnChips[*numDrawn] = newChip; // adds the unique chip to the drawn list
    (*numDrawn)++;                   // increment the number of drawn chips
}

void displayDrawnChips(int drawnChips[], int numDrawn)
{
    int j = 10;
    printf("History: \n");
    for (int i = 0; i < numDrawn; i++)
    {
        if (i == j)
        {
            printf("\n");
            j += 10;
        }

        printf("%2i ", drawnChips[i]);

        if (i + 1 == numDrawn)
        {
            printf("\n\nDrawn Bingo chip: \e[1;33m %2i \e[0m \n", drawnChips[i]);
            forCheck = drawnChips[i];
        }
    }
    printf("\n");
}

void displayPlayerCards(struct Player *players, int num_players, int num)
{
    if (num == 1)
    {
        for (int playerIndex = 0; playerIndex < num_players; playerIndex++)
        {
            printf("\nPlayer %i's Cards:\n\n", playerIndex + 1);

            for (int cardIndex = 0; cardIndex < players[playerIndex].num_cards; cardIndex++)
            {
                printf("Card %i:\n", cardIndex + 1);

                // Open the corresponding card file to read and display
                char filename[50];
                snprintf(filename, sizeof(filename), "Player%iCard%i.txt", playerIndex + 1, cardIndex + 1);
                FILE *cardFile = fopen(filename, "r");

                if (cardFile == NULL)
                {
                    printf("Error opening card file: %s\n", filename);
                    continue;
                }

                for (int row = 0; row < row_bingo; row++)
                {
                    for (int column = 0; column < column_bingo; column++)
                    {
                        int number;
                        fscanf(cardFile, "%i", &number); // Read each number
                        printf("%3i ", number);          // Display the number
                    }
                    printf("\n"); // Newline after each row
                }

                printf("\n");
                fclose(cardFile);
            }
        }
    }

    if (num == 0)
    {
        char filename[50];

        for (int playerIndex = 0; playerIndex < num_players; playerIndex++)
        {
            printf("\nPlayer %i's Cards:\n\n", playerIndex + 1);
            for (int cardIndex = 0; cardIndex < players[playerIndex].num_cards; cardIndex++)
            {
                printf("Card %i:\n", cardIndex + 1);
                snprintf(filename, sizeof(filename), "Player%iCard%i.txt", playerIndex + 1, cardIndex + 1);
                FILE *cardFile = fopen(filename, "r");

                snprintf(filename, sizeof(filename), "Player%iCard%iIndexMatch.txt", playerIndex + 1, cardIndex + 1);
                FILE *indexFile = fopen(filename, "r");
                int index_Array[max_bingo_chips];
                int indexFile_Size = 0;
                while (fscanf(indexFile, "%i", &index_Array[indexFile_Size]) == 1)
                {
                    indexFile_Size += 1;
                }

                int index = 1;
                for (int row = 0; row < row_bingo; row++)
                {
                    for (int column = 0; column < column_bingo; column++)
                    {
                        bool flag = true;
                        int number;
                        fscanf(cardFile, "%i", &number);

                        for (int i = 0; i < indexFile_Size; i++)
                        {
                            if (index_Array[i] == index)
                            {
                                printf(" \e[1;101m%2i\e[0m ", number);
                                flag = false;
                            }
                        }
                        if (flag)
                        {
                            printf("%3i ", number);
                        }
                        index++;
                    }
                    printf("\n");
                }

                printf("\n");
                fclose(cardFile);
                fclose(indexFile);
            }
        }
    }
}

void updatePlayerCards(struct Player *players, int num_players)
{
    char filename[50];

    for (int playerIndex = 0; playerIndex < num_players; playerIndex++)
    {

        for (int cardIndex = 0; cardIndex < players[playerIndex].num_cards; cardIndex++)
        {
            snprintf(filename, sizeof(filename), "Player%iCard%i.txt", playerIndex + 1, cardIndex + 1);
            FILE *cardFile = fopen(filename, "r");
            int index = 1;
            for (int row = 0; row < row_bingo; row++)
            {
                for (int column = 0; column < column_bingo; column++)
                {
                    int number;
                    fscanf(cardFile, "%i", &number);

                    if (number == forCheck)
                    {
                        snprintf(filename, sizeof(filename), "Player%iCard%iIndexMatch.txt", playerIndex + 1, cardIndex + 1);
                        FILE *indexFile = fopen(filename, "a");
                        fprintf(indexFile, "%i\n", index);
                        fclose(indexFile);
                    }
                    index += 1;
                }
            }

            if (checkWinner(playerIndex, cardIndex))
            {
                printf("Bingo! We have a winner! Please check Player %i Card %i: Matched Pattern [%i].\n", playerIndex + 1, cardIndex + 1, matchpattern + 1);
                winnerPlayer[winners] = playerIndex;
                winners++;
            }

            fclose(cardFile);
        }
    }
}

int numberExists(int number, int card[row_bingo][column_bingo])
{
    for (int i = 0; i < row_bingo; i++)
    {
        for (int j = 0; j < column_bingo; j++)
        {
            if (card[i][j] == number)
            {
                return 1;
            }
        }
    }
    return 0;
}

void generateCard(int card[row_bingo][column_bingo])
{
    for (int row = 0; row < row_bingo; row++)
    {
        for (int column = 0; column < column_bingo; column++)
        {
            if (column == 2 && row == 2)
            {
                card[row][column] = 0;
            }
            else
            {
                int uniqueNum;
                do
                {
                    uniqueNum = (rand() % 15 + 1) + (15 * column);
                } while (numberExists(uniqueNum, card));

                card[row][column] = uniqueNum;
            }
        }
    }
}

void generatePlayerCards(struct Player *player)
{
    for (int cardIndex = 0; cardIndex < player->num_cards; cardIndex++)
    {
        int card[row_bingo][column_bingo] = {0}; // initialize with zeros
        generateCard(card);

        for (int i = 0; i < row_bingo; i++)
        {
            for (int j = 0; j < column_bingo; j++)
            {
                player->cards[cardIndex][i][j] = card[i][j];
            }
        }
    }
}

void saveCardToFile(int card[row_bingo][column_bingo], int playerIndex, int cardIndex)
{
    char filename[50];

    snprintf(filename, sizeof(filename), "Player%iCard%i.txt", playerIndex + 1, cardIndex + 1);
    FILE *cardFile = fopen(filename, "w");

    if (cardFile == NULL)
    {
        printf("Error opening file: %s\n", filename);
        return;
    }

    for (int row = 0; row < row_bingo; row++)
    {
        for (int column = 0; column < column_bingo; column++)
        {
            fprintf(cardFile, "%i \n", card[row][column]);
        }
    }

    fclose(cardFile);

    snprintf(filename, sizeof(filename), "Player%iCard%iIndexMatch.txt", playerIndex + 1, cardIndex + 1);
    FILE *indexFile = fopen(filename, "w");

    if (indexFile == NULL)
    {
        printf("Error opening file: %s\n", filename);
        return;
    }
    else
    {
        fprintf(indexFile, "13\n");
    }

    fclose(indexFile);
}

void savePlayerInfo(struct Player *players, int num_players)
{
    // loops through each player and save their cards
    for (int playerIndex = 0; playerIndex < num_players; playerIndex++)
    {
        for (int cardIndex = 0; cardIndex < players[playerIndex].num_cards; cardIndex++)
        {
            saveCardToFile(players[playerIndex].cards[cardIndex], playerIndex, cardIndex);
        }
    }
}

bool isPatternMatch(int *matchedIndexFile, int matchedIndexCount, int *pattern, int patternLength)
{
    int matches = 0;
    // printf("%i\n", patternLength);
    // press_any_key();
    // loops through each element in the pattern
    for (int i = 0; i < patternLength; i++)
    {
        bool found = false;

        // check if this pattern element is in the matched index file
        for (int j = 0; j < matchedIndexCount; j++)
        {
            if (pattern[i] == matchedIndexFile[j])
            {
                found = true;
                break;
            }
        }

        if (found)
        {
            matches++;
        }
        else
        {
            // if any pattern index is not found, this pattern cannot be a winning one
            return false;
        }
    }

    // if all pattern elements were found, returns true
    return (matches == patternLength);
}

bool checkBingoWinner(int *matchedIndexFile, int matchedIndexCount)
{
    // loop through each pattern
    for (int i = 0; i < patternCount; i++)
    {
        for (int u = 0; u < paramcount; u++) // loop for chosen index patterns
        {
            if (parameter_index[u] == i)
            {
                // printf("LT: i | n%i:%i\n\n", patternLengthTotal[parameter_index[u]], i);
                // printf("patterni [%i]: patternu [%i]\n", i, parameter_index[u]);
                if (isPatternMatch(matchedIndexFile, matchedIndexCount, patternPtr[i], patternLengthTotal[i]))
                {
                    // printf("totalL: %i\n", patternLengthTotal[i]);
                    matchpattern = i;

                    double temp = ((numDrawn / paramcount) * patternLengthTotal[i]) - (matchedIndexCount - patternLengthTotal[i]);  //This is how the score is computed, you can change it

                    if(iteration == 1)
                    {
                        currentW.pointw = temp;
                        iteration = 0;
                        change = 1;
                    } else if(temp > currentW.pointw)
                           {
                               currentW.pointw = temp;
                               change = 1;
                           }


                    
                    return true;
                }
            }
        }
    }

    return false;
}

bool checkWinner(int playerIndex, int cardIndex)
{
    char filename[50];

    int matchedIndexFile[max_matchedIndex];
    int matchedIndexCount = 0;

    snprintf(filename, sizeof(filename), "Player%iCard%iIndexMatch.txt", playerIndex + 1, cardIndex + 1);
    FILE *indexFile = fopen(filename, "r");

    while (fscanf(indexFile, "%i", &matchedIndexFile[matchedIndexCount]) != EOF)
    {
        matchedIndexCount++;
    }

    fclose(indexFile);

    if (checkBingoWinner(matchedIndexFile, matchedIndexCount))
    {
        if(change == 1)
        {
            UltimateWinner = playerIndex + 1;
            change = 0;
        }
        return true;
    }
    else
    {
        return false;
    }
}

// ERICKKKKKKKKKK------------------------------------------------------------------------------------------------------

int list_patterns()
{
    clearScreen();
    int num = 0;
    int mode = 0;
    int choice;

    // printf("START------->\n"); //FOR CHECKING VALUES

    // printf("Patterntrack 0: %i\n", patternTrack[0]);
    // printf("Patterntrack 1: %i\n", patternTrack[1]);

    // printf("End------->\n\n");

    printf("CLASSIC PATTERNS:\n");
    for (int limit = 0; limit < patternTrack[0]; limit++)
    {
        printf("[%2i] Pattern No. %2i ", limit + 1, limit);
        printf("-- Length: %2i\n", patternLength[0][limit]);
        num++;
    }

    mode = patternTrack[0];
    printf("\nCUSTOM PATTERNS\n");

    if (dispP == 0)
    {
        //      printf("success\n");
        int pmem = 0;
        for (int limiter = 0; limiter < patternTrack[1]; limiter++)
        {
            num++;
            printf("[%i] Pattern No. %2i ", num, limiter);
            printf("-- Length: %2i\n", patternLength[1][pmem]);
            pmem++;

        } // End of for limiter
        //        printf("end success\n");
    }
    else
    {
        printf("NONE\n");
    }
    num++;
    printf("\n(%i) Generate Patterns...\n", num++);
    printf("(%i) Exit...\n", num);

    //    printf("patternCount: %i\n", patternCount); //for checking only

    printf("\nInput the number of your choice: ");
    scanf("%i", &choice);
    getchar();
    choice = choice - 1;
    //    printf("choice: %i\n", choice); //For checking
    //    printf("mode: %i\n", mode); //For checking
    if (choice <= num)
    {
        if (choice == num - 1)
        {
            saveList();
            return Main_Menu();
        }

        if (choice == num - 2)
        {
            generateRandomPattern(1);
        }

        if (choice < mode)
        {
            displayPattern(choice, 0, choice, 0);
        }
        else
        {
            int pnum = 0;
            pnum = choice - patternTrack[0]; // pwedeng gumawa ng bagong variable kung saan to iiistore imbes na mode coz nakakalito
            //        printf("newmode: %i\n", mode); //for checking value
            displayPattern(choice, 1, pnum, 0); // if 1, ibig sabihin custom
        }
    }
}

int pattern_retrieval(int patternGroup, char *mode)
{
    FILE *retrieve = fopen(mode, "r");

    if (retrieve == NULL)
    {
        if (patternGroup)
        {
            printf("NULL - (%s)\n", mode);
            return generateRandomPattern(0);
        }
        else
        {
            printf("Error Encountered in Opening File(1)\n");
            printf("Press Enter to Exit Program...");
            press_any_key();
            exit(1);
        }
    }

    int num;
    int P_index = 0;
    ;

    while (fscanf(retrieve, "%i", &num) != EOF)
    {
        switch (num)
        {
        case 0:
            if (P_index > 0)
            {
                patternPtr[patternCount] = patternHolder[patternGroup][patternTrack[patternGroup]];
                patternLength[patternGroup][patternTrack[patternGroup]] = P_index;
                patternLengthTotal[patternCount] = P_index;
                P_index = 0;
                patternCount++;
                patternTrack[patternGroup]++;
            }
            break;
        default:
            patternHolder[patternGroup][patternTrack[patternGroup]][P_index] = num;
            P_index++;
        }
    } // End of Whlle

    fclose(retrieve);
    return 0;
}

int displayPattern(int choice, int mode, int pnum, int function) // pnum stands for pattern_number, mode decides if it is a classic or a custom pattern
{
    // mode will make it much more easier to identify which of the patterns are editable and deletable and which are no.
    if (function == 0)
    {
        clearScreen();
    }

    int card[25];
    int h = 0;
    int agree = 0;

    for (int i = 0; i < 25; i++)
    {
        card[i] = i + 1;
    }

    printf("Pattern (%i):\n\n", choice + 1);

    for (int r = 0; r < 5; r++)
    {
        for (int c = 0; c < 5; c++)
        {
            int hold = card[h];
            int flag = 1;

            for (int current = 0; current < patternLength[mode][pnum]; current++)
            {
                if (patternPtr[choice][current] == hold)
                {
                    printf(" \e[1;101m%2d\e[0m ", hold);
                    flag = 0;
                    break;
                }
            } // End of for current

            if (flag)
            {
                printf("%3d ", hold);
            }
            h++;
        } // End of for c

        printf("\n");
    } // End of for r

    if (mode == 1 && function == 0) // Kung kaya i-separate eto from the display function, and make it possible for the display function to be reusable throughout the program
    {
        int user_choice = 0;

        printf("\nPlease choose your action:\n(1)Edit Pattern\n(2)Delete Pattern\n(3)Return to List\n\n");
        printf("Input the number of your choice: ");
        scanf("%i", &user_choice);
        getchar();

        switch (user_choice)
        {
        case 1: // Edit
            Transfer(choice, pnum);
            pLength = patternLength[1][pnum];
            Edit_Pattern(choice, pnum);
            break;
        case 2: // Delete3
            printf("\nAre you sure you want to delete?\n(1)Yes\n(2)No\n");
            printf("Input number of choice: ");
            scanf("%i", &agree);
            getchar();
            if (agree == 1)
            {
                Delete_Pattern(choice, pnum);
            }
            else if (agree == 2)
            {
                getchar();
                return displayPattern(choice, mode, pnum, 0);
            }
            break;
        case 3:
            clearScreen();
            return list_patterns();
            break;
        } // End of Switch
    } // End of if mode 1

    if (function == 1)
    {
        return 0;
    }
    else
    {
        printf("Press Enter to return...");
        press_any_key();
        clearScreen();
        return list_patterns();
    }
}

int generateRandomPattern(int m) // FIX THS IN THE MORNING
{
    clearScreen();

    int set = 18;
    int gen = 0;
    FILE *generate;
    int z;
    int y;
    int count = 0;

    if (save == 0)
    {
        save = 1;
    }

    if (m == 0)
    {
        printf("It seems there are no Custom Patterns yet...\n");
    }
    else
    {
        set = 0;
        printf("Input the number of patterns that you want to generate: ");
        scanf("%i", &set);
        getchar();
    }

    printf("Proceed to Generate Patterns?\n(1)Yes\n(2)No\n");
    printf("Input the number of your chosen action: ");

    do
    {
        scanf("%i", &gen);
        getchar();
    } while (gen != 1 && gen != 2);

    int patternL[set];
    int pattern[set][25];

    switch (gen)
    {
    case 1:
        printf("Generating [%i] patterns...", set);

        for (int i = 0; i < set; i++)
        {

            int prev = (rand() % 4) + 1;
            int length;

            switch (prev) // this so that it is 60% less likely for extremely short or long patterns to occur
            {
            case 1:
            case 5:
                length = (rand() % 24) + 2;
                break;
            case 2:
            case 3:
            case 4:
                length = (rand() % 7) + 5;
                break;
            }

            patternL[count] = length;

            int holder[25] = {0};
            int used[25] = {0};

            for (int j = 0; j < length; j++)
            {
                int num;
                do
                {
                    num = rand() % 25 + 1;
                } while (used[num - 1] || num == 13);

                holder[j] = num;
                used[num - 1] = 1;
                pattern[i][j] = holder[j];

            } // End of for j

            count++;
        } // End of for set

        break;
    case 2:
        if (m == 0)
        {
            return 1;
        }
        else
        {
            return list_patterns();
        }
    } // End of m(gen)//mali to End of Switch Pala

    switch (m)
    {
    case 0:
        generate = fopen(custom, "w");

        if (generate == NULL)
        {
            printf("Error Encountered in Opening File(3)\n");
            printf("Press Enter to Exit...");
            press_any_key();
            return 1;
        }

        for (int c = 0; c < set; c++)
        {
            for (int b = 0; b < patternL[c]; b++)
            {
                fprintf(generate, "%i\n", pattern[c][b]);
            }
            fprintf(generate, "0\n");
        }
        fclose(generate);
        break;
    case 1:

        z = patternCount - 12;
        y = z;

        for (int f = 0, a = patternCount; f < set; f++, a++)
        {
            for (int mem = 0; mem < patternL[f]; mem++)
            {
                patternHolder[1][y][mem] = pattern[f][mem];
            }

            patternPtr[a] = patternHolder[1][y];
            y++;
        }

        patternCount += set;
        patternTrack[1] += set;
        for (int p = 0; p < set; p++)
        {
            patternLength[1][z] = patternL[p];
            z++;
        }

        break;
    } // End of switch m

    if (count == set)
    {
        printf("Successfully generated %i patterns\n", set);
        printf("Press Enter to Continue...");
        press_any_key();

        if (m == 0)
        {
            return pattern_retrieval(1, custom);
        }
        else
        {
            return list_patterns();
        }
    }
    else
    {
        printf("Failed to generate the required %i patterns[count = %i]\n", set, count);
        printf("Press Enter to Continue...");
        press_any_key();
        return 1;
    }
}

void Transfer(int choice, int pnum)
{
    for (int current = 0; current < patternLength[1][pnum]; current++)
    {
        Editable[current] = patternPtr[choice][current];
    }
}

int Edit_Pattern(int choice, int pnum) // To shorten this code, we can use a sort of universal display function, and separate the choice
{
    clearScreen();

    if (save == 0)
    {
        save = 1;
    }

    int card[25];
    int h = 0;

    for (int i = 0; i < 25; i++)
    {
        card[i] = i + 1;
    }

    printf("Pattern No. %i:\n\n", choice + 1);

    for (int r = 0; r < 5; r++)
    {
        for (int c = 0; c < 5; c++)
        {
            int hold = card[h];
            int flag = 1;

            for (int current = 0; current < pLength; current++)
            {
                if (Editable[current] == hold)
                {
                    printf(" \e[1;101m%2d\e[0m ", hold);
                    flag = 0;
                    break;
                }
            } // End of for current

            if (flag)
            {
                printf("%3d ", hold);
            }
            h++;
        } // End of for c

        printf("\n");
    } // End of for r
    int select;
    printf("Input the number of your choice to change its state or enter 0 to exit and save: ");
    scanf("%i", &select);

    if (select == 0)
    {
        patternLength[1][pnum] = pLength;
        patternLengthTotal[choice] = pLength;
        for (int g = 0; g < pLength; g++)
        {
            patternPtr[choice][g] = Editable[g];
        }
        return 0;
    }

    for (int length = 0; length < pLength; length++)
    {
        if (Editable[length] == select)
        {
            int Copy[25] = {0};
            int n = 0;
            Editable[length] = 0;
            for (int i = 0; i < 25; i++)
            {
                if (Editable[i] != 0)
                {
                    Copy[n] = Editable[i];
                    n++;
                }
            }
            pLength += -1; // pwedeng

            memset(Editable, 0, sizeof(Editable));

            for (int y = 0; y < pLength; y++)
            {
                Editable[y] = Copy[y];
            }
            return Edit_Pattern(choice, pnum);
        } // End of if
    } // End of for length

    if (select)
    {
        Editable[pLength] = select;
        pLength++;
        return Edit_Pattern(choice, pnum);
    }
}

void Delete_Pattern(int choice, int pnum)
{

    if (save == 0)
    {
        save = 1;
    }

    int size = patternCount - (choice + 1); //
    int tempPattern[size][25];
    int tempL[size];

    //    printf("size: %i\n", size);

    if (size != 0)
    {
        for (int l = pnum + 1, w = 0; l < patternTrack[1] && w < size; l++, w++) // Puts all the length of succeeding patterns to the selected patterns to a temporary array
        {
            tempL[w] = patternLength[1][l];
            //       printf("tempL%i: %i\n", w, tempL[w]);
        }
        // printf("\n");
        for (int j = choice + 1, k = 0; j < patternCount && k < size; j++, k++) // Puts all the patterns next to the selected pattern to temp pattern
        {
            for (int h = 0; h < tempL[k]; h++)
            {
                tempPattern[k][h] = patternPtr[j][h];
                //            printf("Tpat[%i]: %i\n", j, tempPattern[k][h]);
            }
            // printf("\n");
        } // End of for int j choice + 1
    } // End of if size != 0

    for (int u = choice, v = pnum; u < patternCount; u++, v++) // Sets all the patternPtr to 0 starting from the choice until the last
    {
        memset(patternPtr[u], 0, patternLength[1][v] * sizeof(int));
    }

    if (size != 0)
    {
        memset(&patternLength[1][pnum], 0, (size + 1) * sizeof(int)); //

        for (int t = pnum, x = 0; t < (patternTrack[1] - 1); t++, x++)
        {
            patternLength[1][t] = tempL[x];
        }
    }
    else
    {
        patternLength[1][pnum] = 0;
    }
    // printf("\n");

    if (size != 0)
    {
        for (int j = choice, k = 0; j < patternCount && k < size; j++, k++) // Moves all stored contents together to ocupy the now empty space
        {
            for (int h = 0; h < tempL[k]; h++)
            {
                patternPtr[j][h] = tempPattern[k][h];
                //          printf("Ptr[%i]: %i\n", j, patternPtr[j][h]);
            }
            //         printf("\n");
        } // End of for int j
    }
    patternCount--;
    patternTrack[1]--;
    //  while(getchar() != '\n');
}

int saveList()
{
    clearScreen();
    if (save)
    {
        int choice;
        FILE *saveF;
        printf("Do you want to save your changes?\n(1)Yes\n(2)No\n");
        printf("Input number of choice: ");
        scanf("%i", &choice);

        switch (choice)
        {
        case 1:
            saveF = fopen(custom, "w");

            if (saveF == NULL)
            {
                printf("Error Encountered in Opening File(3)\n");
                printf("Press Enter to exit...");
                press_any_key();
                exit(1);
            }

            for (int q = patternTrack[0], e = 0; q < patternCount; q++, e++)
            {
                for (int r = 0; r < patternLength[1][e]; r++)
                {
                    fprintf(saveF, "%i\n", patternPtr[q][r]);
                } // End of for r
                fprintf(saveF, "0\n");
            } // end of for q

            fclose(saveF);
            printf("\nCHANGES SAVED\n");
            press_any_key();
            return 0;
            break;
        case 2:
            printf("\nCHANGES NOT SAVED...\n");
            press_any_key();
            return 0;
            break;
        default:
            return saveList();
        }
    }
}

void parameter_retrieve()
{
    FILE *parameters = fopen("paramIndex.txt", "r");

    if (parameters == NULL)
    {
        printf("Error Encountered in Opening File (6)\n"); // Hopefully sipagan ako na gumawa ng separate function para lang dito
        printf("Press Enter to End Program...");
        press_any_key();
        exit(1);
    }

    while (fscanf(parameters, "%i", &parameter_index[paramcount]) != EOF)
    {
        // printf("[%i] : %i\n", paramcount, parameter_index[paramcount]);
        paramcount++;
    }

    param_IndexPtr = parameter_index;
    param_num = paramcount;

    fclose(parameters);
}

int parameter_list(int con)
{
    clearScreen();
    int num = 1;
    char pos[] = "ACTIVE";
    char neg[] = "INACTIVE";
    int pnum;
    int choice;
    int sign;
    int flag;

    printf("Active Count: %i\n\n\n", paramcount);

    printf("Classic Patterns: \n");
    for (int i = 0; i < patternTrack[0]; i++)
    {
        flag = 1;
        printf("[%2i] Pattern No. %2i: ", num, i);
        for (int o = 0; o < paramcount; o++)
        {
            if (i == param_IndexPtr[o])
            {
                printf(" \e[0;32m %-3s\e[0m", pos);
                flag = 0;
                break;
            }
        } // End of For o

        if (flag)
        {
            printf("\e[0;31m%-2s\e[0m", neg);
        } // End of if

        if ((i + 1) == con)
        {
            printf(" <<\n");
            sign = flag;
        }
        else
        {
            printf("\n");
        }
        num++;
    } // eND of for int i

    printf("\nCustom Patterns: \n");
    if (dispP == 0)
    {
        for (int i = 0; i < patternTrack[1]; i++)
        {
            flag = 1;
            printf("[%2i] Pattern No. %2i: ", num, i);
            for (int o = 0; o < paramcount; o++)
            {
                if ((num - 1) == param_IndexPtr[o])
                {
                    printf(" \e[0;32m %-3s\e[0m", pos);
                    flag = 0;
                    break;
                }
            } // End of For o

            if (flag)
            {
                printf("\e[0;31m%-2s\e[0m", neg);
            } // End of if

            if ((num) == con)
            {
                printf(" <<\n");
                sign = flag;
            }
            else
            {
                printf("\n");
            }
            num++;
        } // eND of for int i
    }
    else
    {
        printf("None\n");
    }
    int lim = num;
    printf("\n"); // wala pa yung activate all custom/classic
    printf("\e[0;36m(%2i)\e[0m Exit\n\n", lim);

    if (con != 0 && con != lim) // Display Portion
    {
        int mod;
        // while(getchar() != '\n');
        if (con <= patternTrack[0])
        {
            pnum = con - 1;
            mod = 0;
        }
        else
        {
            pnum = (con - 1) - patternTrack[0];
            mod = 1;
        } // Eend of if con < patternTrack

        displayPattern((con - 1), mod, pnum, 1);

        if (sign == 1)
        {
            printf("|| >> \e[34m%s\e[0m << ||\n", neg);
        }
        else if (sign == 0)
        {
            printf("||  >> \e[33m%s\e[0m <<  ||\n", pos);
        }
    } // End of if con

    printf("\nInput the number of your choice: ");
    scanf("%i", &choice);
    getchar();

    if (choice == lim)
    {
        if (param_save == 0)
        {
            parameter_save();
        }
        param_save = 1;
        return Main_Menu();
    }

    if (choice <= patternCount && choice != 0)
    {
        return parameter_edit(choice);
    }
    else
    {
        if (choice != 0)
        {
            printf("Invalid Entry..Try Again...");
            press_any_key();
        }
        return parameter_list(0);
    }
}

int parameter_edit(int con)
{
    if (param_save == 1)
    {
        param_save = 0;
    }

    // printf("print[1]\n");
    // printf("prevcon: %i\n", con);
    clearScreen();
    con = con - 1;
    // printf("con : %i\n", con);

    for (int length = 0; length < paramcount; length++)
    {
        if (param_IndexPtr[length] == con)
        {
            int Copy[max_patterns] = {0};
            int n = 0;
            int exclude = param_IndexPtr[length];
            for (int i = 0; i < paramcount; i++)
            {
                if (param_IndexPtr[i] != exclude)
                {
                    Copy[n] = param_IndexPtr[i];
                    // printf("Copy[%i]: %i\n", n, Copy[n]);
                    n++;
                }
            }
            paramcount--; // pwedeng
            // printf("print[2]\n");
            memset(param_IndexPtr, 0, sizeof(param_IndexPtr));

            for (int y = 0; y < paramcount; y++)
            {
                param_IndexPtr[y] = Copy[y];
            }
            return parameter_list(con + 1);
        } // End of if
    } // End of for length
    // printf("print[3]\n");
    // while(getchar() != '\n');
    parameter_index[paramcount] = con;
    //   printf("param: %i\n", con);
    //   press_any_key();
    paramcount++;
    return parameter_list(con + 1);
}

void parameter_save()
{
    clearScreen();
    FILE *Log;
    int choice;
    printf("Do you want to save your changes?\n(1)Yes\n(2)No\n\n");
    printf("Input the number of your choice: ");
    scanf("%i", &choice);
    getchar();

    switch (choice)
    {
    case 1:
        Log = fopen("paramIndex.txt", "w");
        for (int u = 0; u < paramcount; u++)
        {
            fprintf(Log, "%i\n", param_IndexPtr[u]);
        }
        fclose(Log);

        // memset(parameter_index, 0, sizeof(parameter_index));

        for (int f = 0; f < paramcount; f++)
        {
            parameter_index[f] = param_IndexPtr[f];
        }
        param_num = paramcount;
        return;
        break; // Parang ang useless ng break kung may return man lang
    case 2:
        paramcount = param_num;
        return;
        break;
    default:
        printf("Invalid input...");
        press_any_key();
        return parameter_save();
    }
}

// ERICKKKKKKKKKK------------------------------------------------------------------------------------------------------
void help()
{
    clearScreen();
    printf(">>Help Section<<\n\n");

    printf("General Instructions:\n");
    printf("1. Picking Number of Players and Cards:\n");
    printf("    - When starting a new game, you will be asked to enter the number of players.\n");
    printf("    - Each player will be asked for the number of bingo cards they want.\n");

    printf("2. Customizing Patterns:\n");
    printf("    - Use the 'Generate Pattern' option to create custom bingo patterns. Follow the on-screen instructions to design your pattern.\n");
    printf("    - Custom patterns add variety to your game and can be saved for future use.\n");

    printf("3. Editing Classic Patterns:\n");
    printf("    - Classic patterns can be edited by selecting the 'Generate Pattern' option.\n");
    printf("    - You can modify existing patterns or create new variations.\n");

    printf("4. Game Parameters:\n");
    printf("    - Use the Game Parameters Option to alter which patterns are applicable in the game\n");
    printf("    - You can change each pattern into an Active or Inactive State by entering their number\n");

    printf("\n\n\t\t\t\t>> Thank you for playing Bingo! Enjoy the game and good luck! <<\n\n");
    getchar();
    press_any_key();
    main();
}

// NEWWWWWWWWWWWWWWWWWWWWWWWWWW---------------------------------------------------------------

// void leaderboardMenu(){}

//void LBfileretrieve(){}

//void ifWinner(){}

//void LBstore(){}

void retrLead()
{
    FILE *lead = fopen("leaderboard.txt", "r");
 
    if(lead == NULL)
    {
        prevwin = 0;
    }

    while(fscanf(lead, "%s %lf", leader[prevwin].name, &leader[prevwin].pointw) != EOF)
    {
        prevwin++;
    }
    fclose(lead);

    if(prevwin > 5)
    {
        printf("INVALID NUMBER OF SCANNED DATA\n");
        
    }
}

void leaderboard()
{
    clearScreen();
    bound;
    printf("\tLEADERBOARD\n");
    bound;

    if(prevwin == 0)
    {
        printf("NONE...\n");
    } else
      {
        printf("Rank");
        printf("  Name       ");
        printf("|  Score\n");
        for(int q = 0; q < prevwin; q++)
        {
            // printf("[%2i]", q + 1);
            // printf("%2s ", leader[q].name);
            // printf("| ");
            // printf("%8i ", leader[q].pointw);
            // printf("\n");
            for(int h = 0; h < 3; h++)
            {
                switch(h)
                {
                    case 0:
                        printf("[%2i]  ", q + 1);
                        break;
                    case 1:
                        printf("%-10s ", leader[q].name);
                        break;
                    case 2:
                        printf("|  %3.2lf", leader[q].pointw);
                        break;
                }
            }
            printf("\n");
        }
      }
    getchar();
    printf("\nPress Enter to Return...");
    while(getchar() != '\n');

}

void Ultimate()
{
    int histore = 0;
    printf("\nPlayer %i, CONGRATULATIONS!!! YOU are the Ultimate Winner!!!\nYou have a Score of %.2lf!!\n", UltimateWinner, currentW.pointw);
    printf("\nPress Enter to Continue...");
    press_any_key();
    clearScreen();

    if(currentW.pointw > leader[prevwin - 1].pointw)
    {
      histore = 1;
    }

    if(prevwin < 5)
    {
        histore = 2;
    }

    if(prevwin == 0)
    {
        histore = 3;
    }

    switch(histore)
    {
        case 0:
            break;
        case 1: case 2:
            printf("Your score reached the required threshold for our leaderboard!!");
            compareW(histore);
            InputName(rank);
            break;
        case 3:
            InputName(0);
            break;
    }

}

void compareW(int w)
{
    if(w == 1)
    {
        snprintf(leader[prevwin - 1].name, sizeof(leader[prevwin - 1].name), "%s", "temporary");
        leader[prevwin - 1].pointw = currentW.pointw;
    }

    if(w == 2)
    {
        snprintf(leader[prevwin].name, sizeof(leader[prevwin].name), "%s", "temporary");
        leader[prevwin].pointw = currentW.pointw;
        prevwin++;
    }

    int numwin = prevwin;
    int n;
    int place = prevwin - 1;

    while(n != (numwin - 1))
    {
        n = 0;
        for(int u = 0; u < (numwin - 1); u++)
        {
           if(leader[u].pointw <leader[u + 1].pointw)
           {
             if(u == place)
             {
                 place = u + 1;
             } else if((u + 1) == place)
                    {
                       place = u;
                    }

             char tempo[30];
             double aTemp;
             // snprintf(tempo, sizeof(tempo), "%s", pla[u].name); 
             strcpy(tempo, leader[u].name);
             memset(leader[u].name, 0, sizeof(leader[u].name));
             strcpy(leader[u].name, leader[u + 1].name);
             memset(leader[u + 1].name, 0, sizeof(leader[u + 1].name));
             strcpy(leader[u + 1].name, tempo);
             aTemp = leader[u].pointw;
             leader[u].pointw = leader[u + 1].pointw;
             leader[u + 1].pointw = aTemp;
           } else 
             {
               n++;
             }
        }        
    }
   rank = place;

}

void InputName(int w)
{
    press_any_key();
    clearScreen();
    
    printf("YOU ARE RANK %i\n\n", w + 1);
    
    printf("Please Inout your name [6 characters or less]: ");
    scanf("%s", leader[w].name);
    getchar();
    storeW();

    press_any_key();
    clearScreen();
    printf("Thank you for playing...");
    press_any_key();
}

void storeW()
{
    FILE *storelead = fopen("leaderboard.txt", "w");

    if(storelead == NULL)
    {
        printf("Error Encountered in Opening leaderboards text file\n");
        return;
    }

    for(int c = 0; c < prevwin; c++)
    {
        fprintf(storelead, "%s %.2lf\n", leader[c].name, leader[c].pointw);
    }

    fclose(storelead);
}
