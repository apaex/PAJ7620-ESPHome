import esphome.codegen as cg
from esphome.components import i2c, text_sensor
import esphome.config_validation as cv
from esphome.const import (
    CONF_ID,
)

CODEOWNERS = ["@apaex"]
#DEPENDENCIES = ["i2c"]
AUTO_LOAD = [ "text_sensor" ]
CONF_GESTURE = "gesture"


ns = cg.esphome_ns.namespace("paj7620")
PAJ7620 = ns.class_("PAJ7620", cg.PollingComponent)


CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(PAJ7620),
            cv.Optional(CONF_GESTURE): text_sensor.text_sensor_schema(
                icon="mdi:hand-clap"
            )
        }
    )

    .extend(cv.polling_component_schema("100ms"))
#    .extend(i2c.i2c_device_schema(0x73))
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
#    await i2c.register_i2c_device(var, config)

    if gesture_config := config.get(CONF_GESTURE):
        sens = await text_sensor.new_text_sensor(gesture_config)
        cg.add(var.set_gesture_text_sensor(sens))

    cg.add_library("Wire", "*")


