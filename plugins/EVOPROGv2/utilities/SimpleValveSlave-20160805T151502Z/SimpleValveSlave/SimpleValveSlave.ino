
/*

Control of a 28BYJ48 Stepper Motor based pinch valve

This version assumes possible valve positions as positive integers
Valve position resets after power off

Author: R Rodrigues
e-mail: r.rodrigues@warwick.ac.uk
Published by the EVOPROG project
www.evoprog.eu

Released 24/01/2016
\Update 01/06/2016 - eeprom: valve position

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

#include <TinyWireS.h>
#include <EEPROM.h>

#define I2C_SLAVE_ADDRESS 46 // EACH I2C SLAVE DEVICE MUST HAVE A UNIQUE ADDRESS

#ifndef TWI_RX_BUFFER_SIZE  //MAKE SURE TWO WIRE INTERFACE BUFFER HAS THE CORRECT SIZE
#define TWI_RX_BUFFER_SIZE ( 16 )
#endif

//PINS CONNECTED TO ULN2003APG 
#define valvePin1 0
#define valvePin2 1 
#define valvePin3 2 
#define valvePin4 3


volatile int motorDelay= 500; //DEFINES THE DELAY AFTER EACH STEP: LOWER MEANS FASTER

//DEFINES COIL ACTIVATION SEQUENCE; FULL STEPPING MODE, 2 STEPS PER INSTRUCTION
int lookup[8] = {B01001, B00011, B00110 ,B01100,B01001, B00011, B00110 ,B01100};

//ALL COILS OFF 
int stopTurn = B00000;


volatile uint8_t reg_position=-1; //INTERNAL RESGISTER, TRACKS STATE FOR COMMS

volatile int valvePosition = 1; //KEEPS TRACK OF VALVE POSITION

volatile boolean moveValve = false; //TRACKS IF A MOVE COMMAND HAS BEEN ISSUED

volatile int moveSteps = 32; //NUMBER OF STEPS TO MOVE PER TRAVEL UNIT
    //32 for 45 degrees
    //16 for 22.5 degrees
volatile int target = 0; //TARGET POSITION RECEIVED



void setup() {
  //EEPROM.update(253,1); // USED TO SET UP THE INITIAL POSITION OF THE VALVE IN THE EEPROM
  pinMode( valvePin1 , OUTPUT); //SET STEPPER MOTOR PINS AS OUTPUT
  pinMode( valvePin2 , OUTPUT);
  pinMode( valvePin3 , OUTPUT);
  pinMode( valvePin4 , OUTPUT);

  pinMode(7, OUTPUT);
  
  TinyWireS.begin(I2C_SLAVE_ADDRESS); //START COMMS
  
  TinyWireS.onReceive(receiveEvent); //RECEIVE EVENT HANDLING
  TinyWireS.onRequest(requestEvent); //REQUEST EVENT HANDLING

  valvePosition = EEPROM.read(253); //READ VALUE FOR THE LAST POSITION
  _delay_ms(3);

  digitalWrite(7,HIGH);
  _delay_ms(1000);
  digitalWrite(7,LOW);
}

void loop() {
 TinyWireS_stop_check(); //REQUIRED FOR COMMS


if(moveValve){ //CHECKS FOR ORDER TO MOVE
  int dif = target-valvePosition; //CHECKS NUMBER OF TRAVEL UNITS
  
  moveSteps= 32*dif; //CALCULATES NUMBER OF STEPS
  
  int count = 15; //COUNTS 15 STEPS BEFORE CHECKING FOR THE STOP SIGNAL IN THE I2C LINE, TO AVOID COMMUNICATION ISSUES
  if(dif>-1){ 
    //MOVING CLOCKWISE
    while(moveSteps>0){
      clockwiseValve(); //MOVE ONE STEP
      count--;  //VARIABLE TO CHECK FOR STOP COMMAND
      moveSteps--; //COUNT DOWN NUMBER OF STEPS
      if(count==0){
        TinyWireS_stop_check();
        count=15;
      }
    }
    stopValve(); //SWITCHES COILS OFF
    moveValve=false; //DONE MOVING
    valvePosition=target; //ARRIVED TO TARGET POSITION
    
  }else{
    //MOVING COUNTERCLOCKWISE (SAME AS CLOCKWIE)
    moveSteps = abs(moveSteps); //POSITIVE VALUE NEEDED
    while(moveSteps>0){ 
      anticlockwiseValve();
      moveSteps--;
      count--;
      if(count==0){
        TinyWireS_stop_check();
        count=15;
      }
    }
    stopValve(); //SWITCHES COILS OFF
    moveValve=false; //DONE MOVING
    valvePosition=target; //ARRIVED TO TARGET POSITION
  }
  EEPROM.update(253,target); //UPDATE VALVE POSITION IN THE EEPROM 
  _delay_ms(10);
}
 
}

void stopValve(){ //COILS OFF TO LIMIT CURRENT DRAW
    digitalWrite(valvePin1, LOW);    
    digitalWrite(valvePin2, LOW);
    digitalWrite(valvePin3, LOW);
    digitalWrite(valvePin4, LOW);
    
}

void clockwiseValve(){ //MOVE STEPPER CLOCKWISE
  for(int i = 7; i >= 0; i--) // 8 pulses
  {
    digitalWrite(valvePin1, bitRead(lookup[i], 0));
    delayMicroseconds(motorDelay); 
    digitalWrite(valvePin2, bitRead(lookup[i], 1));
    delayMicroseconds(motorDelay); 
    digitalWrite(valvePin3, bitRead(lookup[i], 2));
    delayMicroseconds(motorDelay); 
    digitalWrite(valvePin4, bitRead(lookup[i], 3));
    delayMicroseconds(motorDelay);   
  }
  
  
}

void anticlockwiseValve(){ //MOVE STEPPER COUNTERCLOCKWISE
  for(int i = 0; i < 8; i++) // 8 pulses
  {
    digitalWrite(valvePin1, bitRead(lookup[i], 0));
    delayMicroseconds(motorDelay); 
    digitalWrite(valvePin2, bitRead(lookup[i], 1));
    delayMicroseconds(motorDelay); 
    digitalWrite(valvePin3, bitRead(lookup[i], 2));
    delayMicroseconds(motorDelay); 
    digitalWrite(valvePin4, bitRead(lookup[i], 3));
    delayMicroseconds(motorDelay);   
  }
  
}

void requestEvent() //MASTER REQUESTS REGISTER VALUES
{   
    if(reg_position==7){
       TinyWireS.send(0xAA); //REPLIES TO THE INITIAL CHECK OF THE MASTER - CONFIRMS PRESENCE OF A CONTROLLER WITH THE ADDRESS
    }else if(reg_position==11){
       TinyWireS.send(15); //CHANGE OF STEPPER DELAY
    }else if(reg_position==12){
      if(moveValve){
       TinyWireS.send(100); //BUSY MOVING TO A NEW POSITION
      }else{
        TinyWireS.send(101); //NOT MOVING
      }
	} else if(reg_position == 20) {
		TinyWireS.send(valvePosition);
    }else{
       TinyWireS.send(35); //REGISTER NOT USED    
    }
}



void receiveEvent(uint8_t howMany)
{
    if (howMany < 1){// Sanity-check
        return;
    }
    if (howMany > TWI_RX_BUFFER_SIZE){// Sanity-check
       
        return;
    }

    reg_position = TinyWireS.receive(); //RECEIVE REGISTER POSITION
    howMany--;
    
    if (!howMany){
        return;
    } 
    
    while(howMany--)
    {
      if(reg_position==10){
        //NOT IMPLEMENTED
      }else if(reg_position==11){ //CHANGE OF STEPPER DELAY
        motorDelay = 100*TinyWireS.receive(); 
       }else if(reg_position==12){ //SETS TARGET POSITION
        if (target>-1){ //SANITY CHECK
        target = TinyWireS.receive();
        if(target!=valvePosition){ //CHECK IF POSITION NEEDS TO BE CHANGED
         moveValve=true; //FLAG THE NEED TO MOVE TO A NEW POSITION
         
        }
        }
        
      } else if (reg_position==253) {
		  int temp1 = TinyWireS.receive();
		  EEPROM.update(253,temp1); //UPDATE VALVE POSITION IN THE EEPROM 
	  }


    }
      
 }

        
    

