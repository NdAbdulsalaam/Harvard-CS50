# TODO
import sys


def main():
    # Ensure correct usage of arguments
    if len(sys.argv) != 1:
        sys.exit("Usage: python credit.py")

    while True:
        try:
            # Verify input from the user
            card_number = int(input("Number: "))
            break
        except:
            continue
    # Call the Luhn’s Algorithm
    card_len, f_one, f_two, total_sums = luhn_algo(card_number)

    if total_sums == 0:
        if (card_len == 15) and (f_two == 34 or f_two == 37):
            print("AMEX")
        elif (card_len == 16) and (f_two >= 51 and f_two <= 55):
            print("MASTERCARD")
        elif (card_len == 13 or card_len == 16) and (f_one == 4):
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")


def luhn_algo(card_number):
    """
    Most cards use an algorithm invented by Hans Peter Luhn of IBM. According to Luhn’s algorithm,
    the validity of a credit card number can be determined (syntactically) as follows:

    1. Multiply every other digit by 2, starting with the number’s second-to-last digit,
    and then add those products’ digits together.
    2. Add the sum to the sum of the digits that weren’t multiplied by 2.
    3. If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0),
    the number is valid!

    """
    # Get card_number's length
    card_len = len(str(card_number))

    # Case-1 (multiply the other digits by 2 and get the sum)
    prod_sums = 0
    temp = card_number // 10
    while temp > 0:
        rem = temp % 10
        prod = rem * 2
        prod_sums += ((prod % 10) + (prod // 10))
        temp = temp // 100

     # Case-2 (Sum other digits that were not multiplied by 2)
    sums = 0
    temp = card_number
    while temp > 0:
        rem = temp % 10
        sums += rem
        temp = temp // 100

    # Get the total sum
    total_sums = (sums + prod_sums) % 10

    # Get the first and the first_two digits
    temp = card_number
    while temp > 10:
        f_two = temp
        temp = temp // 10
        f_one = temp

    return card_len, f_one, f_two, total_sums


if __name__ == "__main__":
    main()