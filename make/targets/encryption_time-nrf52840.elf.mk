ifeq (1,$(includecount))

include make/config/target-nrf52840.mk
include make/config/lib-tinyprintf.mk

MODULES += \
	src \
	src/uart

LDFLAGS += \
	-Tsrc/ld/nrf52840.ld

APPS += encryption_time-nrf52840.elf

endif