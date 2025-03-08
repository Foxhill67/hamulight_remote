import esphome.codegen as cg
from esphome.components import light
from esphome.const import (
    CONF_ID
)
from esphome.core import CORE

CODEOWNERS = ["foxhill67"]

hamulight_remote_ns = cg.esphome_ns.namespace('hamulight_remote')
HamulightRemote = hamulight_remote_ns.class_('HamulightRemote', cg.Component, light.LightOutput)

