#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to count letters, words, and sentences
void count(const char *text, int *letters, int *words, int *sentences) {
    *letters = 0;
    *words = 0;
    *sentences = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        // Count letters
        if (isalpha(text[i])) {
            (*letters)++;
        }
        // Count words
        if (isspace(text[i]) || text[i + 1] == '\0') {
            if (text[i] != ' ' && text[i] != '\n') {
                (*words)++;
            }
        }
        // Count sentences
        if (text[i] == '.' || text[i] == '!' || text[i] == '?') {
            (*sentences)++;
        }
    }
}

int calculateGrade(int letters, int words, int sentences) {
    // Coleman-Liau formula
    float L = (float)letters / words * 100; // Letters per 100 words
    float S = (float)sentences / words * 100; // Sentences per 100 words
    float index = 0.0588 * L - 0.296 * S - 15.8; // Calculate the index

    return (int)(index + 0.5); // Round to the nearest integer
}

int main() {
    char text[1000];
    int letters, words, sentences;

    // Prompt the user to enter text
    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin); // Read the input line

    // Count letters, words, and sentences
    count(text, &letters, &words, &sentences);

    // Calculate the readability grade
    int grade = calculateGrade(letters, words, sentences);

    // Display the result
    if (grade < 1) {
        printf("Before Grade 1\n");
    } else if (grade >= 16) {
        printf("Grade 16+\n");
    } else {
        printf("Grade %d\n", grade);
    }

    return 0;
}
