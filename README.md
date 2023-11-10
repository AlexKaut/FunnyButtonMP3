# Instructions on how to make a meme button on an arduino with a mp3 module 



## Introduction
Initially, this project is designed for a "lamp in the form of a keyboard keycap", but, of course, this concept and schemes can be safely assembled in any other case. An important point of this project is different assembly options - you can choose the power supply and LEDs that suit you

https://github.com/Alex-Kaut/FunnyButtonMP3/assets/86695572/9d83f757-1403-4bb2-91cd-4f2a717b995c

# BOM
A lamp in the shape of a keycap - 1

Arduino nano - 1

DFminiMP3 - 1

SD card - 1 

Speaker - 1 

Toggle switch - 1

Resistors 220 Ohm - 2 

## Light: 

First option - leds with 150-220ohms resistors 

Second option -led strip with transistor key (IRF740 as an example) 

Third option - address led strip

## Power: 

First optioh - 5 volt cable with power supply, or you can just use USB

Second option - 2 or 3 batteries 18650 and 5 volt voltage stabilizer (7805 as an example)

# Schematics 
## Power
The supply voltage of the circuit depends on which LEDs you plan to use in your assembly. In my final version, an addressable LED strip is used, it is powered by 5 volts. I needed battery power, so I connected two 18650 batteries in series, got 7.4-8.4 volts, and then lowered it to 5 volts using a voltage stabilizer 7805. You can simply power it from USB cable, then you won't need a voltage stabilizer. 
## Audio core - Arduino and DFminiMP3 
![AudioPart](https://github.com/Alex-Kaut/FunnyButtonMP3/assets/86695572/e33951ce-5b77-4581-b4e3-6a2000ac0562)

To connect DFminiMP3 with arduino 220ohm resistor should be used. The next important point is the button. Such lamps come in several models, so the connection scheme of the button on the board will vary slightly. If desired, you can completely replace the native board or remove it from its slot and solder directly to the button legs. I didn't want to take out the native board, so I found a multimeter to connect the button using a multimeter. In my version of the 220 volt lamp, the button is connected with one pin between two diodes from the diode bridge, and the second pin to the leg of the resistor. I bit off one leg of all these components so that they no longer played a role on the PCB, and soldered wires to the second leg - I put the wire from the diode on the arduino pin, and connected the wire from the resistor to the ground. Since this is a lamp, the button is a switch, this moment will be taken into account in the firmware

## LED 

### Adress LED strip 
![AddressLEDstrip](https://github.com/Alex-Kaut/FunnyButtonMP3/assets/86695572/3f8301b5-72e4-4753-ab2e-440a7923dbce)
Simply connect the address LED strip via a 100ohm resistor to the arduino and download the appropriate firmware. Do not forget that the address LED strip has a direction, so before connecting, double-check it by the arrows drawn. For this option, you will need your own firmware. Well, thanks to the capabilities of such a tape, you can program various lighting effects
### Simple LEDs 
![SimpleLed](https://github.com/Alex-Kaut/FunnyButtonMP3/assets/86695572/a72817a8-a777-4a89-81c1-0fb417d342ad)
This is the simplest way to implement the glow, since it does not need a transistor key. It is not recommended to use more than 20 milliamps from one arduino pin, so we simply connect the LEDs through resistors to different pins. When I tested this option, I connected 2 LEDs in parallel with a 150 ohm resistor for one pin, and I made 4 such bundles, a total of 8 LEDs turned out. In order for this option to turn out well, you need to place the LEDs inside the case very competently, otherwise the case will be illuminated unevenly - somewhere dim, and somewhere a light spot
### Transistor key 
![LedStrip](https://github.com/Alex-Kaut/FunnyButtonMP3/assets/86695572/e85b564c-be09-4e0e-8778-2a26110dda34)
This is a very convenient option for such a project, thanks to the transistor key, you can connect a powerful load (LEDs) and control it with one arduino pin. You can use, for example, IRF740 and a 5 volt LED strip. Or you can take a 12 volt LED strip, power it directly from the batteries (with two 18650 batteries connected in series, it will glow dimly, so you can put 3 batteries), and turn it on through a key

## DFminiMP3 
![DFminiMP3](https://github.com/Alex-Kaut/FunnyButtonMP3/assets/86695572/cce7852f-f49a-4ec3-973f-5a97268b4754)

DFminiMP3 plays audio files from a micro SD card. On a clean sd card, we create a folder "mp3", and into this folder downloads audio files with the names "0001", "0002" and so on. In my case, only one audio file "0001" is used

# Firmware 
## Button part 
```cpp
bool Status = 0; 

void setup() {
  pinMode(button_pin, INPUT_PULLUP);  //Button
  Status = !digitalRead(button_pin);
}

void loop() {
  if (digitalRead(button_pin) == Status) {
    //DO SOMETHING
    Status = !Status;
  }
}
```
This template allows you to use the switch as a push button 

## DFminiMP3 library 
https://github.com/Alex-Kaut/FunnyButtonMP3/blob/main/Firmware/DFRobotDFPlayerMini-master.zip
DFRobotDFPlayerMini.h - Download it and put in arduino libraries folder 

## Adress LED strip firmware
https://github.com/FastLED/FastLED?ysclid=loqho9iymx269211766
FastLED.h -Download it and put in arduino libraries folder 
```cpp

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
```
The code is simple and clear: set the pins, number of LEDs in the strip, the color - that's all, you can upload it to the arduino

## Basic firmware 
```cpp
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
```
If you have assembled a variant with several LEDs for different arduino pins, just write the "define pins" to which the LEDs are connected (led_pin1, led_pin2, etc.) and flash the arduino

If you have assembled a variant with transistor key, delete "void led_turn(){}" and rewrite the code a bit, it will look like this 

```cpp
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

#define button_pin 6
#define key_pin 2

bool Status = 0;

void setup() {
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  pinMode(key_pin, OUTPUT);           //Key
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
    digitalWrite(key_pin, HIGH);        //Leds ON
    myDFPlayer.play(1);                 //Playing first mp3 file
    delay(1000);
    myDFPlayer.pause();                 //Mp3 stop
    digitalWrite(key_pin, LOW)          //Leds OFF
    Status = !Status;
  }
}
```
