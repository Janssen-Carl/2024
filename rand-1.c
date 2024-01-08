#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
     char choice;

     do
     {
          int range, guess = 0, attempt = 1, att;
          system("cls");

          printf("Please input the range: ");
          scanf("%i", &range);

          srand(time(0));
          int num = (rand() % range) + 1;

          printf("Please input how many attemps: ");
          scanf("%i", &att);

          printf("\nYou have %i attempts!", att);
          printf("\nGuess %i: ", attempt);
          scanf("%i", &guess);

          while (guess != num && attempt < att)
          {
               printf("\nIncorrect! ");
               if (guess < num)
               {
                    printf("\nHigher!");
               }
               if (guess > num)
               {
                    printf("\nLower!");
               }
               attempt++;
               printf("\n\nGuess %i: ", attempt);
               scanf("%i", &guess);
          }

          if (guess == num && attempt <= att)
          {
               printf("\nCorrect! Congratulations!\n");
          }
          else
          {
               printf("\nIncorrect! The Number is %i.\n", num);
          }

          getchar();
          printf("\nPlay Again? (y/n) ");
          scanf(" %c", &choice);
          choice = tolower(choice);

     } while (choice == 'y');
     system("cls");
     return 0;
}