// Import libraries
#include <cs50.h>
#include <stdio.h>


int counter(long num), sum, tnum2, slnum; // temporary number and second_to_the_last number
long ccnum, fnum, lnum, tnum, f2num; // credit card, first, last, temporary, and first2 numbers

int main(void)
{
    // Prompt for card number
    ccnum = get_long("Enter card number: ");

    // Check for card length
    int count = counter(ccnum);

    //--------------------CHECKSUM--------------------------------

    //Case-01(Multiply every other digit by 2):
    tnum = ccnum ;
    while (tnum > 0)
    {
        lnum = tnum % 10 ;
        sum = sum + lnum ;
        tnum = tnum / 100 ;
    }

    // Case-02(Multiplication every other digit by 2):
    tnum = ccnum / 10 ;
    while (tnum > 0)
    {
        slnum = (tnum % 10) ;
        tnum2 = slnum * 2 ;
        sum = sum + (tnum2 % 10) + (tnum2 / 10)  ;
        tnum = tnum / 100 ;
    }

    // Check for the first, and the first two numbers
    tnum = ccnum;
    do
    {
        f2num = tnum;
        tnum = tnum / 10;
        fnum = tnum;
    }
    while (tnum > 10);

    // Checking Last number
    lnum = ccnum % 10;

    // Print AMEX, MASTERCARD, VISA, OR INVALID
    if (sum  % 10 == 0)
    {
        if (count == 16 && (f2num >= 51 && f2num <= 55))
        {
            printf("MASTERCARD\n");
        }
        else if ((count == 13 || count == 16) && fnum == 4)
        {
            printf("VISA\n");
        }
        else if (count == 15 && (f2num == 34 || f2num == 37))
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

int counter(long num)
{
    int count = 0;
    do
    {
        num /= 10;
        count++;
    }
    while (num != 0);

    return count;
}