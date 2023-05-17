#include "FreeRTOS.h"
#include "task.h"

#include "encrypt.h"

#include "log.h"
#include "uart.h"

#include "nrf.h"
#include "nrf_sdh.h"
#include "nrf_sdh_freertos.h"
#include "nrf_drv_clock.h"

static void start_softdevice(
    void)
{
    ret_code_t err_code;

    /* Initialize clock driver for better time accuracy in FREERTOS */
    err_code = nrf_drv_clock_init();
    configASSERT(err_code == NRFX_SUCCESS);

    nrf_sdh_freertos_init(NULL, NULL);
    ret_code_t err = nrf_sdh_enable_request();
    configASSERT(err == NRF_SUCCESS);
}

static void main_task(
    void *pv_param)
{

    log_line(" ");
    log_line("Encryption time test application");
    log_line("================================");
    log_line(" ");

    encrypt_init();
    for (;;) {
        vTaskDelay(pdMS_TO_TICKS(200));
        encrypt_run();
    }
}

int main(
    void)
{
    start_softdevice();
    vPortInitialiseBlocks();

    /* Initialize serial port for debug interface */
    uart_init(&(const uart_config_t) {
        .baudrate = UART_BAUDRATE_BAUDRATE_Baud1M,
        .pin_txd = 6,
        .pin_rxd = 0xffffffff,
        .irq_priority = 6
    });
    log_init();

    xTaskCreate(main_task, "main", 1024, NULL, 1, NULL);
    vTaskStartScheduler();
    return 0;
}