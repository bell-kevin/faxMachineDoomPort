CROSS_COMPILE ?= mips-linux-gnu-
CC := $(CROSS_COMPILE)gcc
AR := $(CROSS_COMPILE)ar
STRIP := $(CROSS_COMPILE)strip
CFLAGS_OPT := -Os -march=mips32 -ffunction-sections -fdata-sections
