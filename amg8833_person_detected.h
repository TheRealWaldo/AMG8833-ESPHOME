#include "esphome.h"
#include <SparkFun_GridEYE_Arduino_Library.h>

class AMG8833PersonDetectedComponent : public PollingComponent, public BinarySensor
{
public:
    float get_setup_priority() const override { return esphome::setup_priority::BUS; }
    AMG8833PersonDetectedComponent() : PollingComponent(100) {}

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
        }
        if (max - min > 4)
        {
            if (!last_state)
            {
                publish_state(true);
                delay_count = delay;
            }
            last_state = true;
        }
        else
        {
            if (last_state)
            {
                delay_count--;
                if (delay_count <= 0)
                {
                    publish_state(false);
                    last_state = false;
                }
            }
        }
    }

protected:
    GridEYE grideye;
    static const int size = 8;
    static const int total_pixels = size * size;
    static const int delay = 50;
    int delay_count = delay;
    bool last_state = false;
};
