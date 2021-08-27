import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import text_sensor
from esphome.const import (
    CONF_ID,
)
from . import AMG8833, CONF_AMG8833_ID

CODEOWNERS = ["@TheRealWaldo"]
DEPENDENCIES = ["amg8833"]
AUTO_LOAD = ["text_sensor"]

CONF_CAMERA_SENSOR = "camera_sensor"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_AMG8833_ID): cv.use_id(AMG8833),
        cv.Optional(CONF_CAMERA_SENSOR): text_sensor.TEXT_SENSOR_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(text_sensor.TextSensor),
            }
        )
    }
)


async def to_code(config):
    hub = await cg.get_variable(config[CONF_AMG8833_ID])
    if CONF_CAMERA_SENSOR in config:
        var = cg.new_Pvariable(config[CONF_CAMERA_SENSOR][CONF_ID])

        await text_sensor.register_text_sensor(var, config[CONF_CAMERA_SENSOR])
        cg.add(hub.set_camera_text_sensor(var))
