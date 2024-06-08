#define BTN_PIN 2
#define LED_S 3
#define LED_R 5
#define LED_Y 6
#define LED_G 10
#define LED_B 11

#include <GyverButton.h>
#include <EEPROM.h>

#define INIT_ADDR 1023
#define INIT_KEY 42

GButton butt(BTN_PIN);
boolean POWER = 1;
boolean star = 1;
byte mode = 1;

//------яркость
#define LED_step 10
boolean LED_br_direction = 1;
int LED_br = 255;
int LED_br_b = 100;
int LED_br_3 = 255;
int LED_br_3_b = 100;

//------2 режим
#define speed_2_step 10
byte LED_2 = 1;
int speed_2 = 500;
boolean speed_2_direction = 1;

//------3 режим
#define speed_3_step 1
byte LED_3 = 1;
int val = 0;
int speed_3 = 20;
boolean dir = 1;
boolean speed_3_direction = 1;

unsigned long count ;

void setup() {
  //Serial.begin(9600);
  if (EEPROM.read(INIT_ADDR) != INIT_KEY) {
    EEPROM.write(INIT_ADDR, INIT_KEY);
    EEPROM.put(0, LED_br);
    EEPROM.put(2, LED_br_b);
    EEPROM.put(4, LED_br_3);
    EEPROM.put(6, LED_br_3_b);
    EEPROM.put(10, mode);
    EEPROM.put(11, LED_br_direction);
    EEPROM.put(12, speed_2_direction);
    EEPROM.put(13, speed_2);
    EEPROM.put(14, speed_3_direction);
    EEPROM.put(15, speed_3);
  }
  EEPROM.get(0, LED_br);
  EEPROM.get(2, LED_br_b);
  EEPROM.get(4, LED_br_3);
  EEPROM.get(6, LED_br_3_b);
  EEPROM.get(10, mode);
  EEPROM.get(11, LED_br_direction);
  EEPROM.get(12, speed_2_direction);
  EEPROM.get(13, speed_2);
  EEPROM.get(14, speed_3_direction);
  EEPROM.get(15, speed_3);
  butt.setTimeout(300);
  butt.setStepTimeout(60);
  butt.setType(LOW_PULL);
  pinMode(BTN_PIN, INPUT_PULLUP);
  pinMode(LED_S, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_Y, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
}
void loop() {
  //Serial.println(speed_3);
  buttTick();
  mainLoop();

}
void mainLoop() {
  if (POWER) {
    if (star)
      digitalWrite(LED_S, LED_br);
    else
      digitalWrite(LED_S, 0);
    switch (mode) {
      case 1://постоянно горит
        analogWrite(LED_R, LED_br);
        analogWrite(LED_Y, LED_br);
        analogWrite(LED_G, LED_br);
        analogWrite(LED_B, LED_br_b);
        break;
      case 2://быстро мигает по одному светодиоду
        if (millis() - count <= speed_2)
          switch (LED_2) {
            case 1:
              analogWrite(LED_R, LED_br);
              analogWrite(LED_B, 0);
              break;
            case 2:
              analogWrite(LED_R, 0);
              analogWrite(LED_Y, LED_br);
              break;
            case 3:
              analogWrite(LED_Y, 0);
              analogWrite(LED_G, LED_br);
              break;
            case 4:
              analogWrite(LED_G, 0);
              analogWrite(LED_B, LED_br_b);
              break;
          }
        else {
          LED_2++;
          count = millis();
          if (LED_2 == 5)
            LED_2 = 1;
        }
        break;
      case 3://бысто мигает два работают два мигают(пятнашки)
        if (millis() - count <= speed_2)
          switch (LED_2) {
            case 1:
              analogWrite(LED_R, LED_br);
              analogWrite(LED_Y, LED_br);
              analogWrite(LED_B, 0);
              break;
            case 2:
              analogWrite(LED_R, 0);
              analogWrite(LED_Y, LED_br);
              analogWrite(LED_G, LED_br);
              break;
            case 3:
              analogWrite(LED_Y, 0);
              analogWrite(LED_G, LED_br);
              analogWrite(LED_B, LED_br_b);
              break;
            case 4:
              analogWrite(LED_G, 0);
              analogWrite(LED_B, LED_br_b);
              analogWrite(LED_R, LED_br);
              break;
          }
        else {
          LED_2++;
          count = millis();
          if (LED_2 == 5)
            LED_2 = 1;
        }
        break;
      case 4://плавное переливание

        if (millis() - count >= speed_3) {
          count = millis();
          LED_br_3 = getBrightCRT(val);
          LED_br_3_b = getBrightCRT(val);
          LED_br_3 = map(LED_br_3, 0, 255, 0, LED_br);
          LED_br_3_b = map(LED_br_3_b, 0, 255, 0, LED_br);
          if (dir) val = val + 6; // увеличиваем яркость
          else val = val - 6; // уменьшаем
          val = constrain(val, 0, 255);
          if (val >= 255 || val <= 0)
            dir = !dir;
          if (val <= 0) {
            LED_3++;
            if (LED_3 == 5)
              LED_3 = 1;
          }
          switch (LED_3) {
            case 1:
              analogWrite(LED_R, LED_br_3);
              break;
            case 2:
              analogWrite(LED_Y, LED_br_3);
              break;
            case 3:
              analogWrite(LED_G, LED_br_3);
              break;
            case 4:
              analogWrite(LED_B, LED_br_3_b);
              break;
          }
        }
        break;
      case 5://дыхание
        if (millis() - count >= speed_3) {
          count = millis();
          LED_br_3 = getBrightCRT(val);
          LED_br_3_b = getBrightCRT(val);
          LED_br_3 = map(LED_br_3, 0, 255, 0, LED_br);
          LED_br_3_b = map(LED_br_3_b, 0, 255, 0, LED_br_b);
          if (dir) val = val + 6; // увеличиваем яркость
          else val = val - 6; // уменьшаем
          val = constrain(val, 0, 255);
          if (val >= 255 || val <= 0)
            dir = !dir;
          analogWrite(LED_R, LED_br_3);
          analogWrite(LED_Y, LED_br_3);
          analogWrite(LED_G, LED_br_3);
          analogWrite(LED_B, LED_br_3_b);
        }
        break;
    }
  } else
  {
    analogWrite(LED_S, 0);
    analogWrite(LED_R, 0);
    analogWrite(LED_Y, 0);
    analogWrite(LED_G, 0);
    analogWrite(LED_B, 0);
    eeprom();
  }
}
byte getBrightCRT(byte val) {
  return ((val > 20) ? (((long)val * val + 255) >> 8) : 0);
}
void buttTick() {
  butt.tick();
  if (butt.isDouble()) {
    POWER = !POWER;
  }
  if (POWER && butt.isSingle()) {
    mode++;
    if (mode == 6)mode = 1;
    analogWrite(LED_R, 0);
    analogWrite(LED_Y, 0);
    analogWrite(LED_G, 0);
    analogWrite(LED_B, 0);
  }
  if (POWER && butt.isHolded()) {
    LED_br_direction = ! LED_br_direction;
    speed_2_direction = !speed_2_direction;
    speed_3_direction = !speed_3_direction;
  }
  if (POWER && butt.isStep()) {
    if (LED_br_direction) {
      LED_br = LED_br + LED_step;
      LED_br_b = LED_br_b + LED_step;
    }
    else {
      LED_br = LED_br - LED_step;
      LED_br_b = LED_br_b - LED_step;
    }
    LED_br = constrain(LED_br, 10, 255);
    LED_br_b = constrain(LED_br_b, 10, 150);
  }
  if (POWER && butt.isStep(1)) {
    if (speed_2_direction)
      speed_2 = speed_2 - speed_2_step;
    else
      speed_2 = speed_2 + speed_2_step;
    speed_2 = constrain(speed_2, 100, 2000);
    if (speed_3_direction)
      speed_3 = speed_3 - speed_3_step;
    else
      speed_3 = speed_3 + speed_3_step;
    speed_3 = constrain(speed_3, 1, 100);
  }
  if (POWER && butt.isHold() && !LED_br_direction)
    star = 0;
  else star = 1;
}
void eeprom() {
  EEPROM.update(0, LED_br);
  EEPROM.update(2, LED_br_b);
  EEPROM.update(4, LED_br_3);
  EEPROM.update(6, LED_br_3_b);
  EEPROM.update(10, mode);
  EEPROM.update(11, LED_br_direction);
  EEPROM.update(12, speed_2_direction);
  EEPROM.update(13, speed_2);
  EEPROM.update(14, speed_3_direction);
  EEPROM.update(15, speed_3);
}
