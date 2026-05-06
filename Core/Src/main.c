
#include "main.h"
#include "systick.h"
#include <stdio.h>

#define LED_GPIO_PORT GPIOC
#define LED_GPIO_PIN  GPIO_PIN_13

static void LED_Init(void)
{
    rcu_periph_clock_enable(RCU_GPIOC);
    gpio_init(LED_GPIO_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, LED_GPIO_PIN);
    gpio_bit_set(LED_GPIO_PORT, LED_GPIO_PIN);
}
int main(void)
{
    systick_config();
    LED_Init();

    while(1) {
        // LED 交替闪烁 500ms
        gpio_bit_write(LED_GPIO_PORT, LED_GPIO_PIN, SET);
        delay_1ms(500);
        gpio_bit_write(LED_GPIO_PORT, LED_GPIO_PIN, RESET);
        delay_1ms(500);
    }
}
