#define _POSIX_C_SOURCE 200809L
#include "fax_platform.h"

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

int fax_stream_write_pbm_frame(int fd, int width, int height, int frame_index)
{
    dprintf(fd, "P1\n%d %d\n", width, height);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int px = (((x + frame_index) / 8) ^ ((y + frame_index) / 8)) & 1;
            dprintf(fd, "%d ", px);
        }
        dprintf(fd, "\n");
    }
    return 0;
}
