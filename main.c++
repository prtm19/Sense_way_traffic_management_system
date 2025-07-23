
// Smart Traffic Light

#define LANE1_SENSOR A1

#define LANE1_RED 2
#define LANE1_YELLOW 3
#define LANE1_GREEN 4

// int lane1_density = 0;
// int lane2_density = 0;

void setup()
{
    pinMode(LANE1_SENSOR, INPUT);

    pinMode(LANE1_GREEN, OUTPUT);
    pinMode(LANE1_YELLOW, OUTPUT);
    pinMode(LANE1_RED, OUTPUT);

    Serial.begin(9600);
}

void loop()
{
    // Step 1: Red LED glows for 2 seconds
    digitalWrite(LANE1_RED, HIGH);   // Turn on red LED
    digitalWrite(LANE1_YELLOW, LOW); // Ensure yellow is off
    digitalWrite(LANE1_GREEN, LOW);  // Ensure green is off
    countdownTimer(5, "Red Signal");

    // Step 2: Yellow LED glows for 2 seconds
    digitalWrite(LANE1_RED, LOW);     // Turn off red LED
    digitalWrite(LANE1_YELLOW, HIGH); // Turn on yellow LED
    digitalWrite(LANE1_GREEN, LOW);   // Ensure green is off
    countdownTimer(1, "Yellow Signal");

    // Step 3: Check IR sensor to determine green LED timing
    int irSensorValue = digitalRead(LANE1_SENSOR); // Read IR sensor value

    if (irSensorValue == HIGH)
    {                                    // If an object is detected
        digitalWrite(LANE1_GREEN, HIGH); // Turn on green LED for 10 seconds
        digitalWrite(LANE1_YELLOW, LOW); // Ensure yellow is off
        digitalWrite(LANE1_RED, LOW);    // Ensure red is off
        countdownTimer(5, "Green Signal (Vehicle are available)");
    }
    else
    {                                    // If no object is detected
        digitalWrite(LANE1_GREEN, HIGH); // Turn on green LED for 2 seconds
        digitalWrite(LANE1_YELLOW, LOW); // Ensure yellow is off
        digitalWrite(LANE1_RED, LOW);    // Ensure red is off
        countdownTimer(2, "Green Signal (No vehicle)");
    }
}
// Countdown timer function
void countdownTimer(int seconds, const char *signalName)
{
    for (int i = seconds; i > 0; i--)
    {
        Serial.print(signalName);
        Serial.print(" - Time Remaining: ");
        Serial.print(i);
        Serial.println(" seconds");
        delay(1000); // Wait for 1 second
    }

    // Loop will restart, and process will repeat
}