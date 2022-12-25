#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    // Ensure user gave only one command line argument
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    //Open memory card file
    FILE *memoryCard = fopen(argv[1], "r");
    if (memoryCard == NULL)
    {
        fprintf(stderr, "Error: File cannot be opened\n");
        return 1;
    }

    //Variable to track image number
    int filecount = 0;

    //Buffer to store data
    unsigned char buffer[512];

    //char *filename = "000.jpg";
    char filename[8];
    FILE *jpeg;
    bool isjpeg = false;

    //Read 512 bytes from file to a buffer untill end of card is reached
    while (fread(buffer, 512, 1, memoryCard))
    {
        //Checking for start of new jpeg by looking at header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            isjpeg = true;
            //Close first file and open and continue writing to the next file
            if (filecount != 0)
            {
                fclose(jpeg);
            }
            //If first jpeg, start writing to 000.jpg
            //Filenames: ###.jpg starting at 000.jpg
            sprintf(filename, "%03i.jpg", filecount);
            jpeg = fopen(filename, "w");

            //Write data from buffer to file
            fwrite(buffer, 512, 1, jpeg);

            //Increment file number
            filecount++;
        }
        //If already found jpeg
        else
        {
            if (isjpeg == true)
            {
                //Continue writing data from buffer to file after jpeg is found
                fwrite(buffer, 512, 1, jpeg);
            }
        }
    }

    //Close memory card file
    fclose(memoryCard);

    //Close last jpeg file
    fclose(jpeg);
}