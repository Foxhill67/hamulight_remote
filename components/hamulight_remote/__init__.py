import esphome.codegen as cg
from esphome.components import light
from esphome.core import CORE

CODEOWNERS = ["foxhill67"]

hamulight_remote_ns = cg.esphome_ns.namespace('hamulight_remote')
HamulightRemote = hamulight_remote_ns.class_('HamulightRemote', cg.Component, light.LightOutput)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)  # Registers the component
    yield light.register_light(var, config)  # Registers the light
