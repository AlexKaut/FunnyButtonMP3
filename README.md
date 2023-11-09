[BOM.txt](https://github.com/Alex-Kaut/FunnyButtonMP3/files/13302351/BOM.txt)# FunnyButtonMP3
Instructions on how to make a meme button on an arduino with a mp3 module 

https://github.com/Alex-Kaut/FunnyButtonMP3/assets/86695572/9d83f757-1403-4bb2-91cd-4f2a717b995c

# Introduction
Initially, this project is designed for a "lamp in the form of a keyboard keycap", but, of course, this concept and schemes can be safely assembled in any other case. An important point of this project is different assembly options - you can choose the power supply and LEDs that suit you

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

Second option - 2 batteries 18650 and 5 volt voltage stabilizer (7805 as an example)

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
