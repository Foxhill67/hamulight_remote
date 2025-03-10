import esphome.codegen as cg
from esphome.components import light

CODEOWNERS = ["foxhill67"]
MULTI_CONF = False

hamulight_remote_ns = cg.esphome_ns.namespace('hamulight_remote')
HamulightRemote = hamulight_remote_ns.class_('HamulightRemote', cg.Component, light.LightOutput)
