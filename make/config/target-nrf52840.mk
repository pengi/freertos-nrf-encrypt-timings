ifeq (1,$(includecount))

include make/config/target-cortex-m4.mk
include make/config/lib-nrf5-sdk.mk
include make/config/softdevice-s140.mk

# This build is all about freertos, so include it as target, so we here can map
# correct freertos related files too
include make/config/lib-freertos.mk

MODULES +=

SRC += \
	$(FREERTOS)/portable/GCC/nrf52/port.c \
	$(FREERTOS)/portable/CMSIS/nrf52/port_cmsis.c \
	$(FREERTOS)/portable/CMSIS/nrf52/port_cmsis_systick.c \
	$(NRF5_SDK)/modules/nrfx/mdk/gcc_startup_nrf52840.S \
	$(NRF5_SDK)/modules/nrfx/mdk/system_nrf52840.c
	
INC += \
	$(FREERTOS)/portable/GCC/nrf52 \
	$(FREERTOS)/portable/CMSIS/nrf52 \
	$(NRF5_SDK)/modules/nrfx/mdk \
  	$(NRF5_SDK)/components/toolchain/cmsis/include

CFLAGS += \
	-DNRF52840_XXAA

endif