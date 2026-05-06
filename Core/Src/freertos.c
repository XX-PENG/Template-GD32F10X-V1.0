#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os2.h"


osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTaskAttributes = {
    .name = "defaultTask",
    .stack_size = configMINIMAL_STACK_SIZE * sizeof(uint32_t),
    .priority = (osPriority_t) osPriorityNormal
};

static void StartDefaultTask(void *argument);


void FREERTOS_Init(void)
{
    defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTaskAttributes);
    if (defaultTaskHandle == NULL)
    {
        while(1) {}
    }
}

static void StartDefaultTask(void *argument)
{
    (void)argument;

    while(1)
    {
        gpio_bit_write(LED_GPIO_PORT, LED_GPIO_PIN, SET);
        osDelay(500);
        gpio_bit_write(LED_GPIO_PORT, LED_GPIO_PIN, RESET);
        osDelay(500);
    }
}