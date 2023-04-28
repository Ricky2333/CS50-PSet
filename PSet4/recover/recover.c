#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

const int BLOCK_SIZE = 512;
typedef uint8_t BYTE;

// function prototype
int check_signature(BYTE buffer[]);

int main(int argc, char *argv[])
{
    // check if there is only 1 command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // open forensic image
    FILE *raw_file = fopen(argv[1], "r");
    if (raw_file == NULL)
    {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }

    // create a jpeg file to store the first image
    int cnt = 0;
    char file_name[8];
    int has_signature = 0;

    // iterate those blocks
    BYTE buffer[BLOCK_SIZE];
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        // check if this block has a JPEG signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] / 16 == 0xe)
        {
            // create a new jpeg file
            has_signature = 1;
            // format file name and create a pointer
            sprintf(file_name, "%03i.jpg", cnt);
            FILE *output_file = fopen(file_name, "w");

            // write this block of data into this file
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, output_file);

            // close this file
            fclose(output_file);

            // increment the counter
            cnt++;
        }
        else
        {
            // a jpeg file is opened
            if (has_signature)
            {
                // append this block to the current file
                FILE *output_file = fopen(file_name, "a");
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, output_file);
                fclose(output_file);
            }
        }
    }
    // close the raw file
    fclose(raw_file);
}