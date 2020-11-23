#include <OneWire.h> 
#include <DallasTemperature.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET -1  // GPIO0
Adafruit_SSD1306 OLED(OLED_RESET);

// WIRE TMP to pin D5 (GPIO14)
#define ONE_WIRE_BUS 0
OneWire oneWire(ONE_WIRE_BUS);  
DallasTemperature sensors(&oneWire);

int tmp1 = 0;
int tmp2 = 0;
int pir_status = 0;
int pir_silence = 0;

unsigned long time_now = 0;

void setup() {
Serial.begin(115200);
  pinMode(12,OUTPUT); //LED pin
  pinMode(14,INPUT); //PIR pin
  sensors.begin(); 
  OLED.begin();
  OLED.display();

  //oled hello
  OLED.clearDisplay(); // Clear the display buffer
  OLED.display();
  OLED.setTextSize(2);
  OLED.setTextColor(WHITE);
  OLED.setCursor(0,0);
  OLED.println("WELCOME");

}
void loop() {
pir_status = digitalRead(14);
Serial.println(pir_status);
if(pir_status == 1 && pir_silence < millis()-7000){
  digitalWrite(12,HIGH);
  OLED.clearDisplay(); // Clear the display buffer
  OLED.display();
  OLED.setRotation(2);
  OLED.setTextSize(2);
  OLED.setCursor(0,0);
  OLED.print("MOTION");
  OLED.setCursor(0,15);
  OLED.print("DETECTED");
  OLED.display();
  delay(1000);
  pir_silence = millis();
}
else{  digitalWrite(12,LOW);
}

if(millis() > time_now + 10000){
  //get tmp
  sensors.requestTemperatures(); // Send the command to get tmperature readings 
  tmp1 = sensors.getTempCByIndex(0);
  tmp2 = sensors.getTempCByIndex(1);
  time_now = millis();

  //display data
  OLED.clearDisplay(); // Clear the display buffer
  OLED.display();
  OLED.setRotation(2);
  OLED.setTextSize(1);
  OLED.setCursor(0,0);
  OLED.print("Int:      Ext:");
  OLED.setTextSize(2);
  OLED.setCursor(0,15);
  OLED.print(tmp1);
  OLED.setCursor(55,15);
  OLED.print(tmp2);
  OLED.display(); //output 'display buffer' to screen  
  }

}
