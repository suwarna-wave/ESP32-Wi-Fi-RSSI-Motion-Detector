#include <WiFi.h>

const char* ssid = "YOUR SSID";
const char* password = "YOUR PASSWORD";

int baselineRSSI = 0;
int threshold = 6;     // change this after testing
int ledPin = 2;        // built-in LED on many ESP32 boards

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");

  // Take baseline RSSI
  long total = 0;
  for (int i = 0; i < 30; i++) {
    total += WiFi.RSSI();
    delay(200);
  }

  baselineRSSI = total / 30;

  Serial.print("Baseline RSSI: ");
  Serial.println(baselineRSSI);
}

void loop() {
  int currentRSSI = WiFi.RSSI();
  int difference = abs(currentRSSI - baselineRSSI);

  Serial.print("RSSI: ");
  Serial.print(currentRSSI);
  Serial.print(" | Difference: ");
  Serial.println(difference);

  if (difference > threshold) {
    Serial.println("Motion Detected!");
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  delay(300);
}