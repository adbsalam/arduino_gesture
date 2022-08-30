#include "RevEng_PAJ7620.h"
#include <IRremote.h>

// Create gesture sensor driver object
RevEng_PAJ7620 sensor = RevEng_PAJ7620();


#define BIT_SIZE              32
#define TV_POWER              0xE0E040BF
#define TV_VOLUME_UP          0xE0E0E01F
#define TV_VOLUME_DOWN        0xE0E0D02F
#define TV_OK                 0xE0E016E9
#define TV_RETURN .           0xE0E01AE5
#define TV_RIGHT              0xE0E046B9
#define TV_LEFT               0xE0E0A659
#define TV_UP                 0xE0E006F9
#define TV_DOWN               0xE0E08679


const int SEND_PIN = 7;
const int power = 4;
const int info = 5;
const int factory = 6;
const int threespeed = 7;

IRsend irsend(SEND_PIN);

void setup(){

  pinMode (power, INPUT_PULLUP);
  pinMode (info, INPUT_PULLUP);
  pinMode (factory, INPUT_PULLUP);
  pinMode (threespeed, INPUT_PULLUP);
  
  uint8_t error = 0;

  Serial.begin(115200);

  Serial.println("PAJ7620 sensor demo: Recognizing all 9 gestures.");

  if( !sensor.begin() ) 
  {
    Serial.print("PAJ7620 I2C error - halting");
    while(true) { }
  }

  Serial.println("PAJ7620 init: OK");
  Serial.println("Please input your gestures:");
}


void loop() {
  Gesture gesture;                  // Gesture is an enum type from RevEng_PAJ7620.h
  gesture = sensor.readGesture();   // Read back current gesture (if any) of type Gesture

  switch (gesture)
  {
    case GES_FORWARD:
      {
        sendOk();
        Serial.print("GES_FORWARD");
        break;
      }

    case GES_BACKWARD:
      {
        Serial.print("GES_BACKWARD");
        break;
      }

    case GES_LEFT:
      {
        sendLeft();
        Serial.print("GES_LEFT");
        break;
      }

    case GES_RIGHT:
      {
        sendRight();
        Serial.print("GES_RIGHT");
        break;
      }

    case GES_UP:
      {
        sendUp();
        Serial.print("GES_UP");
        break;
      }

    case GES_DOWN:
      {
        sendDown();
        Serial.print("GES_DOWN");
        break;
      }

    case GES_CLOCKWISE:
      {
        sendVolumeUp();
        Serial.print("GES_CLOCKWISE");
        break;
      }

    case GES_ANTICLOCKWISE:
      {
        sendVolumeDown();
        Serial.print("GES_ANTICLOCKWISE");
        break;
      }

    case GES_WAVE:
      {
        sendPowerOn();
        Serial.print("GES_WAVE");
        break;
      }

    case GES_NONE:
      {
        break;
      }
  }

  if( gesture != GES_NONE )
  {
    Serial.print(", Code: ");
    Serial.println(gesture);
  }

  delay(100);
}

void sendPowerOn(){
   irsend.sendSAMSUNG(TV_POWER, BIT_SIZE); 
}

void sendOk(){
   irsend.sendSAMSUNG(TV_OK, BIT_SIZE); 
   irsend.sendSAMSUNG(TV_OK, BIT_SIZE); 
}

void sendUp(){
   irsend.sendSAMSUNG(TV_UP, BIT_SIZE); 
   irsend.sendSAMSUNG(TV_UP, BIT_SIZE); 
}

void sendDown(){
   irsend.sendSAMSUNG(TV_DOWN, BIT_SIZE); 
   irsend.sendSAMSUNG(TV_DOWN, BIT_SIZE); 
}

void sendLeft(){
   irsend.sendSAMSUNG(TV_LEFT, BIT_SIZE); 
   irsend.sendSAMSUNG(TV_LEFT, BIT_SIZE); 
}

void sendRight(){
   irsend.sendSAMSUNG(TV_RIGHT, BIT_SIZE); 
   irsend.sendSAMSUNG(TV_RIGHT, BIT_SIZE); 
}

void sendVolumeUp(){
   irsend.sendSAMSUNG(TV_VOLUME_UP, BIT_SIZE); 
   irsend.sendSAMSUNG(TV_VOLUME_UP, BIT_SIZE); 
   irsend.sendSAMSUNG(TV_VOLUME_UP, BIT_SIZE); 
   irsend.sendSAMSUNG(TV_VOLUME_UP, BIT_SIZE); 
   irsend.sendSAMSUNG(TV_VOLUME_UP, BIT_SIZE); 
   irsend.sendSAMSUNG(TV_VOLUME_UP, BIT_SIZE); 
}

void sendVolumeDown(){
   irsend.sendSAMSUNG(TV_VOLUME_DOWN, BIT_SIZE); 
   irsend.sendSAMSUNG(TV_VOLUME_DOWN, BIT_SIZE); 
   irsend.sendSAMSUNG(TV_VOLUME_DOWN, BIT_SIZE); 
   irsend.sendSAMSUNG(TV_VOLUME_DOWN, BIT_SIZE); 
   irsend.sendSAMSUNG(TV_VOLUME_DOWN, BIT_SIZE); 
}
