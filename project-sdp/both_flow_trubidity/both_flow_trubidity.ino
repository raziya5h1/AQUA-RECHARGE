// Pin definitions for RGB LED
int redPin = 2;    // Red pin connected to GPIO2
int greenPin = 4;  // Green pin connected to GPIO4
int bluePin = 5;   // Blue pin connected to GPIO5

#define RELAY_PIN 13  // GPIO pin connected to the relay module

// Turbidity sensor pin
int sensorPinTurbidity = 34;  // Sensor connected to GPIO34 (analog pin on ESP32)

// Flow sensor pin
int sensorPinFlow = 12;
volatile long pulse = 0;
float volume;
unsigned long lastPulseTime = 0;
const unsigned long timeout = 1000; // 1 second timeout for no flow detection

void setup() {
  // Set RGB LED pins as outputs
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  // Initialize flow sensor
  pinMode(sensorPinFlow, INPUT);
  attachInterrupt(digitalPinToInterrupt(sensorPinFlow), increase, RISING);
  
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Initially OFF (Active LOW Relay)

  // Initialize Serial Monitor
  Serial.begin(9600);
}

void loop() {
  measureTurbidity();
  measureFlow();
  delay(1000);  // Delay before the next measurement cycle
}

// Function to measure turbidity and control RGB LED
void measureTurbidity() {
  int sensorValue = analogRead(sensorPinTurbidity);
  Serial.print("Turbidity Sensor Value: ");
  Serial.println(sensorValue);
  
  if (sensorValue > 2000) {  // Clear water
    setRGB(0, 255, 0);  // Green LED
    Serial.println("Clear Water");
    digitalWrite(RELAY_PIN, LOW);  // Turn ON solenoid valve
    //delay(30000);  // Keep it ON for 5 seconds
  }
  else if (sensorValue >= 1000 && sensorValue <= 2000) {  // Cloudy water
    setRGB(0, 0, 255);  // Blue LED
    Serial.println("Cloudy Water");
     digitalWrite(RELAY_PIN, HIGH); // Turn OFF solenoid valve
    //delay(1000);  // Wait for 5 seconds
  }
  else {  // Dirty water
    setRGB(255, 0, 0);  // Red LED
    Serial.println("Dirty Water");
     digitalWrite(RELAY_PIN, HIGH); // Turn OFF solenoid valve
    //delay(1000);  // Wait for 5 seconds
  }
}

// Function to measure flow rate
void measureFlow() {
  unsigned long currentTime = millis();
  if (currentTime - lastPulseTime > timeout) {
    pulse = 0; // Reset pulse count if no pulses detected within timeout
  }
  
  volume = 2.663 * pulse;
  Serial.print("Water Flow: ");
  Serial.print(volume);
  Serial.println(" mL");
}

// Function to set the color of the RGB LED
void setRGB(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

// Interrupt function to count pulses from the flow sensor
void increase() {
  pulse++;
  lastPulseTime = millis();
}

