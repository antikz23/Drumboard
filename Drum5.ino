
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
#define SOUND1    7
#define SOUND2    8
#define SOUND3    9
#define SOUND4    10
#define DRUM1     0    // Our analog pin
#define DRUM2     1    // Our analog pin
#define DRUM3     2    // Our analog pin
#define DRUM4     3    // Our analog pin

byte val = 0;

#define button_delay 100
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
  //  pinMode(VOL_DOWN, INPUT_PULLUP);
  //  pinMode(VOL_UP, INPUT_PULLUP);
}

void loop()
{

  val = analogRead(DRUM1);  // Read the voltage
  if (val > 60)
  {
    val = map(val, 60, 255, 160, 204);
    sfx.playTrack(1);
    delay(button_delay);
  }

  if (digitalRead(SOUND2) == LOW)
  {
    sfx.playTrack(2);
    delay(button_delay);
  }

  if (digitalRead(SOUND3) == LOW)
  {
    sfx.playTrack(3);
    delay(button_delay);
  }

  if (digitalRead(SOUND4) == LOW)
  {
    sfx.playTrack(4);
    delay(button_delay);
  }

  if (digitalRead(VOL_DOWN) == LOW)
  {
    int v = sfx.volDown();
    delay(button_delay);
  }

  if (digitalRead(VOL_UP) == LOW)
  {
    int v = sfx.volUp();
    delay(button_delay);
  }


}
