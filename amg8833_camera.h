#include "esphome.h"
#include <SparkFun_GridEYE_Arduino_Library.h>
#include <base64.h>

class AMG8833CameraComponent : public PollingComponent, public TextSensor
{
public:
    AMG8833CameraComponent() : PollingComponent(1000) {}

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
        std::string payload;

        for (unsigned char i = 0; i < total_pixels; i++)
        {
            payload += grideye.getPixelTemperatureRaw(i);
        }
        String encoded = base64::encode(payload.c_str());
        payload = "";
        payload += encoded.c_str();
        publish_state(payload);
    }

protected:
    GridEYE grideye;
    static const int size = 8;
    static const int total_pixels = size * size;
};
