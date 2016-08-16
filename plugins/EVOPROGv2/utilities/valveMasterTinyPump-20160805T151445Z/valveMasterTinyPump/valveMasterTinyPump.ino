/*

Master for the control of multiple pinch valve and syringe pumps

Author: R Rodrigues
e-mail: r.rodrigues@warwick.ac.uk
Published by the EVOPROG project
www.evoprog.eu

Released 10/05/2016
Update 02/06/2016 - added comments, changed slave checking to cover 125 positions

Copyright (C) 2016  Rui Rodrigues

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

boolean DEBUG = true; //USE TO GET VERBOSE OUTPUT

#include "Wire.h"
#include <SerialCommand.h>

#define arr_len( x )  ( sizeof( x ) / sizeof( *x ) ) //lenght of an array

#define intFromByte(x,y) (x + (y << 8)) //CONVERT BYTE TO INT

SerialCommand sCmd;

void setup() {

  Serial.begin(115200); //Start Serial communication for control
  Serial.println("Start test");

  sCmd.addCommand("D", debugSerial);
  sCmd.addCommand("rValvePos", readValvePos);
  sCmd.addCommand("M",moveToSwitch); //move valve to position
  sCmd.addCommand("P",pumpRate); //set pumping rate in Hz
  sCmd.addCommand("pPump",pumpPause); //pause pump (omit address to send command to all pumps)
  sCmd.addCommand("calClock",calibrateClock); //change internal ATtiny clock calibration variable (this will become a constant for each pump calibrated against its specific linear regulator)
  sCmd.addCommand("writeClock",writeClock); //write clock variable to the EEPROM
  sCmd.addCommand("oValvePos",overrideValvePosition); //change valve position register
  sCmd.addCommand("wValvePos",writeValvePosition); //write valve position variable to the EEPROM
  sCmd.addCommand("oSwitch",overrideActiveSwitch); //change active microswitch 
  sCmd.addCommand("wSwitch",writeActiveSwitch); //write active microswitch to EEPROM
  sCmd.addCommand("oDir",overrideActiveDirection); //change rotation of stepper motor 
  sCmd.addCommand("wDir",writeActiveDirection); //write rotation to EEPROM

  
  Wire.begin(); //Start library for i2c communication
  Wire.endTransmission();

  delay(100);

// for(int i=0;i<125;i++){ //checks for slaves within the range
//    getOKfromSlave(i);
//  }
  Serial.println("Ready");
}


void loop() { 
  sCmd.readSerial();  //wait for instruction
}

void calibrateClock(){
  twoPartInstruction(255); //send new value for the ATTiny oscilator calibration variable OSCCAL 
}

void writeClock(){
  twoPartInstruction(254); //write new value for the ATTiny oscilator calibration variable OSCCAL into EEPROM
}

void writeValvePosition(){ //write valve's current position (pos int)
  twoPartInstruction(253);
}

void overrideValvePosition(){ //override valve's new position to the EEPROM
  twoPartInstruction(252);
}

void writeActiveSwitch(){ //write pump's active switch (values 0/1)
  twoPartInstruction(251);
}

void overrideActiveSwitch(){ //override pump's active switch (values 0/1)
  twoPartInstruction(250);
}

void writeActiveDirection(){ //write pump's current direction of rotation (values 0/1)
  twoPartInstruction(249);
}

void overrideActiveDirection(){ //override pump's current direction of rotation (values 0/1)
  twoPartInstruction(248);
}


void writeValveSpeed(){ //change valve speed
  sendInt(247);
}

void overrideValveSpeed(){ //write valve speed to EEPROM
  sendInt(246);
}


void moveToSwitch(){ //MOVES A PARTICULAR VALVE TO A POSITION
  twoPartInstruction(12);
}

void sendInt(int inst){ //send an integer value  to the address
   String temp = sCmd.next();
   int address = temp.toInt();  //get slave's address
   temp = sCmd.next();
   
   char intbuf[16]; //create buffer for int
   temp.toCharArray(intbuf, sizeof(intbuf));
   unsigned int newInt = atoi(intbuf); 
  
  int wireRet; // variable to old return value for comms commands

  unsigned char data[sizeof(newInt)]; //char array to old int bytes
  memcpy(&data,&newInt,sizeof(newInt)); //copy values
  
  Wire.beginTransmission(address); //start comm
  
  unsigned char dataC[3]={inst,data[0],data[1]}; //pack instruction
  wireRet=Wire.write(dataC,3); //send data
  
  Serial.println(wireRet); //print return from comm
  
  wireRet=Wire.endTransmission(); //end transmission
  
 
}


void getOKfromSlave(int slaveAddress){ //CHECK IF COMMS ARE WORKING WITH SLAVES
  uint8_t reply;
  byte wireRet = 0;

  Wire.beginTransmission(slaveAddress); //start comms with address
  Wire.write(7); //send register change command            
  
  wireRet= Wire.endTransmission();    
        
  if (DEBUG && wireRet!=0) { //prints if there is an error in debug mode
    Serial.println("error during check");
    Serial.println(wireRet);
  }
  delay(5);
  Wire.beginTransmission(slaveAddress); //start transmission again and request 1 byte
  wireRet= Wire.requestFrom(slaveAddress,1);

  Wire.endTransmission();
  
  delay(5);
  
  reply = Wire.read(); //get reply
  processReply(reply,slaveAddress); //process the reply for output

 
}

void twoPartInstruction(int registerSlave){//instruction that sends a register address and extra bytes
  String temp = sCmd.next();
  int address = temp.toInt(); //A NEW POSITION IS EXPECTED
  if(address!=0){ //if not broadcast
  temp = sCmd.next();
  unsigned char mainInstruction = temp.toInt(); //A NEW POSITION IS EXPECTED
  unsigned char dataC[2]={registerSlave,mainInstruction}; //pack data
  int wireRet;
  Wire.beginTransmission(address); //start comms
  wireRet=Wire.write(dataC,2); //send command
  if (DEBUG) Serial.println(wireRet); //check for return value in debug mode
  wireRet=Wire.endTransmission(); //end comms
  if (DEBUG) Serial.println(wireRet); //check for return value in debug mode
  }
}

void onePartInstruction(int registerSlave){ //instruction that only sends a register address
  
  String temp = sCmd.next();
  int address = temp.toInt(); //A NEW POSITION IS EXPECTED
  if(address!=0 || registerSlave==9){ //if not broadcast or pump pause command is being sent (pump pause can be sent without argument to stop all pumps)
  int wireRet;
  Wire.beginTransmission(address); //start comms
  wireRet=Wire.write(registerSlave);//send command
  if (DEBUG) Serial.println(wireRet);//check for return value in debug mode
  wireRet=Wire.endTransmission();//end comms
  if (DEBUG) Serial.println(wireRet);//check for return value in debug mode
  }
}

void pumpPause(){ //send command to pause pump
  onePartInstruction(9);
}

void pumpRate(){  //send frequency of stepping for pump
                  //this can be made into a more general function to send float values
   String temp = sCmd.next();
   int address = temp.toInt(); //A NEW POSITION IS EXPECTED
   if(address!=0){ //if not broadcast
     if (DEBUG) { //print the target address
     Serial.println("Address:");
     Serial.println(address);
     }
     temp = sCmd.next();
     char floatbuf[32]; // make this at least big enough for the whole float
     temp.toCharArray(floatbuf, sizeof(floatbuf));
     float rate = atof(floatbuf); 
    
    int wireRet;
  
    unsigned char data[sizeof(rate)]; //create array to hold float bytes
    memcpy(&data,&rate,sizeof(rate)); //copy bytes
    
    
    Wire.beginTransmission(address); //begin comms
    
    unsigned char dataC[5]={8,data[0],data[1],data[2],data[3]}; //pack data
    wireRet=Wire.write(dataC,5); //send command
    if (DEBUG) Serial.println(wireRet); //check for return value in debug mode
    wireRet=Wire.endTransmission(); //end transmission
    if (DEBUG) Serial.println(wireRet); //check for return value in debug mode

   }
}



void processReply(int reply,int slaveAddress){//PROCESSES REPLY FROM SLAVE
 if(reply==0xAA){ //slave replied
  
    Serial.println(slaveAddress);
    Serial.println("ATtiny84: READY");
    
  }else if(DEBUG && reply==0xFF){ //get slave reply in debug mode
    Serial.println("Address:" + slaveAddress);
    Serial.println("ATtiny84: COMMAND NOT RECOGNISED"); 
  }else if(DEBUG){ //unexpected reply
    
    Serial.println("ATtiny84: UNEXPECTED REPLY CODE");
    Serial.println(reply);
  }

}

void debugSerial() {
  Serial.println("is available?");
  String temp = sCmd.next();
  int slaveAddress = temp.toInt();
  
  getOKfromSlave(slaveAddress);
}

void readValvePos() {
  uint8_t reply;
  byte wireRet = 0;

  String temp = sCmd.next();
  int slaveAddress = temp.toInt();

  Wire.beginTransmission(slaveAddress); //start comms with address
  Wire.write(20); //send register change command            
  
  wireRet= Wire.endTransmission();    
        
  if (DEBUG && wireRet!=0) { //prints if there is an error in debug mode
    Serial.println("error during check");
    Serial.println(wireRet);
  }
  delay(5);
  Wire.beginTransmission(slaveAddress); //start transmission again and request 1 byte
  wireRet= Wire.requestFrom(slaveAddress,1);

  Wire.endTransmission();
  
  delay(5);
  
  reply = Wire.read(); //get reply
  Serial.println(reply);  
}



