byte mode = 1;
boolean butt_flag = 0;
unsigned long count;
unsigned long dreb;

void setup() {
  Serial.begin(9600);
  pinMode(3, INPUT_PULLUP);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}
void loop() {
  digitalWrite(5, 0);
  digitalWrite(6, 0);
  digitalWrite(10, 0);
  digitalWrite(11, 0);
  if (!digitalRead(3) == 0  && butt_flag == 1 && millis() - dreb >= 200) {
    butt_flag = 0;
    mode++;
    if (mode == 4)mode = 1;
    dreb = millis();
  }
  switch (mode) {
    case 3://постоянно горит
      while (!butt_flag) {
        analogWrite(5, 100);
        analogWrite(6, 100);
        analogWrite(10, 100);
        analogWrite(11, 100);
        if (!digitalRead(3) == 1 && butt_flag == 0 && millis() - dreb >= 200) {
          butt_flag = 1;
          dreb = millis();
        }
      }
      break;
    case 2://быстро мигает по одному светодиоду
      count = millis();
      while (!butt_flag) {
        if (millis() - count <= 500) {
          digitalWrite(5, 1);
          digitalWrite(11, 0);
        }
        if (millis() - count >= 500 && millis() - count <= 1000) {
          digitalWrite(6, 1);
          digitalWrite(5, 0);
        }
        if (millis() - count >= 1000 && millis() - count <= 1500) {
          digitalWrite(6, 0);
          digitalWrite(10, 1);
        }
        if (millis() - count >= 1500 && millis() - count <= 2000) {
          digitalWrite(10, 0);
          digitalWrite(11, 1);
        }
        if (millis() - count >= 2000 && millis() - count <= 2500) count = millis();
        if (!digitalRead(3) == 1 && butt_flag == 0 && millis() - dreb >= 200) {
          butt_flag = 1;
          dreb = millis();
        }
      }
      break;
    case 1://медленно переливается
      byte br1 = 0;
      byte br2 = 0;
      byte br3 = 0;
      byte br4 = 0;
      byte fade1 = 1;
      byte fade2 = 1;
      boolean led1 = 1;
      boolean led2 = 0;
      boolean led3 = 0;
      boolean led4 = 0;
      while (!butt_flag) {
        if (led1) {
          if (br1 == 180) {
            fade1 = -fade1;
            led2 = !led2;
            
          }
          br1 = br1 + fade1;
          if (br1 == 0) {
            led1 = !led1;
            fade1 = -fade1;
          }  
          analogWrite(5, br1);
        }
        if (led2) { 
          if (br2 == 180) {
            led3 = !led3;
            fade2 = -fade2;
          }
                 br2 = br2 + fade2;
          if (br2 == 0) {
            led2 = !led2;
            fade2 = -fade2;
          } 
          analogWrite(6, br2);
        }
        if (led3) {
          if (br1 == 180) {
            led4 = !led4;
            fade1 = -fade1;
          }
                br1 = br1 + fade1;
          if (br1 == 0) {
            led3 = !led3;
            fade1 = -fade1;
          }
    
          analogWrite(10, br1);
        }
        if (led4) {
         
          if (br2 == 180) {
            led1 = !led1;
            fade2 = -fade2;
          }
                  br2 = br2 + fade2;
          if (br2 == 0) {
            led4 = !led4;
            fade2 = -fade2;
          }
   
          analogWrite(11, br2);
        }
        delay(50);
        if (!digitalRead(3) == 1 && butt_flag == 0 && millis() - dreb >= 200) {
          butt_flag = 1;
          dreb = millis();
        }
      }
      break;
      /* case 4://бысто мигает два работают два мигают(пятнашки)
      */
  }

}
