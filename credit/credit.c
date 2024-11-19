check50 cs50/problems/2024/x/credit
#include <cs50.h>
#include <stdio.h>

long get_card_number();
int is_valid(long number);
int get_card_type(long number);

int main(void)
{
    long card_number = get_card_number();

    if (is_valid(card_number))
    {
        int card_type = get_card_type(card_number);
        switch (card_type)
        {
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
    }
    else
    {
        printf("INVALID\n");
    }
}

long get_card_number()
{
    long number;
    do
    {
        number = get_long("Number: ");
    }
    while (number <= 0);
    return number;
}

int is_valid(long number)
{
    int sum = 0;
    int count = 0;
    long temp = number;

    // Luhn's algorithm
    while (temp > 0)
    {
        count++;
        int digit = temp % 10;
        if (count % 2 == 0)
        {
            digit *= 2;
            if (digit > 9)
            {
                digit -= 9;
            }
        }
        sum += digit;
        temp /= 10;
    }

    return (sum % 10 == 0);
}

int get_card_type(long number)
{
    // Get the first two digits and the total number of digits
    int first_digit = number;
    while (first_digit >= 10)
    {
        first_digit /= 10;
    }

    int num_digits = 0;
    long temp = number;
    while (temp > 0)
    {
        num_digits++;
        temp /= 10;
    }

    // Determine the card type
    if (num_digits == 15 && (first_digit == 3 || first_digit == 4 || first_digit == 7))
    {
        return 1; // AMEX
    }
    else if (num_digits == 16 && (first_digit == 5))
    {
        // Check if it's MasterCard (52-55)
        int second_digit = number / 10 % 10;
        if (second_digit >= 2 && second_digit <= 5)
        {
            return 2; // MASTERCARD
        }
    }
    else if ((num_digits == 13 || num_digits == 16) && first_digit == 4)
    {
        return 3; // VISA
    }

    return 0; // INVALID
}
