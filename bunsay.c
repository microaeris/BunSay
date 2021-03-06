#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <time.h>

#define MAX_LINE_SIZE 31
#define MAX_BUBBLE_SIZE 35 // MAX_LINE_SIZE + 2
#define CENTER_BUBBLE_COL 19
#define NUM_BUN_QUOTE 13

#define min(a,b) \
       ({ __typeof__ (a) _a = (a); \
          __typeof__ (b) _b = (b); \
          _a < _b ? _a : _b; })

const char *S_BUBBLE_LEFT = "= ";
const char *S_BUBBLE_RIGHT = " =\n";

const char *S_BUN = 
"     ____        ===\n\
 ___(__  \\       ==\n\
(__  \\ \\  |     =\n\
   \\__\\|__|\n\
  /  _    _\\\n\
 /   _    _ |\n\
 \\..[_] .[_]|\n\
  \\`____^__/\n\
   /|x-x-|\\\n\
  / |-x-x| \\\n\
 '-'/x-x-\\`-'\n\
   /______\\\n\
    | | | |\n\
    \\_\\ \\_\\\n";

const char *S_BUN_CANE =
"     ____        ===\n\
 ___(__  \\       ==\n\
(__  \\ \\  |     =\n\
   \\__\\|__|\n\
  /  _    _\\\n\
 /   _    _ |\n\
 \\..[_] .[_]|\n\
  \\`____^__/\n\
   /|x-x-|\\\n\
  | |-x-x| \\\n\
   \\/x-x-\\`-'\n\
   /______\\||\n\
    | | | |||\n\
    |_|/_/ ||\n";

const char *S_BUN_GRUMP =
"     ____        ===\n\
 ___(__  \\       ==\n\
(__  \\ \\  |     =\n\
   \\__\\|__|\n\
  /  \\    /\\\n\
 /   _    _ |\n\
 \\..[_] .[_]|\n\
  \\`____^__/\n\
   /|x-x-|\\\n\
  ( |-x-x| )\n\
   \\/x-x-\\/\n\
   /______\\\n\
    | || |\n\
    |_||_|\n";

const char *S_BUN_STAR = 
"     ____        ===\n\
 ___(__  \\       ==\n\
(__  \\ \\  |     =\n\
   \\__\\|__|\n\
  /  _    _\\\n\
 /   _    _ |\n\
 \\..[_] .[_]|\n\
  \\`____^__/\n\
   /|  A |\\\n\
  / | <O>| \\\n\
 '-'/  V \\`-'\n\
   /______\\\n\
    | | | |\n\
    \\_\\ \\_\\\n";

const char *S_BUN_BLING =
"     ____        ===\n\
 ___(__  \\       ==\n\
(__  \\ \\  |     =\n\
   \\__\\|__|\n\
  /  _    _\\\n\
 /   _    _ |\n\
 \\..[_] .[_]|\n\
  \\`____^__/\n\
   /| \\ /|\\\n\
  / |  ¥ | \\\n\
 '-'/    \\`-'\n\
   /______\\\n\
    | | | |\n\
    \\_\\ \\_\\\n";

const char *S_BUN_DOT = 
"     ____        ===\n\
 ___(__  \\       ==\n\
(__  \\ \\  |     =\n\
   \\__\\|__|\n\
  /  _    _\\\n\
 /   _    _ |\n\
 \\..[_] .[_]|\n\
  \\`____^__/\n\
   /| ¤ ¤|\\\n\
  / |¤ ¤ | \\\n\
 '-'/ ¤ ¤\\`-'\n\
   /______\\\n\
    | | | |\n\
    \\_\\ \\_\\\n";

const char *S_BUN_SMILIE = 
"     ____        ===\n\
 ___(__  \\       ==\n\
(__  \\ \\  |     =\n\
   \\__\\|__|\n\
  /  _    _\\\n\
 /   _    _ |\n\
 \\..[_] .[_]|\n\
  \\`____^__/\n\
   /| _ _|\\\n\
  / | ._,| \\\n\
 '-'/    \\`-'\n\
   /______\\\n\
    | | | |\n\
    \\_\\ \\_\\\n";

