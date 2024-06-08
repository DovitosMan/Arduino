// Подключаем библиотеку FastLED.
#include <FastLED.h>

// Указываем, какое количество пикселей у нашей ленты.
#define LED_COUNT 50

// Указываем, к какому порту подключен вход ленты DIN.
#define LED_PIN 13

// Создаем переменную strip для управления нашей лентой.
CRGB strip[LED_COUNT];

void setup()
{
  // Добавляем ленту.
  FastLED.addLeds<WS2812, LED_PIN, GRB>(strip, LED_COUNT);
}

void loop()
{
  // Включаем все светодиоды.
  for (int i = 0; i < LED_COUNT; i++)
  {
    strip[i] = CRGB::Red; // Красный цвет.
  }
  // Передаем цвета ленте.
  FastLED.show();
  // Ждем 500 мс.
  delay(500);
  // Выключаем все светодиоды.
  for (int i = 0; i < LED_COUNT; i++)
  {
    strip[i] = CRGB::Black; // Черный цвет, т.е. выключено.
  }
  // Передаем цвета ленте.
  FastLED.show();
  // Ждем 500 мс.
  delay(500);
}
