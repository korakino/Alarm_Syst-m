# 🚨 Alarm_Syst-m (Domotic Alarm System)

Un système de sécurité domotique complet basé sur **Arduino Uno R3**. Ce projet étudiant intègre la détection de mouvement, le contrôle d'accès par code secret et des alertes visuelles/sonores.

L'une des grandes forces de ce code est son architecture **non-bloquante** (utilisation de la fonction `millis()`), permettant au système de rester fluide et à l'écoute du clavier même lorsque la sirène d'alerte est déclenchée.

## ✨ Fonctionnalités Principales

* 👁️ **Surveillance active :** Détection d'intrusion instantanée via un capteur de mouvement PIR.
* 🔐 **Contrôle d'accès On/Off :** Clavier matriciel 4x3 pour saisir le code secret. Le code agit comme un interrupteur : tapez-le pour armer le système en partant, tapez-le à nouveau pour le désarmer en rentrant.
* 📺 **Écran LCD I2C :** Interface graphique en temps réel affichant le statut interactif ("Alarme armée", "Access GRANTED", "Access DENIED").
* 🔊 **Alarme bi-ton :** Sirène alternant entre deux fréquences (1000Hz / 1500Hz) de manière non-bloquante pour permettre la saisie d'urgence.
* ⚙️ **Modification de mot de passe :** Fonction embarquée (`modif_password`) prévue pour redéfinir le code secret en direct.

## 📁 Architecture du Dépôt

* `/mainB/` : Contient le cœur du projet.
  * `mainB.ino` : Boucle principale et logique d'états de l'alarme.
  * `prototypes.h` : Déclarations des fonctions, variables globales et configuration de la matrice du clavier.
* `/I2C_LCD_master/` : Ressources pour l'écran.
  * `resources/I2C_LCD_Library.zip` : **⚠️ Bibliothèque requise à installer manuellement** pour faire fonctionner l'affichage.

## 🛠️ Matériel Requis (Hardware)

* 1x Arduino Uno R3
* 1x Clavier matriciel (Keypad) 4x3
* 1x Capteur de mouvement PIR (ex: HC-SR501)
* 1x Écran LCD I2C (Adresse par défaut `0x51`)
* 1x Buzzer passif
* 1x LED (avec résistance de 220Ω)
* Plaque d'essai et câbles de connexion (Jumper wires)

## 🔌 Câblage (Pinout)

| Composant | Broche Arduino | Remarques |
| :--- | :--- | :--- |
| **Buzzer** | Pin 10 | |
| **Capteur PIR** | Pin 12 | VCC -> 5V, GND -> GND |
| **LED Statut** | Pin 13 | |
| **Keypad Lignes (1 à 4)** | Pins 8, 7, 6, 5 | De haut en bas |
| **Keypad Colonnes (1 à 3)**| Pins 4, 3, 2 | De gauche à droite |
| **Écran LCD** | SDA / SCL | Connecté via le bus I2C matériel |

## 🚀 Installation & Utilisation

1. **Installer la bibliothèque LCD :** * Téléchargez le fichier `I2C_LCD_Library.zip` situé dans le dossier `/I2C_LCD_master/resources/`.
   * Dans l'IDE Arduino, allez dans *Croquis > Inclure une bibliothèque > Ajouter la bibliothèque .ZIP* et sélectionnez ce fichier.
2. Assurez-vous d'avoir également la bibliothèque `Keypad` installée via le gestionnaire de bibliothèques.
3. Ouvrez le fichier `mainB/mainB.ino` dans l'IDE Arduino et téléversez-le sur votre carte.
4. **Utilisation :**
   * Au démarrage, tapez votre code puis `*` pour armer le système.
   * En cas de mouvement, l'alarme sonne.
   * Retapez votre code puis `*` pour désarmer et stopper l'alerte.

## 📄 Licence
Ce projet est sous licence MIT - voir le fichier [LICENSE](LICENSE) pour plus de détails.
