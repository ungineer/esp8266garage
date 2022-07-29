#define SENSOR_PIN 3
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define DOOR_CLOSED HIGH
#define DOOR_OPEN LOW

// You should get Auth Token in the Blynk App when you create a new project
char auth[] = "";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "";
char pass[] = "";

int lastDoorState = -1;
int currentDoorState = -1;
// this is to display a message in the app
WidgetLCD lcd(V3);

void checkDoorAndDisplayMessage()
{
  currentDoorState = digitalRead(SENSOR_PIN);
  
  if (currentDoorState == lastDoorState) return;

  if (currentDoorState == DOOR_OPEN) {
   lcd.print(0,0, "Door Open");
  }  else {
   lcd.print(0,0, "Door Closed");
  }

  // this is to ensure that the notifications don't get pushed on every cycle of the app
  // but only when the door is opened or closed
  lastDoorState = currentDoorState; 
}

void setup()
{
  Blynk.begin(auth, ssid, pass);
  // Setup physical button pin
  // PULLUP is important here to make sure that when the door is open, the 
  // pin is not floating, which would cause random readings
  pinMode(SENSOR_PIN, INPUT_PULLUP);
}

void loop()
{
  Blynk.run();
  checkDoorAndDisplayMessage();
}
