
int nStep;

volatile int targetPosition = 0;
//DEFINES COIL ACTIVATION SEQUENCE; FULL STEPPING MODE, 2 STEPS PER INSTRUCTION
const int lookup[8] = {B01001, B00011, B00110 ,B01100,B01001, B00011, B00110 ,B01100};
//ALL COILS OFF 
const int stopTurn = B00000;



void moveValveEnabled(){
  EEPROM.update(253,target);
  _delay_ms(10);
   //CHECKS FOR ORDER TO MOVE
  int dif = target-valvePosition; //CHECKS NUMBER OF TRAVEL UNITS
  int tempMoveSteps= 32*dif; //CALCULATES NUMBER OF STEPS
  int count = 15; //COUNTS 15 STEPS BEFORE CHECKING FOR THE STOP SIGNAL IN THE I2C LINE, TO AVOID COMMUNICATION ISSUES
  if(dif>-1){ 
    //MOVING CLOCKWISE
    while(tempMoveSteps>0){
      clockwiseValve();
      count--;
      tempMoveSteps--;
      if(count==0){
        TinyWireS_stop_check();
        count=15;
      }
    }
    stopValve(); //SWITCHES COILS OFF
    moveValve=false; //DONE MOVING
    valvePosition=target; //ARRIVED TO TARGET POSITION
  
  }else{
    //MOVING COUNTERCLOCKWISE
    tempMoveSteps = abs(tempMoveSteps); //POSITIVE VALUE NEEDED
    while(tempMoveSteps>0){
      anticlockwiseValve();
      tempMoveSteps--;
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
}


void stopValve(){ //COILS OFF
    digitalWrite(valvePin1, LOW);    
    digitalWrite(valvePin2, LOW);
    digitalWrite(valvePin3, LOW);
    digitalWrite(valvePin4,LOW);
    
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



