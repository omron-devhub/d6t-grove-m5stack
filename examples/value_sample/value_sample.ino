#include <driver/dac.h>
#include <M5Stack.h>
#include "OmronD6T.h"

OmronD6T sensor;

void setup()
{
  M5.begin();
  dac_output_disable(DAC_CHANNEL_1);
  Serial.begin(9600);
}

void loop()
{
  sensor.scanTemp();
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextSize(2);
  M5.Lcd.println("-------------------------");
  int x, y;
  for (y = 0; y < 4; y++)
  {
    for (x = 0; x < 4; x++)
    {
      M5.Lcd.print(sensor.temp[x][y]);
      M5.Lcd.print(' ');
    }
    M5.Lcd.println("");
  }
  delay(1000);
}
