#define _POSIX_C_SOURCE 200809L
#include "fax_platform.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

static fax_video_config_t g_cfg;
static int g_video_ready = 0;

int video_init(const fax_video_config_t *cfg)
{
    if (cfg == NULL || cfg->width <= 0 || cfg->height <= 0 || cfg->bpp <= 0) {
        return -1;
    }

    memset(&g_cfg, 0, sizeof(g_cfg));
    g_cfg = *cfg;
    g_video_ready = 1;
    log_printf("video_init: %dx%d %dbpp mode=%d\n", cfg->width, cfg->height, cfg->bpp, (int)cfg->mode);
    return 0;
}

int video_present(const uint8_t *framebuffer, size_t framebuffer_size)
{
    if (!g_video_ready || framebuffer == NULL || framebuffer_size == 0U) {
        return -1;
    }

    switch (g_cfg.mode) {
    case FAX_OUTPUT_FB:
        return fax_fb_draw_checkerboard(g_cfg.width, g_cfg.height, 8);
    case FAX_OUTPUT_PRINTER:
        return fax_printer_write_pbm(g_cfg.output_path ? g_cfg.output_path : "fax_frame.pbm", g_cfg.width, g_cfg.height, 1);
    case FAX_OUTPUT_STREAM:
        return fax_stream_write_pbm_frame(STDOUT_FILENO, g_cfg.width, g_cfg.height, (int)(time_now_ms() % 255U));
    default:
        (void)framebuffer;
        (void)framebuffer_size;
        return -1;
    }
}

void video_shutdown(void)
{
    g_video_ready = 0;
}

void timing_sleep_ms(uint32_t ms)
{
    struct timespec req;
    req.tv_sec = (time_t)(ms / 1000U);
    req.tv_nsec = (long)((ms % 1000U) * 1000000U);
    nanosleep(&req, NULL);
}

uint64_t time_now_ms(void)
{
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return ((uint64_t)now.tv_sec * 1000ULL) + (uint64_t)(now.tv_nsec / 1000000L);
}

void log_printf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
}
