// Pin definitions for RGB LED
int redPin = 2;    // Red pin connected to GPIO2
int greenPin = 4;  // Green pin connected to GPIO4
int bluePin = 5;   // Blue pin connected to GPIO5

// Turbidity sensor pin
int sensorPin = 34;  // Sensor connected to GPIO34 (analog pin on ESP32)

void setup() {
  // Set RGB LED pins as outputs
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Initialize the Serial Monitor for debugging
  Serial.begin(9600);
}

void loop() {
  // Read the turbidity sensor value (analog input)
  int sensorValue = analogRead(sensorPin);
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);  // Print raw sensor value to see the range

  // Map the sensor value (adjust as necessary)
  // Assuming 0 to 4095 range (for ESP32 ADC), adjust the thresholds for clean/dirty water.
  // Let's use thresholds based on the sensor value observed:
  // - Clean Water: Sensor value < 1000 (adjust this based on your sensor)
  // - Cloudy Water: Sensor value between 1000 and 2000
  // - Dirty Water: Sensor value > 2000
 
  if (sensorValue > 2000) {  // Clear water
    setRGB(0, 255, 0);  // Green LED
    Serial.println("Clear Water");
  }
  else if (sensorValue >= 1000 && sensorValue <= 2000) {  // Cloudy water
    setRGB(0, 0, 255);  // Blue LED
    Serial.println("Cloudy Water");
  }
  else if (sensorValue < 1000) {  // Dirty water
    setRGB(255, 0, 0);  // Red LED
    Serial.println("Dirty Water");
  }

  delay(1000);  // Delay for 1 second before reading again
}

// Function to set the color of the RGB LED
void setRGB(int red, int green, int blue) {
  analogWrite(redPin, red);    // Set the red color intensity
  analogWrite(greenPin, green); // Set the green color intensity
  analogWrite(bluePin, blue);   // Set the blue color intensity
}
