#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// each of our text files contains 1000 words
#define LISTSIZE 1000

// values for colors and score (EXACT == right letter, right place; CLOSE == right letter, wrong place; WRONG == wrong letter)
#define EXACT 2
#define CLOSE 1
#define WRONG 0

// ANSI color codes for boxed in letters
#define GREEN   "\e[38;2;255;255;255;1m\e[48;2;106;170;100;1m"
#define YELLOW  "\e[38;2;255;255;255;1m\e[48;2;201;180;88;1m"
#define RED     "\e[38;2;255;255;255;1m\e[48;2;220;20;60;1m"
#define RESET   "\e[0;39m"

// user-defined function prototypes
string get_guess(int wordsize);
int check_word(string guess, int wordsize, int status[], string choice);
void print_word(string guess, int wordsize, int status[]);

int main(int argc, string argv[])
{
    // ensure proper usage
    // TODO #1
    if (argc != 2)
    {
        printf("Usage: ./wordle wordsize\n");
        return 1;
    }

    int wordsize = 0;

    // ensure argv[1] is either 5, 6, 7, or 8 and store that value in wordsize instead
    // TODO #2
    if (strcmp(argv[1], "5") == 0 || strcmp(argv[1], "6") == 0 || strcmp(argv[1], "6") == 0 || strcmp(argv[1], "7") == 0
        || strcmp(argv[1], "8") == 0)
    {
        wordsize = atoi(argv[1]);
    }
    else
    {
        printf("Error: wordsize must be either 5, 6, 7, or 8\n");
        return 1;
    }

    // open correct file, each file has exactly LISTSIZE words
    char wl_filename[6];
    sprintf(wl_filename, "%i.txt", wordsize);
    FILE *wordlist = fopen(wl_filename, "r");
    if (wordlist == NULL)
    {
        printf("Error opening file %s.\n", wl_filename);
        return 1;
    }

    // load word file into an array of size LISTSIZE
    char options[LISTSIZE][wordsize + 1];

    for (int i = 0; i < LISTSIZE; i++)
    {
        fscanf(wordlist, "%s", options[i]);
    }

    // pseudorandomly select a word for this game
    srand(time(NULL));
    string choice = options[rand() % LISTSIZE];

    // allow one more guess than the length of the word
    int guesses = wordsize + 1;
    bool won = false;

    // print greeting, using ANSI color codes to demonstrate
    printf(GREEN"This is WORDLE50"RESET"\n");
    printf("You have %i tries to guess the %i-letter word I'm thinking of\n", guesses, wordsize);

    // main game loop, one iteration for each guess
    for (int i = 0; i < guesses; i++)
    {
        // obtain user's guess
        string guess = get_guess(wordsize);

        // array to hold guess status, initially set to zero
        int status[wordsize];

        // set all elements of status array initially to 0, aka WRONG
        // TODO #4
        memset(status, 0, sizeof(status));

        // Calculate score for the guess
        int score = check_word(guess, wordsize, status, choice);

        printf("Guess %i: ", i + 1);

        // Print the guess
        print_word(guess, wordsize, status);

        // if they guessed it exactly right, set terminate loop
        if (score == EXACT * wordsize)
        {
            won = true;
            break;
        }
    }

    // Print the game's result
    // TODO #7
    if (won)
    {
        printf("You won!\n");
    }
    else
    {
        printf("You lose! The correct word is %s\n", choice);
    }

    // that's all folks!
    return 0;
}

string get_guess(int wordsize)
{
    string guess = "";
    int len = 0;
    bool len_equal_wordsize = true;
    bool all_lower = true;

    // ensure users actually provide a guess that is the correct length
    // TODO #3
    do
    {
        len_equal_wordsize = true;
        all_lower = true;
        // get user input
        guess = get_string("Input a %i-letter word: ", wordsize);

        // check length of user's input
        len = strlen(guess);
        if (len != wordsize)
        {
            len_equal_wordsize = false;
        }

        // check if user's input is composed of lowercase characters
        for (int i = 0; i < len; i++)
        {
            if (!(guess[i] >= 'a' && guess[i] <= 'z'))
            {
                all_lower = false;
            }
        }
    }
    while (!len_equal_wordsize || !all_lower);

    return guess;
}

int check_word(string guess, int wordsize, int status[], string choice)
{
    int score = 0;

    // compare guess to choice and score points as appropriate, storing points in status
    // TODO #5
    // update status
    for (int i = 0; i < wordsize; i++)
    {
        char cg = guess[i];
        char cc = choice[i];
        if (cg == cc)
        {
            status[i]  = EXACT;
        }
        else
        {
            bool flag = false;
            for (int j = 0; j < wordsize; j++)
            {
                if (cg == choice[j])
                {
                    status[i] = CLOSE;
                    flag = true;
                }
            }
            if (!flag)
            {
                status[i] = WRONG;
            }
        }
    }

    // calculate score
    for (int i = 0; i < wordsize; i++)
    {
        score += status[i];
    }

    return score;
}

void print_word(string guess, int wordsize, int status[])
{
    // print word character-for-character with correct color coding, then reset terminal font to normal
    // TODO #6
    for (int i = 0; i < wordsize; i++)
    {
        if (status[i] == EXACT)
        {
            printf(GREEN"%c", guess[i]);
        }
        else if (status[i] == CLOSE)
        {
            printf(YELLOW"%c", guess[i]);
        }
        else
        {
            printf(RED"%c", guess[i]);
        }
    }

    printf(RESET"\n");
    return;
}