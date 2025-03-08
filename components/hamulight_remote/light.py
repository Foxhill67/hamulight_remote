import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import light
from esphome.const import CONF_ID
from esphome.core import CORE, LogLevel

from . import hamulight_remote_ns, HamulightRemote

CONFIG_SCHEMA = light.LIGHT_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(HamulightRemote),
})

async def to_code(config):
    CORE.log(LogLevel.INFO, "hamulight_remote: to_code() called") # Corrected log function
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await light.register_light(var, config)
