#include "esphome.h"
#include <SparkFun_GridEYE_Arduino_Library.h>

class AMG8833Component : public PollingComponent
{
public:
    AMG8833Component() : PollingComponent(60000) {}
    Sensor *sensor_temperature = new Sensor();
    Sensor *max_temperature = new Sensor();
    Sensor *min_temperature = new Sensor();
    Sensor *avg_temperature = new Sensor();
    Sensor *min_index = new Sensor();
    Sensor *max_index = new Sensor();

    float get_setup_priority() const override { return esphome::setup_priority::BUS; }

    void setup() override
    {
        Wire.begin();
        grideye.begin();
    }

    void loop() override
    {
    }

    void update() override
    {
        float pixel_temperature;
        float min = 0;
        float max = 0;
        float avg = 0;
        unsigned char local_min_index = 0;
        unsigned char local_max_index = 0;

        for (unsigned char i = 0; i < total_pixels; i++)
        {
            pixel_temperature = grideye.getPixelTemperature(i);
            if (i == 0 || pixel_temperature > max)
            {
                max = pixel_temperature;
                local_max_index = i;
            }
            if (i == 0 || pixel_temperature < min)
            {
                min = pixel_temperature;
                local_min_index = i;
            }
            avg += pixel_temperature;
        }
        avg = avg / total_pixels;
        max_temperature->publish_state(max);
        min_temperature->publish_state(min);
        min_index->publish_state(local_min_index);
        max_index->publish_state(local_max_index);
        avg_temperature->publish_state(avg);
        sensor_temperature->publish_state(grideye.getDeviceTemperature());
    }

protected:
    GridEYE grideye;
    static const int size = 8;
    static const int total_pixels = size * size;
};
