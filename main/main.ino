#include "prototypes.h"



void setup() {
  // On initialise la communication avec l'ordinateur
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Systeme d'alarme demarre. En attente du code...");
  pinMode(buzzer, OUTPUT);
  pinMode(movePin, INPUT);
  pinMode(LEDPin, OUTPUT);


  // Initialisation de l'écran UNE SEULE FOIS au démarrage
  LCD.CleanAll(WHITE);    
  LCD.FontModeConf(Font_6x8, FM_ANL_AAA, BLACK_BAC);
  LCD.CharGotoXY(0,0);
  LCD.print("Alarme armee !");
  LCD.CharGotoXY(0,16);
  LCD.print("En attente...");
  
  Serial.println("Systeme d'alarme demarre.");

}

void loop() {


  char touche = monClavier.getKey();  // On écoute le clavier

  mouvement = digitalRead(movePin);

  
  if (touche) 
  {  // Si une touche a été pressée
    if (touche == '*')
    {
      if (compare_ans_passwd(answer))
      { 
        noTone(buzzer);       // On coupe le son immédiatement
        digitalWrite(LEDPin, LOW);
        tempsDesarmement = millis();
        LCD.CleanAll(WHITE);
        LCD.CharGotoXY(0, 0);
        
        if (!alarme_armee) 
        {
          alarme_armee = true;
          LCD.print("Access GRANTED");
          LCD.CharGotoXY(0, 10);
          LCD.print("Alarme armee");
          Serial.println("Access GRANTED");
          Serial.println("Alarme armee");
        }
        else 
        {
          alarme_armee = false;
          alarme_active = false;
          LCD.print("Access GRANTED");
          LCD.CharGotoXY(0, 10);
          LCD.print("Alarme desarmee");
          Serial.println("Access GRANTED");
          Serial.println("Alarme desarmee");
        }
        
      }
      else
      {
        // Mauvais code
        LCD.CleanAll(WHITE);
        LCD.CharGotoXY(0,0);
        LCD.print("Access DENIED");
        Serial.println("Access DENIED");
      }
    }
    else
    {
      LCD.CleanAll(WHITE); 
      LCD.CharGotoXY(0,0);
      LCD.print("Touche pressee : ");
      Serial.print("Touche pressee : ");

      answer[answer_count] = touche;
      LCD.print(touche);
      Serial.println(touche);
      Serial.println(answer_count);
      answer_count++;
    }
  }
  

  // --- SI MOUVEMENT DETECTE (L'ALARME SONNE) ---
  if(mouvement == HIGH && alarme_armee) 
  {
    digitalWrite(LEDPin, HIGH);
    Serial.println("ALERTE : Mouvement detecte !");
    alarme_active = true;
  }

  if (alarme_active)
  {
    if (millis() - chronoBuzzer >= 200) 
    { 
      chronoBuzzer = millis(); // On remet le chronomètre à zéro
      
      if (noteAigue) 
      {
        tone(buzzer, 1500);
        noteAigue = false; // La prochaine fois, on fera la note grave
      } else {
        tone(buzzer, 1000);
        noteAigue = true;  // La prochaine fois, on fera la note aiguë
      }
    }
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




void modif_password(char new_password[], char password[], char touche){
  int lenpwd = 0;
    //Initialisation nouveau mot de passe
    while(lenpwd < PASSWD)
    {
      if (touche)
      {
      	Serial.print("Touche pressee : ");
        answer[answer_count] = touche;
        Serial.println(touche);
        Serial.println(answer_count);
      
    	  password[answer_count] = new_password[answer_count];
      	answer_count++;
      }
      
      else Serial.println("En attente...");
  	}
    Serial.println("Mot de passe modifie");
}

