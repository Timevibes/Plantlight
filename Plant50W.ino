#define relaisFan 5
#define butUP 9
#define butDOWN 8
#define pwmLightPin 11
#define pwmFanPin 3
#define readLight analogRead(lightPotPin)
#define read_pot analogRead(POT_Pin)
#include <Dusk2Dawn.h>
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress insideThermometer;
#define thermistor A1
//-------------------Thermistor
float vcc = 4.99;                       // only used for display purposes, if used
                                        // set to the measured Vcc.
float pad = 9780;                       // balance/pad resistor value, set this to
                                        // the measured resistance of your pad resistor
float thermr = 10000;
int fanPulse = 4;
unsigned long pulseDuration;

int dlsBegin [2] = {3,26};
int dlsEnd [2] = {10,29};

Dusk2Dawn Amsterdam(52.390556, 4.914358, 1);//52.390556, 4.914358

int sunWake[2] = {0,0};
int sunSleep [2] = {0,0};
bool dimmingUp = false;
bool dimmingDown = false;
unsigned int dim = 0;
unsigned long dimMillis = 0;
unsigned long timelag = 21176;
unsigned const int MAX_PWM_VAL = 254; 
unsigned const int MIN_PWM_VAL = 0;
tmElements_t tm;
int prevMinute = 99;
int prevSecond = 99;

void setup() {
  pinMode(relaisFan,OUTPUT);
  digitalWrite(relaisFan,HIGH);
  pinMode(butUP,INPUT_PULLUP);
  pinMode(butDOWN,INPUT_PULLUP);
  pinMode(fanPulse, INPUT);
  digitalWrite(fanPulse,HIGH);
  pinMode(pwmFanPin,OUTPUT);
  pinMode(pwmLightPin,OUTPUT);
  TCCR2B = (TCCR2B & 0b11111000) | 0x01;
  pinMode(thermistor,INPUT);
//  Serial.begin(115200);
  RTC.read(tm);
  startUP();
  sensors.begin();
  if (!sensors.getAddress(insideThermometer, 0)) Serial.println("Unable to find address for Device 0"); 
  sensors.setResolution(insideThermometer, 9);
}

int pwmFanSpeed=0;
int lPot =0;
//unsigned long lastMillis = 1000;
float temperatureNTC = 0;
float temperatureDS18B20 = 0; 
//unsigned int dim = 0;
bool allowed = false;

void loop() {
  light();
  overHeatProtection();
  pwmFanDrive();
  pwmDrive();
  buttons();
  if(RTC.read(tm) && tm.Minute!= prevMinute){
    prevMinute = tm.Minute;
    getSunRiseSet();
    checkSunRiseSet ();
//    printTime();
    sensors.requestTemperatures(); 
    ds18B20(insideThermometer);   
    Thermistor();
//    if(tm.Minute%10 == 0){
//      startUP();
//    }
//    Serial.print("Temp DS18B20: ");
//    Serial.print(temperatureDS18B20);
//    Serial.print("  Thermistor: ");
//    Serial.print(temperatureNTC);
//    Serial.print(" Fan Pwm: ");
//    Serial.print(pwmFanSpeed);
////    readPulse();
//    Serial.print(" light PWM: ");
//    Serial.println(dim);
  }
}
