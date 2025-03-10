import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import light
from esphome.const import CONF_OUTPUT_ID
import logging

from . import HamulightRemote

CONFIG_SCHEMA = light.LIGHT_SCHEMA.extend({
    cv.GenerateID(CONF_OUTPUT_ID): cv.declare_id(HamulightRemote)
})

async def to_code(config):
    logging.info("hamulight_remote: light.py to_code() called")
    var = cg.new_Pvariable(config[CONF_OUTPUT_ID])
    id = config[CONF_OUTPUT_ID].id
    await cg.register_component(var, config)
    await light.register_light(var, config)
  
