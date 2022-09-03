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
const int irPowerPin = 2;

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

  error = paj7620ReadReg(0x43, 1, &data);      
  if (!error) 
  {
    switch (data)                 
    {
      case GES_RIGHT_FLAG:
        delay(GES_REACTION_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_LEFT_FLAG) 
        {
          sendCommand(TV_RETURN, "Right-Left");
        }
        else if(data == GES_FORWARD_FLAG) 
        {
          sendCommand(TV_OK, "Forward");
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) 
        {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
        }
        else
        {
          sendCommand(TV_RIGHT, "Right");
        }          
        break;
      case GES_LEFT_FLAG:
        delay(GES_REACTION_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_RIGHT_FLAG) 
        {
          sendCommand(TV_RETURN, "Left-Right");
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
          sendCommand(TV_LEFT, "Left");
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
          sendCommand(TV_UP, "Up");
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
          sendCommand(TV_DOWN, "Down");
        }
        break;
      case GES_FORWARD_FLAG:
        delay(GES_REACTION_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_BACKWARD_FLAG) 
        {
          sendCommand(TV_HOME, "Forward-Backward");
          delay(GES_QUIT_TIME);
        }
        else
        {
          sendCommand(TV_OK, "Forward");
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
        sendCommand(TV_VOLUME_UP, "Clockwise");
        break;
      case GES_COUNT_CLOCKWISE_FLAG:
        sendCommand(TV_VOLUME_DOWN, "anti-clockwise");
        break;  
      default:
        paj7620ReadReg(0x44, 1, &data1);
        if (data1 == GES_WAVE_FLAG) 
        {
          sendCommand(TV_POWER, "wave");
        }
        break;
    }
  }
  delay(100);
}

void sendCommand(uint32_t command, String gesture){
  digitalWrite(irPowerPin, HIGH);
  Serial.println(gesture); 
  irsend.sendSAMSUNG(command, BIT_SIZE); 
  irsend.sendSAMSUNG(command, BIT_SIZE); 
  irsend.sendSAMSUNG(command, BIT_SIZE);
  digitalWrite(irPowerPin, LOW);
}
