#include "fax_platform.h"

#include <stdint.h>
#include <stdio.h>

static int pixel_for_mode(int x, int y, int mode)
{
    if (mode == 0) {
        return ((x / 8) + (y / 8)) & 1;
    }
    return (((x ^ y) + (y / 3)) & 7) < 4;
}

int fax_printer_write_pbm(const char *path, int width, int height, int pattern_mode)
{
    FILE *fp = fopen(path, "wb");
    if (!fp) {
        perror("fopen pbm output");
        return -1;
    }

    fprintf(fp, "P4\n%d %d\n", width, height);
    for (int y = 0; y < height; ++y) {
        uint8_t byte = 0;
        int bit_count = 0;
        for (int x = 0; x < width; ++x) {
            int pixel = pixel_for_mode(x, y, pattern_mode) ? 1 : 0;
            byte = (uint8_t)((byte << 1) | (uint8_t)pixel);
            bit_count++;
            if (bit_count == 8) {
                fwrite(&byte, 1, 1, fp);
                bit_count = 0;
                byte = 0;
            }
        }
        if (bit_count != 0) {
            byte <<= (uint8_t)(8 - bit_count);
            fwrite(&byte, 1, 1, fp);
        }
    }

    fclose(fp);
    return 0;
}
