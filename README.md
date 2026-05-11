# 🚨 Alarm_Syst-m (Domotic Alarm System)

Un système de sécurité domotique sur **Arduino Uno R3**. Ce projet intègre la détection de mouvement, le contrôle d'accès par code secret et des alertes visuelles/sonores.

## ✨ Fonctionnalités Principales

* 👁️ **Surveillance active :** Détection d'intrusion instantanée via un capteur de mouvement PIR.
* 🔐 **Contrôle d'accès :** Clavier matriciel 4x3 pour saisir le code secret, avec masquage visuel (affichage de `*` lors de la frappe).
* 📺 **Écran LCD I2C :** Interface graphique en temps réel affichant le statut ("Alarme armée", "Access GRANTED", alertes).
* 🔊 **Alarme bi-ton :** Sirène alternant entre deux fréquences (2000Hz / 4000Hz) de manière non-bloquante.
* ⏱️ **Délai de sortie / Réarmement :** Après un désarmement, l'utilisateur a **1 minute** pour quitter les lieux avant que le système ne se réarme automatiquement.
* ⚙️ **Modification de mot de passe :** Fonction intégrée (`modif_password`) pour redéfinir le code secret en direct.

## 📁 Architecture du Dépôt

* `/mainB/` : Contient le cœur du projet.
  * `mainB.ino` : Boucle principale et logique de la machine à états.
  * `prototypes.h` : Déclarations des fonctions, variables globales et matrice du clavier.
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
2. Assurez-vous d'avoir également la bibliothèque `Keypad` de Mark Stanley installée via le gestionnaire de bibliothèques.
3. Ouvrez le fichier `mainB/mainB.ino` dans l'IDE Arduino et téléversez-le sur votre carte.
4. **Utilisation :**
   * Au démarrage, le système est "Armé".
   * En cas de mouvement, l'alarme sonne.
   * Tapez votre code à 3 chiffres suivi de `*` pour désarmer le système.
   * Vous avez ensuite 60 secondes pour partir avant l'auto-réarmement.

