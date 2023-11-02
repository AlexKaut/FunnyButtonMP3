#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "FastLED.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);


#define LED_PIN 3     
#define LED_NUM 21    //Number of LEDs
#define BUTTON_PIN 6  

bool Status = 0;
CRGB leds[LED_NUM];

void setup() {
  mySoftwareSerial.begin(9600);
  //Serial.begin(115200); //Use it to check button

  pinMode(BUTTON_PIN, INPUT_PULLUP);  //Button

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Using SoftwareSerial to connect with DFminiMp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(30);  //Volume level, 30 is maximum
  Status = !digitalRead(BUTTON_PIN);


  FastLED.addLeds< WS2812, LED_PIN, GRB>(leds, LED_NUM);
  FastLED.setBrightness(0);
  for (int i = 0; i < LED_NUM; i++) {   //Setting the yellow color
    leds[i].setRGB(255, 110, 0);
  }
  FastLED.show();
}

void loop() {
  if (digitalRead(BUTTON_PIN) == Status) {
    FastLED.setBrightness(200);
    FastLED.show();
    myDFPlayer.play(1); //Playing first mp3 file
    delay(1350);

    myDFPlayer.pause();
    FastLED.setBrightness(0);
    FastLED.show();
    Status = !Status;
  }
  //Serial.println(digitalRead(A3)); //Use it to check button
}
