
void ds18B20 (DeviceAddress deviceAddress) {
  float temp = sensors.getTempC(deviceAddress);
  if (temp > -10.0 && temp < 120.0) {
    temperatureDS18B20 = temp;
  }
}

void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  Serial.print("Temp C: ");
  Serial.print(tempC);
  
}

void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}
