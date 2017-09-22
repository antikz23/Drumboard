int x;
int y;
int z;
int a;
int b;
int c;
int d;
int e;
int f;
int v;
int w;

/*
  Menu driven control of a sound board over UART.
  Commands for playing by # or by name (full 11-char name)
  Hard reset and List files (when not playing audio)
  Vol + and - (only when not playing audio)
  Pause, unpause, quit playing (when playing audio)
  Current play time, and bytes remaining & total bytes (when playing audio)

  Connect UG to ground to have the sound board boot into UART mode
*/

#include <SoftwareSerial.h>
#include "Adafruit_Soundboard.h"


// Choose any two pins that can be used with SoftwareSerial to RX & TX
#define SFX_TX 5
#define SFX_RX 6

// Connect to the RST pin on the Sound Board
#define SFX_RST 4

// You can also monitor the ACT pin for when audio is playing!

// we'll be using software serial
SoftwareSerial ss = SoftwareSerial(SFX_TX, SFX_RX);

// pass the software serial to Adafruit_soundboard, the second
// argument is the debug port (not used really) and the third
// arg is the reset pin
Adafruit_Soundboard sfx = Adafruit_Soundboard(&ss, NULL, SFX_RST);
// can also try hardware serial with
//Adafruit_Soundboard sfx = Adafruit_Soundboard(&Serial1, NULL, SFX_RST);

#define DRUM1 0    // Our analog pin

byte val = 0;      // Initializing the variable for the voltage value

#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_7segment matrix = Adafruit_7segment();

void setup()
{
  Serial.begin(115200);
  Serial.println("Adafruit Sound Board!");

  ss.begin(9600);
  pinMode(3, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(0, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  matrix.begin(0x70);

}

void loop()
{
  // matrix.print(200, DEC);
  //matrix.writeDisplay();


  x = digitalRead(3);
  y = digitalRead(2);
  z = digitalRead(1);
  a = digitalRead(0);
  b = digitalRead(7);
  c = digitalRead(8);
  d = digitalRead(9);
  e = digitalRead(11);
  f = digitalRead (12);

  if (x == LOW)
  {
    sfx.playTrack(1);
  }
  if (y == LOW)
  {
    sfx.playTrack(2);
  }
  if (z == LOW)
  {
    sfx.playTrack(3);
  }
  if (a == LOW)
  {
    sfx.playTrack(4);
  }

  val = analogRead(DRUM1);  // Read the voltage
  if (val > 30)
  {
    sfx.playTrack(5);
  }

  if (c == LOW)
  {
    sfx.playTrack(6);
  }

  if (d == LOW)
  {
    sfx.playTrack(7);
  }

  if (e == LOW)
  {
    (v >= 0, v++) && (v <= 204);
    if (! (v = sfx.volUp()) ) {
      matrix.print(v++, DEC);
      matrix.writeDisplay();
      delay(500);
    }
    matrix.print(v + 1, DEC);
    matrix.writeDisplay();
    delay(500);

  }
  if (f == LOW)
  {
    (v <= 204, v--) && (v >= 0);
    if (! (v = sfx.volDown()) ) {
      matrix.print(v--, DEC);
      matrix.writeDisplay();
      delay(500);
    }
    matrix.print(v - 1, DEC);
    matrix.writeDisplay();
    delay(500);
  }



}

void flushInput() {
  // Read all available serial input to flush pending data.
  uint16_t timeoutloop = 0;
  while (timeoutloop++ < 40) {
    while (ss.available()) {
      ss.read();
      timeoutloop = 0;  // If char was received reset the timer
    }
    delay(1);
  }
}

char readBlocking() {
  while (!Serial.available());
  return Serial.read();
}

uint16_t readnumber() {
  uint16_t x = 0;
  char c;
  while (! isdigit(c = readBlocking())) {
    //Serial.print(c);
  }
  Serial.print(c);
  x = c - '0';
  while (isdigit(c = readBlocking())) {
    Serial.print(c);
    x *= 10;
    x += c - '0';
  }
  return x;
}

uint8_t readline(char *buff, uint8_t maxbuff) {
  uint16_t buffidx = 0;

  while (true) {
    if (buffidx > maxbuff) {
      break;
    }

    if (Serial.available()) {
      char c =  Serial.read();
      //Serial.print(c, HEX); Serial.print("#"); Serial.println(c);

      if (c == '\r') continue;
      if (c == 0xA) {
        if (buffidx == 0) {  // the first 0x0A is ignored
          continue;
        }
        buff[buffidx] = 0;  // null term
        return buffidx;
      }
      buff[buffidx] = c;
      buffidx++;
    }
  }
  buff[buffidx] = 0;  // null term
  return buffidx;
}
/************************ MENU HELPERS ***************************/
