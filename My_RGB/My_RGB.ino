// ----- Общие параметры ленты
#define AUTO_BRIGHTNESS 0  // автоматическая яркость
#define IR_PIN 2 // пин подключения IR приемника
#define REZISTOR A2 // пин фоторезистора
#define LED_max 70 // Максимальная яркость (500)
#define LED_min 0  // Минимальная яркость (0)

// ----- Библиотеки
#include "EEPROM.h"
#include "GyverRGB.h"
GRGB strip(9, 10, 11);
#include "GyverButton.h"

// ----- Переменные
byte mode = 1; // режим
byte IRData; // запоминание кнопки пульта
unsigned long eepromTimer;
boolean eepromFlag, LED_state = 1, ir_flag;

// ----- Режим статичной подсветки
byte HUE_1 = 0;
byte HUE_2 = 85;
byte HUE_3 = 170;
byte SAT_1 = 255;
byte SAT_2 = 255;
byte SAT_3 = 255;
byte VOL_1 = 255;
byte VOL_2 = 255;
byte VOL_3 = 255;

// ----- Режим RGB плавная смена света
unsigned long RGB_timer;
#define RGB_step 5
int fade = A0; // Скорость режима
int R = 255;
int G = 0;
int B = 0;
int Rkey = 1;
int Gkey = 0;
int Bkey = 0;

// ---- Кнопки пульта
#include "IRLremote.h"
CHashIR IRLremote;
uint32_t IRdata;

#define BUTT_UP     0xF39EEBAD
#define BUTT_DOWN   0xC089F6AD
#define BUTT_LEFT   0xE25410AD
#define BUTT_RIGHT  0x14CE54AD
#define BUTT_OK     0x297C76AD
#define BUTT_1      0x4E5BA3AD
#define BUTT_2      0xE51CA6AD
#define BUTT_3      0xE207E1AD
#define BUTT_4      0x517068AD
#define BUTT_5      0x1B92DDAD
#define BUTT_6      0xAC2A56AD
#define BUTT_7      0x5484B6AD
#define BUTT_8      0xD22353AD
#define BUTT_9      0xDF3F4BAD
#define BUTT_0      0xF08A26AD
#define BUTT_STAR   0x68E456AD
#define BUTT_HASH   0x151CD6AD

// -----------для разработчиков-------------------------
#define DEBUG 1
#define First_number 50
#define First_cell 1023


void setup() {
#if (DEBUG) // включение монитора порта
  Serial.begin(9600);
#endif
  if (EEPROM.read(First_cell) != First_number) { // действия при первом запуске
    EEPROM.write(First_cell, First_number);
    EEPROM.put(0, mode);
    EEPROM.put(1, HUE_1);
    EEPROM.put(2, HUE_2);
    EEPROM.put(3, HUE_3);
    EEPROM.put(4, SAT_1);
    EEPROM.put(5, SAT_2);
    EEPROM.put(6, SAT_3);
     EEPROM.put(7, VOL_1);
    EEPROM.put(8, VOL_2);
    EEPROM.put(9, VOL_3);
    
  }
  eepromGet();
  IRLremote.begin(IR_PIN);
  pinMode(A0, OUTPUT);
  analogReference(DEFAULT);

}
void loop() {
#if (AUTO_BRIGHTNESS)
  autoBrightness();
#else
  strip.setMaxCurrent (93, 12000, 300);
#endif
  remoteTick();
  modeLoop();
  eepromTick();
  Serial.print(mode);
}
void modeLoop() {
  if (LED_state) {
    switch (mode) {
      case 1:
      case 2:
      case 3:
        static_LED();
        break;
      case 4 :
        RGB_LED();
        break;
        /* case 5:
           redLed();
           break;
          case 6:
           redLed();
           break;
          case 7:
           redLed();
           break;
          case 8:
           redLed();
           break;
          case 9:
           redLed();
           break;*/
    }
  }
}
void autoBrightness() {
  int LED_br = analogRead(REZISTOR);
  if (LED_br >= LED_max) LED_br = LED_max;
  if (LED_br <= LED_min) LED_br = LED_min;
  LED_br = map(LED_br, LED_min, LED_max, 550, 50);
  /* Serial.print(analogRead(A2));
    Serial.print("   ");
    Serial.println(LED_br);*/
  strip.setMaxCurrent (93, 12000, LED_br);
}
void remoteTick() {
  if (IRLremote.available())  {
    auto data = IRLremote.read();
    IRdata = data.command;
    ir_flag = true;
  }
  if (ir_flag) { // если данные пришли
    switch ( IRdata) {
      case BUTT_1: mode = 1;
        break;
      case BUTT_2: mode = 2;
        break;
      case BUTT_3: mode = 3;
        break;
      case BUTT_4: mode = 4;
        break;
      case BUTT_5: mode = 5;
        break;
      case BUTT_6: mode = 6;
        break;
      case BUTT_7: mode = 7;
        break;
      case BUTT_8: mode = 8;
        break;
      case BUTT_9: mode = 9;
        break;
      // case BUTT_0: ;
      //   break;
      //   case BUTT_STAR:
      //   break;
      case BUTT_HASH: LED_state = !LED_state; strip.setRGB(0, 0, 0); eepromUpdate();
        break;
      //  case BUTT_OK:
      case BUTT_UP :
        if (mode == 1) {
          VOL_1 = VOL_1 + 20;
          VOL_1 = constrain(VOL_1, 0, 255);
        }
        if (mode == 2) {
          VOL_2 = VOL_2 + 20;
          VOL_2 = constrain(VOL_2, 0, 255);
        }
        if (mode == 3) {
          VOL_3 = VOL_3 + 20;
          VOL_3 = constrain(VOL_3, 0, 255);
        }
        break;
      case BUTT_DOWN : {
          if (mode == 1) {
            VOL_1 = VOL_1 - 20;
            VOL_1 = constrain(VOL_1, 0, 255);
          }
          if (mode == 2) {
            VOL_2 = VOL_2 - 20;
            VOL_2 = constrain(VOL_2, 0, 255);
          }
          if (mode == 3) {
            VOL_3 = VOL_3 - 20;
            VOL_3 = constrain(VOL_3, 0, 255);
          }

        }
    }
  }
}
void eepromGet() {
  EEPROM.get(0, mode);
  EEPROM.get(1, HUE_1);
  EEPROM.get(2, HUE_2);
  EEPROM.get(3, HUE_3);
  EEPROM.get(4, SAT_1);
  EEPROM.get(5, SAT_2);
  EEPROM.get(6, SAT_3);
  EEPROM.get(7, VOL_1);
  EEPROM.get(8, VOL_2);
  EEPROM.get(9, VOL_3);
}
void eepromTick() {
  if (eepromFlag)
    if (millis() - eepromTimer >= 10000) {
      eepromTimer = millis();
      eepromFlag = 0;
      eepromUpdate();
    }
}
void eepromUpdate() {
  EEPROM.update(0, mode);
  Serial.println("aaaaa");
}
