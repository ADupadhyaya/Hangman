#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
const char* select_word(void)
{
    const char *word_bank[]={"BICYCLE", "CIRCUIT", "DIAMOND", "HORIZON", "LIBRARY", "MONSTER", "PENGUIN", "PHANTOM", "PYRAMID", "VAMPIRE", "WHISTLE","LAPTOP","DESKTOP","MOBILE","APPLE", "BANANA", "COFFEE", "DRAGON", "GALAXY", "GUITAR", "JUNGLE", "MONKEY", "PIRATE", "PLANET", "ROCKET", "SHADOW", "SILENT", "WIZARD"};
    int total_words= sizeof(word_bank)/sizeof(word_bank[0]);
    int random_index= rand() % total_words;
    return (word_bank[random_index]);
}
void initialize_guessed_word(const char *secret_word, char *guessed_word)
{
    int length=strlen(secret_word);
    for(int i=0;i<length;i++)
    {
        guessed_word[i]='_';
    }
    guessed_word[length]='\0';
    //printf("%s \n", guessed_word);
}
int check_guess(const char *secret_word, char *guessed_word, char guess)
{
    int found=0;
    int length=strlen(secret_word);
    for(int i=0;i<length;i++)
    {
        if(secret_word[i]==guess)
        {
            guessed_word[i]=guess;
            found=1;
        }
    }
    return found;
}
int already_guessed(char guess, const char *used_letters, int used_count)
{
    for(int i = 0; i < used_count; i++)
    {
        if(used_letters[i]==guess)
        return 1;
    }
    return 0;
}
void display_hangman(int lives)
{
    int wrong_guesses=6-lives;
    switch(wrong_guesses)
    {
        case 0:
            printf(" +---+\n");
            printf(" |   |\n");
            printf("     |\n");
            printf("     |\n");
            printf("     |\n");
            printf("     |\n");
            printf("=========\n");
            break;

        case 1:
            
            printf(" +---+\n");
            printf(" |   |\n");
            printf(" O   |\n");
            printf("     |\n");
            printf("     |\n");
            printf("     |\n");
            printf("=========\n");
                break;

        case 2:
            printf(" +---+\n");
            printf(" |   |\n");
            printf(" O   |\n");
            printf(" |   |\n");
            printf("     |\n");
            printf("     |\n");
            printf("=========\n");
            break;

        case 3:
            printf(" +---+\n");
            printf(" |   |\n");
            printf(" O   |\n");
            printf("/|   |\n");
            printf("     |\n");
            printf("     |\n");
            printf("=========\n");
            break;

        case 4:
            printf(" +---+\n");
            printf(" |   |\n");
            printf(" O   |\n");
            printf("/|\\  |\n");
            printf("     |\n");
            printf("     |\n");
            printf("=========\n");
            break;

        case 5:
            printf(" +---+\n");
            printf(" |   |\n");
            printf(" O   |\n");
            printf("/|\\  |\n");
            printf("/    |\n");
            printf("     |\n");
            printf("=========\n");
            break;

        case 6:
            printf(" +---+\n");
            printf(" |   |\n");
            printf(" O   |\n");
            printf("/|\\  |\n");
            printf("/ \\  |\n");
            printf("     |\n");
            printf("=========\n");
            break;
    }
}

int main()
{
    srand(time(NULL));
    printf("enetr 1 for single player game enter 2 for 2player game \n");
    int choice;
    scanf("%d",&choice);
    const char *secret_word = NULL;
    char Custom_word[50];
    char guessed_word[50];
    
    if(choice == 1)
    {
        secret_word =select_word();
    }
    else if(choice ==2)
    {
        printf("enter secret a word \n");
        scanf("%49s",Custom_word);
        secret_word=Custom_word;
        for(int i=0;i<strlen(Custom_word);i++)
        {
            Custom_word[i]=toupper(Custom_word[i]);
        }
        system("clear");
    }
    else
    {
        printf("Invalid choice!\n");
        return 1;
    }
    initialize_guessed_word(secret_word, guessed_word);
    
    int lives=6;
    char used_letters[26];
    int used_count = 0;
    while(lives>0 && strcmp(guessed_word,secret_word)!=0)
    {
        display_hangman(lives);
        printf("%s \n",guessed_word);
        printf("no of lives left = %d \n",lives);
      

        char guess;
        
        printf("take a guess: \n");
        scanf(" %c",&guess);
        if(!isalpha((unsigned char)guess))
        {
            printf("Please enter an alphabetic character!\n");
            continue;
        }
        guess = toupper((unsigned char)guess);
        if(already_guessed(guess, used_letters, used_count) == 1)
        {
            printf("You already guessed %c! Try another letter.\n", guess);
        }
        else
        {
             used_letters[used_count] = guess;
             used_count++;

                if(check_guess(secret_word, guessed_word, guess) == 0)
                {
                    lives--;
                    printf("%c is a wrong guess! Lives left = %d\n", guess, lives);
                }
                else
                 {
                    printf("%c is a correct guess!\n", guess);
                }
        }
        
    }
    if(lives == 0)
    {
        display_hangman(lives);
        printf("\nGame Over! You lost.\n");
        printf("The secret word was: %s\n", secret_word);
        
    }
    else
    {
        printf("\nCongratulations! You won!\n");
    }   

    return 0;
}
