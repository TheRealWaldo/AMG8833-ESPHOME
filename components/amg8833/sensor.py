import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import (
    DEVICE_CLASS_TEMPERATURE,
    ICON_THERMOMETER,
    ICON_EMPTY,
    STATE_CLASS_MEASUREMENT,
    UNIT_CELSIUS,
    UNIT_EMPTY,
)
from . import AMG8833, CONF_AMG8833_ID

CODEOWNERS = ["@TheRealWaldo"]
DEPENDENCIES = ["amg8833"]
AUTO_LOAD = ["sensor"]

CONF_SENSOR_TEMP_SENSOR = 'sensor_temp'
CONF_MAX_TEMP_SENSOR = 'max_temp'
CONF_MIN_TEMP_SENSOR = 'min_temp'
CONF_AVG_TEMP_SENSOR = 'avg_temp'
CONF_MIN_INDEX_SENSOR = 'min_index'
CONF_MAX_INDEX_SENSOR = 'max_index'

CONFIG_SCHEMA = (
    sensor.SENSOR_SCHEMA.extend({
        cv.GenerateID(CONF_AMG8833_ID): cv.use_id(AMG8833),
        cv.Optional(CONF_SENSOR_TEMP_SENSOR): sensor.sensor_schema(
            icon=ICON_THERMOMETER,
            device_class=DEVICE_CLASS_TEMPERATURE,
            unit_of_measurement=UNIT_CELSIUS,
            accuracy_decimals=2,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_MAX_TEMP_SENSOR): sensor.sensor_schema(
            icon=ICON_THERMOMETER,
            device_class=DEVICE_CLASS_TEMPERATURE,
            unit_of_measurement=UNIT_CELSIUS,
            accuracy_decimals=1,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_MIN_TEMP_SENSOR): sensor.sensor_schema(
            icon=ICON_THERMOMETER,
            device_class=DEVICE_CLASS_TEMPERATURE,
            unit_of_measurement=UNIT_CELSIUS,
            accuracy_decimals=1,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_AVG_TEMP_SENSOR): sensor.sensor_schema(
            icon=ICON_THERMOMETER,
            device_class=DEVICE_CLASS_TEMPERATURE,
            unit_of_measurement=UNIT_CELSIUS,
            accuracy_decimals=1,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_MIN_INDEX_SENSOR): sensor.sensor_schema(
            icon=ICON_EMPTY,
            unit_of_measurement=UNIT_EMPTY,
            accuracy_decimals=0,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_MAX_INDEX_SENSOR): sensor.sensor_schema(
            icon=ICON_EMPTY,
            unit_of_measurement=UNIT_EMPTY,
            accuracy_decimals=0,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
    })
)


async def to_code(config):
    hub = await cg.get_variable(config[CONF_AMG8833_ID])

    if CONF_SENSOR_TEMP_SENSOR in config:
        var = await sensor.new_sensor(config[CONF_SENSOR_TEMP_SENSOR])
        cg.add(hub.set_sensor_temperature_sensor(var))

    if CONF_MAX_TEMP_SENSOR in config:
        var = await sensor.new_sensor(config[CONF_MAX_TEMP_SENSOR])
        cg.add(hub.set_max_temperature_sensor(var))

    if CONF_MIN_TEMP_SENSOR in config:
        var = await sensor.new_sensor(config[CONF_MIN_TEMP_SENSOR])
        cg.add(hub.set_min_temperature_sensor(var))

    if CONF_AVG_TEMP_SENSOR in config:
        var = await sensor.new_sensor(config[CONF_AVG_TEMP_SENSOR])
        cg.add(hub.set_avg_temperature_sensor(var))

    if CONF_MIN_INDEX_SENSOR in config:
        var = await sensor.new_sensor(config[CONF_MIN_INDEX_SENSOR])
        cg.add(hub.set_min_index_sensor(var))

    if CONF_MAX_INDEX_SENSOR in config:
        var = await sensor.new_sensor(config[CONF_MAX_INDEX_SENSOR])
        cg.add(hub.set_max_index_sensor(var))
