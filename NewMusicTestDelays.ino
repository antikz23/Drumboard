#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>
#include <Wire.h>
#include "Adafruit_Trellis.h"



#define NUMKEYS           12
#define INTPIN A1
#define BREAKOUT_RESET  9
#define BREAKOUT_CS     10
#define BREAKOUT_DCS    8
#define SHIELD_RESET  -1
#define SHIELD_CS     7
#define SHIELD_DCS    6

#define CARDCS 4
#define DREQ 3

unsigned int duration[16];
char note[24];
const char beat[24][6] = {"A.mp3", "B.mp3", "C.mp3", "D.mp3", "E.mp3", "F.mp3", "G.mp3"};
int count, next, last;

Adafruit_Trellis matrix0 = Adafruit_Trellis();
Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0);
Adafruit_VS1053_FilePlayer musicPlayer =
  Adafruit_VS1053_FilePlayer(BREAKOUT_RESET, BREAKOUT_CS, BREAKOUT_DCS, DREQ, CARDCS);
//Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

void setup()
{
  pinMode(7, OUTPUT);
  pinMode(INTPIN, INPUT);
  pinMode(BREAKOUT_RESET, OUTPUT);

  trellis.begin(0x70);  // only one
  for (uint8_t i = 0; i < NUMKEYS; i++) {
    trellis.setLED(i);
    trellis.writeDisplay();
    delay(50);
  }
  // then turn them off
  for (uint8_t i = 0; i < NUMKEYS; i++) {
    trellis.writeDisplay();
    delay(50);
  }

  Serial.begin(9600);
  Serial.println("Adafruit VS1053/Trellis Test");
  if (! musicPlayer.begin()) { // initialise the music player
    Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
    while (1);
  }
  Serial.println(F("VS1053 found"));

  if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    while (1);  // don't do anything more
  }


  musicPlayer.setVolume(20, 20);

  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int

}

void loop() {
  delay(30); // 30ms delay is required, dont remove me!


  if (trellis.readSwitches()) {
    // go through every button
    for (uint8_t i = 0; i < NUMKEYS; i++) {
      next = millis();
      duration[count++] = next - last;
      last = next;
      // if it was pressed, turn it on
      if (trellis.justPressed(i)) {
        musicPlayer.startPlayingFile(beat[i]);
        note[count] = i;
      }
      // if it was released, turn it off
      if (trellis.justReleased(i)) {
        musicPlayer.stopPlaying();

      }
    }
    if (trellis.justPressed(12))
    {
      delay(1000);  //CREATE A PAUSE BEFORE PLAYING THE STORED SOUND
      for (int x = 1; x <= count - 1; x++)
      { //PLAY THE FIVE TONES
        musicPlayer.startPlayingFile(beat[note[x]]);
      
        delay(duration[x] - 100);
        //delay(250);
        musicPlayer.stopPlaying();
      }
      count = 0;
    }
  }
}



