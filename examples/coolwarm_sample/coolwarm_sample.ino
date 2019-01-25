#include <Arduino.h>
#include <driver/dac.h>
#include <M5Stack.h>
#include <OmronD6T.h>

OmronD6T sensor;

int color[7];
int range_min = 25;
int range_max = 35;

uint16_t rgbToColor(uint8_t red, uint8_t green, uint8_t blue){
  return ((red>>3)<<11) | ((green>>2)<<5) | (blue>>3);
}

void initColormap() {
  color[0] = rgbToColor(76,134,228);
  color[1] = rgbToColor(127,178,248);
  color[2] = rgbToColor(177,208,245);
  color[3] = rgbToColor(221,220,219);
  color[4] = rgbToColor(252,194,173);
  color[5] = rgbToColor(255,151,125);
  color[6] = rgbToColor(234,94,78);
}

int getRangeColor(float temperature) {
  float range = range_max - range_min;
  float block = range / 7;
  if (temperature < range_min) {
    return 0;
  } else if (temperature < (range_min + block)) {
    return 1;
  } else if (temperature < (range_min + (block * 2))) {
    return 2;
  } else if (temperature < (range_min + (block * 3))) {
    return 3;
  } else if (temperature < (range_min + (block * 4))) {
    return 4;
  } else if (temperature < (range_min + (block * 5))) {
    return 5;
  } else {
    return 6;
  }
}

void setup() {
  M5.begin();
  dac_output_disable(DAC_CHANNEL_1);
  Serial.begin(9600);
  delay(1000);
  initColormap();
}

void loop() {
  sensor.scanTemp();
  int16_t rectw = (M5.Lcd.width() / 4);
  int16_t recth = (M5.Lcd.height() / 4);
  int x, y;
  for (y = 0; y < 4; y++) {
    for (x = 0; x < 4; x++) {
      float temperature = sensor.temp[x][y];
      int rangecolor = getRangeColor(temperature);
      Serial.print("temperature : ");
      Serial.println(temperature);
      Serial.print("rangecolor : ");
      Serial.println(rangecolor);
      M5.Lcd.fillRect((rectw * x), (recth * y), rectw, recth, color[rangecolor]);
    }
  }
  delay(1000);
}
