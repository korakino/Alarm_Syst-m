
// PIR sensor pin
const int pirPin = 12;
int pirState = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(13, OUTPUT);

  Serial.println("\nCalibrage du capteur de mouvement (attente de 60s)...");
  delay(60000); // On fige l'Arduino pendant 20 secondes au démarrage
  
  Serial.println("Systeme d'alarme demarre. En attente du code...");
}

void loop() {
  int motion = digitalRead(pirPin);

  if (motion == HIGH) {
    if (pirState == LOW) {
      Serial.println("Motion Detected");
      digitalWrite(13, HIGH);
      pirState = HIGH;
    }
  } else {
    if (pirState == HIGH) {
      Serial.println("Not Detected");
      digitalWrite(13, HIGH);
      pirState = LOW;
    }
  }

  delay(500);
}