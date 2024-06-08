//Константы
#define WIFI_SSID "tplink_123"
#define WIFI_PASS "17475792"
#define BTN_PIN 14  // пин кнопки
#define MOSFET 16   // пин мосфета
bool KEY=1;

//Библиотеки
#include <ESP8266WiFi.h>
#include <GyverButton.h>
GButton butt1(BTN_PIN);

void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");
  Serial.println(WiFi.localIP());
  // Подключение пинов
  pinMode(MOSFET, OUTPUT);
  // pinMode(2,INPUT); //пин фотоэнкодера
}

void loop() {
  butt1.tick();  // опрос кнопки
  if (butt1.isSingle()) {
    Serial.println("1");
    digitalWrite(MOSFET, KEY);
    KEY=!KEY;
  }
}
