# 🚨 Alarm_Syst-m (Domotic Alarm System)

Un système de sécurité domotique complet basé sur **Arduino Uno R3**. Intègre la détection de mouvement, le contrôle d'accès par code secret et des alertes visuelles/sonores.

L'une des grandes forces de ce code est son architecture **non-bloquante** (utilisation de `millis()` avec gestion de l'overflow) et sa stabilité, permettant au système de rester fluide et réactif même lorsque la sirène hurle.

## ✨ Fonctionnalités Principales

* 👁️ **Surveillance active :** Détection d'intrusion instantanée via un capteur de mouvement PIR (avec filtre anti-spam sur le moniteur série).
* 🔐 **Contrôle d'accès On/Off :** Clavier matriciel 4x3 pour saisir le code secret. Le code agit comme un interrupteur : tapez-le pour armer le système en partant, tapez-le à nouveau pour le désarmer en rentrant.
* 📺 **Écran LCD I2C :** Interface graphique en temps réel affichant le statut interactif ("Alarme armée", "Access GRANTED", "Access DENIED"), avec séquence d'initialisation sécurisée.
* 🔊 **Alarme bi-ton :** Sirène alternant entre deux fréquences (1000Hz / 1500Hz) de manière non-bloquante pour permettre la saisie d'urgence.
* ⚙️ **Modification de mot de passe :** Fonction embarquée (`modif_password`) prévue pour redéfinir le code secret en direct.
* 🛡️ **Protection Anti-Crash :** Protection matérielle contre les chutes de tension (brownout) lors du déclenchement de l'alarme.

## 📁 Architecture du Dépôt

* `/main/` : Contient le cœur du projet.
  * `main.ino` : Boucle principale et logique d'états de l'alarme.
  * `prototypes.h` : Déclarations des fonctions, variables globales et configuration de la matrice du clavier.
  * `resources/I2C_LCD_Library.zip` : **⚠️ Bibliothèque requise à installer manuellement** pour faire fonctionner l'affichage.

## 🛠️ Matériel Requis (Hardware)

* 1x Arduino Uno R3
* 1x Clavier matriciel (Keypad) 4x3
* 1x Capteur de mouvement PIR (ex: HC-SR501)
* 1x Écran LCD I2C (Adresse par défaut `0x51`)
* 1x Buzzer passif
* 1x LED rouge ou composant visuel
* 2x Résistances de 220Ω (Une pour la LED, une pour le buzzer)
* Plaque d'essai et câbles de connexion (Jumper wires)

## 🔌 Câblage (Pinout)

| Composant | Broche Arduino | Remarques |
| :--- | :--- | :--- |
| **Buzzer** | Pin 10 | **⚠️ Placer une résistance de 220Ω en série** pour éviter que l'Arduino ne crashe (brownout). |
| **Capteur PIR** | Pin 12 | VCC -> 5V, GND -> GND |
| **LED Statut** | Pin 13 | En série avec une résistance de 220Ω |
| **Keypad Lignes (1 à 4)** | Pins 8, 7, 6, 5 | De haut en bas |
| **Keypad Colonnes (1 à 3)**| Pins 4, 3, 2 | De gauche à droite |
| **Écran LCD** | SDA / SCL | Connecté via le bus I2C matériel |

## 🚀 Installation & Utilisation

1. **Installer la bibliothèque LCD :** 
   * Téléchargez le fichier `I2C_LCD_Library.zip`.
   * Dans l'IDE Arduino, allez dans *Croquis > Inclure une bibliothèque > Ajouter la bibliothèque .ZIP* et sélectionnez ce fichier.
2. Assurez-vous d'avoir également la bibliothèque `Keypad` installée via le gestionnaire de bibliothèques.
3. Ouvrez le fichier `main/main.ino` dans l'IDE Arduino et téléversez-le sur votre carte.
4. **Utilisation :**
   * Au démarrage, l'écran s'initialise.
   * En cas de mouvement, la LED s'allume et l'alarme sonne.
   * Tapez votre code puis `*` pour désarmer et stopper l'alerte ou pour le réarmer si il a été désarmé précédemment. 

## 📄 Licence
Ce projet est sous licence MIT - voir le fichier [LICENSE](LICENSE) pour plus de détails.
