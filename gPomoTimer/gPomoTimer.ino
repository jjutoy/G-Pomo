/*
  AUTHOR: John Jutoy
  Ver1 12/7/2018
  *****************TASKS:
  - account for millis() rollover if RTC still not implemented
  - figure out how to stop led cycle on any button press
  - set modes for more options for songs and times.
  *****************BUGS:

  PWM on LED's don't seem to work/break ir-Reciever
*/

//HEX CODE Values for IR-Remote
//IR_Code: FFA25D, Bits: 32 - 1
//IR_Code: FF629D, Bits: 32 - 2
//IR_Code: FFE21D, Bits: 32 - 3
//IR_Code: FF22DD, Bits: 32 - 4
//IR_Code: FF02FD, Bits: 32 - 5
//IR_Code: FFC23D, Bits: 32 - 6
//IR_Code: FFE01F, Bits: 32 - 7
//IR_Code: FFA857, Bits: 32 - 8
//IR_Code: FF906F, Bits: 32 - 9
//IR_Code: FF6897, Bits: 32 - *
//IR_Code: FF9867, Bits: 32 - 0
//IR_Code: FFB04F, Bits: 32 - #
//IR_Code: FF18E7, Bits: 32 - up
//IR_Code: FF10EF, Bits: 32 - left
//IR_Code: FF38C7, Bits: 32 - ok
//IR_Code: FF5AA5, Bits: 32 - right
//IR_Code: FF4AB5, Bits: 32 - down

//Mario Tune Framework Code
//  by: Dipto Pratyaksa
//  last updated: 31/3/13
#define NOTE_Rest 0
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

//Melodies and Frequency Arrays
//Mario main theme melody
int melody[] = {

  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};
//Underworld melody
int underworld_melody[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4,
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};

//Underwolrd tempo
int underworld_tempo[] = {
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18, 18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};

int wind_scene_melody[] = {
  NOTE_D5, NOTE_E5,
  NOTE_F5, NOTE_C5, NOTE_A5, NOTE_D6, NOTE_Rest, NOTE_Rest, NOTE_D6
};

int wind_scene_tempo[] = {
  4, 4,
  8, 8, 8, 8, 8, 8, 8, 8
};

int stranger_things_melody[] = {
  NOTE_A5, NOTE_C5, NOTE_E5, NOTE_G5, NOTE_A6, NOTE_G5, NOTE_E5, NOTE_C5,
  NOTE_A5, NOTE_C5, NOTE_E5, NOTE_G5, NOTE_A6, NOTE_G5, NOTE_E5, NOTE_C5,
  NOTE_A5, NOTE_C5, NOTE_E5, NOTE_G5, NOTE_A6, NOTE_G5, NOTE_E5, NOTE_C5,
  NOTE_A5, NOTE_C5, NOTE_E5, NOTE_G5, NOTE_A6, NOTE_G5, NOTE_E5, NOTE_C5
};

int stranger_things_tempo[] = {
  16, 16, 16, 16, 16, 16, 16, 16,
  16, 16, 16, 16, 16, 16, 16, 16,
  16, 16, 16, 16, 16, 16, 16, 16,
  16, 16, 16, 16, 16, 16, 16, 16
};

//int jingleBells_melody[] = {
//  NOTE_C4, NOTE_A5, NOTE_G4, NOTE_F4,
//  NOTE_C4, NOTE_C4, NOTE_C4,
//  NOTE_C4, NOTE_A5, NOTE_G4, NOTE_F4,
//  NOTE_D4,
//
//  NOTE_D4, NOTE_AS5, NOTE_A5, NOTE_G4,
//  NOTE_E4,
//  NOTE_C5, NOTE_C5, NOTE_AS5, NOTE_G4,
//  NOTE_A5,
//
//  NOTE_C4, NOTE_A5, NOTE_G4, NOTE_F4,
//  NOTE_C4,
//  NOTE_C4, NOTE_A5, NOTE_G4, NOTE_F4,
//  NOTE_D4, NOTE_D4
//};
//
//int jingleBells_tempo[] = {
//  4, 4, 4, 4,
//  4 / 3, 8, 8,
//  4, 4, 4, 4,
//  4 / 3,
//
//  4, 4, 4, 4,
//  4 / 3,
//  4, 4, 4, 4,
//  4 / 3,
//
//  4, 4, 4, 4,
//  4 / 3,
//  4, 4, 4, 4,
//  4 / 3, 4
//};

#include <IRremote.h>
const int irReceiverPin = 13;
IRrecv irrecv(irReceiverPin);
decode_results irRem;

//init pins for LED's
int redPin = 11;
int greenPin = 10;
int bluePin = 9;
int song = 0;
#define melodyPin 3
long timerStart = 0;
long timerDur = 0;
bool timerOn = false;

long lastLED = 0;
long delayLED = 2500; //blink delay
//clean this mess...
int ledA[] = {redPin, greenPin, bluePin};

#define BUTTONPRESSWAIT_TIME 150
int state = LOW;
int blinkDelay = 500;
bool cycle = true;
int i = 0;
int mode = 0;
long lastPressTime = 0;


void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(3, OUTPUT);//buzzer

  delay(1000);
  Serial.println("PROGRAM STARTED"); //For debugging
  Serial.println();
  digitalWrite(redPin, HIGH);
}

//************************************************LOOP START*****************************************

