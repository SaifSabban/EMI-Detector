int sensorPin = A5; // Pin That Attaches To Antenna.

const int led[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; //LEDs that show Level Of EMI.
const int thresholds[] = {190, 170, 150, 130, 110, 90, 70, 50, 30, 10}; // EMI Voltage Threshold.
//const int thresholds[] = {130, 110, 90, 70, 50, 30, 10};
// const int thresholds[] = {200, 175, 150, 125, 100, 75, 50};
const int ledNumber = (sizeof(led) / sizeof(led[0])); // Size Of Array.
int ledOn = 0; // Used To Set a Few Leds On, & the Rest On Low .
int delaytime = 50; // Delay Time For Initilisation.

unsigned long MessageTimer; // Counts the Amount of time Since Last Message.
const unsigned long MessageTime = 1000; // Delay To How Often You Want The Messages To Refreash.

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < ledNumber; i++) { // Set All LEDs, Sequentially As Output & High.
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], HIGH);
    delay(delaytime);
  }
  for (int i = ledNumber; i > 0; i--) { // Set All LEDs, Sequentially As Low.
    digitalWrite(led[i], LOW);
    delay(delaytime);
  }

  Serial.println(F("***** Starting EMI Detector Code By SSS *****"));
  MessageTimer = millis(); // Starts Message Timer.
}

void loop() {
  int sensorValue = analogRead(sensorPin); // Reads Antenna Voltage.

  ledOn = 0; // Resets What LEDs Are On.

  for (int i = 0; i < ledNumber; i++) { // Counts How Many Items Are Equal Or Over The Threshold Voltage, using ledOn.
    if (sensorValue > thresholds[i]) ledOn++;
  }
  for (int i = 0; i < ledOn; i++) { // Turns On ledOn amount of Leds On.
    digitalWrite(led[i], HIGH);
  }
  for (int i = ledOn; i < ledNumber; i++) { // Turns Of all the other Leds, By Starting i at ledOn.
    digitalWrite(led[i], LOW);
  }

  if (millis() - MessageTimer >= MessageTime) { // Prints out Sensor Value To Everything Running Smoothly, Updates Every MessageTime.
    Serial.print(F("Sensor Value = ")); Serial.println(sensorValue);
    MessageTimer = millis();
  }
}
