#include <Arduino.h>

int RPM_MIN = 200;
int RPM_MAX = 6000;
int LOOP_TIME = 33; // ~30fps

int potPin = A0;  // select the input pin for the potentiometer
int RPMPin = 2;   // select the pin for the LED
int phasePin = 4; // select the pin for phase signal

int phase_counter = 0;

void setup()
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(RPMPin, OUTPUT); // declare the ledPin as an OUTPUT
  pinMode(phasePin, OUTPUT);
}

void loop()
{
  int val = analogRead(potPin); // read the value from the sensor

  int rpm = map(val, 0, 1023, RPM_MIN, RPM_MAX);

  int wait = 1000 / (2 * rpm / 60); // time to wait for between clock`s edges
  wait = wait / 3;

  Serial.print(val);
  Serial.print(" ");
  Serial.print(rpm);
  Serial.print(" ");
  Serial.print(wait);
  Serial.print(" ");
  Serial.println(phase_counter);
  
  digitalWrite(RPMPin, HIGH);
  if (phase_counter == 6)
  {
    digitalWrite(phasePin, HIGH);
    phase_counter = 0;
  }
  delay(wait);

  digitalWrite(RPMPin, LOW);
  digitalWrite(phasePin, LOW);
  delay(wait);

  phase_counter++;
}
