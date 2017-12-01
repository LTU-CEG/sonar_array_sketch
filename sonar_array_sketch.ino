//          Copyright Emil Fresk 2015-2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE.md or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//
// Settings
//
const int delta_time_ms = 50; // Time between pings
const int sonar_array[] = {2, 3, 4, 5}; // List of pins where a sonar is connected


//
// Helper variables
//
int current_sonar = 0;

void setup()
{  
  // initialize serial communication:
  Serial.begin(57600);
}

void loop()
{
  int time = millis();
  long mm = ping_sonar(sonar_array[current_sonar]);
  
  
  Serial.print(current_sonar);
  Serial.print(',');
  Serial.print(mm);
  Serial.println();
  
  current_sonar++;
  
  if (current_sonar >= sizeof(sonar_array) / sizeof(int))
    current_sonar = 0;

  int diff = millis() - time;
  
  if (diff > delta_time_ms || diff < 0)
    diff = delta_time_ms;
    
  delay(delta_time_ms - diff);
}

long ping_sonar(int pingPin)
{
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(pingPin, INPUT);
  
  return us2mm(pulseIn(pingPin, HIGH, 30000));
}

long us2mm(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  return ((10 / 2) * microseconds / 29);
}
