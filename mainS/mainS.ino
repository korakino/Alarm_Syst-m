#include "prototypes.h"
#include <Wire.h>
#include <I2C_LCD.h>
I2C_LCD LCD;
uint8_t I2C_LCD_ADDRESS = 0x51; //Device address configuration, the default value is 0x51.



void setup() {
  // On initialise la communication avec l'ordinateur
  Wire.begin();
  
  LCD.CleanAll(WHITE);    //Clean the screen with black or white.
  //8*16 font size��auto new line��black character on white back ground.
  LCD.FontModeConf(Font_6x8, FM_ANL_AAA, BLACK_BAC);

  Serial.begin(9600);
  Serial.println("Systeme d'alarme demarre. En attente du code...");
  pinMode(buzzer, OUTPUT);
  pinMode(movePin, INPUT);
  pinMode(LEDPin, OUTPUT);
}

void loop() {

  char touche = monClavier.getKey();  // On écoute le clavier

  mouvement = digitalRead(movePin);

  // --- SI MOUVEMENT DETECTE (L'ALARME SONNE) ---
  if(mouvement == HIGH && alarme_active) {
    digitalWrite(LEDPin, HIGH);
    Serial.println("ALERTE : Mouvement detecte !");
    
    // On garde les delay() ici car l'alarme est en cours, c'est moins grave de bloquer un peu
    tone(buzzer, 4000);
    delay(200);
    tone(buzzer, 2000);
    delay(200);
  }
  
  // --- SI AUCUN MOUVEMENT (MODE VEILLE) ---
  else {
    noTone(buzzer); // On s'assure que le buzzer est éteint
    
    unsigned long tempsActuel = millis(); // On regarde le chronomètre

    // Si 500ms se sont écoulées...
    if (tempsActuel - tempsPrecedent >= intervalle) {
      tempsPrecedent = tempsActuel; // On met à jour la mémoire du temps
      
      // On inverse l'état de la LED (si elle est éteinte on l'allume, et vice-versa)
      if (etatLED == LOW) {
        etatLED = HIGH;
      } else {
        etatLED = LOW;
      }
      digitalWrite(LEDPin, etatLED); // On applique le nouvel état à la LED
    }
  }
  
  if (touche) {  // Si une touche a été pressée
    if (touche == '*'){
          if (compare_ans_passwd(answer)){ 
            alarme_active = false;
            Serial.println("access granted");
            LCD.CharGotoXY(0,0);
            LCD.print("access granted");
          }
          else 
          {
            Serial.println("access denied");
            LCD.CharGotoXY(0,0);
            LCD.print("access denied");
            answer_count = 0; 

            delay(2000);
            LCD.CharGotoXY(0,0);
            LCD.print("En attente du prochain code...");
            Serial.println("En attente du prochain code...");
            delay(2000);
          }
    }
    else{
      LCD.CharGotoXY(0,0);
      LCD.print("Touche pressée : ");
      Serial.print("Touche pressée : ");

      answer[answer_count] = touche;
      LCD.CharGotoXY(95, 0);
      LCD.print(touche);
      Serial.println(touche);
      Serial.println(answer_count);
      answer_count++;
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
        delay (500);
      }
      
      else Serial.println("En attente...");
  	}
    Serial.println("Mot de passe modifie");
}