const char *S_BUN_STRIPE = 
"     ____        ===\n\
 ___(__  \\       ==\n\
(__  \\ \\  |     =\n\
   \\__\\|__|\n\
  /  _    _\\\n\
 /   _    _ |\n\
 \\..[_] .[_]|\n\
  \\`____^__/\n\
   /|««««|\\\n\
  / |»»»»| \\\n\
 '-'/««««\\`-'\n\
   /______\\\n\
    | | | |\n\
    \\_\\ \\_\\\n";

const char *S_BUN_TOP = 
"     ____        ===\n\
 ___(__  \\       ==\n\
(__  \\ \\  |     =\n\
   \\__\\|__|\n\
  /  _    _\\\n\
 /   _    _ |\n\
 \\..[_] .[_]|\n\
  \\`____^__/\n\
   /|§§§§|\\\n\
  / |§§§§| \\\n\
 '-'/    \\`-'\n\
   /______\\\n\
    | | | |\n\
    \\_\\ \\_\\\n";

const char *S_BUN_AYY = 
"     ____        ===\n\
 ___(__  \\       ==\n\
(__  \\ \\  |     =\n\
   \\__\\|__|\n\
  /  _    _\\\n\
 /   _    _ |\n\
 \\..[_] .[_]|\n\
  \\`____^__/\n\
   /| ayy|\\\n\
  / |lmao| \\\n\
 '-'/    \\`-'\n\
   /______\\\n\
    | | | |\n\
    \\_\\ \\_\\\n";

const char *S_BUN_RUBY = 
"     ____        ===\n\
 ___(__  \\       ==\n\
(__  \\ \\  |     =\n\
   \\__\\|__|\n\
  /  _    _\\\n\
 /   _    _ |\n\
 \\..[_] .[_]|\n\
  \\`____^__/\n\
   /|++++|\\\n\
  / |RUBY| \\\n\
 '-'/++++\\`-'\n\
   /______\\\n\
    | | | |\n\
    \\_\\ \\_\\\n";

const char *aBunQuotes[] = 
{
    "I\'m not sick, I\'m just Albino!",
    "Who counts the candles on a birthday cake, anyway? I just threw some on for decoration!",
    "You can always take the red-eye.",
    "Hi li\'l ears!",
    "Hey li\'l ears, can you say this? \"Naughty Nook nicked a nice kitchen knife.\"",
    "Woot! Woot WOOT!",
    "Of course I have the latest Bagel Boy comic! It\'s, like, the total MUST have item for young misses in the you know, you know? Oh but, um... I\'m a little short of Bells this month... Actually I gotta fess up! I\'m totally broke! That\'s why I gotta charge you a teeny-tiny little rental fee for it, li\'l ears!",
    "Sooo, I heard that you\'re a totally picky eater. Is that true, li\'l ears?",
    "My favorite coffee is Blue Mountain with lots of milk and exactly three spoonfuls of sugar.",
    "Modern style is the best!",
    "Wish me a happy birthday on December 25th.",
    "My goal is to be a photographer!",
    "Wanna see me do a handstand?"
};

const int nGifts     = 25; // Count the num elements by hand 
const char *aGifts[] =
{
    "apple", "pear", "peach", "orange", 
    "durian", "banana", "cherry", "fruit",
    "lemon", "lychee", "mango", "persimmon",
    "beetle", "firefly", "ladybug", "butterfly",
    "stag", "bells", "carpet", "wallpaper", 
    "letter", "fish", "shark", "eel", "flower"
};

char *sAcceptGift = "Hehe, thanks so much li\'l ears! This is my favorite!";
char *sRejectGift = "Bleh, not my cup of tea.";

//const char *DELIM = "- ;:*()[]{}+=—";
const char *DELIM = " \n";

/**
 * Welp, my version of gcc doesn't support strdup(). 
 * Duplicates the string passed in into a new space.
 */
