

void pumpCommandEnable(){
   
     digitalWrite( pinStep, LOW );
     _delay_us(5);
     digitalWrite( pinStep, HIGH );
     
     delay(delayStepping);
     delayMicroseconds(delayMicroSStepping);


}



void pumpCommandSpeedUp(){
   
     digitalWrite( pinStep, LOW );
     _delay_us(5);
     digitalWrite( pinStep, HIGH );
     
     delay(delayStepping/2);
     delayMicroseconds(delayMicroSStepping/2);


}
