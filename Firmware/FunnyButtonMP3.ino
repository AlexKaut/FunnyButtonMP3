#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

#define button_pin 6
#define led_pin1 2
#define led_pin2 3
#define led_pin3 5
#define led_pin4 7

bool Status = 0;

void led_turn(bool led_status) {
  digitalWrite(led_pin1, led_turn);
  digitalWrite(led_pin2, led_turn);
  digitalWrite(led_pin3, led_turn);
  digitalWrite(led_pin4, led_turn);
  return(0);
}

void setup() {
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  pinMode(led_pin1, OUTPUT);          //Leds
  pinMode(led_pin2, OUTPUT);
  pinMode(led_pin3, OUTPUT);
  pinMode(led_pin4, OUTPUT);

  pinMode(button_pin, INPUT_PULLUP);  //Button


  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Using SoftwareSerial to connect with DFminiMp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(30);  //Volume level, 30 is maximum
  Status = !digitalRead(button_pin);
}
void loop() {
  if (digitalRead(button_pin) == Status) {
    led_turn(HIGH);         //Leds ON
    myDFPlayer.play(1);     //Playing first mp3 file
    delay(1000);
    myDFPlayer.pause();     //Mp3 stop
    led_turn(LOW);          //Leds OFF
    Status = !Status;
  }
}
