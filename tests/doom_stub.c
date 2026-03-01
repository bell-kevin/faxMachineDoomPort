#include "fax_platform.h"

#include <stdint.h>
#include <string.h>

#define W 160
#define H 100

static uint8_t framebuffer[W * H];

int main(void)
{
    fax_video_config_t cfg = {
        .width = W,
        .height = H,
        .bpp = 8,
        .mode = FAX_OUTPUT_STREAM,
        .output_path = NULL,
    };

    if (video_init(&cfg) != 0) {
        return 1;
    }

    for (int frame = 0; frame < 8; ++frame) {
        memset(framebuffer, (uint8_t)(frame * 16), sizeof(framebuffer));
        if (video_present(framebuffer, sizeof(framebuffer)) != 0) {
            video_shutdown();
            return 1;
        }
        timing_sleep_ms(33);
    }

    video_shutdown();
    return 0;
}
