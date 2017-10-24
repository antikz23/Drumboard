
#include <SoftwareSerial.h>
#include "Adafruit_Soundboard.h"
#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

// Choose any two pins that can be used with SoftwareSerial to RX & TX
#define SFX_TX    5
#define SFX_RX    6
#define SFX_RST   4

#define sound_delay 50
byte val = 0;

// we'll be using software serial
SoftwareSerial ss = SoftwareSerial(SFX_TX, SFX_RX);

Adafruit_Soundboard sfx = Adafruit_Soundboard(&ss, NULL, SFX_RST);

void setup()
{
  touch = cap.touched();
  if (touch != 0)
  {
    //Serial.print(touch);

    if (touch == 1)
    {
      Serial.print(1);
      sfx.playTrack(1);
      delay(sound_delay);
    }
    if (touch == 2)
    {
      Serial.print(2);
      sfx.playTrack(2);
      delay(sound_delay);
    }
    if (touch == 4)
    {
      Serial.print(4);
      sfx.playTrack(3);
      delay(sound_delay);
    }
  }
  delay(200);
}
