#include <SoftwareSerial.h>
#include "Adafruit_Soundboard.h"
#include <Wire.h>
#include <Keypad.h>
#define SFX_TX    11
#define SFX_RX    10
#define SFX_RST   12

#define sound_delay 50
byte val = 0;
SoftwareSerial ss = SoftwareSerial(SFX_TX, SFX_RX);
Adafruit_Soundboard sfx = Adafruit_Soundboard(&ss, NULL, SFX_RST);

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
// Define the Keymap
char keys[ROWS][COLS] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'0', 'F', 'E', 'D'}
};
// Connect keypad R0, R1, R2 and R3 to these Arduino pins.
byte rowPins[ROWS] = { 5, 4, 3, 2 };
// Connect keypad C0, C1, C2 and C3 to these Arduino pins.
byte colPins[COLS] = { 9, 8, 7, 6 };

// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

#define ledpin 13

void setup()
{
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  Serial.begin(9600);
  ss.begin(9600);
  sfx.reset();
}

void loop()
{
  if (digitalRead, 2 == HIGH)
  {
    Serial.print('1');
  }

  char key = kpd.getKey();
  if (key) // Check for a valid key.
  {
    switch (key)
    {
      case '1':
        sfx.playTrack(1);
        delay(sound_delay);
        Serial.println('1');
        break;

      case '4':
        sfx.playTrack(2);
        delay(sound_delay);
        Serial.println('4');
        break;

      case '7':
        sfx.playTrack(3);
        delay(sound_delay);
        Serial.println('7');
        break;

      case '0':
        sfx.playTrack(4);
        delay(sound_delay);
        Serial.println('0');
        break;

      default:
        Serial.println(key);
    }
  }
  
}
