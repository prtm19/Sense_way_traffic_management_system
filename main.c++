// Traffic Light Pins
int redNorth = 2, yellowNorth = 3, greenNorth = 4;
int redEast = 5, yellowEast = 6, greenEast = 7;
int redSouth = 8, yellowSouth = 9, greenSouth = 10;
int redWest = 11, yellowWest = 12, greenWest = 13;

// IR Sensor Pins
#define irNorth A0
#define irEast  A1
#define irSouth A2
#define irWest  A3

void setup() {
  // Traffic signal pins as OUTPUT
  for (int pin = 2; pin <= 13; pin++) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW); // Start with all OFF
  }

  // IR sensor pins as INPUT
  pinMode(irNorth, INPUT);
  pinMode(irEast, INPUT);
  pinMode(irSouth, INPUT);
  pinMode(irWest, INPUT);

  Serial.begin(9600);
}

void loop() {
  controlAllLanes(); // Central controller
}

// Central lane controller
void controlAllLanes() {
  // Lane IR sensor pins
  int irSensors[] = {irNorth, irEast, irSouth, irWest};

  // Signal pins: green, yellow, red
  int greenPins[] = {greenNorth, greenEast, greenSouth, greenWest};
  int yellowPins[] = {yellowNorth, yellowEast, yellowSouth, yellowWest};
  int redPins[] = {redNorth, redEast, redSouth, redWest};

  // Lane names
  const char* laneNames[] = {"NORTH", "EAST", "SOUTH", "WEST"};

  for (int i = 0; i < 4; i++) {
    controlTraffic(irSensors[i], greenPins[i], yellowPins[i], redPins[i], laneNames[i]);
  }
}

// Function to control signal for one lane
void controlTraffic(int irSensor, int greenPin, int yellowPin, int redPin, const char* laneName) {
  turnAllRed(); // Set all lanes to red first

  // Yellow signal ON
  digitalWrite(yellowPin, HIGH);
  countdownTimer(2, "Yellow", laneName);
  digitalWrite(yellowPin, LOW);

  // Read sensor value
  int sensorVal = digitalRead(irSensor); // LOW if traffic is present
  int greenTime = (sensorVal == HIGH) ? 5 : 2; // Green time based on traffic

  // Green ON, Red OFF
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
  countdownTimer(greenTime, "Green", laneName);
  digitalWrite(greenPin, LOW);

  // Red ON again
  digitalWrite(redPin, HIGH);
}

// All RED function
void turnAllRed() {
  int redPins[] = {redNorth, redEast, redSouth, redWest};
  for (int i = 0; i < 4; i++) {
    digitalWrite(redPins[i], HIGH);
  }
}

// Timer with Serial monitor display
void countdownTimer(int seconds, const char* signal, const char* lane) {
  for (int i = seconds; i > 0; i--) {
    Serial.print("[");
    Serial.print(lane);
    Serial.print("] ");
    Serial.print(signal);
    Serial.print(" - Time Left: ");
    Serial.print(i);
    Serial.println(" sec");
    delay(300); // 1 second delay
  }
}
