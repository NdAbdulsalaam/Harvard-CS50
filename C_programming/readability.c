#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Declare functions for main
int count_letters(string word);
int count_words(string word);
int count_sentences(string word);
int coleman_index(float letters, float words, float sentences);

int main(void)
{
    // Prompt for text
    string text = get_string("Text: ");

    //  Call function to count letters, words, sentences.
    float letters = count_letters(text);
    float words = count_words(text);
    float sentences = count_sentences(text);

    // Call function to calculate the Coleman-Liau index
    int index = coleman_index(letters, words, sentences);

    // Outputs the grade level as defined by the Coleman-Liau index
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 1 && index <= 16)
    {
        printf("Grade %i\n", index);
    }
    else
    {
        printf("Grade 16+\n");
    }
}

// Function to count letters
int count_letters(string word)
{
    int count = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if (isupper(word[i]) || islower(word[i]))
        {
            count ++;
        }
    }
    return count;
}

// Function to count words
int count_words(string word)
{
    int count = 1;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if (isspace(word[i]))
        {
            count ++;
        }
    }
    return count;
}

// Function to count sentences
int count_sentences(string word)
{
    int count = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if (word[i] == '.' || word[i] == '?' || word[i] == '!')
        {
            count ++;
        }
    }
    return count;
}

// Function to calculate the Coleman-Liau index (index = 0.0588 * L - 0.296 * S - 15.8)
int coleman_index(float letters, float words, float sentences)
{
    float letters_per_100words = letters / words * 100;
    float sentences_per_100words = sentences / words * 100;

    int index = (int) round(0.0588 * letters_per_100words - 0.296 * sentences_per_100words - 15.8);

    return index;
}
