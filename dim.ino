void light() {
    if(dimmingUp){
      DimUp(dim,dimmingUp,dimMillis);
    }
    if(dimmingDown){
      DimDown(dim,dimmingDown,dimMillis);
    }
}

void DimUp(unsigned int& dim, bool& dimmingUp, unsigned long& milles) {
  if(millis() -milles > timelag) {
    milles = millis();
    dim++;
  }
  if(dim >= MAX_PWM_VAL) {
    dimmingUp = false;
    Serial.print("dimming Up stopped");
  }
}

void DimDown(unsigned int& dim, bool& dimmingDown, unsigned long& milles) {
  if(millis() - milles > timelag && dim >MIN_PWM_VAL) {
    milles = millis();
    dim--;
//    Serial.println("dimming down is active");
  }
  if(dim <= MIN_PWM_VAL) {
    dimmingDown = false;
    Serial.print("dimming Down stopped");
  }
}

void pwmDrive(){
  if(dim == 0) {
    digitalWrite(pwmLightPin,LOW);
    digitalWrite(relaisFan,LOW);
  }else if(dim>0 && dim <254){
    analogWrite(pwmLightPin,dim);
    digitalWrite(relaisFan,HIGH);
  }else if(dim >= 254) {
    digitalWrite(pwmLightPin,HIGH);
    digitalWrite(relaisFan,HIGH);
  }
}
