#include <IRremote.h>
#include <Wire.h>
#include "paj7620.h"


#define TV_POWER              0xE0E040BF
#define TV_VOLUME_UP          0xE0E0E01F
#define TV_VOLUME_DOWN        0xE0E0D02F
#define TV_OK                 0xE0E016E9
#define TV_RETURN             0xE0E01AE5
#define TV_RIGHT              0xE0E046B9
#define TV_LEFT               0xE0E0A659
#define TV_UP                 0xE0E006F9
#define TV_DOWN               0xE0E08679
#define TV_HOME               0xE0E058A7


#define GES_REACTION_TIME     300
#define GES_QUIT_TIME         100
#define BIT_SIZE              32


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

  Serial.begin(9600);
  Serial.println("\nPAJ7620U2 TEST DEMO: Recognize 15 gestures.");

  error = paj7620Init();  
}

void loop()
{
  uint8_t data = 0, data1 = 0, error; 

  error = paj7620ReadReg(0x43, 1, &data);       // Read Bank_0_Reg_0x43/0x44 for gesture result.
  if (!error) 
  {
    switch (data)                   // When different gestures be detected, the variable 'data' will be set to different values by paj7620ReadReg(0x43, 1, &data).
    {
      case GES_RIGHT_FLAG:
        delay(GES_REACTION_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_LEFT_FLAG) 
        {
          sendReturn();
          Serial.println("Right-Left");
        }
        else if(data == GES_FORWARD_FLAG) 
        {
          sendOk();
          Serial.println("Forward");
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) 
        {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
        }
        else
        {
          sendRight();
          Serial.println("Right");
        }          
        break;
      case GES_LEFT_FLAG:
        delay(GES_REACTION_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_RIGHT_FLAG) 
        {
          sendReturn();
          Serial.println("Left-Right");
        }
        else if(data == GES_FORWARD_FLAG) 
        {
          Serial.println("Forward");
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) 
        {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
        }
        else
        {
          sendLeft();
          Serial.println("Left");
        }          
        break;
        break;
      case GES_UP_FLAG:
        delay(GES_REACTION_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_DOWN_FLAG) 
        {
          Serial.println("Up-Down");
        }
        else if(data == GES_FORWARD_FLAG) 
        {
          Serial.println("Forward");
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) 
        {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
        }
        else
        {
          sendUp();
          Serial.println("Up");
        }
        break;
      case GES_DOWN_FLAG:
        delay(GES_REACTION_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_UP_FLAG) 
        {
          Serial.println("Down-Up");
        }
        else if(data == GES_FORWARD_FLAG) 
        {
          Serial.println("Forward");
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) 
        {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
        }
        else
        {
          sendDown();
          Serial.println("Down");
        }
        break;
      case GES_FORWARD_FLAG:
        delay(GES_REACTION_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_BACKWARD_FLAG) 
        {
          sendHome();
          Serial.println("Forward-Backward");
          delay(GES_QUIT_TIME);
        }
        else
        {
          sendOk();
          Serial.println("Forward");
          delay(GES_QUIT_TIME);
        }
        break;
      case GES_BACKWARD_FLAG:     
        delay(GES_REACTION_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_FORWARD_FLAG) 
        {
          Serial.println("Backward-Forward");
          delay(GES_QUIT_TIME);
        }
        else
        {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
        }
        break;
      case GES_CLOCKWISE_FLAG:
        sendVolumeUp();
        Serial.println("Clockwise");
        break;
      case GES_COUNT_CLOCKWISE_FLAG:
        sendVolumeDown();
        Serial.println("anti-clockwise");
        break;  
      default:
        paj7620ReadReg(0x44, 1, &data1);
        if (data1 == GES_WAVE_FLAG) 
        {
          sendPowerOn();
          Serial.println("wave");
        }
        break;
    }
  }
  delay(100);
}

void sendPowerOn(){
   irsend.sendSAMSUNG(TV_POWER, BIT_SIZE); 
}

void sendReturn(){
   irsend.sendSAMSUNG(TV_RETURN, BIT_SIZE); 
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

void sendHome(){
   irsend.sendSAMSUNG(TV_HOME, BIT_SIZE); 
   irsend.sendSAMSUNG(TV_HOME, BIT_SIZE); 
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
