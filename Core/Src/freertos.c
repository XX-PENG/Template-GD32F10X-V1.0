#include "FreeRTOS.h"
#include "task.h"
#include "main.h"


static TaskHandle_t defaultTaskHandle;

static void StartDefaultTask(void *argument);


void FREERTOS_Init(void)
{

    if (xTaskCreate(StartDefaultTask,
                    "defaultTask",
                    configMINIMAL_STACK_SIZE,
                    NULL,
                    tskIDLE_PRIORITY + 1U,
                    &defaultTaskHandle) != pdPASS) 
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
        vTaskDelay(pdMS_TO_TICKS(500));
        gpio_bit_write(LED_GPIO_PORT, LED_GPIO_PIN, RESET);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}