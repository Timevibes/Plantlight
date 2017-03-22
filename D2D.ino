void getSunRiseSet (){
  if(tm.Second%1 == 0){ //tm.Hour == 0 && tm.Minute == 0 && tm.Second == 0
    bool dls;
    if((tm.Month > dlsBegin[0] && tm.Day > dlsBegin[1]) && (tm.Month < dlsEnd[0] && tm.Day < dlsEnd[1])) {
      dls = true;
    }
    else dls = false;
//    Serial.println(dls);
    int aSunrise  = Amsterdam.sunrise(tmYearToCalendar(tm.Year), tm.Month, tm.Day,dls);
    int aSunset   = Amsterdam.sunset(tmYearToCalendar(tm.Year), tm.Month, tm.Day, dls);
    char sunrise [] = "00:00";
    Dusk2Dawn::min2str(sunrise, aSunrise);
//    Serial.print(sunrise); 
//    Serial.print(" ");
    sunWake[0] = aSunrise/60;
    sunWake[1] = aSunrise -round(sunWake[0]*60); 
//    Serial.print(sunWake[0]);
//    Serial.print(" ");
//    Serial.print(sunWake[1]);
//    Serial.print(' ');
    char sunset [] = "00:00";
    Dusk2Dawn::min2str(sunset, aSunset);
//    Serial.print(sunset); 
//    Serial.print("  ");
//    Serial.print(" ");
    sunSleep[0] = (aSunset-90)/60;
    sunSleep[1] = (aSunset-90) - round(sunSleep[0]*60);
//    Serial.print(sunSleep[0]);
//    Serial.print(" ");
//    Serial.print(sunSleep[1]);
//    Serial.println(' ');
  }
}

void checkSunRiseSet () {
  if(sunWake[0] == tm.Hour && sunWake[1] == tm.Minute) {
    dimmingUp = true;
  }
  if(sunSleep[0] == tm.Hour && sunSleep[1] == tm.Minute) {
    dimmingDown = true;
  }
}

void startUP() {
  bool dls;
    if((tm.Month > dlsBegin[0] && tm.Day > dlsBegin[1]) && (tm.Month < dlsEnd[0] && tm.Day < dlsEnd[1])) {
      dls = true;
    }else dls = false;
    int aSunrise  = Amsterdam.sunrise(tmYearToCalendar(tm.Year), tm.Month, tm.Day,dls);
    int aSunset   = Amsterdam.sunset(tmYearToCalendar(tm.Year), tm.Month, tm.Day, dls);
    char sunrise [] = "00:00";
    Dusk2Dawn::min2str(sunrise, aSunrise);
    sunWake[0] = aSunrise/60;
    sunWake[1] = aSunrise -round(sunWake[0]*60); 
//    Serial.print(sunWake[0]);
//    Serial.print(" ");
//    Serial.print(sunWake[1]);
//    Serial.print(' ');
    char sunset [] = "00:00";
    Dusk2Dawn::min2str(sunset, aSunset);
    sunSleep[0] = (aSunset-90)/60;
    sunSleep[1] = (aSunset-90) - round(sunSleep[0]*60);
//    Serial.print(sunSleep[0]);
//    Serial.print(" ");
//    Serial.print(sunSleep[1]);
//    Serial.print(' ');
    if(tm.Hour > sunWake[0] && tm.Hour < sunSleep[0]) {
      dim = 254;
//      Serial.println("I'm up!");
    }else {
      dim = 0;
//      Serial.println("I'm Sleepy!");
    }
}

