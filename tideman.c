#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool is_cycle(int winner, int loser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            // ranks lists first prefered candidate to last prefered candidate
            // i is candidate index
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // total of (candidate_count - 1) candidates are preferred
    for (int i = 0; i < candidate_count - 1; i++)
    {
        // ith position and onward are not preferred candidates
        for (int j = i + 1; j < candidate_count; j++)
        {
            // add 1 to preferences[i][j] where vote prefer candidate i over j
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // temp pair
    pair temp;

    // selection sort descending order
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            // swap position if pair[i] has smaller strength of victory vs pair[j]
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[j].winner][pairs[j].loser])
            {
                temp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // if it's not a cycle, checking the pair by reversing loser to winner
        if (!is_cycle(pairs[i].loser, pairs[i].winner))
        {
            // lock pairs[i]
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // each candidate has a boolean value if he/she's a winner
    bool winners[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        // default all candidates as winners
        winners[i] = true;
        for (int j = 0; j < candidate_count; j++)
        {
            // if candidate index i was once a locked loser, set bool to false
            if (locked[j][i])
            {
                winners[i] = false;
                // once its set to false, break out of current loop
                break;
            }
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        // print candidate name if winner flag is true
        if (winners[i])
        {
            printf("%s\n", candidates[i]);
        }
    }

    return;
}

// helper function to check if the loop closes
// if winner alreacy connects to loser, it will create a cycle
bool is_cycle(int winner, int loser)
{
    // base case: if locked[winner][loser] == true
    if (locked[winner][loser])
    {
        return true;
    }
    else
    {
        for (int i = 0; i < candidate_count; i++)
        {
            // if there is a loser attached to winner (True)
            if (locked[winner][i])
            {
                // set loser index as new winner index if recursion is true
                if (is_cycle(i, loser))
                {
                    return true;
                }
            }
        }
    }
    // return false outside of if statement because of potential case:
    // 1->2; 1->3->0, but cannot add 0->1
    // have to check through all nodes if none leads to cycle, then return false
    return false;
}