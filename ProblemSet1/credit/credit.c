#include <stdio.h>

void checkValid(long long);

//Had to change long values to long long because of the memory needed to store the credit card number.
int main(void)
{

    // prompt user for credit card number
    long long creditcard;
    printf("Number: ");
    scanf("%lld", &creditcard); // example: 4003600000000014
    checkValid(creditcard);
}

void checkValid(long long creditcard)
{
    long long placeValue = 10;
    long long valueToSubtract = 0;
    int counter = 1;
    int evenSum = 0;
    int oddSum = 0;
    long firstDigitOfCard;
    long secondDigitOfCard;
    const int onePlaceValue = 10;
    const int twoPlaceValue = 100;
    
    // check validity with Luhn's Algorithm
    while (1)
    {
        long long hold = creditcard % placeValue;
        int singleDigit = ((hold - valueToSubtract) / (placeValue / onePlaceValue));

        // if index is even starting from end of card number
        if ((counter % 2) == 0)
        {
            // multiply every other digit by 2, starting with the second to last
            singleDigit *= 2;

            // add the products digits together.
            int remainder = singleDigit % onePlaceValue;
            evenSum += remainder;
            evenSum += ((singleDigit - remainder) / onePlaceValue);
        }
        // else, add to oddSum
        else
        {
            oddSum += singleDigit;
        }

        // If creditcard numbers have ranout.
        if (creditcard == hold)
        {
            firstDigitOfCard = ((hold - valueToSubtract) / (placeValue / onePlaceValue));
            secondDigitOfCard = (((creditcard % (placeValue / onePlaceValue)) -
                                  (creditcard % (placeValue / twoPlaceValue))) /
                                 (placeValue / twoPlaceValue));
            break;
        }
        // If there are more creditcard numbers to be processed.
        else
        {
            placeValue *= 10;
            valueToSubtract = hold;
            counter++;
        }
    }

    // add the doubled numbers individual digits sum to the sum of the untouched numbers.
    int totalSum = oddSum + evenSum;

    // if sum has a last digit 0, then valid. else INVALID.
    if ((totalSum % 10) == 0)
    {
        // VISA starts with 4
        if (firstDigitOfCard == 4 && (counter == 13 || counter == 16))
        {
            printf("VISA\n");
        }
        // MASTERCARD starts with 51 through 55 inclusive
        else if (firstDigitOfCard == 5 && (secondDigitOfCard > 0 && secondDigitOfCard < 6) &&
                 counter == 16)
        {
            printf("MASTERCARD\n");
        }
        // AMEX start with 34 or 37
        else if (firstDigitOfCard == 3 && (secondDigitOfCard == 4 || secondDigitOfCard == 7) &&
                 counter == 15)
        {
            printf("AMEX\n");
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
