#include "encrypt.h"
#include "nrf.h"
#include "nrf_soc.h"
#include <string.h>

#define ENCRYPT_IRQn                   SWI3_EGU3_IRQn
#define ENCRYPT_IRQHandler             SWI3_EGU3_IRQHandler

#define ENCRYPT_GPIO_PORT              NRF_P0
#define ENCRYPT_GPIO_ENC_PIN           12
#define ENCRYPT_GPIO_TRIG_PIN          13

/* Some random data, doesn't matter... */
static nrf_ecb_hal_data_t ecb_buf;

void encrypt_init(
    void)
{
    NVIC_SetPriority(ENCRYPT_IRQn, 5);
    NVIC_ClearPendingIRQ(ENCRYPT_IRQn);
    NVIC_EnableIRQ(ENCRYPT_IRQn);

    ENCRYPT_GPIO_PORT->PIN_CNF[ENCRYPT_GPIO_ENC_PIN] =
        (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos)
        | (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos)
        | (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos)
        | (GPIO_PIN_CNF_DRIVE_H0H1 << GPIO_PIN_CNF_DRIVE_Pos);

    ENCRYPT_GPIO_PORT->PIN_CNF[ENCRYPT_GPIO_TRIG_PIN] =
        (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos)
        | (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos)
        | (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos)
        | (GPIO_PIN_CNF_DRIVE_H0H1 << GPIO_PIN_CNF_DRIVE_Pos);
}

void encrypt_run(
    void)
{
    NVIC_SetPendingIRQ(ENCRYPT_IRQn);
}

void ENCRYPT_IRQHandler(
    void)
{
    int i;
    ENCRYPT_GPIO_PORT->OUTSET = 1 << ENCRYPT_GPIO_TRIG_PIN;
    for (i = 0; i < 20; i++) {
        /* Just fill with something */
        memset(&ecb_buf, i, sizeof(nrf_ecb_hal_data_t));
        ENCRYPT_GPIO_PORT->OUTSET = 1 << ENCRYPT_GPIO_ENC_PIN;
        sd_ecb_block_encrypt(&ecb_buf);
        ENCRYPT_GPIO_PORT->OUTCLR = 1 << ENCRYPT_GPIO_ENC_PIN;
    }
    ENCRYPT_GPIO_PORT->OUTCLR = 1 << ENCRYPT_GPIO_TRIG_PIN;
}