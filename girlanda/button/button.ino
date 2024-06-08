int pin10 = 3;
int pin11 = 5;
boolean power=1;
boolean butt;
boolean butt_time = 0;
unsigned long count;
void setup() {
  pinMode(pin10, INPUT_PULLUP);
  pinMode(pin11, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  butt = !digitalRead(pin10);
  if (butt == 1 && butt_time == 0 && (millis() - count) > 100) {
    count = millis();
    butt_time = 1;
    Serial.print("1 ");
    digitalWrite(pin11, power);
  }
  if (butt == 0 && butt_time == 1) {
    butt_time = 0;
    power=!power;
    Serial.print("0 ");
  }
}
