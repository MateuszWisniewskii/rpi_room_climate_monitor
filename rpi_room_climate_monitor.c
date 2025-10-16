#include <dht.h>
#include <pico/stdlib.h>
#include <stdio.h>

static const dht_model_t DHT_MODEL = DHT11;
static const uint DATA_PIN = 15;

static float celsius_to_fahrenheit(float temperature)
{
    return temperature * (9.0f / 5) + 32;
}

int main()
{
    stdio_init_all();
    puts("\nDHT test");

    dht_t dht;
    dht_init(&dht, DHT_MODEL, pio0, DATA_PIN, true /* pull_up */);
    float humidity;
    float temperature_c;
    do
    {
        dht_start_measurement(&dht);

        dht_result_t result = dht_finish_measurement_blocking(&dht, &humidity, &temperature_c);
        if (result == DHT_RESULT_OK)
        {
            printf("%.1f C (%.1f F), %.1f%% humidity\n", temperature_c, celsius_to_fahrenheit(temperature_c), humidity);
        }
        else if (result == DHT_RESULT_TIMEOUT)
        {
            puts("DHT sensor not responding. Please check your wiring.");
        }
        else
        {
            assert(result == DHT_RESULT_BAD_CHECKSUM);
            puts("Bad checksum");
        }

        sleep_ms(2000);
    } while (true);
}
