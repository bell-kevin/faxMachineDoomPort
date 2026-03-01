#include "fax_platform.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    int frames = 4;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--frames") == 0 && i + 1 < argc) {
            frames = atoi(argv[++i]);
        }
    }

    for (int i = 0; i < frames; ++i) {
        if (fax_stream_write_pbm_frame(1, 96, 64, i) != 0) {
            fprintf(stderr, "Stream frame generation failed at frame %d\n", i);
            return 1;
        }
    }
    return 0;
}
