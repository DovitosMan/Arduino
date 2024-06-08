void static_LED () {
  if (mode == 1) {
    strip.setHSV (HUE_1, SAT_1, VOL_1);
    Serial.println(VOL_1);
  }
  if (mode == 2) {
    strip.setHSV (HUE_2, SAT_2, VOL_2);
  }
  if (mode == 3) {
    strip.setHSV (HUE_3, SAT_3, VOL_3);
  }
  /*Serial.print(HUE_1);
  Serial.print(HUE_2);
  Serial.print(HUE_3);
  Serial.println("");*/
}
