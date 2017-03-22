bool prevUp = true;
bool prevDown = true;

void readPulse() {
pulseDuration = pulseIn(fanPulse, LOW);
double frequency = 1000000/pulseDuration;
Serial.print("  RPM:");
Serial.print(frequency/2*60);
}


void buttons() {
  bool up = digitalRead(butUP);
  bool down = digitalRead(butDOWN);
  if(!up & dim<=253) {
    dim++;
//    Serial.println("UP");
  }else if(!down && dim>0) {
    dim--;
//    Serial.println("DOWN");
  }
  if(!down &!up) {
    startUP();
  }
  
  delay(20);
}


void overHeatProtection() {
  if(temperatureNTC > 35 && temperatureNTC < 50 || temperatureDS18B20 > 35 && temperatureDS18B20 < 50){
    pwmFanSpeed = 200; 
  }else if(temperatureNTC > 50 && temperatureNTC < 80 || temperatureDS18B20 > 50 && temperatureDS18B20 < 80){
    pwmFanSpeed = 255;
  }
  else if (temperatureNTC > 80 || temperatureDS18B20 > 80){
  }else{
    pwmFanSpeed = 130;
  }
}

void pwmFanDrive(){
    analogWrite(pwmFanPin,pwmFanSpeed);
}
