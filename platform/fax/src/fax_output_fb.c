#include "fax_platform.h"

#include <errno.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

int fax_fb_draw_checkerboard(int width, int height, int square_size)
{
    int fd = open("/dev/fb0", O_RDWR);
    if (fd < 0) {
        perror("open /dev/fb0");
        return -1;
    }

    struct fb_fix_screeninfo finfo;
    struct fb_var_screeninfo vinfo;
    if (ioctl(fd, FBIOGET_FSCREENINFO, &finfo) != 0 || ioctl(fd, FBIOGET_VSCREENINFO, &vinfo) != 0) {
        perror("ioctl FBIOGET_*SCREENINFO");
        close(fd);
        return -1;
    }

    long screen_size = (long)finfo.smem_len;
    uint8_t *fbp = (uint8_t *)mmap(NULL, (size_t)screen_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (fbp == MAP_FAILED) {
        perror("mmap framebuffer");
        close(fd);
        return -1;
    }

    int w = (width > 0 && width < (int)vinfo.xres) ? width : (int)vinfo.xres;
    int h = (height > 0 && height < (int)vinfo.yres) ? height : (int)vinfo.yres;

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            int checker = ((x / square_size) + (y / square_size)) & 1;
            uint8_t val = checker ? 0xFFU : 0x00U;
            long location = (long)(x + (int)vinfo.xoffset) * (vinfo.bits_per_pixel / 8) +
                            (long)(y + (int)vinfo.yoffset) * (long)finfo.line_length;

            if (location >= 0 && location + (vinfo.bits_per_pixel / 8) <= screen_size) {
                if (vinfo.bits_per_pixel == 16) {
                    uint16_t rgb565 = checker ? 0xFFFFU : 0x0000U;
                    *((uint16_t *)(fbp + location)) = rgb565;
                } else if (vinfo.bits_per_pixel == 32) {
                    *((uint32_t *)(fbp + location)) = (uint32_t)(val << 16 | val << 8 | val);
                } else {
                    fbp[location] = val;
                }
            }
        }
    }

    munmap(fbp, (size_t)screen_size);
    close(fd);
    return 0;
}
