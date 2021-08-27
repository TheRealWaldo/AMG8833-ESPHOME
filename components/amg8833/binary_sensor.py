import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor
from esphome.const import (
    DEVICE_CLASS_OCCUPANCY,
    CONF_DEVICE_CLASS,
)
from . import AMG8833, CONF_AMG8833_ID

CODEOWNERS = ["@TheRealWaldo"]
DEPENDENCIES = ["amg8833"]
AUTO_LOAD = ["binary_sensor"]


CONFIG_SCHEMA = (
    binary_sensor.BINARY_SENSOR_SCHEMA.extend({
        cv.GenerateID(CONF_AMG8833_ID): cv.use_id(AMG8833),
        cv.Optional(CONF_DEVICE_CLASS, default=DEVICE_CLASS_OCCUPANCY): binary_sensor.device_class,
    })
)


async def to_code(config):
    hub = await cg.get_variable(config[CONF_AMG8833_ID])
    var = await binary_sensor.new_binary_sensor(config)
    cg.add(hub.set_person_detected_sensor(var))
