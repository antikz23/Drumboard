#include <SoftwareSerial.h>
#include "Adafruit_Soundboard.h"
#include <Wire.h>
#include "Adafruit_Trellis.h"
#define SFX_TX    11
#define SFX_RX    10
#define SFX_RST   12
unsigned long duration[16];
unsigned long note[16];
int count, next, last;
int x;

#define sound_delay 50
byte val = 0;
SoftwareSerial ss = SoftwareSerial(SFX_TX, SFX_RX);
Adafruit_Soundboard sfx = Adafruit_Soundboard(&ss, NULL, SFX_RST);

Adafruit_Trellis matrix0 = Adafruit_Trellis();
Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0);

#define INTPIN A1

void setup() {
  Serial.begin(9600);
  Serial.println("Trellis Demo");
  pinMode(7, OUTPUT);
  pinMode(INTPIN, INPUT);
  digitalWrite(INTPIN, HIGH);
  trellis.begin(0x70);  // only one
  ss.begin(9600);
  sfx.reset();
}

void loop() {
  delay(30); // 30ms delay is required, dont remove me!

  if (trellis.readSwitches()) 
  {
    if (trellis.justPressed(0))
    {
      sfx.playTrack(1);
    }
    if (trellis.justReleased(0))
    {
      
    }
      
  }
}
