#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "FastLED.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);


#define LED_PIN 3     //AdressableLED pin 
#define LED_NUM 14    //Number of LEDs
#define BUTTON_PIN 6  //Button pin 

//Array for random playback of mp3 files 
#define MIN_VALUE 1         //0001.mp3 
#define MAX_VALUE 39        //The number of the last mp3 file on the DFminiMP3 SD card 
#define ARRAY_SIZE (MAX_VALUE - MIN_VALUE + 1)

#define COLOR_ORDER GRB

//Colors array
CRGB colors[] = {
  CRGB::Red,
  CRGB::Blue,
  CRGB::Green,
  CRGB::Pink,
  CRGB::White,
  CRGB::Aqua,
  CRGB::Yellow,
  CRGB::Purple,
  CRGB::Lime,
  CRGB::Magenta,
  CRGB::Orange,
  CRGB::Violet, 
  CRGB::Azure, 
  CRGB::Cyan,
  CRGB::Chartreuse, 
  CRGB::Brown, 
  CRGB::Gold 
};

int numbers[ARRAY_SIZE];
int currentIndex = 0;

//Array with mp3 file lengths in seconds. To generate this array, you can use python script
int mp3length[] = {3, 8, 13, 1, 3, 11, 1, 5, 4, 4, 10, 4, 6, 4, 4, 8, 2, 6, 8, 10, 
2, 1, 4, 2, 3, 5, 3, 4, 2, 2, 2, 3, 3, 2, 2, 6, 1, 8, 2};

bool Status = 0;     //Button status 
CRGB leds[LED_NUM];


void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);  //Button pin 
  pinMode(0, INPUT);                  //Analog pin for random seed 

  if (!myDFPlayer.begin(Serial)) {    //Using Serial to connect with DFminiMp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(29);  // Volume level, 30 is maximum
  Status = !digitalRead(BUTTON_PIN);

  randomSeed(analogRead(0));

  FastLED.addLeds< WS2812, LED_PIN, GRB>(leds, LED_NUM);
  FastLED.setBrightness(0);
  for (int i = 0; i < LED_NUM; i++) {   //Setting the yellow color
    leds[i].setRGB(255, 110, 0);
  }
  FastLED.show();

  //Initializing an array with numbers from MIN_VALUE to MAX_VALUE
  for (int i = 0; i < ARRAY_SIZE; i++) {
    numbers[i] = MIN_VALUE + i;
  }
  //Shuffling the array
  shuffleArray(numbers, ARRAY_SIZE);
  
}

void loop() {
  if (digitalRead(BUTTON_PIN) == Status) {      

    CRGB randomColor = colors[random(0, sizeof(colors) / sizeof(colors[0]))];
    fill_solid(leds, LED_NUM, randomColor);
    FastLED.show();    
    
    int randomNumber = getNextRandom();
    FastLED.setBrightness(150);
    FastLED.show();
    myDFPlayer.play(randomNumber);        //Playing first mp3 file
    delay(250);   //Debounce delay

    unsigned long startTime = millis();   //Starting the mp3 file playback timer
    while (millis() - startTime < (mp3length[randomNumber - 1] * 1000) - 250) { 
      if (digitalRead(BUTTON_PIN) != Status) { 
        break;    //If the button is pressed, playback is interrupted
      }
    }

    myDFPlayer.pause();
    FastLED.setBrightness(0);
    FastLED.show();
    delay(180);   //Delay for debouncing
    if (digitalRead(BUTTON_PIN) == Status) {
      Status = !Status;
    }
  }
  //Serial.println(digitalRead(BUTTON_PIN)); //Use it to check button 
}


int getNextRandom() {
  if (currentIndex >= ARRAY_SIZE) {     //If all numbers used, shuffle the array 
    shuffleArray(numbers, ARRAY_SIZE);
    currentIndex = 0;
  }

  //Return next number from array
  return numbers[currentIndex++];
}

void shuffleArray(int arr[], int size) {
  for (int i = size - 1; i > 0; i--) {
    int j = random(0, i + 1);
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }
}
