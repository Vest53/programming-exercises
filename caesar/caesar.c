#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void encrypt(char *plaintext, int key) {
    char ciphertext[strlen(plaintext) + 1]; // Create a buffer for ciphertext
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char current_char = plaintext[i];

        // Encrypt uppercase letters
        if (isupper(current_char)) {
            ciphertext[i] = (current_char - 'A' + key) % 26 + 'A';
        }
        // Encrypt lowercase letters
        else if (islower(current_char)) {
            ciphertext[i] = (current_char - 'a' + key) % 26 + 'a';
        }
        // Leave non-alphabetic characters unchanged
        else {
            ciphertext[i] = current_char;
        }
    }
    ciphertext[strlen(plaintext)] = '\0'; // Null-terminate the ciphertext
    printf("Ciphertext: %s\n", ciphertext);
}

int main(int argc, char *argv[]) {
    // Check if the user provided a key
    if (argc != 2) {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Convert key to an integer
    int key = atoi(argv[1]);
    if (key < 0) {
        printf("Key must be a non-negative integer\n");
        return 1;
    }

    // Get plaintext from user
    char plaintext[1000];
    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    // Remove newline character from fgets
    plaintext[strcspn(plaintext, "\n")] = 0;

    // Encrypt the plaintext
    encrypt(plaintext, key);

    return 0;
}
