
#include <TinyWireS.h>
#include <EnableInterrupt.h>
#include <EEPROM.h>

#define I2C_SLAVE_ADDRESS 7 // EACH I2C SLAVE DEVICE MUST HAVE A UNIQUE ADDRESS

#ifndef TWI_RX_BUFFER_SIZE
#define TWI_RX_BUFFER_SIZE ( 16 )
#endif

#define arr_len( x )  ( sizeof( x ) / sizeof( *x ) )
//extern uint8_t *bytes;
//uint16_t myInt1 = bytes[0] + (bytes[1] << 8);

#define intFromByte(x,y) (x + (y << 8))

int delayEnable = 1;
int delayP = 5;

volatile uint8_t reg_position=-1; //INTERNAL RESGISTER, TRACKS STATE FOR COMMS

/*const int pinMode0 =  24;
const int pinMode1 =  26;
const int pinMode2 =  28;*/
const int pinEnable = 8;
const int pinStep =   9; // Step signal 
const int pinDir =    10; // Direction


//PINS CONNECTED TO ULN2003APG 
#define valvePin1 0
#define valvePin2 1 
#define valvePin3 2 
#define valvePin4 3
const int motorDelay= 800; //DEFINES THE DELAY AFTER EACH STEP: LOWER MEANS FASTER
volatile int target = 0; //TARGET POSITION RECEIVED
volatile int valvePosition = 0; //KEEPS TRACK OF VALVE POSITION
int otherPos = 1;



volatile boolean pinDirCurrent = 1;
//volatile int lastPinInt= -1;
const int switchPin[2] = {5,7};

volatile int delayStepping;
volatile int delayMicroSStepping;
volatile int mode;
volatile int currentSwitch=0; 
volatile boolean moveValve = false; //TRACKS IF A MOVE COMMAND HAS BEEN ISSUED
volatile boolean pumpCommand = false;
volatile boolean switchCommand = false;
volatile boolean activatePumpCommand = false;
volatile boolean speedPump = false;
// int moveSteps = 32; //NUMBER OF STEPS TO MOVE PER TRAVEL UNIT

const int switchCompensate[2] = {1135,1135};

long switchInterval = 0;//(long)moveSteps*(long)otherPos*8*4*(long)motorDelay;


long switchStart = -1;
long switchEnd = -1;

void setup() {
  //eeprom_write_byte((uint8_t*)(255),108);
  MCUCR &= ~PUD;
/*
  EEPROM.write(255,107);
  EEPROM.write(253,1);
  EEPROM.write(251,0);
  EEPROM.write(249,1);*/

  OSCCAL = EEPROM.read(255);
  _delay_ms(3);
  valvePosition = EEPROM.read(253);
  _delay_ms(3);
  currentSwitch = EEPROM.read(251);
  _delay_ms(3);
  changeActiveSwitch();
  pinDirCurrent = EEPROM.read(249);
  _delay_ms(3);
  //motorDelay = intFromByte((uint8_t)EEPROM.read(245),(uint8_t)EEPROM.read(247));

/*  pinMode( pinMode0 , OUTPUT );
  pinMode( pinMode1 , OUTPUT );
  pinMode( pinMode2 , OUTPUT );*/
  pinMode( pinEnable, OUTPUT );
  pinMode( pinDir   , OUTPUT );
  pinMode( pinStep  , OUTPUT );
  pinMode(valvePin1, OUTPUT);
  pinMode(valvePin2, OUTPUT);
  pinMode(valvePin3, OUTPUT);
  pinMode(valvePin4, OUTPUT);
  
  digitalWrite( pinEnable, LOW);
  /*digitalWrite( pinMode0, HIGH);
  digitalWrite( pinMode1, HIGH);
  digitalWrite( pinMode2, HIGH);*/
  
  pinMode(switchPin[0], INPUT);
  pinMode(switchPin[1], INPUT);

  //enableInterrupt(switchPin[0], handleSwitch1, RISING);
  //enableInterrupt(switchPin[1], handleSwitch2, RISING);
  

  TinyWireS.begin(I2C_SLAVE_ADDRESS);
  
  TinyWireS.onReceive(receiveEvent); //RECEIVE EVENT HANDLING
  TinyWireS.onRequest(requestEvent); //REQUEST EVENT HANDLING

  digitalWrite( pinEnable, HIGH);

  digitalWrite(10, HIGH);
  _delay_ms(1000);
  digitalWrite(10, LOW);
}

