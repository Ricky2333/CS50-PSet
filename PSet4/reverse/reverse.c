#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3 || (strstr(argv[1], ".wav") == NULL) || (strstr(argv[2], ".wav") == NULL))
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }

    // Read header
    // TODO #3
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, inptr);

    // Use check_format to ensure WAV format
    // TODO #4
    if (!check_format(header))
    {
        printf("This file is not a wav file\n");
        return 1;
    }

    // Open output file for writing
    // TODO #5
    FILE *outptr = fopen(argv[2], "w");
    if (outptr == NULL)
    {
        printf("Could not open %s\n", argv[2]);
        return 1;
    }

    // Write header to file
    // TODO #6
    fwrite(&header, sizeof(WAVHEADER), 1, outptr);

    // Use get_block_size to calculate size of block
    // TODO #7
    int block_size = get_block_size(header);

    // Write reversed audio to file
    // TODO #8
    BYTE buffer[block_size];
    // move the pointer to the last block
    fseek(inptr, -block_size, SEEK_END);
    do
    {
        // read 1 block of data from the input file
        fread(buffer, block_size, 1, inptr);

        // move the pointer to previois block
        fseek(inptr, -2 * block_size, SEEK_CUR);

        // write this block of data to the output file
        fwrite(buffer, block_size, 1, outptr);
    }
    while (ftell(inptr) >= sizeof(header));
    // another way to implement this part
    // if you read the mannual of wav, you can find "subchunk2Size = block_num * block_size"
    // for (int i = 0; i < header.subchunk2Size / block_size; i++)
    // {
    //     fread(buffer, block_size, 1, inptr);
    //     fseek(inptr, -2 * block_size, SEEK_CUR);
    //     fwrite(buffer, block_size, 1, outptr);
    // }

    // close files
    fclose(inptr);
    fclose(outptr);
}

// Use check_format to ensure WAV format
int check_format(WAVHEADER header)
{
    // TODO #4
    if (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E')
    {
        return 1;
    }
    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    return header.numChannels * header.bitsPerSample / 8;
}