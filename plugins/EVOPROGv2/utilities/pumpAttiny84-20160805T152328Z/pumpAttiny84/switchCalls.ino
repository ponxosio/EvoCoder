
void handleSwitch(void){
  if(valvePosition==0){
    target = otherPos;
  }else if(valvePosition==otherPos){
    target = 0;
  }
  pinDirCurrent = !pinDirCurrent;
  currentSwitch = !currentSwitch;
  switchCommand=true;
  moveValve = true;
  disableInterrupt(switchPin[!currentSwitch]);
  enableInterrupt(switchPin[currentSwitch], handleSwitch, RISING);
  digitalWrite( pinDir, pinDirCurrent);
} 


void changeActiveSwitch(){
  disableInterrupt(switchPin[!currentSwitch]);
  enableInterrupt(switchPin[currentSwitch], handleSwitch, RISING);
 EEPROM.update(251,currentSwitch);
  
}

