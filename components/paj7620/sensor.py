import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import (
    CONF_ID,
)

CODEOWNERS = ["@apaex"]
DEPENDENCIES = [ ]
AUTO_LOAD = [ "text_sensor" ]
#MULTI_CONF = True

# C++ namespace
ns = cg.esphome_ns.namespace("paj7620")
PAJ7620 = ns.class_("PAJ7620", cg.PollingComponent)


CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(PAJ7620),
#            cv.Optional(CONF_VOLTAGE): sensor.sensor_schema(
#                UNIT_EMPTY, ICON_EMPTY, 0, DEVICE_CLASS_EMPTY
#            )
        }
    )

    .extend(cv.polling_component_schema("60s"))
#    .extend(cv.COMPONENT_SCHEMA)
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    cg.add_library("Wire", "*")
    cg.add_library("seeed-studio/Grove Gesture", "1.0.0")