char *strdup(const char *str)
{
    int n     = strlen(str) + 1;
    char *dup = malloc(n);

    if (dup == NULL) {
        fprintf(stderr, "Could not malloc.\n");
        return NULL;
    }

    if (dup) {
        strcpy(dup, str);
    }

    return dup;
}

/**
 * Inspired by cowsay, but with more bunnies.
 * Prints an ASCII bunny with a quote bubble 
 * containing the string you pass it.
 * The bunny has default lines it can say 
 * and has different dresses and poses that
 * can be displayed depending on the args passed in.
 *
 * Precedence of arguments:
 * Use last pose argument passed in
 * Gift quotes (--give) come before normal quotes
 * Use first normal quote in argv
 *
 * gcc -o bunsay bunsay.c -Wall -g -std=c99
 */
int main(int argc, char *argv[]) {
    int opt            = 0;
    int nQuoteLen      = -1;
    char cBunPose      = '\0';
    char sResult[2048] = "";
    char *sQuote       = 0;
    char *sGift        = 0;

    // Give the bunny a pre-written line to say if nothing is passed in
    if (argc < 2) {
        // Picks a random hard coded phrase to say -- refactor FIXME 
        srand(time(NULL));
        int nQuoteNum = rand() % NUM_BUN_QUOTE;
        nQuoteLen     = strlen(aBunQuotes[nQuoteNum]);
        sQuote        = (char *) malloc(nQuoteLen + 1);

        if (sQuote == NULL) {
            fprintf(stderr, "Could not malloc.\n");
            return -1;
        }

        strncpy(sQuote, aBunQuotes[nQuoteNum], nQuoteLen);
    } 

    // Long opts to read in 
    static struct option long_options[] = {
        {"give", required_argument, 0, 'v'},
        {0,      0,                 0,   0}
    };

    // Read in the options from the command line.
    // Uses the last arg to choose the pose/dress.
    int nLongIndex = 0;
    while ((opt = getopt_long(argc, argv, "abcdgimrstv:",
                              long_options, &nLongIndex)) != -1) {
        switch (opt) {
            case 'a':       // Display Bun with Ayy dress
                cBunPose         = 'a';
                argv[optind - 1] = 0;
                break;
            case 'b':       // Display Bun with bling
                cBunPose         = 'b';
                argv[optind - 1] = 0;
                break;
            case 'c':       // Display Bun with cane
                cBunPose         = 'c';
                argv[optind - 1] = 0;
                break;
            case 'd':       // Display Bun with polka dot dress
                cBunPose         = 'd';
                argv[optind - 1] = 0;
                break;
            case 'g':       // Display grumpy Bun
                cBunPose         = 'g';
                argv[optind - 1] = 0;
                break;
            case 'i':       // Display Bun with stripe dress
                cBunPose         = 'i';
                argv[optind - 1] = 0;
                break;
            case 'm':       // Display Bun with smilie dress
                cBunPose         = 'm';
                argv[optind - 1] = 0;
                break;
            case 'r':       // Display Bun with Ruby dress
                cBunPose         = 'r';
                argv[optind - 1] = 0;
                break;
            case 's':       // Display Bun with star dress
                cBunPose         = 's';
                argv[optind - 1] = 0;
                break;
            case 't':       // Display Bun with top white dress
                cBunPose         = 't';
                argv[optind - 1] = 0;
                break;
            case 'v':       // Give item to Bun
                sGift            = optarg;
                argv[optind - 1] = 0;
                argv[optind]     = 0;   // CHECK IF THIS WORKS
                break;
            default:
                printf("What do you want? I didn't catch that.\n");
        }
    }

    // Check if we just got a gift. Gift take precidence over quotes
    if (sGift != NULL) {
        // If it's an acceptable gift
        for (int i = 0; i < nGifts; ++i) {
            if (strcmp(aGifts[i], sGift) == 0) {
                nQuoteLen = strlen(sAcceptGift);
                sQuote = (char *) malloc(nQuoteLen + 1);

                if (sQuote == 0) {
                    fprintf(stderr, "Could not malloc.\n");
                    return -1;
                }

                strncpy(sQuote, sAcceptGift, nQuoteLen);
                break;
            }
        }

        // If it's not an acceptable gift
        if (sQuote == NULL) {
            nQuoteLen = strlen(sRejectGift);
            sQuote = (char *) malloc(nQuoteLen + 1);

            if (sQuote == 0) {
                fprintf(stderr, "Could not malloc.\n");
                return -1;
            }

            strncpy(sQuote, sRejectGift, nQuoteLen);
        }

        nQuoteLen = strlen(sQuote);
    } else {
        // Get the quote, which the first arg without a '-' in front
        for (int i = 1; i < argc; ++i) {
            if (argv[i] != NULL && argv[i][0] != '-') {
                nQuoteLen = strlen(argv[i]);
                sQuote    = (char *) malloc(nQuoteLen + 1);

                if (sQuote == NULL) {
                    fprintf(stderr, "Could not malloc.\n");
                    return -1;
                }

                strncpy(sQuote, argv[i], nQuoteLen);
                break;
            }
        }
    }

    // Didn't find a quote or the --give command!
    if (sQuote == NULL) {
        // Picks a random hard coded phrase to say -- refactor FIXME 
        srand(time(NULL));
        int nQuoteNum = rand() % NUM_BUN_QUOTE;
        nQuoteLen     = strlen(aBunQuotes[nQuoteNum]);
        sQuote        = (char *) malloc(nQuoteLen + 1);

        if (sQuote == NULL) {
            fprintf(stderr, "Could not malloc.\n");
            return -1;
        }

        strncpy(sQuote, aBunQuotes[nQuoteNum], nQuoteLen);
    }

    // Build the top quote bubble around the quote
    int nBubbleLen = min(nQuoteLen + 4, MAX_BUBBLE_SIZE);
    char sBubbleTop[nBubbleLen];
    sBubbleTop[0] = ' ';

    for (int i = 1; i < nBubbleLen; ++i) {
        sBubbleTop[i] = '=';
    }
    sBubbleTop[nBubbleLen - 1] = '\n';

    // A single lined quote, easy peasy
    if (nQuoteLen <= MAX_LINE_SIZE) {
        // Length of margin 
        int nMarginLen = CENTER_BUBBLE_COL - (nBubbleLen / 2);
        char *sMargin;

        if (nMarginLen > 0) {
            sMargin = (char *) malloc(nMarginLen + 1);

            if (sMargin == NULL) {
                fprintf(stderr, "Could not malloc.\n");
                free(sQuote);
                return -1;
            }

            for (int i = 0; i < nMarginLen; ++i) {
                sMargin[i] = ' ';
            }
        }

        strncat(sResult, sMargin, nMarginLen);
        strncat(sResult, sBubbleTop, nBubbleLen);
        strncat(sResult, sMargin, nMarginLen);
        strncat(sResult, S_BUBBLE_LEFT, 2);
        strncat(sResult, sQuote, nQuoteLen);
        strncat(sResult, S_BUBBLE_RIGHT, 3);
        strncat(sResult, sMargin, nMarginLen);
        strncat(sResult, sBubbleTop, nBubbleLen);

        free(sMargin);
    } else {
        // Process a mutli lined quote. Need to cut the quote into line sizes.
        // Have to copy over the delim character manually because strtok deletes them.
        strncat(sResult, sBubbleTop, nBubbleLen);
        strncat(sResult, S_BUBBLE_LEFT, 2);

        // Copy of the quote to copy the delims from
        char *sQuoteCopy = (char *) strdup(sQuote);
        char *sToken     = strtok(sQuote, DELIM);
        int nCurLineLen  = 0;

        if (sQuoteCopy == NULL) {
            fprintf(stderr, "Could not malloc.\n");
            free(sQuote);
            return -1;
        }

        // Build the quote and the bubble
        while (sToken) {
            int nCurTokenLen = strlen(sToken) + 1; // +1 for space
            char cDelim      = (char) sQuoteCopy[sToken -
                               sQuote + nCurTokenLen - 1];

            // Decide if we should start a new line
            if (nCurLineLen + nCurTokenLen >= MAX_LINE_SIZE) {
                // We need to start a new line

                // Add proper number of spaces to end of line if needed
                int nEndMargin = MAX_LINE_SIZE - nCurLineLen;
                if (nEndMargin > 0) {
                    char sEndMargin[nEndMargin];

                    for (int i = 0; i < nEndMargin; ++i) {
                        sEndMargin[i] = ' ';
                    }
                    strncat(sResult, sEndMargin, nEndMargin);
                }

                // If current token is longer than a line
                // Gotta break it up into multiple lines
                // Set the leftover bit of the long string as sToken
                if (nCurTokenLen > MAX_LINE_SIZE) {
                    // TIRED -- TODO LATER
                    // Make this a seperate function
                }

                strncat(sResult, S_BUBBLE_RIGHT, 3);
                strncat(sResult, S_BUBBLE_LEFT, 2);
                strncat(sResult, sToken, nCurTokenLen);

                // Copy the delim -- refactor FIXME
                int nStrLen = strlen(sResult);

                if (cDelim == '\n') {
                    cDelim = ' ';
                }

                sResult[nStrLen]     = cDelim;
                sResult[nStrLen + 1] = '\0'; // Move the end of sResults over
                nCurLineLen          = nCurTokenLen;
            } else {
                // Print on current line
                strncat(sResult, sToken, nCurTokenLen);

                // Copy the delim -- refactor FIXME
                int nStrLen = strlen(sResult);

                if (cDelim == '\n') {
                    cDelim = ' ';
                }

                sResult[nStrLen]     = cDelim;
                sResult[nStrLen + 1] = '\0'; // Move the end of sResults over
                nCurLineLen          += nCurTokenLen;
            }

            sToken = strtok(NULL, DELIM);
        }

        // Add proper number of spaces to end of line
        int nEndMargin = MAX_LINE_SIZE - nCurLineLen + 1;
        if (nEndMargin > 0) {
            char sEndMargin[nEndMargin];
            for (int i = 0; i < nEndMargin; ++i) {
                sEndMargin[i] = ' ';
            }
            strncat(sResult, sEndMargin, nEndMargin);
        }

        strncat(sResult, S_BUBBLE_RIGHT, 3);
        strncat(sResult, sBubbleTop, nBubbleLen);
        free(sQuoteCopy);
    }

    // Add on the ASCII bunny
    switch (cBunPose) {
        case 'a':       // Display Bun with Ayy dress
            strncat(sResult, S_BUN_AYY, strlen(S_BUN_AYY));
            break;
        case 'b':       // Display Bun with bling
            strncat(sResult, S_BUN_BLING, strlen(S_BUN_BLING));
            break;
        case 'c':       // Display Bun with cane
            strncat(sResult, S_BUN_CANE, strlen(S_BUN_CANE));
            break;
        case 'd':       // Display Bun with polka dot dress
            strncat(sResult, S_BUN_DOT, strlen(S_BUN_DOT));
            break;
        case 'g':       // Display grumpy Bun
            strncat(sResult, S_BUN_GRUMP, strlen(S_BUN_GRUMP));
            break;
        case 'i':       // Display Bun with stripe dress
            strncat(sResult, S_BUN_STRIPE, strlen(S_BUN_STRIPE));
            break;
        case 'm':       // Display Bun with smilie dress
            strncat(sResult, S_BUN_SMILIE, strlen(S_BUN_SMILIE));
            break;
        case 'r':       // Display Bun with Ruby dress
            strncat(sResult, S_BUN_RUBY, strlen(S_BUN_RUBY));
            break;
        case 's':       // Display Bun with star dress
            strncat(sResult, S_BUN_STAR, strlen(S_BUN_STAR));
            break;
        case 't':       // Display Bun with top white dress
            strncat(sResult, S_BUN_TOP, strlen(S_BUN_TOP));
            break;
        default:
            strncat(sResult, S_BUN, strlen(S_BUN));
    }

    printf(sResult);
    free(sQuote);
    return 1;
}