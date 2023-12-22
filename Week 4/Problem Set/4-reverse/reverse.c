#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s input.wav output.wav\n", argv[0]);
        return 1;
    }

    // Open input file for reading
    FILE *input_file = fopen(argv[1], "rb");
    if (input_file == NULL)
    {
        fprintf(stderr, "Could not open input file.\n");
        return 1;
    }

    // Read header
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, input_file);

    // Use check_format to ensure WAV format
    if (!check_format(header))
    {
        fprintf(stderr, "Input file is not in WAV format.\n");
        fclose(input_file);
        return 1;
    }

    // Open output file for writing
    FILE *output_file = fopen(argv[2], "wb");
    if (output_file == NULL)
    {
        fprintf(stderr, "Could not open output file.\n");
        fclose(input_file);
        return 1;
    }

    // Write header to file
    fwrite(&header, sizeof(WAVHEADER), 1, output_file);

    // Use get_block_size to calculate size of block
    int block_size = get_block_size(header);

    // Write reversed audio to file
    fseek(input_file, 0, SEEK_END);                 // Move file pointer to the end
    long file_size = ftell(input_file);             // Get file size
    fseek(input_file, sizeof(WAVHEADER), SEEK_SET); // Move file pointer back to audio data start

    // Iterate through audio data and write reversed blocks
    for (long pos = file_size - block_size; pos >= sizeof(WAVHEADER); pos -= block_size)
    {
        fseek(input_file, pos, SEEK_SET);        // Move file pointer to current block
        uint8_t *block = malloc(block_size);     // Allocate memory for the block
        fread(block, 1, block_size, input_file); // Read the block from the input file

        fwrite(block, 1, block_size, output_file); // Write the reversed block to the output file
        free(block);                               // Free allocated memory
    }

    // Close files
    fclose(input_file);
    fclose(output_file);

    return 0;
}

int check_format(WAVHEADER header)
{
    // Check if the format is WAV by comparing the format field to "WAVE"
    return (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E');
}

int get_block_size(WAVHEADER header)
{
    // Calculate block size in bytes (number of channels * bytes per sample)
    return header.numChannels * (header.bitsPerSample / 8);
}
