#define IR_SEND_PIN 3
#define CODE_UP 0xFE00FE04
#define CODE_DOWN 0xFE00FE05

#include <IRremote.h>

IRsend irsend;

void setup() {
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
}

void loop() {
  
  if (digitalRead(4) == LOW) {
    irsend.sendNEC(CODE_UP, 32);
    delay(10);
  } 
  else if (digitalRead(5) == LOW) {
    irsend.sendNEC(CODE_DOWN, 32);
    delay(10);
  } 
}