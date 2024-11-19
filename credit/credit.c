#include <cs50.h>
#include <stdio.h>
#include <math.h>

long get_card_number();
int is_valid(long number);
int get_card_type(long number);

int main(void) {
    long card_number = get_card_number();

    if (is_valid(card_number)) {
        int card_type = get_card_type(card_number);
        switch (card_type) {
            case 1:
                printf("AMEX\n");
                break;
            case 2:
                printf("MASTERCARD\n");
                break;
            case 3:
                printf("VISA\n");
                break;
            default:
                printf("INVALID\n");
                break;
        }
    } else {
        printf("INVALID\n");
    }
}

long get_card_number() {
    long number;
    do {
        number = get_long("Number: ");
    } while (number <= 0);
    return number;
}

int is_valid(long number) {
    int sum = 0;
    int count = 0;
    long temp = number;

    // Luhn's algorithm
    while (temp > 0) {
        count++;
        int digit = temp % 10;
        if (count % 2 == 0) {
            digit *= 2;
            if (digit > 9) {
                digit -= 9;
            }
        }
        sum += digit;
        temp /= 10;
    }

    return (sum % 10 == 0);
}

int get_card_type(long number) {
    // Get the first two digits and the total number of digits
    int num_digits = 0;
    long temp = number;

    while (temp > 0) {
        num_digits++;
        temp /= 10;
    }

    int first_digit = number / (long) pow(10, num_digits - 1);
    int first_two_digits = number / (long) pow(10, num_digits - 2);

    // Determine the card type
    if (num_digits == 15 && (first_two_digits == 34 || first_two_digits == 37)) {
        return 1;  // AMEX
    } else if (num_digits == 16 && (first_two_digits >= 51 && first_two_digits <= 55)) {
        return 2;  // MASTERCARD
    } else if ((num_digits == 13 || num_digits == 16) && first_digit == 4) {
        return 3;  // VISA
    }

    return 0;  // INVALID
}
