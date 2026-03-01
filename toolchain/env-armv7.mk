CROSS_COMPILE ?= arm-linux-gnueabihf-
CC := $(CROSS_COMPILE)gcc
AR := $(CROSS_COMPILE)ar
STRIP := $(CROSS_COMPILE)strip
CFLAGS_OPT := -Os -mcpu=cortex-a7 -mthumb -ffunction-sections -fdata-sections
