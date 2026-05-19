int entrySensor = 2;
int exitSensor = 3;

int led = 8;
int buzzer = 9;

int visitorCount = 0;
int maxLimit = 5;

int lastEntryState = LOW;
int lastExitState = LOW;

bool roomFullPrinted = false;

void setup() {
  pinMode(entrySensor, INPUT);
  pinMode(exitSensor, INPUT);

  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);

  Serial.println("Smart Visitor Counter Started");
  Serial.println("--------------------------------");
  Serial.print("Current Count: ");
  Serial.println(visitorCount);
}

void loop() {
  int entryState = digitalRead(entrySensor);
  int exitState = digitalRead(exitSensor);

  // Entry detected
  if (entryState == HIGH && lastEntryState == LOW) {
    visitorCount++;

    Serial.println("Person Entered");
    Serial.print("Current Count: ");
    Serial.println(visitorCount);

    delay(500);
  }

  // Exit detected
  if (exitState == HIGH && lastExitState == LOW) {
    if (visitorCount > 0) {
      visitorCount--;
    }

    Serial.println("Person Exited");
    Serial.print("Current Count: ");
    Serial.println(visitorCount);

    delay(500);
  }

  // Room full condition
  if (visitorCount >= maxLimit) {
    digitalWrite(led, HIGH);
    digitalWrite(buzzer, HIGH);

    if (roomFullPrinted == false) {
      Serial.println("ALERT: ROOM FULL!");
      roomFullPrinted = true;
    }
  } 
  else {
    digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);
    roomFullPrinted = false;
  }

  lastEntryState = entryState;
  lastExitState = exitState;
}