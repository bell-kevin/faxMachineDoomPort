#include "fax_platform.h"

#include <stdio.h>

int main(int argc, char **argv)
{
    const char *out = (argc > 1) ? argv[1] : "fax_printer_test.pbm";
    if (fax_printer_write_pbm(out, 384, 240, 1) != 0) {
        fprintf(stderr, "Printer raster PBM generation failed.\n");
        return 1;
    }

    printf("Generated raster image: %s\n", out);
    return 0;
}
