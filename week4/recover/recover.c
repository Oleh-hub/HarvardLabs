// 21.05.2023 roi
// The program that recovers .JPG files from a forensic image, per the Example.
// The details of the task: https://cs50.harvard.edu/x/2023/psets/4/recover/
// The program accepts  one command-line argument, the name of a forensic image from which to recover JPGs.
// Usage: ./recover IMAGE.file
// Example: ./recover card.raw

#include <stdio.h>                      // fopen(), etc.

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    unsigned char buffer[BLOCK_SIZE];   // buffer to read 512 bited blocks of the forinsic file
    long int bytesRead = 0;             // counter of bites read from the infile
    int i = 0;                          // counter for the names of jpg files 000.jpg, 001jpg, ...
    char outfile[8];                    // the fixedname of output file: 000.jpg, 001jpg, ... 999.jpg
    FILE *outptr = NULL;                // pointer at the outputfile
    char *infile = argv[1];             // filename of forensic image of the corrupted disk
    FILE *inptr = fopen(infile, "rb");  // Open input file to read in binary, because the first bites format is "0xff 0xd8 0xff..."

    // Ensure proper usage.
    if (argc != 2) // Check if there is one command-line argument, a forensic image from where JPGs are  to be recovered
    {
        printf("Usage: ./recover INFILE \n");
        return 1;
    }

    // If the forensic image cannot be opened for reading, the program informs the user, and main returns 1.
    if (inptr == NULL)
    {
        printf("Failed to open the sourced file.\n");
        return 1;
    }

    do
    {
        bytesRead = fread(buffer, sizeof(unsigned char), BLOCK_SIZE, inptr);
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // The begin of the a new JPG file (0xff 0xd8 0xff 0xeX) is found
            if (outptr != NULL) // Close the previous output file if there was one
            {
                fclose(outptr);
            }

            sprintf(outfile, "%03i.jpg", i);    // give output file a name from 000.jpg
            outptr = fopen(outfile, "wb");      // Open an output .jpg file 2 write in binary

            if (outptr == NULL)
            {
                printf("Failed to open the output file %s.\n", outfile);
                return 1;
            }
            fwrite(buffer, sizeof(unsigned char), BLOCK_SIZE, outptr); //write the begining of jpg ("0xff 0xd8 0xff...")to output file
            i++; //  used to name new output file 000.jpeg, 001.jpeg ...

        }
        else
        {
            if (outptr != NULL) // if output file is open write fürther into it
            {
                fwrite(buffer, sizeof(unsigned char), BLOCK_SIZE, outptr);
            }
        }

    }
    while (bytesRead == BLOCK_SIZE); // read into buffer till less of BLOCK_SIZE is read (eof or error while reading)

    if (outptr != NULL)
    {
        fclose(outptr);
    }
    fclose(inptr);
}