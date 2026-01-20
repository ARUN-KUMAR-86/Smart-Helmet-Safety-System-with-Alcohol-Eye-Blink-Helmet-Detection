// === Pin setup ===
const int irSensor = 2;         // IR sensor for eye blink (LOW = closed)
const int mq5Pin = A0;          // MQ-5 alcohol sensor
const int trigPin = 8;          // Ultrasonic trigger (helmet detection)
const int echoPin = 9;          // Ultrasonic echo
const int buzzerPin = 12;       // Buzzer
const int ledPin = 13;          // LED indicator
const int motorPin = 7;         // Motor relay or output pin

// === Thresholds ===
int alcoholThreshold = 400;     // Adjust after testing MQ-5
int wearDistance = 10;          // cm — if less than this, helmet is worn

void setup() {
  pinMode(irSensor, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  digitalWrite(buzzerPin, LOW);
  digitalWrite(ledPin, LOW);
  digitalWrite(motorPin, LOW); // motor OFF initially

  Serial.begin(9600);
  Serial.println("System Started: Helmet + Alcohol + Eye Detection Active");
  delay(5000); // MQ-5 warm-up time
}

// === Function to get distance from Ultrasonic ===
long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2; // Convert to cm
  return distance;
}

// === Alarm functions ===
void alarmOn() {
  digitalWrite(buzzerPin, HIGH);
  digitalWrite(ledPin, HIGH);
}

void alarmOff() {
  digitalWrite(buzzerPin, LOW);
  digitalWrite(ledPin, LOW);
}

void loop() {
  // === Read all sensors ===
  int eyeState = digitalRead(irSensor);   // LOW = eyes closed
  int alcoholVal = analogRead(mq5Pin);    // MQ-5 sensor value
  long distance = getDistance();          // Helmet ultrasonic distance

  Serial.print("Alcohol: ");
  Serial.print(alcoholVal);
  Serial.print(" | Eye: ");
  Serial.print(eyeState == LOW ? "Closed" : "Open");
  Serial.print(" | Helmet Dist: ");
  Serial.print(distance);
  Serial.println(" cm");

  bool alarm = false;
  bool motorOn = true;

  // === Helmet detection ===
  if (distance > wearDistance || distance <= 0) {
    alarm = true;
    motorOn = false;
    Serial.println("⚠️ Helmet not worn!");
  }

  // === Alcohol detection ===
  if (alcoholVal > alcoholThreshold) {
    alarm = true;
    motorOn = false;
    Serial.println("⚠️ Alcohol detected!");
  }

  // === Eye detection ===
  if (eyeState == LOW) {
    alarm = true;
    motorOn = false;
    Serial.println("⚠️ Eyes closed!");
  }

  // === Output control ===
  if (alarm) {
    alarmOn();
    digitalWrite(motorPin, LOW); // motor OFF
  } else {
    alarmOff();
    digitalWrite(motorPin, HIGH); // motor ON
    Serial.println("✅ All safe — Motor ON");
  }

  delay(500);
}