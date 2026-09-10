#define BLYNK_TEMPLATE_ID "yourid"
#define BLYNK_TEMPLATE_NAME "yourname"
#define BLYNK_AUTH_TOKEN "yourtoken"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "xyz";      // WiFi name
char pass[] = "xyz";        // WiFi password

int pirPin = D5;                 // PIR connected to D5
unsigned long lastMotionTime = 0;
bool pollinatorActive = false;

void setup() {
  Serial.begin(115200);

  pinMode(pirPin, INPUT);

  Serial.println("Connecting to WiFi...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Serial.println("WiFi + Blynk Connected!");
}

void loop() {
  Blynk.run();

  int val = digitalRead(pirPin);

  // If motion is detected
  if (val == HIGH) {
    lastMotionTime = millis();

    if (!pollinatorActive) {
      pollinatorActive = true;
      Serial.println("Pollinator detected!");
      Blynk.virtualWrite(V1, "🌼 Pollinator detected!");
    }
  }

  // If 10 seconds passed with no motion
  if (pollinatorActive && (millis() - lastMotionTime > 10000)) {
    pollinatorActive = false;
    Serial.println("No activity — Safe to spray.");
    Blynk.virtualWrite(V1, "✔ No activity — Safe to spray");
  }
}
