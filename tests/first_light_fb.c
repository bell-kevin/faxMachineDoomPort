#include "fax_platform.h"

#include <stdio.h>

int main(void)
{
    int rc = fax_fb_draw_checkerboard(320, 240, 16);
    if (rc != 0) {
        fprintf(stderr, "Framebuffer test failed; check /dev/fb0 permissions and device support.\n");
        return 1;
    }

    printf("Framebuffer checkerboard drawn successfully.\n");
    return 0;
}
