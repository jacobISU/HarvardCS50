// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "wb");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    // Create array of 1 byte(uint8_t) integers to hold the header file.
    uint8_t header[HEADER_SIZE];

    // Read from the input file 1 byte at a time into the uint_8 array header.
    fread(header, HEADER_SIZE, 1, input);

    // Write from the uint_8 array, each byte into the output file.
    fwrite(header, HEADER_SIZE, 1, output);

    // Read samples from input file and write updated data to output file
    // Create a buffer for a single sample.
    int16_t buffer;

    // Read into buffer, single samples (2 bytes or int16_t) from input while there are samples to
    // be read.
    while (fread(&buffer, sizeof(int16_t), 1, input) != 0)
    {
        // Update the volume
        buffer *= factor;

        // Write from buffer the updated 2byte(int16_t) samples into the output file.
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
