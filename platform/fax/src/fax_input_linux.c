#include "fax_platform.h"

#include <fcntl.h>
#include <linux/input.h>
#include <string.h>
#include <unistd.h>

void input_poll(fax_input_state_t *state)
{
    if (state == NULL) {
        return;
    }
    memset(state, 0, sizeof(*state));

    int fd = open("/dev/input/event0", O_RDONLY | O_NONBLOCK);
    if (fd < 0) {
        return;
    }

    struct input_event ev;
    while (read(fd, &ev, sizeof(ev)) == (ssize_t)sizeof(ev)) {
        if (ev.type != EV_KEY || ev.value == 0) {
            continue;
        }
        switch (ev.code) {
        case KEY_UP: state->key_up = 1; break;
        case KEY_DOWN: state->key_down = 1; break;
        case KEY_LEFT: state->key_left = 1; break;
        case KEY_RIGHT: state->key_right = 1; break;
        case KEY_ENTER: state->key_use = 1; break;
        case KEY_SPACE: state->key_fire = 1; break;
        case KEY_ESC: state->key_menu = 1; break;
        default: break;
        }
    }

    close(fd);
}
