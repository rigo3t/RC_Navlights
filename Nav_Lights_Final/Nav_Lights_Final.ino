/*
Nav Lights
 This sketch simulates the light sequence for navigation lights 
 as mounted on Airbus aircraft as of the time of this writing, and a 
 replaced beacon "breathing" operation light
 
 By:
 Rigo & Rigo / February 2014
 
 Requirement:
 8 LEDs
 1x Green (Right Nav)
 1x Yellow (Rear Nav)
 3x Red (Left Nav and 2x Operating Beacon)
 3X White (Srobe wingtip and rear)
 
 Sequence 
 L&R Wing Nav: ON
 Wingtip Strobe: delay FLASH delay ms FLASH (WTSS)
 Back Strobe synced to WT Strobe sequence as follows: (WTSS) delay ms FLASH
 Beacon "breathing fade" with synced bright pulse to back strobe. 
 */

// Always the same pins on the board

#include <math.h>

const int posNav = 13;     // Red, Green and White LEDs for Positioning
const int strobeF = 10;    // Strobe lights on the wingtips' front
const int strobeR = 9;     // Strobe light tail
const int beaconOp = 11;   // Operation beacon 2x

boolean flagintervalLong = false; //it flags which off time period was before being on again

int strobeFState = HIGH; // the variable to check whether the led is on or off
int strobeRState = HIGH; // the variable to check whether the led is on or off

long strobeRIntervaloff = 1199;  // 1199millis rear strobe off period
long strobeRIntervalon = 79;     // 79millis rear strobe on
long strobeFIntervaloff = 79;    // 79millis front strobe short off 
long strobeFIntervalon = 99;     // 99millis front strobe on
long strobeFIntervalofflong = 999; // 999millis front strobe off long period

long strobeFCounteroff = 0;    // I use these variables to store the amount of time it's been since the led was last on, or off.
long strobeFCounteron = 0;     // I use these variables to store the amount of time it's been since the led was last on, or off. 
long strobeRCounteroff = 500;  // Stores the startup time of the rear strobe light
long strobeRCounteron = 500;   //


void setup() {

pinMode(strobeF, OUTPUT); // PIN 10 output
pinMode(strobeR, OUTPUT); // PIN 9 output
pinMode(posNav, OUTPUT);  // PIN 13 output
pinMode(beaconOp, OUTPUT); // PWM PIN 11
Serial.begin(9600); // Begin serial connection with PC
}

void strobeFFunction() // Function to power the rear strobe light
{
 if(strobeFState == HIGH) //when strobe F State is ON 
 {
    if(millis() - strobeFCounteron > strobeFIntervalon) //checks if the time lapsed is larger than the interval switched on
    {
      strobeFCounteron = millis();                      // If so, then switch it off
      strobeFCounteroff = millis();
      Serial.print("strobeFCounteron = ");
      Serial.println(strobeFCounteron);
      strobeFState = LOW;
      digitalWrite(strobeF, strobeFState);
      Serial.println("Strobe Wingtip OFF");
    }
 }
  else                                                 //if not, then, analize if the counter off is larger than the intervaloff long and if the boolean flaginterval long is met. Boolean was necessary or it would never exceed the required time without switching ot another state
  { //when strobe F State is OFF
     if(millis() - strobeFCounteroff > strobeFIntervalofflong && flagintervalLong) 
      {
      strobeFCounteron = millis();
      strobeFCounteroff = millis();
      Serial.print("strobeFCounteroff = ");
      Serial.println(strobeFCounteroff);
      strobeFState = HIGH;
      flagintervalLong = false;
      digitalWrite(strobeF, strobeFState);
      Serial.println("Strobe Wingtip ON");
      }
      else                                            //if the previous wasn't true either, check if the counter off is larger than the interval off short and it is NOT flagintervalLong! If it wasn't then switch it to true so it will be caught on the next iteration.
      {
          if(millis() - strobeFCounteroff > strobeFIntervaloff && !flagintervalLong) 
        {
        strobeFCounteron = millis();
        strobeFCounteroff = millis();
        Serial.print("strobeFCounteroff = ");
        Serial.println(strobeFCounteroff);
        strobeFState = HIGH;
        flagintervalLong = true;
        digitalWrite(strobeF, strobeFState);
        Serial.println("Strobe Wingtip ON");
        }
      }
   } 
 }



void strobeRFunction() // Function to power the rear strobe light
{
 if(strobeRState == HIGH) //when strobe R State is ON
 {
    if(millis() - strobeRCounteron > strobeRIntervalon) // if the strobe counter is larger than it's interval on, then switch off. 
    {
      strobeRCounteron = millis();
      strobeRCounteroff = millis();
      Serial.print("strobeRCounteron = ");
      Serial.println(strobeRCounteron);
      strobeRState = LOW;
      digitalWrite(strobeR, strobeRState);
      Serial.println("Strobe Rear OFF");
    }
 }
  else
  { //when strobe R State is OFF
     if(millis() - strobeRCounteroff > strobeRIntervaloff) //if not then switch on
      {
      strobeRCounteron = millis();
      strobeRCounteroff = millis();
      Serial.print("strobeRCounteroff = ");
      Serial.println(strobeRCounteroff);
      strobeRState = HIGH;
      digitalWrite(strobeR, strobeRState);
      Serial.println("Strobe Rear ON");
      }
   } 
 }
 
void beaconOperation() // Function to switch on beacon operation light.
{
  float val = (exp(sin(millis()/1000.0*PI)) - 0.36787944)*108.0; // Mathematical equation used for fading the Operation Beacon in a "breathing" pattern. 
  analogWrite(beaconOp, val);
  
}

 void navigationL() //simply puts the position lights on
 {
    digitalWrite (posNav, HIGH); //Position lights are always on.
}


void loop()
{
  navigationL();      //Run position lights function
  beaconOperation();  //Run beacon lights function
  strobeFFunction();  //Run strobe wingtip function
  if (millis() > 499) //Run strobe rear IF the condition that at least 499millis have elapsed to keep time along with the dual blink of the strobe is met
  { 
   strobeRFunction(); // calls strobe rear function
  }
}

