const int LEDPin = 5;
const int det = 6;
int mouvement;



void setup() 
{
  pinMode(det, INPUT);
  pinMode(LEDPin, OUTPUT);  
  Serial.begin(9600);
}

void loop()
{
  mouvement = digitalRead(det);


  if (mouvement == HIGH){
    digitalWrite(LEDPin, HIGH);
  }

  else
  {
    digitalWrite(LEDPin, LOW);
  }

  Serial.print(mouvement);
  Serial.print("\n");
}
