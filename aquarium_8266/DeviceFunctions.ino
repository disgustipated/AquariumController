void getTimeFromNtp() {
  // Begin NTP
  Serial.print("Begin NTP...");
  timeClient.begin();
  while (!timeClient.update()) yield();
  timeStruct.hours = timeClient.getHours();
  timeStruct.minutes = timeClient.getMinutes();
  timeStruct.seconds = timeClient.getSeconds();
  timeStruct.nextNtp = ntpInterval;
  Serial.println(" OK.");
}

char* toCharArray(String str) {
  return &str[0];
}

//Merge in functions from dht library to compute heat index
float convertCtoF(float c) { return c * 1.8 + 32; }
float convertFtoC(float f) { return (f - 32) * 0.55555; }
