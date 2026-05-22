int ledPin = 5;
int buzzer = 9;
int movePin = 6;
int mouvement = 0;


void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(movePin, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  mouvement = digitalRead(movePin);
  noTone(buzzer);

  if(mouvement == HIGH)
  {
    digitalWrite(ledPin, HIGH);
    tone(buzzer, 4000);
    delay(200);

    tone(buzzer, 2000);
    delay(200);
  }

  else
  {
    digitalWrite(ledPin, HIGH);
    delay(500);

    digitalWrite(ledPin, LOW);
    delay(500);
  }

  
  Serial.print(mouvement);
  Serial.print("\n");
}
