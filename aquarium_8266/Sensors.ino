void checkSensors(){
  currMillis = millis();
  if (currMillis - prevMillisSensors >= CHECK_SENSORS_INTERVAL){
    prevMillisSensors = currMillis;
 
    StaticJsonDocument<512> mqttDoc;
    JsonObject sMsg = mqttDoc.to<JsonObject>();
    
    sensors.requestTemperatures(); // Send the command to get temperature readings 
    Serial.print("Temperature is: "); 
    Serial.println(sensors.getTempFByIndex(0));
    float f = sensors.getTempFByIndex(0);
    
    // Check if any reads failed and exit early (to try again).
    if (isnan(f)) {
      SensorError();
      Serial.println(F("Failed to read from sensor!"));
      return;
    }
    
    if (f != 2147483647){
        sMsg["temp"] = f;
        publishMessage(baseTopic +String("sump"),sMsg);
      } else {
        sMsg["temp"] = 0;
        SensorError();
        publishMessage(baseTopic +String("sump"),sMsg);
      }
  }
}

void checkWaterLevels(String sensorName, int trigPin, int echoPin){
  currMillis = millis();
  if (currMillis - wprevMillisSensors >= WATER_CHECK_SENSORS_INTERVAL && sensorName != prevSensor ){
    wprevMillisSensors = currMillis;
    prevSensor = sensorName;
    StaticJsonDocument<512> mqttDoc;
    JsonObject wlMsg = mqttDoc.to<JsonObject>();
    
    Serial.println("Reading " + sensorName + " levels"); 
    // Clear the trigPin by setting it LOW:
    digitalWrite(trigPin, LOW);
    
    delayMicroseconds(5);
   // Trigger the sensor by setting the trigPin high for 10 microseconds:
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Read the echoPin. pulseIn() returns the duration (length of the pulse) in microseconds:
    duration = pulseIn(echoPin, HIGH);
    
    // Calculate the distance:
    distance = duration*0.034/2; //in cm
    distanceIn = distance*0.3937; //in inches

    wlMsg["waterLevel"] = distanceIn;
    publishMessage(baseTopic + String(sensorName), wlMsg);
  }
}
