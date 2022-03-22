/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_task_wdt.h"

#ifdef __cplusplus
}
#endif

#include <driver/gpio.h>
#include <driver/uart.h>


#define BUFFER_SIZE 1024

#define GPIO_OUTPUT_PIN (gpio_num_t) 16
#define GPIO_OUTPUT_PIN_SEL  (1UL << GPIO_OUTPUT_PIN)

#define EX_UART_NUM UART_NUM_0

#define UART_QUEUE_SIZE 50

xTaskHandle blink_task_handle;
xTaskHandle debug_task_handle;

xQueueHandle uart0_queue;

void debug_task(void *pvParam){
    const char test_message[] = "Debug over ESP8266 \n";
    while(1){
        uart_write_bytes(EX_UART_NUM, test_message, sizeof(test_message)/sizeof(char));
        esp_task_wdt_reset();
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

extern "C" void app_main() {

    /* Configure debug UART */
    uart_config_t debug_uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };

    uart_param_config(EX_UART_NUM, &debug_uart_config);
    uart_driver_install(EX_UART_NUM, (BUFFER_SIZE * 2), (BUFFER_SIZE * 2), UART_QUEUE_SIZE, &uart0_queue, 0);

    /* Initialize watchdog timer */
    esp_task_wdt_init();

    xTaskCreate(debug_task,
                "Task to handle debug messages over serial",
                1024,
                NULL,
                1,
                &debug_task_handle);

    /* Scheduler starting is automatic */

    while(1){
        

    }
}
