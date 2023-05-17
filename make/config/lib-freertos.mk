ifeq (1,$(includecount))

# depends on nrf5-sdk only for providing the freertos source
include make/config/lib-nrf5-sdk.mk

FREERTOS = $(NRF5_SDK)/external/freertos

SRC += \
	$(FREERTOS)/source/list.c \
	$(FREERTOS)/source/queue.c \
	$(FREERTOS)/source/stream_buffer.c \
	$(FREERTOS)/source/tasks.c \
	$(FREERTOS)/source/timers.c \
	$(FREERTOS)/source/portable/MemMang/heap_1.c

INC += \
	$(FREERTOS)/source/include
	
CFLAGS += \
	-DFREERTOS

endif