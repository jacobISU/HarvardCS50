#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Accepts one command-line argument for forensic image.
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // open memory card
    FILE *card = fopen(argv[1], "rb");

    // Initialize output file as not opened.
    FILE *output = NULL;

    // if card is open
    if (card != NULL)
    {
        // Create buffer for a block of data
        uint8_t buffer[512];

        // file number name
        int count = 0;

        // While there's still data left to read from the memory card
        // fread(first address to read, analyze 1 byte at a time, from a 512 byte chunk, from this
        // file)
        while (fread(buffer, 1, 512, card) == 512)
        {
            // if first 4 bytes are that of a JPEG
            if ((buffer[0] == 255) &&                // 0xff
                (buffer[1] == 216) &&                // 0xd8
                (buffer[2] == 255) &&                // 0xff
                (buffer[3] > 223 && buffer[3] < 240) // 0xe0 to 0xef
            )
            {
                // if output file is already being wrote to. Close it for new JPEG.
                if (output != NULL)
                {
                    fclose(output);
                }

                char output_name[8];
                sprintf(output_name, "%03i.jpg", count++);
                output = fopen(output_name, "wb");
                fwrite(buffer, 1, 512, output);
            }
            // Keep writing from same JPEG.
            else
            {
                if (output != NULL)
                {
                    fwrite(buffer, 1, 512, output);
                }
            }
        }

        // Close all files.
        fclose(card);
        fclose(output);
    }
    else
    {
        printf("File did not open\n");
        return 1;
    }
}
