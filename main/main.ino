#include "prototypes.h"



void setup() {
  Serial.begin(9600);
  Wire.begin();
  Serial.println("init");
  delay(500);
  // Initialisation de l'écran UNE SEULE FOIS au démarrage
  LCD.CleanAll(WHITE);
  LCD.FontModeConf(Font_6x8, FM_ANL_AAA, BLACK_BAC);
  Serial.println("prepare écran...");
  LCD.CharGotoXY(0, 0);
  LCD.print("Alarme armee !");
  LCD.CharGotoXY(0, 16);
  LCD.print("En attente...");
  // On initialise la communication avec l'ordinateur
  pinMode(buzzer, OUTPUT);
  pinMode(movePin, INPUT);
  pinMode(LEDPin, OUTPUT);


  Serial.println("\nSysteme d'alarme demarre. En attente du code...");
  delay(60000);




  Serial.println("Systeme d'alarme demarre.");
}

void loop() {


  char touche = monClavier.getKey();  // On écoute le clavier

  mouvement = analogRead(movePin);
  // Serial.println(mouvement);


  if (touche) {  // Si une touche a été pressée
    if (touche == '*') {
      if (compare_ans_passwd(answer)) {
        noTone(buzzer);  // On coupe le son immédiatement
        digitalWrite(LEDPin, LOW);
        tempsDesarmement = millis();
        LCD.CleanAll(WHITE);
        LCD.CharGotoXY(0, 0);

        if (!alarme_armee) {
          alarme_armee = true;
          LCD.print("Access GRANTED");
          LCD.CharGotoXY(0, 10);
          LCD.print("Alarme armee");
          Serial.println("Access GRANTED");
          Serial.println("Alarme armee");
        } else {
          alarme_armee = false;
          alarme_active = false;
          LCD.print("Access GRANTED");
          LCD.CharGotoXY(0, 10);
          LCD.print("Alarme desarmee");
          Serial.println("Access GRANTED");
          Serial.println("Alarme desarmee");
        }

      } else {
        // Mauvais code
        LCD.CleanAll(WHITE);
        LCD.CharGotoXY(0, 0);
        LCD.print("Access DENIED");
        Serial.println("Access DENIED");
      }
      answer_count = 0;

    } else if (touche == '#') {
      modif_password(password);

    } else {
      LCD.CleanAll(WHITE);
      LCD.CharGotoXY(0, 0);
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
  if (mouvement >= 100 && alarme_armee && !alarme_active) {
    digitalWrite(LEDPin, HIGH);
    Serial.println("ALERTE : Mouvement detecte !");
    LCD.CleanAll(WHITE);
    LCD.CharGotoXY(0, 0);
    LCD.print("ALERTE : Mouvement detecte !");
    alarme_active = true;
  }

  if (alarme_active) {
    if (millis() - chronoBuzzer >= 200) {
      chronoBuzzer = 0;
      chronoBuzzer = millis();  // On remet le chronomètre à zéro

      if (noteAigue) {
        tone(buzzer, 1500);
        Serial.println(mouvement);
        // Serial.println("BIP !");
        digitalWrite(LEDPin, HIGH);

        noteAigue = false;  // La prochaine fois, on fera la note grave
      } else {
        tone(buzzer, 1000);
        Serial.println(mouvement);
        // Serial.println("BIP !");
        noteAigue = true;  // La prochaine fois, on fera la note aiguë
        digitalWrite(LEDPin, LOW);
      }
    }
  }
}




bool compare_ans_passwd(char ans[]) {
  bool verifier = true;
  int count = 0;
  while (count < PASSWD && verifier) {
    if (ans[count] != password[count]) verifier = false;
    count++;
  }
  return verifier;
}




void modif_password(char password[]) {

  int lenpwd = 0;
  bool autorise = false;
  bool exit = false;
  char new_password[PASSWD];
  LCD.CleanAll(WHITE);
  LCD.CharGotoXY(0, 0);
  LCD.print("Veuillez rentrer votre code actuel");
  Serial.print("Veuillez rentrer votre code actuel");
  //Initialisation nouveau mot de passe
  while (!exit) {
    char touche = monClavier.getKey();
    if (touche) {
      if (touche == '*') {
        if (!autorise) {
          if (compare_ans_passwd(new_password)) {
            autorise = true;
            LCD.CleanAll(WHITE);
            LCD.CharGotoXY(0, 0);
            LCD.print("Mot de passe valide");
            Serial.print("Mot de passe valide");
            lenpwd = 0;
          } else {
            LCD.CleanAll(WHITE);
            LCD.CharGotoXY(0, 0);
            LCD.print("Mot de passe incorrecte");
            Serial.print("Mot de passe incorrecte");
            exit = true;
          }
        } else {
          for (int i = 0; i < PASSWD; i++)
            password[i] = new_password[i];
          LCD.CleanAll(WHITE);
          LCD.CharGotoXY(0, 0);
          LCD.print("Mot de passe modifie");
          Serial.print("Mot de passe modifie");
          exit = true;
        }
      } else {
        LCD.CleanAll(WHITE);
        LCD.CharGotoXY(0, 0);
        LCD.print("Touche pressee : ");
        Serial.print("Touche pressee : ");

        new_password[lenpwd] = touche;
        LCD.print(touche);
        Serial.println(touche);
        Serial.println(lenpwd);
        lenpwd++;
      }
    }
  }






  lenpwd++;
}
