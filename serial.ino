void readSerial(){
  if(Serial.available()>0){
    char in = Serial.read();
    switch (in){
      case '0':
        allowed = false;
        Serial.println("Pot not active");
        break;
      case '1':
        allowed = true;
        Serial.println("Pot now active");
        break;
    }
  }
}

void printTime(){
      Serial.print("Ok, Time = ");
      print2digits(tm.Hour);
      Serial.write(':');
      print2digits(tm.Minute);
      Serial.write(':');
      print2digits(tm.Second);
      Serial.print(", Date (D/M/Y) = ");
      Serial.print(tm.Day);
      Serial.write('/');
      Serial.print(tm.Month);
      Serial.write('/');
      Serial.print(tmYearToCalendar(tm.Year));
      Serial.println();
}

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}

