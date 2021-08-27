#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/i2c/i2c.h"
#include <SparkFun_GridEYE_Arduino_Library.h>

namespace esphome
{
    namespace amg8833
    {
        class AMG8833 : public PollingComponent, public i2c::I2CDevice
        {
        public:
            float get_setup_priority() const override { return esphome::setup_priority::BUS; }
            void setup() override;
            void loop() override;
            void update() override;

            void set_person_detected_sensor(binary_sensor::BinarySensor *person_detected_sensor) { person_detected_sensor_ = person_detected_sensor; }
            void set_sensor_temperature_sensor(sensor::Sensor *sensor_temperature_sensor) { sensor_temperature_sensor_ = sensor_temperature_sensor; }
            void set_max_temperature_sensor(sensor::Sensor *max_temperature_sensor) { max_temperature_sensor_ = max_temperature_sensor; }
            void set_min_temperature_sensor(sensor::Sensor *min_temperature_sensor) { min_temperature_sensor_ = min_temperature_sensor; }
            void set_avg_temperature_sensor(sensor::Sensor *avg_temperature_sensor) { avg_temperature_sensor_ = avg_temperature_sensor; }
            void set_min_index_sensor(sensor::Sensor *min_index_sensor) { min_index_sensor_ = min_index_sensor; }
            void set_max_index_sensor(sensor::Sensor *max_index_sensor) { max_index_sensor_ = max_index_sensor; }
            void set_camera_text_sensor(text_sensor::TextSensor *camera_text_sensor) { camera_text_sensor_ = camera_text_sensor; }

        protected:
            GridEYE grideye;
            static const int size = 8;
            static const int total_pixels = size * size;
            static const int delay = 50;
            int delay_count = delay;
            bool last_state = false;

            binary_sensor::BinarySensor *person_detected_sensor_{nullptr};
            sensor::Sensor *sensor_temperature_sensor_{nullptr};
            sensor::Sensor *max_temperature_sensor_{nullptr};
            sensor::Sensor *min_temperature_sensor_{nullptr};
            sensor::Sensor *avg_temperature_sensor_{nullptr};
            sensor::Sensor *min_index_sensor_{nullptr};
            sensor::Sensor *max_index_sensor_{nullptr};
            text_sensor::TextSensor *camera_text_sensor_{nullptr};
        };
    }
}
