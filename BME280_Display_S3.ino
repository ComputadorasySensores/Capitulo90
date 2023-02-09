#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "TFT_eSPI.h"
#include "iconos_bme280_140x170.h"

Adafruit_BME280 bme;

TFT_eSPI tft= TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

void setup() {
  Wire.begin(43, 44);

  tft.init();
  tft.setRotation(1);
  tft.setSwapBytes(true);
  tft.fillScreen(TFT_WHITE);
  tft.pushImage(180,0,140,170,iconos_bme280_140x170);

  sprite.createSprite(179,150);
 
  sprite.setTextColor(TFT_BLACK,TFT_WHITE);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(1);
  tft.drawString("Computadoras y Sensores",10,160);
  tft.setTextSize(2);
  bool status;

  status = bme.begin(0x76);  
  if (!status) {
    tft.drawString("No se encuentra BME280",10,50);
    while (1);
  }

}


void loop() { 
  sprite.fillSprite(TFT_WHITE);
  sprite.setFreeFont(&Orbitron_Light_32);
  sprite.drawString(String(bme.readTemperature()),20,10);
  sprite.drawString(String(bme.readHumidity()),20,60);
  sprite.drawString(String(bme.readPressure()/100),20,110);
  sprite.pushSprite(0,0);
  delay(1000);
}
