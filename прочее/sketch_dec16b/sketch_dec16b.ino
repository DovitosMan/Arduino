int brightness = 0;    // уставливаем начально значение яркости
int fadeAmount = 5;    // шаг приращения/убывания яркости
 
void setup()  {
  // устанваливаем пин 9 в режим выхода
  pinMode(9, OUTPUT);
  Serial.begin(9600);
}
 
void loop()  {
  // устанавливаем значение широты импульса на выходе 9
  // задавая яркость светодиода
  analogWrite(9, brightness);   
  // измением значение в переменной для яркости
  brightness = brightness + fadeAmount;

 
  // при достижение крайних значений для яркости
  // меняем знак переменной шага приращения/убывания яркости
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ;
     Serial.print(brightness);
    delay(10000);
   
    
  }   
  // делаем паузу для достижения плавного наращивания/убывания яркости  
  delay(30);                           
}
