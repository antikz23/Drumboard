#include <SoftwareSerial.h>
#include "Adafruit_Soundboard.h"
#include <Adafruit_Soundboard.h>
#include <Wire.h>
#include "Adafruit_MPR121.h"

#define SFX_TX    5
#define SFX_RX    6
#define SFX_RST   4

#define sound_delay 50
byte val = 0;

SoftwareSerial ss = SoftwareSerial(SFX_TX, SFX_RX);
Adafruit_Soundboard sfx = Adafruit_Soundboard(&ss, NULL, SFX_RST);

int touch;
Adafruit_MPR121 cap = Adafruit_MPR121();


void setup()
{
  ss.begin(9600);
  sfx.reset();
  Serial.begin(9600);
  cap.begin(0x5A);
}

void loop()
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

