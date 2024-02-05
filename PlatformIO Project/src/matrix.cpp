#include "matrix.h"

#define IN_A 38
#define IN_B 39
#define OUT_A 0
#define OUT_B 22

char getKey() {
  pinMode(IN_A, INPUT_PULLDOWN);
  pinMode(IN_B, INPUT_PULLDOWN);
  pinMode(OUT_A, OUTPUT);
  pinMode(OUT_B, OUTPUT);

  // Set the first row to HIGH and read the values of the columns
  digitalWrite(OUT_A, HIGH);
  digitalWrite(OUT_B, LOW);
  delay(1);  // Optional delay for stabilization
  uint8_t val1 = digitalRead(IN_A);
  uint8_t val2 = digitalRead(IN_B);

  // Set the second row to HIGH and read the values of the columns
  digitalWrite(OUT_A, LOW);
  digitalWrite(OUT_B, HIGH);
  delay(1);  // Optional delay for stabilization
  uint8_t val3 = digitalRead(IN_A);
  uint8_t val4 = digitalRead(IN_B);

  // Check the values to determine the pressed key
  if (val1 == HIGH && val2 == LOW) {
    return '1';
  } else if (val1 == LOW && val2 == HIGH) {
    return '2';
  } else if (val3 == HIGH && val4 == LOW) {
    return '3';
  } else if (val3 == LOW && val4 == HIGH) {
    return '4';
  } else {
    return '\0';  // Return null character if no key is pressed
  }
}
