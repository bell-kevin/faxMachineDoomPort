#ifndef FAX_PLATFORM_H
#define FAX_PLATFORM_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    FAX_OUTPUT_FB = 0,
    FAX_OUTPUT_PRINTER = 1,
    FAX_OUTPUT_STREAM = 2
} fax_output_mode_t;

typedef struct {
    int width;
    int height;
    int bpp;
    fax_output_mode_t mode;
    const char *output_path;
} fax_video_config_t;

typedef struct {
    int key_up;
    int key_down;
    int key_left;
    int key_right;
    int key_use;
    int key_fire;
    int key_menu;
} fax_input_state_t;

int video_init(const fax_video_config_t *cfg);
int video_present(const uint8_t *framebuffer, size_t framebuffer_size);
void video_shutdown(void);

void input_poll(fax_input_state_t *state);

void timing_sleep_ms(uint32_t ms);
uint64_t time_now_ms(void);

void log_printf(const char *fmt, ...);

int fax_fb_draw_checkerboard(int width, int height, int square_size);
int fax_printer_write_pbm(const char *path, int width, int height, int pattern_mode);
int fax_stream_write_pbm_frame(int fd, int width, int height, int frame_index);

#ifdef __cplusplus
}
#endif

#endif
