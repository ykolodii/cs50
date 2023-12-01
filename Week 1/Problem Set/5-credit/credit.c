#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt for the card number
    long int card_number;
    do
    {
        card_number = get_long("Number: ");
    }
    while (card_number <= 0);

    // Copy the original card number for later use
    long long original_card_number = card_number;

    // Calculate the first two digits before entering the Luhn's Algorithm validation loop
    int first_two_digits = 0;
    while (original_card_number >= 100)
    {
        original_card_number /= 10; // Move one digit at a time
    }
    first_two_digits = original_card_number;

    // Reset original_card_number for Luhn's Algorithm validation
    original_card_number = card_number;

    // Validate the credit card number using Luhn's Algorithm
    int sum = 0;
    int length = 0;

    // Loop for Luhn's Algorithm validation
    while (original_card_number > 0)
    {
        int digit = original_card_number % 10;

        if (length % 2 == 1)
        {
            digit *= 2;

            while (digit > 0)
            {
                sum += digit % 10;
                digit /= 10;
            }
        }
        else
        {
            sum += digit;
        }

        original_card_number /= 10;
        length++;
    }

    // Check if the credit card number is valid
    if (sum % 10 == 0)
    {
        // Determine the type of credit card based on its length and starting digits
        if (length == 15 && (first_two_digits == 34 || first_two_digits == 37))
        {
            printf("AMEX\n");
        }
        else if ((length == 16) && (first_two_digits >= 51 && first_two_digits <= 55))
        {
            printf("MASTERCARD\n");
        }
        else if ((length == 13) || (length == 16) && (first_two_digits / 10 == 4))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
