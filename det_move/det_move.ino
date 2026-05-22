int LEDPin = 3;
int det = 2;


void setup() 
{
  pinMode(det, INPUT_PULLUP);
  pinMode(LEDPin, OUTPUT);  
  Serial.begin(9600);
}

void loop()
{
  if (digitalRead(det) == 1){
    digitalWrite(LEDPin, HIGH);
  }

  else
  {
    digitalWrite(LEDPin, LOW);
  }
}
