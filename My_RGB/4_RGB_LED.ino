void RGB_LED() {
  int RGB_speed = analogRead(A5);
  RGB_speed = map(RGB_speed, 0, 1023, 0, 500);
 /* Serial.print(RGB_speed);
  Serial.print("   ");
  Serial.println(analogRead(A5));*/
  if (millis() - RGB_timer > RGB_speed)
  {
    RGB_timer = millis();
    strip.setRGB(R, G, B);
    if (Rkey == 1) {
      R -= RGB_step;
      G += RGB_step;
      if (G >= 255) {
        Rkey = 0;
        Gkey = 1;
      }
    }
    if (Gkey == 1) {
      B += RGB_step;
      G -= RGB_step;
      if (B >= 255) {
        Gkey = 0;
        Bkey = 1;
      }
    }
    if (Bkey == 1) {
      R += RGB_step;
      B -= RGB_step;
      if (R >= 255) {
        Bkey = 0;
        Rkey = 1;
      }
    }
  }
}
