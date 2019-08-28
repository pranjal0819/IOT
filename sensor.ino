#include <SoftwareSerial.h>

int sensor_pin0 = A0;
int sensor_pin1 = A1;
int sensor_pin2 = A2;
int output_value0;
int output_value1;
int output_value2;
long lastMsg = 0;
SoftwareSerial s(5, 6); // (Rx, Tx)

void setup() {
  Serial.begin(9600);
  s.begin(9600);
  Serial.println("Reading From the Sensor ...");
  delay(2000);
}
void loop() {
  long now = millis();
  if (now - lastMsg > 4100) {
    lastMsg = now;
    output_value0 = analogRead(sensor_pin0);
    output_value1 = analogRead(sensor_pin1);
    output_value2 = analogRead(sensor_pin2);
    
    Serial.print(output_value0);
    Serial.print(", ");
    Serial.print(output_value1);
    Serial.print(", ");
    Serial.println(output_value2);
    
    output_value0 = map(output_value0, 555, 10, 0, 100);
    output_value1 = map(output_value1, 555, 10, 0, 100);
    output_value2 = map(output_value2, 555, 10, 0, 100);
    
    Serial.print("Data: ");
    Serial.print(output_value0);
    Serial.print(", ");
    Serial.print(output_value1);
    Serial.print(", ");
    Serial.println(output_value2);
    
    if (s.available() > 0)
    {
      if (output_value0 < 0)
        s.write(1024);
      else 
        s.write(output_value0);
      if (output_value1 < 0)
        s.write(1024);
      else 
        s.write(output_value1);
      if (output_value2 < 0)
        s.write(1024);
      else 
        s.write(output_value2);
    }
  }
}
