import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import light # Add light import
from esphome.const import CONF_ID
import logging

CODEOWNERS = ["foxhill67"]
MULTI_CONF = False

hamulight_remote_ns = cg.esphome_ns.namespace('hamulight_remote')
HamulightRemote = hamulight_remote_ns.class_('HamulightRemote', cg.Component, light.LightOutput) # Use light.LightOutput

CONFIG_SCHEMA = light.LIGHT_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(HamulightRemote),
})

def to_code(config):
    logging.info("hamulight_remote: light.py to_code() called")
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)  # Registers the component
    yield light.register_light(var, config)  # Registers the light platform
