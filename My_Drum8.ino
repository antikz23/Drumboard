
#include <SoftwareSerial.h>
#include "Adafruit_Soundboard.h"
#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

// Choose any two pins that can be used with SoftwareSerial to RX & TX
#define SFX_TX    5
#define SFX_RX    6
#define SFX_RST   4

#define VOL_UP    12
#define VOL_DOWN  11
#define DRUM1     0    // Our analog pin
#define DRUM2     1    // Our analog pin
#define DRUM3     2    // Our analog pin
#define DRUM4     3    // Our analog pin
#define sound_delay 50
byte val = 0;

// we'll be using software serial
SoftwareSerial ss = SoftwareSerial(SFX_TX, SFX_RX);

Adafruit_Soundboard sfx = Adafruit_Soundboard(&ss, NULL, SFX_RST);

void setup()
{
  ss.begin(9600);
  sfx.reset();
  //  pinMode(SOUND1, INPUT_PULLUP);
  //  pinMode(SOUND2, INPUT_PULLUP);
  //  pinMode(SOUND3, INPUT_PULLUP);
  //  pinMode(SOUND4, INPUT_PULLUP);
    pinMode(VOL_DOWN, INPUT_PULLUP);
    pinMode(VOL_UP, INPUT_PULLUP);
}

void loop()
{

  val = analogRead(DRUM1);  // Read the voltage
  if (val > 45)
  {
    sfx.playTrack(1);
    delay(sound_delay);
  }

  val = analogRead(DRUM2);  // Read the voltage
  if (val > 45)
  {
    sfx.playTrack(2);
    delay(sound_delay);
  }

  val = analogRead(DRUM3);  // Read the voltage
  if (val > 45)
  {
    sfx.playTrack(3);
    delay(sound_delay);
  }

  val = analogRead(DRUM4);  // Read the voltage
  if (val > 45)
  {
    sfx.playTrack(4);
    delay(sound_delay);
  }

  if (digitalRead(VOL_DOWN) == LOW)
  {
    int v = sfx.volDown();
  }

  if (digitalRead(VOL_UP) == LOW)
  {
    int v = sfx.volUp();
  }


}
