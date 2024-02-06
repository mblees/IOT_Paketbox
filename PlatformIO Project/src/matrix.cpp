#include "matrix.h"

const byte ROWS = 2; // Anzahl der Zeilen der Tastatur
const byte COLS = 2; // Anzahl der Spalten der Tastatur

char keys[ROWS][COLS] = {
  {'1','2'},
  {'4','5'},
};

byte rowPins[ROWS] = {0, 23}; // Verbindung der Tastaturzeilen mit den Arduino-Pins
byte colPins[COLS] = {2, 25}; // Verbindung der Tastaturspalten mit den Arduino-Pins

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

char getKey(){
  char key = keypad.getKey(); // Tastenabfrage
  if(key){
    return key;
  }
  return ' ';
}
