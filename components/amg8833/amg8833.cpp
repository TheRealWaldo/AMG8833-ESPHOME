#include "amg8833.h"
#include <base64.h>

namespace esphome
{
  namespace amg8833
  {

    void AMG8833::setup()
    {
      Wire.begin();
      grideye.begin();
    }

    void AMG8833::loop()
    {
    }

    void AMG8833::update()
    {
      float pixel_temperature;
      float min = 0;
      float max = 0;
      float avg = 0;
      unsigned char local_min_index = 0;
      unsigned char local_max_index = 0;
      std::string payload;

      for (unsigned char i = 0; i < total_pixels; i++)
      {
        pixel_temperature = grideye.getPixelTemperature(i);
        payload += grideye.getPixelTemperatureRaw(i);
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

      if (max - min > 4)
      {
        if (!last_state)
        {
          this->person_detected_sensor_->publish_state(true);
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
            this->person_detected_sensor_->publish_state(false);
            last_state = false;
          }
        }
      }

      String encoded = base64::encode(payload.c_str());
      payload = "";
      payload += encoded.c_str();
      this->camera_text_sensor_->publish_state(payload);

      avg = avg / total_pixels;
      this->max_temperature_sensor_->publish_state(max);
      this->min_temperature_sensor_->publish_state(min);
      this->min_index_sensor_->publish_state(local_min_index);
      this->max_index_sensor_->publish_state(local_max_index);
      this->avg_temperature_sensor_->publish_state(avg);
      this->sensor_temperature_sensor_->publish_state(grideye.getDeviceTemperature());
    }
  }
}
