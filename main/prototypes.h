#include <Keypad.h>
#include <Wire.h>
#include <I2C_LCD.h>
#define PASSWD 3

I2C_LCD LCD;
uint8_t I2C_LCD_ADDRESS = 0x51; //Device address configuration, the default value is 0x51.



const byte ROWS = 4;  // 4 lignes
const byte COLS = 3;  // 3 colonnes
int LEDPin = 13;
int buzzer = 10;
int movePin = A1;
int mouvement = 0;



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
char answer[PASSWD]; // Plus besoin de le remplir de zéros
int answer_count = 0;

bool alarme_armee = true;
bool alarme_active = false;
unsigned long tempsPrecedent = 0; 
const long intervalle = 500; // La LED clignotera toutes les 500 millisecondes
int etatLED = LOW;
unsigned long chronoBuzzer = 0;
bool noteAigue = true;
unsigned long tempsDesarmement = 0;
