// Pin Definitions
#define TRIG_PIN 2      // Ultrasonic sensor Trig pin
#define ECHO_PIN 3      // Ultrasonic sensor Echo pin
#define WATER_PIN 6     // Water level sensor signal pin
#define MOISTURE_PIN 7  // Moisture sensor signal pin
#define LDR_PIN A0      // LDR module analog pin
#define BUZZER_PIN 8    // Buzzer pin

// Thresholds
#define DAY_THRESHOLD 600  // LDR threshold for day/night
#define DISTANCE_THRESHOLD 50 // Distance threshold in cm for obstacle detection

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(WATER_PIN, INPUT);
  pinMode(MOISTURE_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.begin(9600);
  dayNightAlert(); // Check day or night on power-up
}
void loop() {
  detectObstacle();
  detectWater();
  detectMoisture();
  delay(500); // Small delay for stability
}

// Function to detect day or night and beep accordingly
void dayNightAlert() {
  int ldrValue = analogRead(LDR_PIN);
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  if (ldrValue > DAY_THRESHOLD) { // Day
    Serial.println("It's Day!");
    for (int i = 0; i < 4; i++) {
      beep(200);
    }
  } else { // Night
    Serial.println("It's Night!");
    for (int i = 0; i < 2; i++) {
      beep(200);
    }
  }
}

// Function to detect obstacles using ultrasonic sensor
void detectObstacle() {
  long duration;
  int distance;

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2; // Convert to cm
  
  if (distance < DISTANCE_THRESHOLD) {
    Serial.println("Obstacle detected!");
    for (int i = 0; i < 3; i++) { // Beep for obstacle
      beep(300);
    }
  }
}
// Function to detect water level
void detectWater() {
  if (digitalRead(WATER_PIN) == HIGH) { // Water detected
    Serial.println("Water detected!");
    for (int i = 0; i < 2; i++) { // Beep for water
      beep(400);
    }
  }
}

// Function to detect moisture
void detectMoisture() {
  if (digitalRead(MOISTURE_PIN) == HIGH) { // Moisture detected
    Serial.println("Moisture detected!");
    for (int i = 0; i < 1; i++) { // Beep for moisture
      beep(500);
    }
  }
}

// Buzzer beep function
void beep(int duration) {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(duration);
  digitalWrite(BUZZER_PIN, LOW);
  delay(duration);
}

