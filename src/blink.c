#pragma GCC optimize ("O0")

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <hardware/regs/intctrl.h>
#include <stdio.h>
#include <pico/stdlib.h>

#define PICO_LED_PIN 10
#define IN_PIN  9

#ifndef LED_DELAY_MS
#define LED_DELAY_MS 100
#endif

QueueHandle_t msg_queue;

// Consumes 33mA
void busy_tight_loop()
{
    while(1)
    {
        uint32_t k;

        for(int i = 0; i < 30;)
        {
            uint32_t j = 0;
            j = ((~j >> i) + 1) * 27644437;
            k = j;
        }
    }
}

// Perform initialisation
int pico_gpio_init(void) {
    // A device like Pico that uses a GPIO for the LED will define PICO_LED_PIN
    // so we can use normal GPIO functionality to turn the led on and off
    gpio_init(PICO_LED_PIN);
    gpio_set_dir(PICO_LED_PIN, GPIO_OUT);

    gpio_init(IN_PIN);
    gpio_set_dir(IN_PIN, GPIO_IN);
    return PICO_OK;
}

// Turn the led on or off
void pico_set_led(bool led_on) {
    gpio_put(PICO_LED_PIN, led_on);
}

// Consumes 33 mA
void blink_led_task(void *params)
{
    while (true) {
        pico_set_led(true);
        vTaskDelay(pdTICKS_TO_MS(LED_DELAY_MS));
        pico_set_led(false);
        vTaskDelay(pdTICKS_TO_MS(LED_DELAY_MS));
    }
}

// Consumes 28 mA
void blink_led_loop()
{
    while (true) {
        pico_set_led(true);
        sleep_ms(LED_DELAY_MS);
        pico_set_led(false);
        sleep_ms(LED_DELAY_MS);
    }
}

// Consumes 32 mA
void toggle_task(__unused void *params){
    for(;;){
    int toggle_value;
    xQueueReceiveFromISR(msg_queue, &toggle_value,NULL);
        if (toggle_value & GPIO_IRQ_EDGE_RISE) {
            pico_set_led(true);
        } else if (toggle_value & GPIO_IRQ_EDGE_FALL) {
            pico_set_led(false);
        }
    }
}

void irq_callback(uint gpio, uint32_t event_mask)
{
    xQueueSendFromISR(msg_queue,&event_mask,NULL);
}

void main()
{
    // stdio_init_all();
    
    int rc = pico_gpio_init();
    hard_assert(rc == PICO_OK);

    // msg_queue = xQueueCreate(10,sizeof(int));
    // xTaskCreate(toggle_task, "Toggle Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1UL, NULL);
    // gpio_set_irq_enabled_with_callback(IN_PIN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL , true, irq_callback);

    // blink_led_loop();

    // xTaskCreate(blink_led_task, "Blink Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1UL, NULL);
    
    // vTaskStartScheduler();

    busy_tight_loop();

    while(1)
    {
        sleep_ms(1);
    }
}