#include "prototypes.h"



void setup() {
  // On initialise la communication avec l'ordinateur
  Serial.begin(9600);
  Serial.println("Systeme d'alarme demarre. En attente du code...");
  pinMode(buzzer, OUTPUT);
  pinMode(movePin, INPUT);
  pinMode(LEDPin, OUTPUT);
}

void loop() {
  char touche = monClavier.getKey();  // On écoute le clavier

  mouvement = digitalRead(movePin);
  noTone(buzzer);

  if(mouvement == HIGH)
  {
    digitalWrite(LEDPin, HIGH);
    Serial.print("buzzer on");
    tone(buzzer, 4000);
    delay(200);

    tone(buzzer, 2000);
    delay(200);
  }

  else
  {
    //digitalWrite(LEDPin, HIGH);
    delay(500);

    //digitalWrite(LEDPin, LOW);
    delay(500);
  }

  Serial.print("\n");
  
  
  if (touche) {  // Si une touche a été pressée
    Serial.print("Touche pressee : ");
    answer[answer_count] = touche;
    Serial.println(touche);
    Serial.println(answer_count);
    answer_count++;
  }
  if (touche == '9'){
      if (compare_ans_passwd(answer)) Serial.println("access garanted");
      else Serial.println("access denied");
      answer_count = 0; 
      Serial.println("En attente du prochain code...");
  }
  
}

bool compare_ans_passwd(char ans[]){
  bool verifier = true;
  int count = 0;
  while (count < PASSWD && verifier){
    if (ans[count] != password[count]) verifier = false;
    count++;
  }
  return verifier;
}