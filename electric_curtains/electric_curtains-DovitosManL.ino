//Библиотеки
#include <ESP8266WiFi.h>
#include <GyverButton.h>

//Константы
#define WIFI_SSID "tplink_123"
#define WIFI_PASS "17475792"

void setup() {
  Serial.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");
  Serial.println(WiFi.localIP());
  
//Подключение пинов
pinMode(D0, OUTPUT); //пин мосфета
//pinMode(2,INPUT); //пин фотоэнкодера
pinMode(D5,INPUT); // пин кнопки
}

void loop() {
  
}
