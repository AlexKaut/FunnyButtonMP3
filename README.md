# FunnyButtonMP3
Materials for assembling button for playing audio memes - Arduino with the DFminiMP3 module

https://github.com/AlexKaut/FunnyButtonMP3/assets/86695572/380a5822-c58d-47d0-9e67-f19f4b310871

# Schematics
## Arduino Pro Mini 3.3V
Using Arduino Pro Mini 3.3V in this circuit is very convenient, since it can be powered directly from 18650 batteries 
![ArduinoProMini-Schematic](https://github.com/AlexKaut/FunnyButtonMP3/assets/86695572/ee5d229f-00b8-4c0e-bcfb-c96e1af25957)

## Arduino Nano 
If you want to use the Arduino Nano, then the circuit will have to be slightly modified: 

The first option is to abandon the battery, power the button via a USB cable. 

The second option is to stabilize the battery voltage to 5 volts. For example, you can connect two 18650 batteries in series, and stabilize the resulting voltage to 5 volts using the 7805. It is not recommended to use the built-in voltage stabilizer on the Arduino, DFminiMP3 may work unstable
![ArduinoNano-Schematic](https://github.com/AlexKaut/FunnyButtonMP3/assets/86695572/d82c80ee-2f55-44e8-9d34-a505a58c4395)

**Please note! In the scheme, a switch with a lock acts as a button! If you want to use a regular push button for this task, you will have to rewrite the firmware code a bit.**

# Firmware
## DFminiMP3 and Python RenamingScript
DFminiMP3 plays mp3 files from a micro SD card. To prepare the SD card for this task, format it, create an MP3 player folder on it and upload audio files to this folder, adding the numbering "0001", "0002" and so on to the beginning of their names. For example, if you had 3 files "Song.mp3", "Cartoon.mp3" and "Spring.mp3", then you will need to rename them to "0001-Song.mp3", "0002-Cartoon.mp3" and "0003-Spring.mp3"
To speed up the process of renaming files, I wrote a simple python script for this task. Run the script, enter the path
to the mp3 folder, and all files in the folder will be numbered in the name, and the script will output an array with the lengths of mp3 files 

This script is using Mutagen Python module 

![image](https://github.com/AlexKaut/FunnyButtonMP3/assets/86695572/2f90402e-c204-4433-b599-cd2704e0bf56)

## Arduino code 
### Firmware Description

Since DFminiMP3 cannot determine the length of audio files lying on the SD card, the length will be set in the firmware of the microcontroller itself. To do this, in the firmware, we will need to set the number of the last file on the SD card (#define MAX_VALUE) and insert an array with lengths that was generated after executing the python script
Open FunnyButtonMP3.ino and find these lines
```cpp
//Array for random playback of mp3 files 
#define MIN_VALUE 1         //0001.mp3 
#define MAX_VALUE 39        //The number of the last mp3 file on the DFminiMP3 SD card 
#define ARRAY_SIZE (MAX_VALUE - MIN_VALUE + 1)
```
In the line "#define MAX_VALUE", specify the number of the last audio file on the SD card

Then edit this section of the code - the array "unsigned long mp3length[]{}" must be replaced with the array obtained as a result of executing the python script
```cpp
int numbers[ARRAY_SIZE];
int currentIndex = 0;

//Array with mp3 file lengths in seconds. To generate this array, you can use python script
unsigned long mp3length[] = {3, 8, 13, 1, 3, 11, 1, 5, 4, 4, 10, 4, 6, 4, 4, 8, 2, 6, 8, 10, 
2, 1, 4, 2, 3, 5, 3, 4, 2, 2, 2, 3, 3, 2, 2, 6, 1, 8, 2};

bool Status = 0;     //Button status 
CRGB leds[LED_NUM];
```

