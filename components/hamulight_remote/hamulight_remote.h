#include "esphome.h"
#include "esphome/components/light/light_output.h"
#include <bitset>
#include <string>

namespace esphome {
namespace hamulight_remote {

class HamulightRemote : public Component, public light::LightOutput {
 private:
   std::string signalToggle = "101010101111110000001000100011101000111011101000111010001000100011101110111011101110111010001110100010001000100010001000111010001000100010001000111010101010";
   std::string dimMesId = "010101111110000001000100011101000111011101000111010001000100011101110111011101110100";
   std::string dimGlue = "0101";
   std::string dimSignals[100];
   int minDimLevel = 20479;
   int dimStep = 289;
   int pin = 4;
   int period = 200;
   int percentage = 0;
   bool isOn = false;

 public:
  void setup() override {
    ESP_LOGD("hamulight", "HamulightRemote setup started");
    pinMode(pin, OUTPUT);
    for (int i = 0; i < 100; i++) {
      dimSignals[i] = createDimSignal(i + 1);
    }
    ESP_LOGD("hamulight", "HamulightRemote setup completed");
  }

  light::LightTraits get_traits() override {
    auto traits = light::LightTraits();
    traits.set_supported_color_modes({light::ColorMode::BRIGHTNESS, light::ColorMode::ON_OFF});
    return traits;
  }

  void write_state(light::LightState *state) override {
//    float newBrightness;
//    bool newIsOn;
//    state->current_values_as_brightness(&newBrightness);
//    state->current_values_as_binary(&newIsOn);

    float newBrightness = state->current_values.get_brightness();
    bool newIsOn = state->current_values.is_on();
   
    int newPercentage = round(newBrightness * 100);
    ESP_LOGD("main", "write_state init, newIsOn=%s, newPercentage=%d", newIsOn, newPercentage);
   
    if (newIsOn != isOn) {
      if (newIsOn) {
        sendSignal(signalToggle, 10, 0);
        percentage = 1;
        ESP_LOGD("main", "Turn light on");
      } else {
        slowDim(newPercentage, 1);
        sendSignal(signalToggle, 10, 0);
        ESP_LOGD("main", "Turn light off");
      }
    }

    if (newIsOn && percentage != newPercentage) {
      slowDim(percentage, newPercentage);
      ESP_LOGD("main", "Send brightness signal, old=%d, new=%d", percentage, newPercentage);
    }

    ESP_LOGD("main", "------------------------------------");
    percentage = newPercentage;
    isOn = newIsOn;
  }

  void slowDim(int percentage, int newPercentage) {
    if (percentage < newPercentage) {
      for (int p = percentage; p < newPercentage; p += 2) {
        sendSignal(dimSignals[p - 1], 1, 10000);
      }
    } else {
      for (int p = percentage; p > newPercentage; p -= 2) {
        sendSignal(dimSignals[p - 1], 1, 10000);
      }
    }
    sendSignal(dimSignals[newPercentage - 1], 2, 45000);
  }

  void sendSignal(const std::string &signal, int count, int messageSpacing) {
    for (int j = 0; j < count; j++) {
      for (size_t i = 0; i < signal.length(); i++) {
        digitalWrite(pin, (signal[i] == '1') ? HIGH : LOW);
        delayMicroseconds(period);
      }
      digitalWrite(pin, LOW);
      delayMicroseconds(messageSpacing);
    }
  }

  std::string createDimSignal(int percentage) {
    int dimLevel = minDimLevel - (dimStep * percentage) + dimStep;
    if (dimLevel < 249) {
      dimLevel += 32222;
    }
    if (percentage == 100) {
      dimLevel = 24357;
    }

    std::string binary = std::bitset<15>(dimLevel).to_string();
    std::string dimEncodedSignal;
    for (char bit : binary) {
      dimEncodedSignal += (bit == '1') ? "0111" : "0100";
    }
    return dimMesId + dimEncodedSignal + dimGlue + dimMesId + dimEncodedSignal;
  }
};

}  // namespace hamulight_remote
}  // namespace esphome
