/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <driver/gpio.h>

#define GPIO_OUTPUT_PIN 16
#define GPIO_OUTPUT_PIN_SEL  (1UL << GPIO_OUTPUT_PIN)

TaskHandle_t blink_task_handle;

static void blink_task(void *pvParam){

    while(1){
        gpio_set_level(GPIO_OUTPUT_PIN,0);
       vTaskDelay(pdMS_TO_TICKS(500));
        gpio_set_level(GPIO_OUTPUT_PIN,1);
        vTaskDelay(pdMS_TO_TICKS(500));
        
         
    }
}

void app_main()
{
    gpio_config_t io_conf;
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set,e.g.GPIO15/16
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = 0;
    //configure GPIO with the given settings
    gpio_config(&io_conf);

    
    xTaskCreate(blink_task,
                "Task to blink in-built LED",
                1000,
                NULL,
                1,
                &blink_task_handle);

    /* Scheduler starting is automatic */
    while(1){
        

    }
}
