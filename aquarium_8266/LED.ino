void MQTTError(){
  digitalWrite(RED_DATA_PIN, LOW);
  delay(2000);
  digitalWrite(RED_DATA_PIN, HIGH);
}

void blinkErrorCode(int errorNumber){
  int iblink = -1;
  Serial.println(errorNumber);
  Serial.println(client.state());
  while(iblink < errorNumber){
    digitalWrite(RED_DATA_PIN, LOW);
    delay(150);
    digitalWrite(RED_DATA_PIN, HIGH);
    delay(1000);
    iblink++;
  }
  delay(2000);
}

void dataSend(){
  digitalWrite(WIFI_INFO_LED_PIN, LOW);
  delay(150);
  digitalWrite(WIFI_INFO_LED_PIN, HIGH);
}

void SensorError(){
  digitalWrite(RED_DATA_PIN, LOW);
  delay(50);
  digitalWrite(RED_DATA_PIN, HIGH);
  delay(50);
  digitalWrite(RED_DATA_PIN, LOW);
  delay(50);
  digitalWrite(RED_DATA_PIN, HIGH);
}
