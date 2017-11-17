#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>
#include <Wire.h>
#include "Adafruit_Trellis.h"
unsigned long duration[16];
unsigned long note[16];
int count, next, last;
int x;

Adafruit_Trellis matrix0 = Adafruit_Trellis();
Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0);

#define INTPIN A1

//#define CLK 13       // SPI Clock, shared with SD card
//#define MISO 12      // Input data, from VS1053/SD card
//#define MOSI 11      // Output data, to VS1053/SD card

#define BREAKOUT_RESET  9
#define BREAKOUT_CS     10
#define BREAKOUT_DCS    8
#define SHIELD_RESET  -1
#define SHIELD_CS     7
#define SHIELD_DCS    6

#define CARDCS 4
#define DREQ 3

Adafruit_VS1053_FilePlayer musicPlayer =
  Adafruit_VS1053_FilePlayer(BREAKOUT_RESET, BREAKOUT_CS, BREAKOUT_DCS, DREQ, CARDCS);
//Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

void setup()
{
  Serial.begin(9600);
  Serial.println("Adafruit VS1053 Simple Test");
  Serial.println(F("VS1053 found"));

  printDirectory(SD.open("/"), 0);

  musicPlayer.setVolume(20, 20);

  //musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int

  /*  Serial.println(F("Playing tracks"));
    delay(50);
    musicPlayer.playFullFile("track002.mp3");
    delay(50);
    musicPlayer.playFullFile("track003.mp3");
    delay(50);
    musicPlayer.playFullFile("track004.mp3");
    delay(50);
    musicPlayer.playFullFile("track005.mp3");
    delay(50);
    musicPlayer.playFullFile("track006.mp3");
    delay(50);
    musicPlayer.playFullFile("track007.mp3");
    delay(50);
    musicPlayer.playFullFile("track008.mp3");
  */

  pinMode(7, OUTPUT);
  pinMode(INTPIN, INPUT);
  digitalWrite(INTPIN, HIGH);
  trellis.begin(0x70);  // only one
}

void loop() {
  delay(30); // 30ms delay is required, dont remove me!

  if (trellis.readSwitches())
  {
    if (trellis.justPressed(0))
    {
      musicPlayer.playFullFile("track001.mp3");
    }
    if (trellis.justReleased(0))
    {
      if (musicPlayer.stopped())
      {
        Serial.println("Done playing music");
        while (1)
        {
          delay(10);
        }

      }
    }
  }


  // File is playing in the background
  if (musicPlayer.stopped())
  {
    Serial.println("Done playing music");
    while (1) {
      delay(10);  // we're done! do nothing...
    }
  }
   if (Serial.available())
    {
     char c = Serial.read();

     // if we get an 's' on the serial console, stop!
     if (c == 's')
     {
       musicPlayer.stopPlaying();
     }

     // if we get an 'p' on the serial console, pause/unpause!
     if (c == 'p') {
       if (! musicPlayer.paused()) {
         Serial.println("Paused");
         musicPlayer.pausePlaying(true);
       } else {
         Serial.println("Resumed");
         musicPlayer.pausePlaying(false);
       }
     }
     delay(100);
    }
 
}


/// File listing helper
void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      //Serial.println("**nomorefiles**");
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}

