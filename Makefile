# faxMachineDoomPort top-level build

CC ?= gcc
AR ?= ar
STRIP ?= strip

BUILD_DIR ?= build
CFLAGS_BASE := -std=c11 -Wall -Wextra -Werror -pedantic
CFLAGS_OPT ?= -Os -ffunction-sections -fdata-sections -fno-asynchronous-unwind-tables
CFLAGS_DBG ?= -g
CFLAGS ?= $(CFLAGS_BASE) $(CFLAGS_OPT) $(CFLAGS_DBG)
CPPFLAGS ?= -Iplatform/fax/include
LDFLAGS ?= -Wl,--gc-sections
LDLIBS ?=

PLATFORM_SRCS := \
	platform/fax/src/fax_platform_posix.c \
	platform/fax/src/fax_output_fb.c \
	platform/fax/src/fax_output_printer.c \
	platform/fax/src/fax_output_stream.c \
	platform/fax/src/fax_input_linux.c

PLATFORM_OBJS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(PLATFORM_SRCS))
PLATFORM_LIB := $(BUILD_DIR)/libfaxplatform.a

TEST_BINS := \
	$(BUILD_DIR)/first_light_fb \
	$(BUILD_DIR)/first_light_printer \
	$(BUILD_DIR)/first_light_stream

.PHONY: all clean help doom_stub

all: $(TEST_BINS)

help:
	@echo "Targets:"
	@echo "  make all                  Build first-light tests"
	@echo "  make doom_stub            Verify platform layer links with a Doom-like loop"
	@echo "  make clean                Remove build outputs"

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(PLATFORM_LIB): $(PLATFORM_OBJS)
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $^

$(BUILD_DIR)/first_light_fb: tests/first_light_fb.c $(PLATFORM_LIB)
	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(PLATFORM_LIB) $(LDFLAGS) $(LDLIBS) -o $@

$(BUILD_DIR)/first_light_printer: tests/first_light_printer.c $(PLATFORM_LIB)
	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(PLATFORM_LIB) $(LDFLAGS) $(LDLIBS) -o $@

$(BUILD_DIR)/first_light_stream: tests/first_light_stream.c $(PLATFORM_LIB)
	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(PLATFORM_LIB) $(LDFLAGS) $(LDLIBS) -o $@

doom_stub: tests/doom_stub.c $(PLATFORM_LIB)
	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(PLATFORM_LIB) $(LDFLAGS) $(LDLIBS) -o $(BUILD_DIR)/doom_stub
	$(STRIP) $(BUILD_DIR)/doom_stub || true

clean:
	rm -rf $(BUILD_DIR)
