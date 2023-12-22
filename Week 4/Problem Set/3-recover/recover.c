#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

// Define a new type to store a byte of data
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check if the correct number of command-line arguments is provided
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <forensic_image>\n", argv[0]);
        return 1;
    }

    // Open the forensic image for reading
    FILE *raw_file = fopen(argv[1], "r");
    if (raw_file == NULL)
    {
        fprintf(stderr,
                "Could not open forensic image for reading.\n"); // print error message to the standard error stream (stderr)
        return 1;
    }

    // Initialize variables
    BYTE buffer[BLOCK_SIZE];
    FILE *jpeg_file = NULL;
    int jpeg_count = 0;

    // Read the forensic image block by block
    while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        // Check for the start of a new JPEG file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Close the previous JPEG file if it's open
            if (jpeg_file != NULL)
            {
                fclose(jpeg_file);
            }

            // Create a new JPEG file
            char filename[8];
            sprintf(filename, "%03d.jpg", jpeg_count); // generate the filename for the JPEG file
            jpeg_file = fopen(filename, "w");
            if (jpeg_file == NULL)
            {
                fprintf(stderr, "Could not create JPEG file.\n");
                fclose(raw_file);
                return 1;
            }

            // Increment the JPEG count
            jpeg_count++;
        }

        // Write the buffer to the current JPEG file if it's open
        if (jpeg_file != NULL)
        {
            fwrite(buffer, 1, BLOCK_SIZE, jpeg_file);
        }
    }

    // Close the files
    if (jpeg_file != NULL)
    {
        fclose(jpeg_file);
    }
    fclose(raw_file);

    return 0;
}
