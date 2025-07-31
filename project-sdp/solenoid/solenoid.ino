#define RELAY_PIN 13  // GPIO pin connected to the relay module

void setup() {
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, HIGH); // Initially OFF (Active LOW Relay)
}

void loop() {
    digitalWrite(RELAY_PIN, LOW);  // Turn ON solenoid valve
    delay(30000);  // Keep it ON for 5 seconds

    digitalWrite(RELAY_PIN, HIGH); // Turn OFF solenoid valve
    delay(1000);  // Wait for 5 seconds
}
