
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"


void FREERTOS_Init(void);

static void GPIO_Init(void)
{
    rcu_periph_clock_enable(RCU_GPIOC);
    gpio_init(LED_GPIO_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, LED_GPIO_PIN);
    gpio_bit_set(LED_GPIO_PORT, LED_GPIO_PIN);
}

int main(void)
{
    GPIO_Init();
    FREERTOS_Init();

    vTaskStartScheduler();

    while(1)
    {
    }
}
