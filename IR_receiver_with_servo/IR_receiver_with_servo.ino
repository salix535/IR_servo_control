#include <IRremote.hpp>
#include <SCServo.h>
#include <LiquidCrystal.h>

#define IR_RECEIVER_PIN 8
#define UP_CODE 545194111
#define DOWN_CODE 2692677759
#define S_RXD 0
#define S_TXD 1

SMS_STS st;
uint32_t received_code;
int received_buffer = 0;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  IrReceiver.begin(IR_RECEIVER_PIN);
  Serial.begin(1000000, SERIAL_8N1);
  st.pSerial = &Serial;
  st.WheelMode(1);
  lcd.begin(16, 2);
  delay(500);
}

  void move_servo() {
    if (received_code == DOWN_CODE) {
      st.WriteSpe(1, -2000);
    }
    else if (received_code == UP_CODE) {
      st.WriteSpe(1, 2000);
    }
  }

void loop() {
  if (IrReceiver.decode()) {
    received_code = IrReceiver.decodedIRData.decodedRawData;
    received_buffer = 10;
    move_servo();
    delay(100);
    IrReceiver.resume();
  } else if (received_buffer-- <= 0) {
    st.WriteSpe(1, 0);
  }
  getServoPosition();
}

void getServoPosition() {
  lcd.clear();
  lcd.setCursor(0, 0);
  int position = st.ReadPos(1);
  lcd.print(position, DEC);
  delay(10);
}