void loop()
{

  cycle = true; //Allows LED Cycling to run if true
  timerCheck();
  
  if (irrecv.decode(&irRem))
  {

//start:

    if (millis() - lastPressTime > BUTTONPRESSWAIT_TIME) {
      //Debug
      Serial.print("IR_Code: ");
      Serial.print(irRem.value);
      Serial.print(", Bits: ");
      Serial.println(irRem.bits);

      switch (irRem.value) {
        case 16753245:
          Serial.println("Pressed 1");
          allLED(false);
          digitalWrite(redPin, HIGH);
          break;

        case 16736925:
          Serial.println("Pressed 2");
          allLED(false);
          digitalWrite(greenPin, HIGH);
          break;

        case 16769565:
          Serial.println("Pressed 3");
          allLED(false);
          digitalWrite(bluePin, HIGH);
          break;

        case 16720605:
          Serial.println("Pressed 4");
          timerSet(1200);
          break;

        case 16712445:
          Serial.println("Pressed 5");
          timerSet(300);
          break;

        case 16761405:
          Serial.println("Pressed 6");
          timerSet(30);
          break;

        case 16769055:
          Serial.println("Pressed 7");
          sing(3);
          break;

        case 16754775:
          Serial.println("Pressed 8");
          sing(2);
          break;

        case 16748655:
          Serial.println("Pressed 9");
          sing(1);
          break;

        case 16738455:
          Serial.println("Pressed *");
          lastPressTime = millis();
          irrecv.resume();
          while (cycle) {
            timerCheck();
            allLED(false);
            digitalWrite(ledA[i], HIGH);

            Serial.println("LED CYCLE");
            //Serial.println(&irRem);
            if (millis() - lastPressTime > 1000) {
              if (irrecv.decode(&irRem)) {
                if (irRem.value == 16738455) {
                  Serial.println("C=F");

                  cycle = false;
                  lastPressTime = millis();
                  //goto start;
                }
                irrecv.resume();
              }

            }

            if (i == 2) {
              i = 0;
            } else {
              i++;
            }

            delay(blinkDelay);

          }




          break;

        case 16750695:
          Serial.println("Pressed 0");
          break;

        case 16756815:
          Serial.println("Pressed #");
          break;

        case 16718055:
          Serial.println("Pressed up");
          allLED(true);
          break;

        case 16716015:
          Serial.println("Pressed left");
          break;

        case 16726215:
          Serial.println("Pressed ok");
          sing(4);
          sing(4);
          break;

        case 16734885:
          Serial.println("Pressed right");
          break;

        case 16730805:
          Serial.println("Pressed down");
          allLED(false);
          break;

        default:
          Serial.println("Input Not Understood");
          break;
      }
      lastPressTime = millis();
    }
    irrecv.resume();
  }
  delay(20);

}


void sing(int s) {
  // iterate over the notes of the melody:
  song = s;
  if (song == 2) {
    Serial.println(" 'Underworld Theme'");
    int size = sizeof(underworld_melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / underworld_tempo[thisNote];

      buzz(melodyPin, underworld_melody[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

    }

  }

  else if (song == 3) {
    Serial.println(" WIND SCENE - CHRONO TRIGGER");
    int size = sizeof(wind_scene_melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / wind_scene_tempo[thisNote];

      buzz(melodyPin, wind_scene_melody[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);
    }
  }
  else if (song == 4) {
    Serial.println(" Stranger THEME");
    int size = sizeof(stranger_things_melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = (8000 / 6) / stranger_things_tempo[thisNote];

      buzz(melodyPin, stranger_things_melody[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 2;   // test
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

    }
  } else {

    Serial.println(" 'Mario Theme'");
    int size = sizeof(melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo[thisNote];

      buzz(melodyPin, melody[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

    }
  }
}

void buzz(int targetPin, long frequency, long length) {
  digitalWrite(bluePin, HIGH);
  long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to
  //// get the total number of cycles to produce
  for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
    digitalWrite(targetPin, HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin, LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
  digitalWrite(bluePin, LOW);

}

//Function to turn on/off all LED's
void allLED(bool on) {
  if (on) {
    digitalWrite(redPin, HIGH);
    digitalWrite(bluePin, HIGH);
    digitalWrite(greenPin, HIGH);
  } else {
    digitalWrite(redPin, LOW);
    digitalWrite(bluePin, LOW);
    digitalWrite(greenPin, LOW);
  }
}

void timerSet(double secDur) {
  allLED(false);
  timerOn = 1;
  timerStart = millis();  
  timerDur = secDur * 1000.0;
}

void timerCheck(){
  if(timerOn == true){
    if(millis() - timerStart >= timerDur){
      timerStart = 0;
      timerOn = false;
      
      cycle = false;
      allLED(true);
      sing(3);
      
    } else if((millis() - timerStart >= 0.66 * timerDur) && (millis() - lastLED >= delayLED)){
      allLED(false);
      digitalWrite(bluePin, HIGH);
      lastLED = millis();   
      
    } else if((millis() - timerStart >= 0.33 * timerDur) && (millis() - lastLED >= delayLED)){
      allLED(false);
      digitalWrite(greenPin, HIGH);   
      lastLED = millis();
      
    } else if(millis() - lastLED >= delayLED) {
      allLED(false);
      digitalWrite(redPin, HIGH);   
      lastLED = millis();
    } else {
      allLED(false);
    }
  }
}


void blinkLED(int ledPin) {
    //code will blink LEDs  
}
