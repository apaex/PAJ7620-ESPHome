import esphome.codegen as cg
from esphome.components import i2c, text_sensor
import esphome.config_validation as cv
from esphome.const import (
    CONF_ID,
)

CODEOWNERS = ["@apaex"]
#DEPENDENCIES = ["i2c"]
AUTO_LOAD = [ "text_sensor" ]


ns = cg.esphome_ns.namespace("paj7620")
PAJ7620 = ns.class_("PAJ7620", cg.PollingComponent)

CONFIG_SCHEMA = (
    text_sensor.sensor_schema(
        PAJ7620,
        icon="mdi:hand-clap",
    )
    .extend(cv.polling_component_schema("100ms"))
#    .extend(i2c.i2c_device_schema(0x73))
)

async def to_code(config):
    var = await text_sensor.new_sensor(config)
    await cg.register_component(var, config)
#    await i2c.register_i2c_device(var, config)

    cg.add_library("Wire", "*")


