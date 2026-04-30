#include <Keypad.h>
#include <stdlib.h>
#define PASSWD 3

const byte ROWS = 4;  // 4 lignes
const byte COLS = 3;  // 3 colonnes

// On dessine la disposition exacte de ton clavier physique
char keys[ROWS][COLS] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' }
};

// --- ATTENTION AU CÂBLAGE ---
// Les numéros ci-dessous dépendent de l'ordre exact de tes fils.
// Si les touches ne correspondent pas quand tu appuies, il suffira de changer cet ordre.

// On assigne 4 broches pour les lignes (par exemple 8, 7, 6, 5)
byte rowPins[ROWS] = { 8, 7, 6, 5 };

// On assigne 3 broches pour les colonnes (par exemple 4, 3, 2)
byte colPins[COLS] = { 4, 3, 2 };

// Création de l'objet "monClavier"
Keypad monClavier = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

char password[PASSWD] = { '1', '2', '3' };
char answer[PASSWD];
int answer_count = 0;
char new_password[PASSWD] = {'0', '0', '0'};












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
  
  
  if (touche =='7')
  {
    modif_password(new_password, password, answer_count, touche);
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

void modif_password(char new_password[], char password[], int answer_count, char touche)
{
  
    //Initialisation nouveau mot de passe
    while(answer_count < PASSWD)
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
