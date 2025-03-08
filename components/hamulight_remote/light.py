from . import hamulight_remote_ns, HamulightRemote
from esphome.components import light
import esphome.config_validation as cv
from esphome.const import CONF_ID

CONFIG_SCHEMA = light.LIGHT_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(HamulightRemote),
})

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await light.register_light(var, config)
