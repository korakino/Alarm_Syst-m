#include "my_prototypes_keyboard.h"

void setup() {
  // On initialise la communication avec l'ordinateur
  Serial.begin(9600);
  Serial.println("Systeme d'alarme demarre. En attente du code...");
}

void loop() {
  char touche = monClavier.getKey();  // On écoute le clavier

  if (touche) {  // Si une touche a été pressée
    Serial.print("Touche pressee : ");
    answer[answer_count] = touche;
    Serial.println(touche);
    Serial.println(answer_count);
    answer_count++;
  }

  // touch to submit pressed
  if (touche == '9') {
    if (compare_ans_passwd(answer)) Serial.println("access garanted");
    else Serial.println("access denied");
    answer_count = 0;
    Serial.println("En attente du prochain code...");
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
