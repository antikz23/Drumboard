#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>
#include <Wire.h>
#include "Adafruit_Trellis.h"
unsigned int duration[16];
char note[16][6];
int count, next, last;
byte val = 0;

Adafruit_Trellis matrix0 = Adafruit_Trellis();
Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0);
#define NUMTRELLIS 1
#define numKeys (NUMTRELLIS * 16)

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
  pinMode(7, OUTPUT);
  pinMode(INTPIN, INPUT);
  digitalWrite(INTPIN, HIGH);
  trellis.begin(0x70);  // only one
  for (uint8_t i = 0; i < numKeys; i++) {
    trellis.setLED(i);
    trellis.writeDisplay();
    delay(50);
  }
  // then turn them off
  for (uint8_t i = 0; i < numKeys; i++) {
    trellis.clrLED(i);
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

  // printDirectory(SD.open("/"), 0);

  musicPlayer.setVolume(20, 20);

  //musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int

}

void loop() {
  delay(30); // 30ms delay is required, dont remove me!
  //Serial.println(count++);

  if (trellis.readSwitches())
  {
    if (trellis.justPressed(0))
    {
      musicPlayer.startPlayingFile("A.mp3");
      next = millis();  //STORES LAST READING FROM TIMER
      duration[count++] = next - last;  //STORES DIFF BETWEEN PRESENT AND LAST READING
      //note[count] = "track001.mp3";
      strncpy(note[count], "A.mp3", 6);
      last = next;
      trellis.setLED(0);
    }
    if (trellis.justReleased(0))
    {
      trellis.clrLED(0);
      musicPlayer.stopPlaying();
    }

    if (trellis.justPressed(1))
    {
      musicPlayer.startPlayingFile("B.mp3");
      next = millis();  //STORES LAST READING FROM TIMER
      duration[count++] = next - last;  //STORES DIFF BETWEEN PRESENT AND LAST READING
      //note[count] = "track002.mp3";
      strncpy(note[count], "B.mp3", 6);
      last = next;
      trellis.setLED(1);
    }
    if (trellis.justReleased(1))
    {
      musicPlayer.stopPlaying();
      trellis.clrLED(1);
    }

    if (trellis.justPressed(2))
    {
      musicPlayer.startPlayingFile("C.mp3");
      next = millis();  //STORES LAST READING FROM TIMER
      duration[count++] = next - last;  //STORES DIFF BETWEEN PRESENT AND LAST READING
      //note[count] = "track003.mp3";
      strncpy(note[count], "C.mp3", 6);
      last = next;
      trellis.setLED(2);
    }
    if (trellis.justReleased(2))
    {
      musicPlayer.stopPlaying();
      trellis.clrLED(2);
    }

    if (trellis.justPressed(3))
    {
      musicPlayer.startPlayingFile("D.mp3");
      next = millis();  //STORES LAST READING FROM TIMER
      duration[count++] = next - last;  //STORES DIFF BETWEEN PRESENT AND LAST READING
      //note[count] = "track004.mp3";
      strncpy(note[count], "D.mp3", 6);
      last = next;
      trellis.setLED(3);
    }
    if (trellis.justReleased(3))
    {
      musicPlayer.stopPlaying();
      trellis.clrLED(3);
    }

    if (trellis.justPressed(4))
    {
      musicPlayer.startPlayingFile("E.mp3");
      next = millis();  //STORES LAST READING FROM TIMER
      duration[count++] = next - last;  //STORES DIFF BETWEEN PRESENT AND LAST READING
      //note[count] = "track005.mp3";
      strncpy(note[count], "E.mp3", 6);
      last = next;
      trellis.setLED(4);
    }
    if (trellis.justReleased(4))
    {
      musicPlayer.stopPlaying();
      trellis.clrLED(4);
    }
    
    if (trellis.justPressed(5))
    {
      next = millis();  //STORES LAST READING FROM TIMER
      duration[count++] = next - last;
      musicPlayer.startPlayingFile("F.mp3");
      //next = millis();  //STORES LAST READING FROM TIMER
      //duration[count++] = next - last;  //STORES DIFF BETWEEN PRESENT AND LAST READING
      //note[count] = "track006.mp3";
      strncpy(note[count], "F.mp3", 6);
      last = next;
      trellis.setLED(5);
    }
    if (trellis.justReleased(5))
    {
      musicPlayer.stopPlaying();
      trellis.clrLED(5);
    }

    if (trellis.justPressed(6))
    {
      next = millis();
      duration[count++] = next - last;
      musicPlayer.startPlayingFile("G.mp3");
      //next = millis();  //STORES LAST READING FROM TIMER
      //  //STORES DIFF BETWEEN PRESENT AND LAST READING
      //note[count] = "track007.mp3";
      strncpy(note[count], "G.mp3", 6);
      last = next;
      trellis.setLED(6);
    }
    if (trellis.justReleased(6))
    {
      musicPlayer.stopPlaying();
      trellis.clrLED(6);
    }
    if (count == 14)
    { //IF THE USER HAS PRESSED THE BUTTON FIVE TIMES
      delay(1000);  //CREATE A PAUSE BEFORE PLAYING THE STORED SOUND
      for (int x = 1; x <= 14; x++)
      { //PLAY THE FIVE TONES
        musicPlayer.startPlayingFile(note[x]);
        delay(duration[x]-30);
         musicPlayer.stopPlaying();
      }
      count = 0;
    }

  }

}


/*  // File is playing in the background
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

    delay(100);
  }
  }*/


/// File listing helper
/*void printDirectory(File dir, int numTabs) {
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
*/
