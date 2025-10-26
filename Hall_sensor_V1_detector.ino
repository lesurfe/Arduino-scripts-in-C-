// Arduino sketch for Portenta H7 to control the built-in LED based on a Hall Sensor (DFRobot V1)

int hall_sensor = 7; // pin digital 7 de Arduino a sensor hall

void setup() {
  Serial.begin(9600); // Initialize Serial communication for debugging and monitoring

  pinMode(hall_sensor, INPUT);

  pinMode(LED_BUILTIN, OUTPUT); // Set the LED pin as an OUTPUT
  digitalWrite(LED_BUILTIN, HIGH); // Ensure LED starts off

}

void loop() {
  int sensorState = digitalRead(7);

  if (sensorState == HIGH) {
    // Action: Magnet detected!
    digitalWrite(LED_BUILTIN, LOW); // Turn the built-in LED ON
    Serial.println("STATUS: Magnet detected! LED is ON."); // We only print status changes when no magnet is present
  } else {
    // Action: No magnet detected.
    digitalWrite(LED_BUILTIN, HIGH);  // Turn the built-in LED OFF
  }

  delay(100); // A small delay to debounce the sensor and stabilize readings
}