void loop() {

   
  TinyWireS_stop_check();
  if(moveValve){
    switchStart = micros();
    moveValveEnabled();
  }
  
  if(activatePumpCommand){
    digitalWrite( pinEnable, LOW);
    _delay_us(1);
    digitalWrite( pinDir, pinDirCurrent);
    //setStepping(mode);
    digitalWrite( pinStep, HIGH );
    pumpCommand=true;
    activatePumpCommand=false;
  }
  
  if(pumpCommand){
    pumpCommandEnable();
    
  }

  if(switchCommand){
    if(!moveValve){ //check valve as already actuated
    EEPROM.update(249,pinDirCurrent);
    _delay_ms(10);
    EEPROM.update(251,currentSwitch);
    _delay_ms(10);
    switchCommand=false;
    speedPump=true;
    }
    
  }

  if(speedPump){
    int addedSteps = 0;

    switchEnd = micros();
    switchInterval = switchEnd-switchStart;
    addedSteps = switchCompensate[currentSwitch];

    int stepsSpeedUp = 2*ceil((float)switchInterval/((float)delayMicroSStepping+(float)delayStepping*1000));
    stepsSpeedUp = stepsSpeedUp+addedSteps;
    int i = 0;
    while(i<stepsSpeedUp){
       pumpCommandSpeedUp();
       i++;
    }
    speedPump=false;
  }
  
}


void requestEvent() //MASTER REQUESTS REGISTER VALUES
{   
    if(reg_position==7){
       TinyWireS.send(0xAA); //NOT IMPLEMENTED IN THIS VERSION
    }else if(reg_position==11){
       TinyWireS.send(15); //CHANGE OF STEPPER DELAY 
    }else{
      
       TinyWireS.send(EEPROM.read(reg_position)); //REGISTER NOT USED    
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
      if(reg_position==9){
        pumpCommand = false;
        digitalWrite( pinEnable, HIGH);
      }
        return;
    } 
    
    while(howMany--)
    {
      if(reg_position==7){
        //NOT IMPLEMENTED
      }else if(reg_position==8){
      
      float frequencyStepping=0;
      unsigned char temp[sizeof frequencyStepping];
      int i=0;
      while(TinyWireS.available()){
        temp[i]=(unsigned char)TinyWireS.receive();
        i++;
      }

    
      memcpy(&frequencyStepping,temp,sizeof frequencyStepping);
      
      float delaySec = (float)(1/frequencyStepping)-0.000058f; //23
      delayStepping = floor(delaySec*1000);
      delayMicroSStepping = floor(((delaySec*1000-(float)delayStepping)*1000));
      
        activatePumpCommand = true;
      }else if(reg_position==9){
        pumpCommand = false;
      }else if(reg_position==10){
        if(valvePosition==0){
          target = otherPos;
        }else if (valvePosition==otherPos){
          target = 0;
        }
        moveValve = true;
      
        
       }else if(reg_position==12){ //SETS TARGET POSITION
        if (target>-1){ //SANITY CHECK
        target = TinyWireS.receive();
        if(target!=valvePosition){ //CHECK IF POSITION NEEDS TO BE CHANGED
         moveValve=true; //FLAG THE NEED TO MOVE TO A NEW POSITION
         
        }
        }
        
      }else if(reg_position==255){ //CHANGE OF STEPPER DELAY

        byte temp1 = (unsigned char) TinyWireS.receive();
        OSCCAL = temp1;
       
        
        
       }else if(reg_position==254){ //WRITE VALUE FOR OSCCAL

        int temp1 = TinyWireS.receive();

        EEPROM.update(255,temp1);
        
       }else if(reg_position==253){ //Write new valve position to memory 

        int temp1 = TinyWireS.receive();

        EEPROM.update(253,temp1);
       }else if(reg_position==252){ //Override valve position variable

        int temp1 = TinyWireS.receive();
        
        valvePosition= (int)temp1;
       }else if(reg_position==251){ //Write new switch position to memory 

        int temp1 = TinyWireS.receive();

        EEPROM.update(251,temp1);
       }else if(reg_position==250){ //Override switch variable

        int temp1 = TinyWireS.receive();

        currentSwitch=temp1;
        changeActiveSwitch();
        
       }else if(reg_position==249){ //Write new direction to memory 

        int temp1 =  TinyWireS.receive();

        EEPROM.update(249,temp1);
       }else if(reg_position==248){ //Override direction  variable

        int temp1 =  TinyWireS.receive();

        pinDirCurrent=temp1;
        
       }
       /*else if(reg_position==247){ //Write new direction to memory 

        uint8_t temp1 = TinyWireS.receive();
        uint8_t temp2 = TinyWireS.receive();
        
        EEPROM.update(245, temp1);
        EEPROM.update(247, temp2);
        
       }else if(reg_position==246){ //Override direction  variable

        uint8_t temp1 = TinyWireS.receive();
        uint8_t temp2 = TinyWireS.receive();
        motorDelay = intFromByte(temp1,temp2);
        
        
       }*/

    }
      
 }





