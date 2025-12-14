#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CODE_LENGTH 4
#define MAX_ATTEMPTS 10

void generateCode(int code[]) {
    for (int i = 0; i < CODE_LENGTH; i++) {
        code[i] = rand() % 10; // digits 0–9
    }
}

void getGuess(int guess[]) {
    int num;
    printf("Enter your 4-digit guess: ");
    scanf("%d", &num);

    for (int i = CODE_LENGTH - 1; i >= 0; i--) {
        guess[i] = num % 10;
        num /= 10;
    }
}

void checkGuess(int code[], int guess[], int *correctPos, int *correctDigit) {
    int usedCode[CODE_LENGTH] = {0};
    int usedGuess[CODE_LENGTH] = {0};

    *correctPos = 0;
    *correctDigit = 0;

    // First pass: correct positions
    for (int i = 0; i < CODE_LENGTH; i++) {
        if (guess[i] == code[i]) {
            (*correctPos)++;
            usedCode[i] = usedGuess[i] = 1;
        }
    }

    // Second pass: correct digits (wrong positions)
    for (int i = 0; i < CODE_LENGTH; i++) {
        if (!usedGuess[i]) {
            for (int j = 0; j < CODE_LENGTH; j++) {
                if (!usedCode[j] && guess[i] == code[j]) {
                    (*correctDigit)++;
                    usedCode[j] = 1;
                    break;
                }
            }
        }
    }
}

int main() {
    int code[CODE_LENGTH];
    int guess[CODE_LENGTH];

    srand(time(NULL));

    generateCode(code);

    printf("\n==== CODE BREAKING GAME ====\n");
    printf("Guess the 4-digit secret code (each digit 0–9)\n");
    printf("You have %d attempts.\n\n", MAX_ATTEMPTS);

    for (int attempt = 1; attempt <= MAX_ATTEMPTS; attempt++) {
        printf("Attempt %d: ", attempt);
        getGuess(guess);

        int correctPos, correctDigit;
        checkGuess(code, guess, &correctPos, &correctDigit);

        if (correctPos == CODE_LENGTH) {
            printf("🎉 Congratulations! You cracked the code!\n");
            return 0;
        }

        printf("Correct digits in correct position: %d\n", correctPos);
        printf("Correct digits in wrong position : %d\n\n", correctDigit);
    }

    // Reveal code if player fails
    printf("\n❌ Out of attempts! The secret code was: ");
    for (int i = 0; i < CODE_LENGTH; i++)
        printf("%d", code[i]);
    printf("\n");

    return 0;
}
