// Import libraries
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// ./substitution JTREKYAVOGDXPSNCUIZLFBMWHQ

char substitute(char text, string key);

int main(int argc, string argv[])
{
    // Check if the arguments are two, reject if not
    if (argc != 2)
    {
        printf("Command expects two arguments\nUsage: ./substitution key\n");
        return 1;
    }
    // Check if the arguments are two
    if (argc == 2)
    {
        // Assign key to variable; key
        string key = argv[1];
        int keylen = strlen(key);
        // Check if key length equals 26 or reject
        if (keylen != 26)
        {
            printf("Key must contain 26 characters\n");
            return 1;
        }
        else
        {
            // Iterate: Check if each character is alphabet or reject
            for (int i = 0; i < keylen; i++)
            {
                if (!isalpha(key[i]))
                {
                    printf("Key must contain only alphabets\n");
                    return 1;
                }
            }
            // Iterate: Check if the characters are unique
            for (int i = 0; i < keylen; i++)
            {
                for (int j = 0; j < keylen; j++)
                {
                    // Break if i equals j since they both point to the same alphabet
                    if (i == j)
                    {
                        break;
                    }
                    // Convert alphabets to lower case and compare. Reject if the same
                    else if (tolower(key[i]) == tolower(key[j]))
                    {
                        printf("Key must contain unique values\n");
                        return 1;
                    }
                }
            }
        }
        // Prompt user for input
        string plaintext = get_string("plaintext: ");
        printf("ciphertext: ");
        //Algorithm for substitution cipher
        // Iterate: Call the substitute function on each alphabet
        for (int i = 0, n = strlen(plaintext); i < n; i++)
        {
            printf("%c", substitute(plaintext[i], key));
        }
        printf("\n");
    }
}

//Function for substitution cipher
char substitute(char alpha, string key)
{
    // Check if alphabet and substitute or else do not substitute
    // Handle upper case alphabets
    if (isupper(alpha))
    {
        int index = (int) alpha - 65;
        return toupper(key[index]);
    }
    // Handle lower case alphabets
    else if (islower(alpha))
    {
        int index = (int) alpha - 97;
        return tolower(key[index]);
    }
    // Handle punctuations, etc.
    else
    {
        return alpha;
    }
}